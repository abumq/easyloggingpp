#ifndef ISSUESTEST_H_
#define ISSUESTEST_H_

#include "test.h"

// https://github.com/easylogging/easyloggingpp/issues/278
TEST(IssuesTest, Issue278) {
    // first log a nullptr
    const char* null_ptr = nullptr;
    LOG(INFO) << "char* nullptr:" << null_ptr;
    std::string expected = BUILD_STR(getDate() << " char* nullptr:\n");
    EXPECT_EQ(expected, tail(1));

    // then log something else and see if it is broken
    LOG(INFO) << "issue278";
    expected = BUILD_STR(getDate() << " issue278\n");
    EXPECT_EQ(expected, tail(1));
}

#endif // ISSUESTEST_H_
