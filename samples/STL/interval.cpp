/** 
 * This file is part of EasyLogging++ samples
 * Sample to demonstrate using ***_EVERY_N logs
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

MAIN(int argc, char** argv)
  int n = 99;
  float nf = (float)n;

  int n2 = 10;
  float n2f = (float)n2;
  
  for (int i = 1; i < 5099; ++i) {
     LINFO_EVERY_N(n) << "i = " << i <<  "  AND  i / " << n << " = " << ((float)i / nf);
  }
  for (int i = 1;i < 110099; ++i) {
     LINFO_EVERY_N(n2) << "i = " << i <<  "  AND  i / " << n2 << " = " << ((float)i / n2f);
     LINFO_EVERY_N(5000) << "Current position is " << _ELPP_COUNTER_POSITION;
  } 

END_MAIN(0)
