#include <mylib.hpp>
#include "easylogging++.h"

_SHARE_EASYLOGGINGPP(MyLib::getEasyloggingStorage())

int main(int argc, char** argv) {
    {
        // Braces only for scoping purpose - remove and compare results
        MyLib lib(argc, argv);
        lib.event(1);
    }
    // See read me
    CLOG(INFO, "mylib") << "A logger initialized in shared storage";
    CLOG(INFO, "default") << "Default, configuration from shared storage";
    return 0;
}
