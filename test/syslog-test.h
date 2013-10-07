#ifndef SYSLOGTEST_H
#define SYSLOGTEST_H

#include "test.h"

static const char* kSysLogFile = "/var/log/syslog";

#if defined(_ELPP_SYSLOG)
TEST(SysLogTest, TestSysLogFile) {

    // To avoid "Easylogging++ last message repeated 2 times"
    SYSLOG(INFO) << "last message suppress";

    SYSLOG(INFO) << "this is my syslog";
    sleep(1); // Make sure daemon has picked it up
    std::string expectedEnd = BUILD_STR(OS::currentHost() << " " << kSysLogIdent << ": INFO : this is my syslog\n");
    std::string actual = tail(1, kSysLogFile);
    if (fileExists(kSysLogFile)) {
        EXPECT_TRUE(Str::endsWith(actual, expectedEnd));
    }
}
#else
    _ELPP_UNUSED(kSysLogFile);
#   warning "Skipping [SysLogTest] for [_ELPP_SYSLOG] not defined"
#endif // defined(_ELPP_SYSLOG)

#endif // SYSLOGTEST_H
