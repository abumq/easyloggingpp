 //
 // This file is part of Easylogging++ samples
 // Very basic sample for Logger::info etc
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {

    _START_EASYLOGGINGPP(argc, argv);

    el::Logger* defaultLogger = el::Loggers::getLogger("default");

    //defaultLogger->log(el::Level::Info, "My first ultimate log message");

    std::vector<int> i;
    i.push_back(1);
    i.push_back(2);
    defaultLogger->log(el::Level::Info, "My first ultimate log message % % %", 123, 222, i);
    //defaultLogger->log(el::Level::Debug, "My first ultimate log message % % %", 123, 222, i);
    //defaultLogger->info("My first ultimate log message % % %", 123, 222, i);

    return 0;
}
