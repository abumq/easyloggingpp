 //
 // This file is part of Easylogging++ samples
 // Simple custom log builder
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

/// @brief Not a very fast log builder but good enough for sample
class MyLogBuilder : public el::api::LogBuilder {
public:
    std::string build(const el::LogMessage* logMessage, bool appendNewLine) const {
        std::stringstream str;
        str << logMessage->message();
        if (appendNewLine) str << "\n";
        return str.str().c_str();
    }
};

int main(void) {
    el::Loggers::getLogger("default")->setLogBuilder(el::api::LogBuilderPtr(new MyLogBuilder()));
    LOG(INFO) << "My first ultimate log message";

    return 0;
}
