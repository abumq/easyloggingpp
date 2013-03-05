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

#ifndef _DISABLE_LOGS  
using namespace easyloggingpp::internal;
using namespace easyloggingpp::configuration;
using namespace easyloggingpp::helper;
#endif

// Do not use cassert as we want custom
// message and return on failure
#define localAssert(assertion) \
  if (!(assertion)) { \
    std::cout << "TEST FAILED: " << #assertion << " [Line: " << __LINE__ << "]"; \
    return 1; \
  } \

int main(int argc, char** argv) {
  // Following is optional to set app arguments that are used for verbose
  // logging
  _START_EASYLOGGINGPP(argc, argv);

#ifndef _DISABLE_LOGS  
  // Currently logger is not initialized - logger gets initialized when first
  // log is written
  localAssert(loggerInitialized == false);
#endif

  // Following triggers logger to initialize as well as write following log
  LINFO << "Initializing logger...";
  
#ifndef _DISABLE_LOGS  
  #ifndef _DISABLE_INFO_LOGS
    // Make sure we have written correct log
    localAssert(utils::ilike(easyloggingpp::helper::readLog(), "%Initializing logger...%") == true);
    // Now we expect logger to be initialized because of above line
    localAssert(loggerInitialized == true);
    // Make sure username and hostname is fetch correctly. The correct username
    // and host name is passed into test via bash script
    localAssert(strcmp(user.c_str(), argv[1]) == 0);
    localAssert(strcmp(host.c_str(), argv[2]) == 0);
  #else
    localAssert(utils::ilike(easyloggingpp::helper::readLog(), "%Initializing logger...%") == false);
    localAssert(registeredLogTypes.size() == 0);
  #endif 
 
  // Verify log is written to correct path
  localAssert(kFinalFilename == "logs/myeasylog.log");

  // Make sure log path exist
  localAssert(logPathExist() == true);
  
  // Remove path and log file
  system(std::string("rm -rf " + CUSTOM_LOG_FILE_LOCATION).c_str());
  
  localAssert(logPathExist() == false);

  createLogPath();  

  localAssert(logPathExist() == true);
#endif

  _END_EASYLOGGINGPP

#ifndef _DISABLE_LOGS  
  localAssert(loggerInitialized == false);

  // Ensure we have 0 counters before writeLogs() is called,
  // writeLogs() register 1 counter
  localAssert(registeredCounters.size() == 0);
#endif

  writeLogs();
  
#ifndef _DISABLE_LOGS  
  // Ensure we have correct amount of counters registered
  localAssert(registeredCounters.size() == 1);
#endif
  
  writeLegacyLogs();

#ifndef _DISABLE_LOGS  
  // Ensure we have correct number of log levels initialized
  localAssert(registeredLogTypes.size() == atoi(argv[3]));
#endif

  for (int i = 1; i <= 10; ++i) {
    LWARNING_EVERY_N(2) << "This is iteration #" << i;
  }

#ifndef _DISABLE_LOGS  
  localAssert(registeredCounters.size() == 2);
#endif

  _END_EASYLOGGINGPP
  
#ifndef _DISABLE_LOGS  
  // Ensure everything is good in the end
  localAssert(registeredLogTypes.empty()); 
  localAssert(registeredCounters.empty()); 
  localAssert(logStream == NULL);
  localAssert(logFile == NULL);
  localAssert(loggerInitialized == false);
#endif
  return 0;
}
