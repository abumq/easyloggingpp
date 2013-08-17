
#ifndef LOGGERS_TEST_H_
#define LOGGERS_TEST_H_

#include "test-helpers.h"

TEST(LoggersTest, RegisterHundredThousandLoggers) {
    cleanLogFile();
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "true");
    TIMED_BLOCK(timer, "HundredThousandLoggersTest");
    for (unsigned int i = 1; i <= 100000; ++i) {
        std::stringstream ss;
        ss << "logger" << i;
        Loggers::getLogger(ss.str());
        LOG_EVERY_N(10000, INFO) << "Registered " << i << " loggers";
    }
    PERFORMANCE_CHECKPOINT_WITH_ID(timer, "100,000 loggers registered");
    CLOG(INFO, "logger84785") << "Writing using logger 'logger84785'";
    PERFORMANCE_CHECKPOINT_WITH_ID(timer, "Log written using logger84785");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
    // We have 4 unique log streams registered at this point!
    //       1.      /tmp/logs/el.gtest.log
    //       2.      /tmp/logs/myeasylog.log
    //       3.      /tmp/my-test-err.log
    //       4.      /tmp/my-test.log
    EXPECT_EQ(4, el::base::elStorage->registeredLoggers()->logStreamsReference()->size());
}

TEST(LoggersTest, CheckHundredThousandLoggers) {

    TIMED_BLOCK(timer, "CheckHundredThousandLoggers");

    unsigned short lIndex = LevelHelper::kMinValid;
    std::fstream* logger1Stream = el::Loggers::getLogger("logger1")->typedConfigurations()->fileStream(LevelHelper::castFromInt(lIndex));
    // Make sure all loggers for all levels have same file stream pointee
    for (unsigned int i = 1; i <= 100000; ++i) {
        std::stringstream ss;
        ss << "logger" << i;
        LevelHelper::forEachLevel(lIndex, [&]() -> bool {
            EXPECT_EQ(logger1Stream, el::Loggers::getLogger(ss.str())->typedConfigurations()->fileStream(LevelHelper::castFromInt(lIndex)));
            return false;
        });
        lIndex = LevelHelper::kMinValid;
        LOG_EVERY_N(10000, INFO) << "Checked " << i << " loggers";
    }
}
#endif // LOGGERS_TEST_H_
