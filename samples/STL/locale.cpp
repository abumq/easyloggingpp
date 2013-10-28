 //
 // This file is part of Easylogging++ samples
 //
 // Demonstration on how locale gives output
 //
 // Revision 1.1
 // @author mkhan3189
 //

#define _ELPP_UNICODE
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, const char** argv) {
    _START_EASYLOGGINGPP(argc, argv);

    LOG(INFO) << L"世界，你好";
    return 0;
}
