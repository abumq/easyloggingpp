/**
 * This file is part of EasyLogging++ samples
 * Demonstration of how fast can EasyLogging++ log
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

SUB(write, (void))

  LDEBUG << "This is start of logging!";
  for (int i = 1; i <= 1000; i++) {
    LINFO << "This is a test number " << i;
  }
  LINFO << "Now EasyLogging++ is logging DEBUG logs that are stored in logs/myeasylog.log by default";
  for (int i = 1; i <= 10; i++) {
    LDEBUG << "Some more logs [" << i << "]";
    LINFO_EVERY_N(2) << "Every second iter [" << i << "]";
  }
  LDEBUG << "This is end of logging!";

END_SUB

int main(void) {
  easyloggingpp::Configurations c;
  c.setToDefault();
  c.set(easyloggingpp::Level::All, easyloggingpp::ConfigurationType::Format, "%datetime %level [%logger] (%thread) %log");
  c.set(easyloggingpp::Level::All, easyloggingpp::ConfigurationType::PerformanceTracking, "true");
  easyloggingpp::Loggers::reconfigureAllLoggers(c);
  write();
  return 0;
}
