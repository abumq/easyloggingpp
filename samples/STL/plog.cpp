 //
 // This file is part of Easylogging++ samples
 // PLOG etc
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    std::fstream f("a file that does not exist", std::ifstream::in);    
    PLOG(INFO) << "A message with plog";
    PLOG_IF(true, INFO) << "A message with plog";
    PLOG_IF(false, INFO) << "A message with plog";
    PCHECK(false) << "This is not good";
    PCHECK(true) << "This is good";
    return 0;
}
