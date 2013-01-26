/**
 * Demonstrate helper function(s) in EasyLogging++
 * @author mkhan3189
 */

#include "../easylogging++.h"
#include <string>
#include <iostream>

int main(void) {
  INFO("Logging first line if _CLEAN_LOGS is defined");
  std::string allLogs = ::easyloggingpp::helper::readLog();
  std::cout << "\n\n";
  std::cout << "Following lines are fetched by ::easyloggingpp::helper::readLog()\n";
  std::cout << "-----------------------------------------------------------------\n";
  std::cout << allLogs;
  _END_EASYLOGGINGPP
  return 0;
}
