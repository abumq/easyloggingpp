/**
 * This file is part of EasyLogging++ samples
 * Demonstration of how fast can EasyLogging++ log
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void write(void) {
  TIMED_FUNC(writeTimer);
  LOG(DEBUG) << "This is start of logging!";
  for (int i = 1; i <= 100; i++) {
    LOG(INFO) << "This is a test number " << i;
  }
  LOG(INFO) << "Now EasyLogging++ is logging DEBUG logs that are stored in logs/myeasylog.log by default";
  for (int i = 1; i <= 10000; i++) {
    LOG(DEBUG) << "Some more logs [" << i << "]";
    LOG_EVERY_N(2, INFO) << "Every second iter [" << i << "]";
  }
  LOG(DEBUG) << "This is end of logging!";
}

int main(void) {
  el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
  write();
  return 0;
}
