// gtest based unit tests

#include "test-helpers.h"
#include "enum-helper-tests.h"
#include "utilities-test.h"
#include "registry-test.h"
#include "configurations-test.h"
#include "global-configurations-test.h"
#include "typed-configurations-test.h"
#include "hit-counter-test.h"
#include "verbose-app-arguments-tests.h"
#include "write-all-test.h"
#include "logger-test.h"
#include "loggable-test.h"

TIMED_BLOCK(testTimer, "Easylogging++ Unit Tests");
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    reconfigureLoggersForTest();

    std::cout << "Logs for test are written in [" << logfile << "]" << std::endl;

    return ::testing::UnitTest::GetInstance()->Run();
}
