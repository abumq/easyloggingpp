#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    
    bool v = true;
    LINFO << std::boolalpha << v;
    LINFO << std::noboolalpha << v;

    return 0;
}
