 //
 // This file is part of Easylogging++ samples
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

const char* getIp(void) {
    return "192.168.1.1";
}

int main(void) {
    
    el::Helpers::installCustomFormatSpecifier(el::CustomFormatSpecifier("%ip_addr", getIp));

    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level %ip_addr : %log");
    LOG(INFO) << "This is test";
    return 0;
}
