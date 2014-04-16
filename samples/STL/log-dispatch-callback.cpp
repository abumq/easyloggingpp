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
        std::cout << "Handled by my handlers " << msg->message() << std::endl;
    }
};

class MyHtmlHandler : public el::LogDispatchCallback {
public:
    MyHtmlHandler() { setCallbackCount(1); }
    void handle(const el::LogMessage* msg) {
        // NEVER EVER DO THIS!
        // 
        //LOG(INFO) << "Other msg " << msg->message();
    }
};

int main(void) {
    
    el::Helpers::installLogDispatchCallback<MyHandler>("MyHandler");
    el::Helpers::installLogDispatchCallback<MyHtmlHandler>("MyHtmlHandler");

    LOG(INFO) << "My first ultimate log message";

    return 0;
}
