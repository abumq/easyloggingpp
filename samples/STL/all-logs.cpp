 //
 // This file is part of Easylogging++ samples
 //
 // Writes all logs (incl. debug version of logs i.e, DLOG etc) using default logger
 // We add logging flag `DisableApplicationAbortOnFatalLog` that prevents application abort on FATAL log
 //
 // Revision 1.1
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
    _START_EASYLOGGINGPP(argc, argv);
    el::Helpers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
    el::Helpers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    
    LOG(INFO);
    LOG(DEBUG);
    LOG(WARNING);
    LOG(ERROR);
    LOG(TRACE);
    VLOG(1);
    LOG(FATAL);

    DLOG(INFO);
    DLOG(DEBUG);
    DLOG(WARNING);
    DLOG(ERROR);
    DLOG(TRACE);
    DVLOG(1);
    DLOG(FATAL);
    el::Helpers::removeFlag(el::LoggingFlag::ColoredTerminalOutput);
    
    LOG_IF(true, INFO);
    LOG_IF(true, DEBUG);
    LOG_IF(true, WARNING);
    LOG_IF(true, ERROR);
    LOG_IF(true, TRACE);
    VLOG_IF(true, 1);
    LOG_IF(true, FATAL);

    LOG_EVERY_N(1, INFO);
    LOG_EVERY_N(1, DEBUG);
    LOG_EVERY_N(1, WARNING);
    LOG_EVERY_N(1, ERROR);
    LOG_EVERY_N(1, TRACE);
    VLOG_EVERY_N(1, 1);
    LOG_EVERY_N(1, FATAL);

    CHECK(1 == 1);
    CCHECK(1 == 1, "default");
    return 0;
}
