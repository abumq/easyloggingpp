#include "easylogging++.h"
#include "configurations_unittest.h"
#include "loggers_unittest.h"
#include <gtest/gtest.h>

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  
    Loggers::getLogger("testLogger"); // Register test logger

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}
