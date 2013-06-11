#include "hashmap.h"
#include <iostream>
#include "../../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

SUB(test,(HashMap<std::string>& h))
    LINFO << h.get(5288);
END_SUB

int main() {
    HashMap<std::string> h;
    for (int i = 0; i < 10000; ++i)
       h.put(i, new std::string("test"));
    test(h);
    cout << "...";

    LINFO << SuperFastHash("test", 10);
    return 0;
}
