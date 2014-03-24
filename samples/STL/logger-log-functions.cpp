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
    defaultLogger->info("My first ultimate log message");
    defaultLogger->debug("My debug from file and line", __FILE__, __LINE__, _ELPP_FUNC);
    defaultLogger->error("My error message");
    defaultLogger->verbose(2, "My verbose message available when --v=2 or more passed in args");

    return 0;
}
