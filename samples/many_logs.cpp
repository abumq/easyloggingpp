/**
 * This file is part of EasyLogging++ samples
 * Demonstration of how fast can EasyLogging++ log
 * @author mkhan3189
 */
#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
  STATUS("PROGRAM STARTED");
  DEBUG("This is start of logging!");
  for (int i = 1; i <= 10; i++) {
    INFO("This is a test number " << i);
  }
  STATUS("Completed!");
  INFO("Now EasyLogging++ is logging DEBUG logs that are stored in logs/myeasylog.log by default");
  for (int i = 1; i <= 10; i++) {
    DEBUG("Some more logs [" << i << "]");
  }
  DEBUG("This is end of logging!");
  STATUS("PROGRAM ENDED");
  _END_EASYLOGGINGPP
}
