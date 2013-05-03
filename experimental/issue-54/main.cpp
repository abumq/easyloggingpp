#define _ELPP_STL_LOGGING
#define _ELPP_STRICT_ROLLOUT

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;
int main() {

    easyloggingpp::Configurations defaultConf;

    defaultConf.setToDefault();

    defaultConf.set(easyloggingpp::Level::ELPP_ALL, easyloggingpp::ConfigurationType::ELPP_ToStandardOutput, "false");

    defaultConf.set(easyloggingpp::Level::ELPP_ALL, easyloggingpp::ConfigurationType::ELPP_RollOutSize, "503065"); // Causes issue - beta version

    easyloggingpp::Loggers::reconfigureAllLoggers(defaultConf);

    easyloggingpp::Loggers::setFilename("issue54.log");

    for (int i = 0; i < 1000; i++)
    {
        LINFO << "Log using LINFO to file";
        BINFO << "Log using BINFO to file";
        LDEBUG << "Log using LDEBUG to file";
        LTRACE << "Log using LTRACE to file";
    }
    // If we remove loop below, it works alright, so I am guessing this issue only occures
    // when roll out is performed
    for (int i = 0; i < 1000; i++)
    {
        LINFO << "Log using LINFO to file";
        BINFO << "Log using BINFO to file";
        LDEBUG << "Log using LDEBUG to file";
        LTRACE << "Log using LTRACE to file";
    }
return 0;
}

