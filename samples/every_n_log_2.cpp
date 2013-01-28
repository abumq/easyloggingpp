/** 
 * This file is part of EasyLogging++ samples
 * Sample to demonstrate using ***_EVERY_N logs (part 2)
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {

  _START_EASYLOGGINGPP(argc, argv); //register arguments for verbose logs

  int n = 5;

  int n2 = 2;
  
  for (int i = 0; i <= 100; i++) {
      INFO_EVERY_N(n, "This will be printed every " << n << " iteration multiple, this is iteration " << i);

      INFO_EVERY_N(n2, "iter = " << i);

      VERBOSE_EVERY_N(n2, 1, "This is verbose level 1 log for iteration " << i);
   }
 
   _END_EASYLOGGINGPP
   return 0;
}
