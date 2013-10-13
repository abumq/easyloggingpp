 // This file is part of Easylogging++ samples
 //
 // Sample to demonstrate using ***_EVERY_N logs
 //
 // Revision 1.1
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);

  for (int i = 1;i < 1000; ++i) {
     LOG_EVERY_N(20, INFO) << "i = " << i;
     LOG_EVERY_N(100, INFO) << "Current position is " << ELPP_COUNTER_POS;
  } 
  return 0;
}
