/*
 * This file is part of EasyLogging++ samples
 * Demonstration of verbose logging
 * @author mkhan3189
 */
#include "../easylogging++.h"
int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);
  INFO("This is demo for verbose logs");
  VERBOSE(1, "This will be printed when program is started using argument --v=1");
  VERBOSE(2, "This will be printed when program is started using argument --v=2");
  VERBOSE(3, "This will be printed when program is started using argument --v=3");
  VERBOSE(1, "This will be printed when program is started using argument --v=1");
  VERBOSE_IF(true, 1, "Always verbose for level 1");   
  return 0;
}
