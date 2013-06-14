//#include "fastmap.h"
#include <iostream>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;
using namespace easyloggingpp;
using namespace easyloggingpp::internal;

int main() {

    ConfigurationMap<bool> h;

    ELPP_FOR_EACH_LEVEL(i,0,
                        h.set(i, i);
                       );

    LINFO << h.get(0);
    LINFO << h.get(4);

    return 0;
}
