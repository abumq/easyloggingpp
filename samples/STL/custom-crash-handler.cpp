 //
 // This file is part of Easylogging++ samples
 // Custom crash handler sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void myCrashHandler(int sig) {
    LOG(ERROR) << "Woops! Crashed!";
    // FOLLOWING LINE IS OPTIONAL
    el::Helpers::logCrashReason(sig, true);
    // FOLLOWING LINE IS ABSOLUTELY NEEDED AT THE END IN ORDER TO ABORT APPLICATION
    el::Helpers::crashAbort(sig);
}

int main(void) {

    el::Helpers::setCrashHandler(myCrashHandler);
    
    LOG(INFO) << "My crash handler!";

    int* i;
    *i = 0; // Crash!

    return 0;
}
