
#ifndef WRITE_ALL_TEST_H_
#define WRITE_ALL_TEST_H_

#include "test-helpers.h"

TEST(WriteAllTests, Entry) {
    reconfigureLoggersForTest();
}

#define TEST_LEVEL(l, name) \
TEST(WriteAllTests, l) {\
    std::string s;\
    LOG(l) << name << " 1";\
    s = BUILD_STR(getDate() << " " << name << " 1\n");\
    EXPECT_EQ(s, tail(2));\
    LOG_IF(true, l) << name << " 2";\
    s = BUILD_STR(getDate() << " " << name << " 1\n"\
               << getDate() << " " << name << " 2\n");\
    EXPECT_EQ(s, tail(3));\
    LOG_IF(true, l) << name << " 3";\
    s = BUILD_STR(getDate() << " " << name << " 3\n");\
    EXPECT_EQ(s, tail(2));\
    LOG_IF(false, l) << "SHOULD NOT LOG";\
    s = BUILD_STR(getDate() << " " << name << " 3\n");\
    EXPECT_EQ(s, tail(2));\
    LOG_EVERY_N(1, l) << name << " every n=1";\
    s = BUILD_STR(getDate() << " " << name << " every n=1\n");\
    EXPECT_EQ(s, tail(2));\
}

TEST_LEVEL(DEBUG, "Debug")
TEST_LEVEL(INFO, "Info")
TEST_LEVEL(ERROR, "Error")
TEST_LEVEL(WARNING, "Warning")
TEST_LEVEL(FATAL, "Fatal")
TEST_LEVEL(TRACE, "Trace")


TEST(WriteAllTests, VERBOSE) {
    Configurations cOld(*Loggers::getLogger("default")->configurations());
    Loggers::reconfigureAllLoggers(ConfigurationType::Format, "%datetime{%a %b %d, %H:%m} %level-%vlevel %log");

    el::Helpers::addFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified); // Accept all verbose levels; we already have vmodules!

    std::string s;
    for (int i = 1; i <= 6; ++i)
        VLOG_EVERY_N(2, 2) << "every n=" << i;

    s = BUILD_STR(getDate() << " VER-2 every n=2\n"
               << getDate() << " VER-2 every n=4\n"
               << getDate() << " VER-2 every n=6\n");
    EXPECT_EQ(s, tail(4));

    VLOG_IF(true, 3) << "Test conditional verbose log";
    s = BUILD_STR(getDate() << " VER-3 Test conditional verbose log\n");
    EXPECT_EQ(s, tail(2));

    VLOG_IF(false, 3) << "SHOULD NOT LOG";
    // Should not log!
    EXPECT_EQ(s, tail(2));

    VLOG(3) << "Log normally (verbose)";
    s = BUILD_STR(getDate() << " VER-3 Log normally (verbose)\n");
    EXPECT_EQ(s, tail(2));

    // Reset it back to old
    Loggers::reconfigureAllLoggers(cOld);
}

TEST(WriteAllTests, EVERY_N) {
    std::string s;
    const char* name = "INFO";
    for (int i = 1; i <= 6; ++i)
        LOG_EVERY_N(2, INFO) << name << " every n=" << i;

    s = BUILD_STR(getDate() << " " << name << " every n=2\n"
               << getDate() << " " << name << " every n=4\n"
               << getDate() << " " << name << " every n=6\n");
    EXPECT_EQ(s, tail(4));
}
#endif // WRITE_ALL_TEST_H_
