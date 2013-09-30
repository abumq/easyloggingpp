 //
 // This file is part of Easylogging++ samples
 // Crash sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class Crasher {
public:
    Crasher(void) { 
        str = nullptr; 
        call3(); 
    }

    void call1(void) {
        LOG(INFO) << "Bye bye!";
        str->clear(); // Crash!
    }

    void call2(void) {
        LOG(INFO) << "Calling call1()";
        call1();
    }

    void call3(void) {
        LOG(INFO) << "Calling call2()";
        call2();
    }
private:
    std::string* str;
};

int main(int argc, char** argv) {
    // If argv[1] == "y" means PREVENT CRASH ABORTION = YES
    if (argc > 1 && argv[1][0] == 'y') {
        el::Helpers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
        LOG(FATAL) << "Before we crash we try to log using FATAL log and make sure app did not crash because we added flag DisableApplicationAbortOnFatalLog";
    }
    Crasher c;
    return 0;
}
