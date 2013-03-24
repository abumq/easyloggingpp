/**
 * This file is part of EasyLogging++ samples
 * Demonstration of container logging using EasyLogging++
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include <vector>
#include <list>
#include <map>
#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    std::vector<std::string> v;
    v.push_back("string 1");
    v.push_back("string 2");
    LINFO << "Now I will print std::vector<std::string> and values are --> " << v << " <-- This is end of log";

    std::vector<bool> boolVec_;
    boolVec_.push_back(true);
    boolVec_.push_back(false);
    boolVec_.push_back(true);
    boolVec_.push_back(true);
    boolVec_.push_back(true);
    boolVec_.push_back(false);
    SWARNING << "Security warning log for bool container " << boolVec_;


    std::list<std::string> list_;
    list_.push_back("String 1");
    list_.push_back("String 2");
    LINFO << "This will print std::list of std::string " << list_;


    std::map<int, std::string> map_;
    map_.insert (std::pair<int, std::string>(1, "one"));
    map_.insert (std::pair<int, std::string>(2, "two"));
    LINFO << "Map: " << map_;

    return 0; 
}
