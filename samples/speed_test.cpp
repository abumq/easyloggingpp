/**
 * This file is part of EasyLogging++ samples
 * Demonstration of how fast can EasyLogging++ log
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

MAIN(int argc, char** argv)
  for (int i = 1; i <= 10000; ++i) {
    LINFO << "This is a info test";
  }
END_MAIN(0)
