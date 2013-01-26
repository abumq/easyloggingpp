// Contain unit tests for EasyLogging++
// Revision: 1.0
// @author mkhan3189

#include "../easylogging++.h"
#include "tests_core.h"
#include "basic_tests.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  basicTests(argc, argv);

  _END_EASYLOGGINGPP
  ANLI
}
