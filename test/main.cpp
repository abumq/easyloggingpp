/*
 * Contain unit tests for EasyLogging++
 *
 * Revision: 1.1
 * @author mkhan3189
 */

#include "../easylogging++.h"
#include "tests_core.h"
#include "basic_tests.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  ANLI
  INFO("Starting tests...");
  basicTests(argc, argv);

  INFO("All tests were passed!");
  _END_EASYLOGGINGPP
  ANLI
}
