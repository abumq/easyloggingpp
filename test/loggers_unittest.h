#ifndef EASYLOGGINGPP_LOGGERS_UNITTEST_H
#define EASYLOGGINGPP_LOGGERS_UNITTEST_H

#include "easylogging++.h"
#include "test_logger.h"
#include <gtest/gtest.h>

using namespace easyloggingpp;
using namespace easyloggingpp::internal;

TEST(RegisteredLoggersTest, Loggers) {

    // We have 4 default loggers and one test logger that we registered in main()
    EXPECT_EQ(registeredLoggers->count(), 5);
    
    Logger* testLogger = Loggers::getLogger("testLogger");
    
    TDEBUG << "First log";
    std::stringstream expectedLine;
    expectedLine << "DEBUG " << utilities::OSUtilities::currentUser() << " " << utilities::OSUtilities::currentHost() << " First log";
    std::ifstream reader(Loggers::ConfigurationsReader::filename(testLogger).c_str(), std::ifstream::in);
    if (reader.is_open()) {
        std::string line;
        while (reader.good()) {
            std::getline(reader, line);
            EXPECT_EQ(expectedLine.str(), line);
            break; // we are just testing first line
        }
    }
    reader.close();
}

#endif // EASYLOGGINGPP_LOGGERS_UNITTEST_H
