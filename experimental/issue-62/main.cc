//#include "fastmap.h"
#include <iostream>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;
using namespace easyloggingpp;
using namespace easyloggingpp::internal;

int main() {

    ConfigurationMap<bool> h;
    unsigned int i = 0;
    do {
        h.set(i, i);
        i = i << 1;
        if (i == 0) ++i;
    } while (i <= easyloggingpp::Level::kMaxValid);

    LINFO << h.get(0);
    LINFO << h.get(4);

    return 0;
}
