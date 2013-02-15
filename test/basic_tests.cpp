#include "basic_tests.h"
#include <cstring>
#include "../easylogging++-full.h"
#include "tests_core.h"
void basicTests(int argc, char** argv) {
  ALI
  
  INFO("Running basic tests...");

  // FIXME: for some weird reason, comparing like so causes valgrind to be sad  
  assert(strcmp(::easyloggingpp::internal::user.c_str(), argv[1]) == 0);
  assert(strcmp(::easyloggingpp::internal::host.c_str(), argv[2]) == 0);

  ALI
  // Number of logs enabled
  assert(::easyloggingpp::internal::registeredLogTypes.size() == 10);
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
  ALI
}
