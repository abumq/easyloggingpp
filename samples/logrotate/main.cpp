#include "../../src/easylogging++.h"
#include <stdio.h>
#include <iostream>

INITIALIZE_EASYLOGGINGPP

/*
 * Send SIGHUP to the application and log is
 * reopended
 * 
 * Ex:
 * $ ls -l   logfile.log
 * -rw-r--r--  1 el  staff  200 Dec  8 10:29 logfile.log
 * $ rm logfile.log
 * $ kill -SIGHUP $(pgrep logrotate-sample)
 * $ ls -l   logfile.log
 * -rw-r--r--  1 el  staff  0 Dec  8 10:33 logfile.log
 *
 * */

#define loggerName "rotate-logger"

void configure_logger()
{
    el::Configurations logConf;
    logConf.setToDefault();
    logConf.setGlobally(el::ConfigurationType::ToStandardOutput,
                            "false");
    logConf.setGlobally(el::ConfigurationType::ToFile, "true");
    logConf.setGlobally(el::ConfigurationType::Filename, "logfile.log");

    logConf.set(el::Level::Debug, el::ConfigurationType::Enabled, "true");
    logConf.set(el::Level::Debug,
                el::ConfigurationType::Format,
                "%datetime %level %msg");
    el::Logger* logger = el::Loggers::getLogger(loggerName);
    el::Loggers::reconfigureLogger(logger, logConf);

}

void handler_hup(int signal)
{
    LOG(INFO) << "SIGHUP received - reconfigure logger";
    el::Logger* logger = el::Loggers::getLogger(loggerName);
    logger->reconfigure();
}

void handler_usr1(int signal)
{
    LOG(INFO) << "SIGUSR1 received - unregister logger";
    el::Loggers::unregisterLogger(loggerName);
}

int main()
{
    std::signal(SIGHUP, handler_hup);
    std::signal(SIGUSR1, handler_usr1);

    LOG(INFO) << "Configuring logger";
    configure_logger();

    char c;
    c = getchar();
    CLOG(DEBUG, loggerName) << "My logger";

    while ((c = getchar()) != 'q')
    {
        CLOG(DEBUG, loggerName) << "My logger";
    }

    std::cout << "Unregistred my logger\n";

    return 0;
}

