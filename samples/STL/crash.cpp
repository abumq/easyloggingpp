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

int main(void) {
    
    Crasher c;
    return 0;
}
