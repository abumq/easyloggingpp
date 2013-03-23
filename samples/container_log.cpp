#include <vector>
#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    std::vector<std::string> v = { "string 1", "string 2" };
    LINFO << "Now I will print std::vector<std::string> and values are --> " << v << " <-- This is end of log";
    return 0; 
}
