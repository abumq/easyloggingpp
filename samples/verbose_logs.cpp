/*
 * This file is part of EasyLogging++ samples
 * Demonstration of verbose logging
 * @author mkhan3189
 */
#include "../easylogging++.h"
int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv)
  
  VERBOSE(1, "This will be printed when program is started using argument --v=1");
  VERBOSE(2, "This will be printed when program is started using argument --v=2");
   
  return 0;
}
