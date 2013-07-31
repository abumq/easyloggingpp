#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void configureLoggers(void) {
    easyloggingpp::Configurations conf("log.conf");
    easyloggingpp::Loggers::setDefaultConfigurations(conf, true);

    // Register and get pointer of custom logger
    easyloggingpp::Logger* mylogger = easyloggingpp::Loggers::getLogger("mylogger");

    // We set app name so that "%app" has something in format - see log.conf for more info
    mylogger->setApplicationName("My App");
   
    // Get existing logger 'trivial' 
    easyloggingpp::Logger* trivialLogger = easyloggingpp::Loggers::getLogger("trivial");
    trivialLogger->setApplicationName("All apps");

    
}

int main(int argc, char *argv[])
{
    configureLoggers();
    // Using 'trivial' logger
    LOG(INFO) << "This is info log";
    LOG(TRACE) << "This is trace log";
    // Using custom logger 'mylogger'
    CLOG(INFO, "mylogger") << "This is log using my new logger";
}
