 //
 // This file is part of Easylogging++ samples
 // Check macros
 //
 // Revision 1.0
 // @author mkhan3189
 //

#define _ELPP_PREVENT_FATAL_ABORT

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    // These checks should fail
    LOG(INFO) << "----- DONT WORRY ABOUT FOLLOWING CHECKS FAILING - THEY ARE EXPECTED";
    CHECK(1 > 2) << "1 is not greater than 2";
    CHECK_EQ(1, 2) << "1 is not equal to 2";
    CHECK_NE(1, 1) << "Wow, I did not know 1 == 1";
    CHECK_STREQ("abc", "def") << " :)";
    CHECK_STRNE("abc", "abc") << " :(";
    CHECK_STRCASEEQ("abc", "ABCD") << " :p";
    CHECK_STRCASENE("abc", "ABC") << " B)";
    int* f = new int;
    int* toF = CHECK_NOTNULL(f);

    (void)toF; // Unused warning suppression

    delete f;
    f = nullptr;
    // These checks should pass 
    LOG(WARNING) << "----- START WORRYING ABOUT CHECKS NOW";
    CHECK(1 < 2) << " snap -- lib has bug!";
    CHECK_EQ(1, 1) << " snap -- lib has bug!";
    CHECK_NE(1, 2) << " snap -- lib has bug!";
    CHECK_STREQ("abc", "abc") << " snap -- lib has bug!";
    CHECK_STRNE("abc", "abe") << " snap -- lib has bug!";
    CHECK_STRCASEEQ("abc", "ABC") << " snap -- lib has bug!";
    CHECK_STRCASENE("abc", "ABE") << " snap -- lib has bug!";
    LOG(INFO) << "----- HOPEFULLY NO CHECK FAILED SINCE YOU STARTED WORRYING!";
    return 0;
}
