 //
 // This file is part of Easylogging++ samples
 // Helpers sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
    _START_EASYLOGGINGPP(argc, argv);
    el::Loggers::configureFromArg("--logging");
    LOG(INFO) << "My first ultimate log message";

    return 0;
}
