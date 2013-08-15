#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    
    bool v = true;
    LOG(INFO) << std::boolalpha << v;
    LOG(INFO) << std::noboolalpha << v;

    return 0;
}
