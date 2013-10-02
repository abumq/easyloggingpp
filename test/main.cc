// gtest based unit tests

#include "test.h"
#include "enum-helper-test.h"
#include "helpers-test.h"
#include "utilities-test.h"
#include "registry-test.h"
#include "configurations-test.h"
#include "global-configurations-test.h"
#include "typed-configurations-test.h"
#include "hit-counter-test.h"
#include "verbose-app-arguments-test.h"
#include "write-all-test.h"
#include "logger-test.h"
#include "loggable-test.h"
#include "custom-format-specifier-test.h"

TIMED_BLOCK(testTimer, "Easylogging++ Unit Tests");
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    reconfigureLoggersForTest();

    std::cout << "Logs for test are written in [" << logfile << "]" << std::endl;

    return ::testing::UnitTest::GetInstance()->Run();
}
