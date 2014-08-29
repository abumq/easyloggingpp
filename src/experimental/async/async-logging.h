// THIS HAS A LOT OF ISSUES HENCE LEAVING IT AS EXPERIMENTAL AT THIS STAGE
#ifndef ASYNC_LOGGING_H
#define ASYNC_LOGGING_H

#define _ELPP_THREAD_SAFE // Needed?

#include <pthread.h>
#include <queue>
#include <condition_variable>

#include "easylogging++.h"
#include <unistd.h>

using namespace el;

class AsyncLogItem {
public:
    explicit AsyncLogItem(const LogMessage& logMessage, const LogDispatchData& data, const base::type::string_t& logLine)
        : m_logMessage(logMessage), m_dispatchData(data), m_logLine(logLine) {}

    virtual ~AsyncLogItem() {}

    inline LogMessage* logMessage(void) {
        return &m_logMessage;
    }

    inline LogDispatchData* data(void) {
        return &m_dispatchData;
    }

    inline base::type::string_t* logLine(void) {
        return &m_logLine;
    }
private:
    LogMessage m_logMessage;
    LogDispatchData m_dispatchData;
    base::type::string_t m_logLine; // We need log line at time of contructing message otherwise time of log will be messed up
};
class AsyncLogQueue : base::threading::ThreadSafe {
public:
    inline AsyncLogItem next(void) {
        base::threading::ScopedLock scopedLock(lock());
        AsyncLogItem result = m_queue.front();
        m_queue.pop();
        return result;
    }

    inline void push(const AsyncLogItem& item) {
        m_queue.push(item);
    }

    inline void push(AsyncLogItem&& item) {
        m_queue.push(item);
    }

    inline bool empty(void) const {
        return m_queue.empty();
    }
private:
    std::queue<AsyncLogItem> m_queue;
};
extern _ELPP_EXPORT AsyncLogQueue logQueue;

class AsyncDispatchWorker : base::threading::ThreadSafe {
public:
    AsyncDispatchWorker() {
        pthread_create(&m_thread, NULL, &AsyncDispatchWorker::runner, this);
        //Loggers::addFlag(LoggingFlag::ImmediateFlush);
        //pthread_join(m_thread, 0);
    }

    virtual ~AsyncDispatchWorker() {
    }

    inline int clean() {
        std::mutex m;
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{ return !logQueue.empty(); });
        emptyQueue();
        lk.unlock();
        cv.notify_one();
        return logQueue.empty() ? 0 : 1;
    }

    inline void emptyQueue() {
        while (!logQueue.empty()) {
            AsyncLogItem data = logQueue.next();
            handle(&data);
            usleep(100);
        }
    }

    void handle(AsyncLogItem* logItem) {
        LogDispatchData* data = logItem->data();
        LogMessage* logMessage = logItem->logMessage();
        Logger* logger = logMessage->logger();
        base::TypedConfigurations* conf = logger->typedConfigurations();
        base::type::string_t* logLine = logItem->logLine();
        if (data->dispatchAction() == base::DispatchAction::NormalLog) {
            if (conf->toFile(logMessage->level())) {
                base::type::fstream_t* fs = conf->fileStream(logMessage->level());
                if (fs != nullptr) {
                    fs->write(logLine->c_str(), logLine->size());
                    if (fs->fail()) {
                        ELPP_INTERNAL_ERROR("Unable to write log to file ["
                            << conf->filename(logMessage->level()) << "].\n"
                                << "Few possible reasons (could be something else):\n" << "      * Permission denied\n"
                                << "      * Disk full\n" << "      * Disk is not writable", true);
                    } else {
                        if (ELPP->hasFlag(LoggingFlag::ImmediateFlush) || (logger->isFlushNeeded(logMessage->level()))) {
                            logger->flush(logMessage->level(), fs);
                        }
                    }
                } else {
                    ELPP_INTERNAL_ERROR("Log file for [" << LevelHelper::convertToString(logMessage->level()) << "] "
                        << "has not been configured but [TO_FILE] is configured to TRUE. [Logger ID: " << logger->id() << "]", false);
                }
            }
        }
#if defined(_ELPP_SYSLOG)
        else if (data->dispatchAction() == base::DispatchAction::SysLog) {
            // Determine syslog priority
            int sysLogPriority = 0;
            if (logMessage->level() == Level::Fatal)
                sysLogPriority = LOG_EMERG;
            else if (logMessage->level() == Level::Error)
                sysLogPriority = LOG_ERR;
            else if (logMessage->level() == Level::Warning)
                sysLogPriority = LOG_WARNING;
            else if (logMessage->level() == Level::Info)
                sysLogPriority = LOG_INFO;
            else if (logMessage->level() == Level::Debug)
                sysLogPriority = LOG_DEBUG;
            else
                sysLogPriority = LOG_NOTICE;
#   if defined(_ELPP_UNICODE)
            char* line = base::utils::Str::wcharPtrToCharPtr(logLine->c_str());
            syslog(sysLogPriority, "%s", line);
            free(line);
#   else
            syslog(sysLogPriority, "%s", logLine->c_str());
#   endif
        }
#endif  // defined(_ELPP_SYSLOG)
    }

    void* run() {
        while(1) {
            emptyQueue();
            usleep(500);
        }
        return NULL;
    }

    static void *runner(void *context) {
        return ((AsyncDispatchWorker *)context)->run();
    }
private:
    pthread_t m_thread;
    std::condition_variable cv;
};

class AsyncLogDispatchCallback : public LogDispatchCallback {
public:
    static void removeDefaultAndInstall(void) {
        Helpers::installLogDispatchCallback<AsyncLogDispatchCallback>(std::string("AsyncLogDispatchCallback"));
        Helpers::uninstallLogDispatchCallback<base::DefaultLogDispatchCallback>(std::string("DefaultLogDispatchCallback"));
    }
protected:
    void handle(const LogDispatchData* data) {
        base::type::string_t logLine = data->logMessage()->logger()->logBuilder()->build(data->logMessage(), data->dispatchAction() == base::DispatchAction::NormalLog);
        if (data->dispatchAction() == base::DispatchAction::NormalLog && data->logMessage()->logger()->typedConfigurations()->toStandardOutput(data->logMessage()->level())) {
            if (ELPP->hasFlag(LoggingFlag::ColoredTerminalOutput))
                data->logMessage()->logger()->logBuilder()->convertToColoredOutput(&logLine, data->logMessage()->level());
            ELPP_COUT << ELPP_COUT_LINE(logLine);
        }
        // Save resources and only queue if we want to write to file otherwise just ignore handler
        if (data->logMessage()->logger()->typedConfigurations()->toFile(data->logMessage()->level())) {
            logQueue.push(std::move(AsyncLogItem(*(data->logMessage()), *data, logLine)));
        }
    }
};

#endif // ASYNC_LOGGING_H
