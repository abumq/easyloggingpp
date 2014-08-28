
#include "async-logging.h"
#include "easylogging++.h"
#include "mymath.h"

_INITIALIZE_EASYLOGGINGPP
AsyncLogQueue logQueue;
AsyncDispatchWorker asyncDispatchWorker;

TIMED_SCOPE(benchmark, "benchmark");

int main(int argc, char *argv[])
{
    AsyncLogDispatchCallback::removeDefaultAndInstall();
    // _INIT_SYSLOG("my_proc", LOG_PID | LOG_CONS | LOG_PERROR, LOG_USER);
    Loggers::reconfigureAllLoggers(ConfigurationType::ToStandardOutput, "false");

    std::cout << "Starting program" << std::endl;
    int MAX_LOOP = 1000000;
    for (int i = 0; i <= MAX_LOOP; ++i) {
        LOG(INFO) << "Log message " << i;
    }
    int result = MyMath::sum(1, 2);
    result = MyMath::sum(1, 3);

    std::cout << "Finished program - now cleaning..." << std::endl;

    // SYSLOG(INFO) << "This is syslog - read it from /var/log/syslog";

    return asyncDispatchWorker.clean();
}
