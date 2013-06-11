#include "fastmap.h"
#include <iostream>
#include "../../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;


int main() {

    FastMap<bool> h;
    for (int i = 0; i < 8; ++i) {
        h.put(i, i);
    }

    LINFO << h.get(0);
    LINFO << h.get(4);

    return 0;
}
