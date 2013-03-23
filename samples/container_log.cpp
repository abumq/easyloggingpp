/**
 * This file is part of EasyLogging++ samples
 * Demonstration of container logging using EasyLogging++
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include <vector>
#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    std::vector<std::string> v = { "string 1", "string 2" };
    LINFO << "Now I will print std::vector<std::string> and values are --> " << v << " <-- This is end of log";

    std::vector<int> intVec_ = { 1, 2, 3, 4, 5 };
    BINFO << "Business info log for int container " << intVec_;

    std::vector<bool> boolVec_ = { true, false, true, true, true, false };
    SWARNING << "Security warning log for bool container " << boolVec_;
    
    return 0; 
}
