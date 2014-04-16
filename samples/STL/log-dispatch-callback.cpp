 //
 // This file is part of Easylogging++ samples
 // Very basic sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class MyHandler : public el::LogDispatchCallback {
public:
    void handle(const el::LogMessage* msg) const;
};

void MyHandler::handle(const el::LogMessage* msg) const {
    std::cout << "Handled by my handlers " << msg->message() << std::endl;
}

int main(void) {
    
    el::Helpers::installLogDispatchCallback<MyHandler>("MyHandler");

    LOG(INFO) << "My first ultimate log message";

    return 0;
}
