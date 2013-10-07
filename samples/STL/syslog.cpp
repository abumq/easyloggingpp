 //
 // This file is part of Easylogging++ samples
 // Syslog sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
   
    _INIT_SYSLOG("syslog_sample", LOG_PID | LOG_CONS | LOG_PERROR, LOG_USER);
 
    SYSLOG(INFO) << "My first easylogging++ syslog message";

    return 0;
}
