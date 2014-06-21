#ifndef FORMAT_SPECIFIER_TEST_H
#define FORMAT_SPECIFIER_TEST_H

#include "test.h"

TEST(FormatSpecifierTest, TestFBaseSpecifier) {
    Configurations c;
    c.setGlobally(el::ConfigurationType::Format, "%datetime{%a %b %d, %H:%m} %fbase: %msg");
    el::Loggers::reconfigureLogger(consts::kDefaultLoggerId, c);
    LOG(INFO) << "My fbase test";
    std::string s = BUILD_STR(getDate() << " format-specifier-test.h: My fbase test\n");
    EXPECT_EQ(s, tail(1));
    // Reset back
    reconfigureLoggersForTest();
}

#endif // FORMAT_SPECIFIER_TEST_H
