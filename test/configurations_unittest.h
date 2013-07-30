#ifndef EASYLOGGINGPP_CONFIGURATION_UNITTEST_H
#define EASYLOGGINGPP_CONFIGURATION_UNITTEST_H

#include "easylogging++.h"
#include <gtest/gtest.h>

using namespace easyloggingpp;
using namespace easyloggingpp::internal;

TEST(Configuration, ParsingTest) {
    Configurations confFile("test_conf.conf");
    Logger* testLogger = Loggers::reconfigureLogger("testLogger", confFile);

    EXPECT_EQ("%level %user %host %log\n", Loggers::ConfigurationsReader::logFormat(testLogger, Level::All));
    EXPECT_EQ("logs/testLog.log", Loggers::ConfigurationsReader::filename(testLogger, Level::All));
    EXPECT_TRUE(Loggers::ConfigurationsReader::enabled(testLogger, Level::All));
    EXPECT_TRUE(Loggers::ConfigurationsReader::toFile(testLogger, Level::All));
    EXPECT_FALSE(Loggers::ConfigurationsReader::toStandardOutput(testLogger, Level::All));
    EXPECT_EQ(1, Loggers::ConfigurationsReader::millisecondsWidth(testLogger, Level::All)); // For milliseconds 1 = 6, 10 = 5 and so on ...
    EXPECT_FALSE(Loggers::ConfigurationsReader::performanceTracking(testLogger, Level::All));
    EXPECT_EQ("%datetime INFO %logger %log\n", Loggers::ConfigurationsReader::logFormat(testLogger, Level::Info));

    confFile.clear();
    
}

#endif // EASYLOGGINGPP_CONFIGURATION_UNITTEST_H
