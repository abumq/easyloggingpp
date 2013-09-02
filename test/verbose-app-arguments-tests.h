#ifndef VMODULE_TESTS_H_
#define VMODULE_TESTS_H_
#include "test-helpers.h"

TEST(VerboseAppArgumentsTest, AppArgsLevel) {

    const char* c[10];
    c[0] = "myprog";
    c[1] = "--v=5";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "--v=x"; // Parses but does not change anything!
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "-v"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));

    // Reset
    c[0] = "myprog";
    c[1] = "--v=1"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_FALSE(VLOG_IS_ON(2));

    c[0] = "myprog";
    c[1] = "--verbose"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));

    // Reset
    c[0] = "myprog";
    c[1] = "--v=1"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_FALSE(VLOG_IS_ON(2));

    // ----------------------- UPPER CASE VERSION OF SAME TEST CASES -----------------
    c[0] = "myprog";
    c[1] = "--V=5";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "--V=x"; // Parses but does not change anything!
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "-V"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));

    // Reset
    c[0] = "myprog";
    c[1] = "--v=1"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_FALSE(VLOG_IS_ON(2));

    c[0] = "myprog";
    c[1] = "--VERBOSE"; // Sets to max level (9)
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));
}

TEST(VerboseAppArgumentsTest, AppArgsVModules) {

    const char* c[10];
    c[0] = "myprog";
    c[1] = "-vmodule=main*=3,easy.\?\?\?=1";
    el::Helpers::setArgs(2, c);

    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(2, "main.cpp", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(3, "main.h", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(4, "main.c", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(5, "main.cpp", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(2, "main.cxx", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(1, "main.cc", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(3, "main-file-for-prog.cc", el::base::elStorage->flags())));

    el::Helpers::removeFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);  // Check strictly

    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(4, "tmain.cxx", el::base::elStorage->flags())));

    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(1, "easy.cpp", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(1, "easy.cxx", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(1, "easy.hxx", el::base::elStorage->flags())));
    EXPECT_TRUE((el::base::elStorage->vRegistry()->allowed(1, "easy.hpp", el::base::elStorage->flags())));

    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(2, "easy.cpp", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(2, "easy.cxx", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(2, "easy.hxx", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(2, "easy.hpp", el::base::elStorage->flags())));

    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(1, "easy.cc", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(1, "easy.hh", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(1, "easy.h", el::base::elStorage->flags())));
    EXPECT_FALSE((el::base::elStorage->vRegistry()->allowed(1, "easy.c", el::base::elStorage->flags())));


}
#endif // VMODULE_TESTS_H_
