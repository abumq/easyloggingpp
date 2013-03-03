/**
 * This file is part of EasyLogging++ samples
 * Demonstration of happy valgrind
 * To see demo, run 'valgrind ./bin/valgrind_happy.cpp.bin' 
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
  LDEBUG << "This is start of logging!";
  for (int i = 1; i <= 10; i++) {
    LINFO << "This is a test number " << i;
  }
  _END_EASYLOGGINGPP // To make valgrind happy
}
