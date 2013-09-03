 //
 // This file is part of Easylogging++ samples
 //
 // Revision 1.0
 // @author mkhan3189
 //

#define _ELPP_PREVENT_FATAL_ABORT
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    
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
    return 0;
}
