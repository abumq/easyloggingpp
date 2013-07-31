/**
 * This file is part of EasyLogging++ samples
 * Demonstration of verbose logging
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

MAIN(int argc, char* argv[])
  _START_EASYLOGGINGPP(argc, argv);
  LINFO << "This is demo for verbose logs";
  LVERBOSE(1) << "This will be printed when program is started using argument --v=1";
  LVERBOSE(2) << "This will be printed when program is started using argument --v=2";
  BVERBOSE(3) << "This will be printed when program is started using argument --v=3";
  LVERBOSE(1) << "This will be printed when program is started using argument --v=1";
  LVERBOSE_IF(true, 1) << "Always verbose for level 1";

  LVERBOSE_EVERY_N(1, 3) << "Verbose every N";
  RETURN(0);
END_MAIN(0)
