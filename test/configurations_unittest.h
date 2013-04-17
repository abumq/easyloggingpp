#ifndef EASYLOGGINGPP_CONFIGURATION_UNITTEST_H
#define EASYLOGGINGPP_CONFIGURATION_UNITTEST_H

#include "easylogging++.h"
#include <gtest/gtest.h>

using namespace easyloggingpp;
using namespace easyloggingpp::internal;

TEST(ConfigurationTest, Parsing) {
    Configurations confFile("test_conf.conf");

    Logger* testLogger = Loggers::reConfigureLogger("testLogger", confFile);

    EXPECT_EQ("%level %user %host %log\n", Loggers::ConfigurationsReader::logFormat(testLogger, Level::ELPP_ALL));
    EXPECT_EQ("logs/testLog.log", Loggers::ConfigurationsReader::filename(testLogger, Level::ELPP_ALL));
    EXPECT_TRUE(Loggers::ConfigurationsReader::enabled(testLogger, Level::ELPP_ALL));
    EXPECT_TRUE(Loggers::ConfigurationsReader::toFile(testLogger, Level::ELPP_ALL));
    EXPECT_FALSE(Loggers::ConfigurationsReader::toStandardOutput(testLogger, Level::ELPP_ALL));
    EXPECT_EQ(1, Loggers::ConfigurationsReader::millisecondsWidth(testLogger, Level::ELPP_ALL)); // For milliseconds 1 = 6, 10 = 5 and so on ...
    EXPECT_FALSE(Loggers::ConfigurationsReader::performanceTracking(testLogger, Level::ELPP_ALL));
    EXPECT_EQ("%datetime INFO %logger %log\n", Loggers::ConfigurationsReader::logFormat(testLogger, Level::ELPP_INFO));
    
}

#endif // EASYLOGGINGPP_CONFIGURATION_UNITTEST_H
