/**
 * Demonstrate helper function(s) in EasyLogging++
 *
 * Revision 1.1
 * @author mkhan3189
 */

#include "easylogging++.h"
#include <string>
#include <iostream>

_INITIALIZE_EASYLOGGINGPP

int main(void) {
  LINFO << "Logging first line if _ALWAYS_CLEAN_LOGS is defined";
  LINFO << "Logs should have already been cleaned up if _ALWAYS_CLEAN_LOGS was defined while compiling";
  LINFO << "If you see just four lines, please open compile.sh and comment out the line with '-D _ALWAYS_CLEAN_LOGS'";
  LINFO << "This will keep appending logs to log file and you can re-use 'helper_functions.cpp.bin' to read all the logs";
  std::string allLogs = ::easyloggingpp::helper::MyEasyLog::readLog();
  std::cout << "\n\n";
  std::cout << "Following lines are fetched by ::easyloggingpp::helper::readLog()\n";
  std::cout << "-----------------------------------------------------------------\n";
  std::cout << allLogs;
  return 0;
}
