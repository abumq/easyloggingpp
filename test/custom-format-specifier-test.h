#ifndef CUSTOM_FORMAT_SPECIFIER_TEST_H
#define CUSTOM_FORMAT_SPECIFIER_TEST_H

#include "test.h"

const char* getIp() {
    return "127.0.0.1";
}

TEST(CustomFormatSpecifierTest, TestInstall) {
    EXPECT_FALSE(el::Helpers::hasCustomFormatSpecifier("%ip"));
    el::Helpers::installCustomFormatSpecifier(el::CustomFormatSpecifier("%ip", getIp));
    EXPECT_TRUE(el::Helpers::hasCustomFormatSpecifier("%ip"));
}

TEST(CustomFormatSpecifierTest, TestResolution) {
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime{%a %b %d, %H:%m} %ip: %log");
    LOG(INFO) << "My ip test";
    std::string s = BUILD_STR(getDate() << " 127.0.0.1: My ip test\n");
    EXPECT_EQ(s, tail(1));
    // Reset back
    reconfigureLoggersForTest();
}

TEST(CustomFormatSpecifierTest, TestUnInstall) {
    EXPECT_TRUE(el::Helpers::hasCustomFormatSpecifier("%ip"));
    el::Helpers::uninstallCustomFormatSpecifier("%ip");
    EXPECT_FALSE(el::Helpers::hasCustomFormatSpecifier("%ip"));
}

#endif // CUSTOM_FORMAT_SPECIFIER_TEST_H
