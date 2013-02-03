/**
 * This file is part of EasyLogging++ samples
 * Demonstration of happy valgrind
 * To see demo, run 'valgrind ./bin/valgrind_happy.cpp.bin' 
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../../easylogging++-full.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
  STATUS("PROGRAM STARTED");
  DEBUG("This is start of logging!");
  for (int i = 1; i <= 10; i++) {
    INFO("This is a test number " << i);
  }
  STATUS("Completed!");
  STATUS("PROGRAM ENDED");
  _END_EASYLOGGINGPP // To make valgrind happy
}
