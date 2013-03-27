/*
 * Contain unit tests for EasyLogging++
 *
 * Revision: 1.2
 * @author mkhan3189
 */

#include <cstring>
#include <iostream>
#include "easylogging++.h"
#include "utils/stringutils.h"
#include "all-logs.h"
#include "legacy-logs.h"

_INITIALIZE_EASYLOGGINGPP

using namespace easyloggingpp::internal;
using namespace easyloggingpp::internal::helper;
using namespace easyloggingpp::configurations;
using namespace easyloggingpp::helper;

// Do not use cassert as we want custom
// message and return on failure
#define localAssert(assertion) \
  if (!(assertion)) { \
    std::cout << "TEST FAILED: " << #assertion << " [Line: " << __LINE__ << "]"; \
    return 1; \
  } \

#define val(x) \
  std::cout << "Value of " << #x << ": " << x << std::endl;

int main(int argc, char** argv) {
  // Following is optional to set app arguments that are used for verbose
  // logging
  _START_EASYLOGGINGPP(argc, argv);

  localAssert(_QUALIFIED_LOGGER.registeredSeverityLevels()->empty() == false);
  localAssert(_QUALIFIED_LOGGER.initialized() == true);

  LINFO << "Write unique log...";
  
  #ifndef _DISABLE_INFO_LOGS
    // Make sure we have written correct log
    localAssert(utils::ilike(easyloggingpp::helper::MyEasyLog::readLog(), "%Write unique log...%") == true);
    // Make sure username and hostname is fetch correctly. The correct username
    // and host name is passed into test via bash script
    localAssert(strcmp(_QUALIFIED_LOGGER.kUser_.c_str(), argv[1]) == 0);
    localAssert(strcmp(_QUALIFIED_LOGGER.kHost_.c_str(), argv[2]) == 0);
  #endif 
 
  // Verify log is written to correct path
  localAssert(_QUALIFIED_LOGGER.kFinalFilename_ == "logs/myeasylog.log");

  // Make sure log path exist
  localAssert(OSUtilities::pathExists(CUSTOM_LOG_FILE_LOCATION) == true);
  
  // Remove path and log file
  system(std::string(std::string("rm -rf ") + std::string(CUSTOM_LOG_FILE_LOCATION)).c_str());
  
  localAssert(OSUtilities::pathExists(CUSTOM_LOG_FILE_LOCATION) == false);

  OSUtilities::createPath(CUSTOM_LOG_FILE_LOCATION);  

  localAssert(OSUtilities::pathExists(CUSTOM_LOG_FILE_LOCATION) == true);

  // Ensure we have 0 counters before writeLogs() is called,
  // writeLogs() register 1 counter
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == 0);

  writeTrivialLogs();
#ifndef _DISABLE_LOGS  
  val(_QUALIFIED_LOGGER.registeredLogCounters()->count())
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == 7);
#else
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == 0);
#endif

  writeBusinessLogs();
#ifndef _DISABLE_LOGS  
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == (7 * 2));
#else
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == 0);
#endif

  writeSecurityLogs();
#ifndef _DISABLE_LOGS  
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == (7 * 3));
#else
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == 0);
#endif
  
  writeLegacyLogs();

  for (int i = 1; i <= 10; ++i) {
    LWARNING_EVERY_N(2) << "EVERY_N(2) log test : This is iteration #" << i << "/10";
  }

#ifndef _DISABLE_LOGS  
  localAssert(_QUALIFIED_LOGGER.registeredLogCounters()->count() == (7 * 3) + 1);
#endif

  return 0;
}
