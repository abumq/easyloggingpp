#ifndef EASYLOGGINGPP_LOGGERS_UNITTEST_H
#define EASYLOGGINGPP_LOGGERS_UNITTEST_H

#include "test_logger.h"
#include <gtest/gtest.h>

using namespace easyloggingpp;
using namespace easyloggingpp::internal;

TEST(Loggers, RegisteredLoggersCountTest) {
    // We have 4 default loggers and one test logger that we registered in main()
    EXPECT_EQ(registeredLoggers->count(), 5);
}

TEST(Loggers, LogFormatTest) {
    Logger* testLogger = Loggers::getLogger("testLogger");
    TDEBUG << "First log";
    std::stringstream expectedLine;
    expectedLine << "DEBUG " << internal::utilities::OSUtils::currentUser() << " " << internal::utilities::OSUtils::currentHost() << " First log";
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
