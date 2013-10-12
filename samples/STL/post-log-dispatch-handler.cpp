 //
 // This file is part of Easylogging++ samples
 // Post log dispatch handler
 //
 // Revision 1.0
 // @author mkhan3189
 //

#define _ELPP_HANDLE_POST_LOG_DISPATCH
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void handler(const el::LogMessage*) {
    // NOTE:
    // SHOULD NOT LOG ANYTHING HERE! WE DON'T LIKE RECURSIVE LOG-DISPATCHES!

    // BUT WE CAN USE std::cout :)
    std::cout << "Log dispatch has been handled";
}

int main(void) {
   
    el::Helpers::installPostLogDispatchHandler(handler);
 
    LOG(INFO) << "My log message";

    return 0;
}
