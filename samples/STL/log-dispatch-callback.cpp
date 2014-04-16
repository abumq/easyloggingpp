 //
 // This file is part of Easylogging++ samples
 // Demonstrates how to use log dispatch callback
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class MyHandler : public el::LogDispatchCallback {
public:
    void handle(const el::LogMessage* msg) {
        std::cout << "Test MyHandler" << std::endl;
    }
};

class MyHtmlHandler : public el::LogDispatchCallback {
public:
    void handle(const el::LogMessage* msg) {
        std::cout << "Test MyHtmlHandler" << std::endl;
    }
};

int main(void) {
    
    el::Helpers::installLogDispatchCallback<MyHandler>("MyHandler");
    el::Helpers::installLogDispatchCallback<MyHtmlHandler>("MyHtmlHandler");

    LOG(INFO) << "My first log message";
    LOG(INFO) << "My second log message";

    return 0;
}
