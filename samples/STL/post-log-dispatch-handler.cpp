 //
 // This file is part of Easylogging++ samples
 //
 // Possible usage of post log dispatch handler
 //
 // Revision 1.0
 // @author mkhan3189
 //

#define _ELPP_HANDLE_POST_LOG_DISPATCH
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

static std::vector<std::string> log_messages_dispatched;

void handler(const el::LogMessage* msg) {
    // NOTE:
    // SHOULD NOT LOG ANYTHING HERE! WE DON'T LIKE RECURSIVE LOG-DISPATCHES!

    // BUT WE CAN USE std::cout :)
    log_messages_dispatched.push_back(msg->message());

    // Also note, this msg pointer will become unavailable as soon as this handler is done.
    // so there will be no point of having a vector like std::vector<el::LogMessage*> and store these pointers
}

int main(void) {
   
    el::Helpers::installPostLogDispatchHandler(handler);
 
    LOG(INFO) << "This is my first message";
    LOG(INFO) << "I am second in the line";

    std::cout << std::endl; // Just enter an empty line to make it more readable

    LOG(INFO) << "Following log messages have been dispatched so far! \n\t" << log_messages_dispatched;
    return 0;
}
