/**
 * This file is part of EasyLogging++ samples
 * Demonstration of how fast can EasyLogging++ log
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

FUNC(int, main, (void))
  STATUS("PROGRAM STARTED");
  for (long i = 1; i <= 10000000; i++) {
    INFO("This is a info test");
  }
  STATUS("PROGRAM ENDED");
END_FUNC

