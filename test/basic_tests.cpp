#include "basic_tests.h"
#include "../easylogging++.h"
#include "tests_core.h"

void basicTests(void) {
  ANLI
  INFO("Starting test...");
  ALI
  // Number of logs enabled
  assert(::easyloggingpp::internal::logTypes.size() == 10);
  ALI
  // Application arguments for verbose logs
  char* args[2];
  args[0] = "program_name";
  args[1] = "--v=3";
  _START_EASYLOGGINGPP(2, args);
  ALI
  assert(::easyloggingpp::internal::verboseLevel == 3);
  // Log path
  assert(::easyloggingpp::internal::kFinalFilename == "logs/myeasylog.log");
  assert(::easyloggingpp::internal::logPathExist() == true);
  system(std::string("mv " + ::easyloggingpp::internal::kFinalFilename + " .").c_str());
  system(std::string("rm -rf " + ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION).c_str());
  assert(::easyloggingpp::internal::logPathExist() == false);
  ALI
  ::easyloggingpp::internal::createLogPath();
  ALI
  assert(::easyloggingpp::internal::logPathExist() == true);
  system(std::string("mv ./" + ::easyloggingpp::configuration::LOG_FILENAME + " " + ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION).c_str());

  INFO("All tests were passed!");
  ALI
  _END_EASYLOGGINGPP // Release memory used by EasyLogging++
  ANLI
}
