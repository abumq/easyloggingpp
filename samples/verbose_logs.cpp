/**
 * This file is part of EasyLogging++ samples
 * Demonstration of verbose logging
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);
  INFO("This is demo for verbose logs");
  VERBOSE(1, "This will be printed when program is started using argument --v=1");
  VERBOSE(2, "This will be printed when program is started using argument --v=2");
  VERBOSE(3, "This will be printed when program is started using argument --v=3");
  VERBOSE(1, "This will be printed when program is started using argument --v=1");
  VERBOSE_IF(true, 1, "Always verbose for level 1");
  _END_EASYLOGGINGPP
  return 0;
}
