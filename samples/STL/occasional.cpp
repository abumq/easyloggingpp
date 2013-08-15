 // This file is part of Easylogging++ samples
 // Sample to demonstrate using ***_EVERY_N logs
 // Revision 1.0
 // @author mkhan3189

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);

  int n = 99;
  float nf = (float)n;

  int n2 = 10;
  float n2f = (float)n2;
  
  for (int i = 1; i < 5099; ++i) {
     LOG_EVERY_N(n, INFO) << "i = " << i <<  "  AND  i / " << n << " = " << ((float)i / nf);
  }
  for (int i = 1;i < 110099; ++i) {
     LOG_EVERY_N(n2, INFO) << "i = " << i <<  "  AND  i / " << n2 << " = " << ((float)i / n2f);
     LOG_EVERY_N(5000, INFO) << "Current position is " << ELPP_COUNTER_POS;
  } 
  return 0;
}
