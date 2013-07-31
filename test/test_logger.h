#ifndef EASYLOGGINGPP_TEST_LOGGER_H
#define EASYLOGGINGPP_TEST_LOGGER_H

#include "easylogging++.h"

using namespace easyloggingpp;
using namespace easyloggingpp::internal;

    // Normal logs
    #define TINFO CINFO("testLogger")
    #define TWARNING CWARNING("testLogger")
    #define TDEBUG CDEBUG("testLogger")
    #define TERROR CERROR("testLogger")
    #define TFATAL CFATAL("testLogger")
    #define TQA CQA("testLogger")
    #define TTRACE CTRACE("testLogger")
    #define TVERBOSE(level) CVERBOSE(level, "testLogger")
    // Conditional logs
    #define TINFO_IF(condition) CINFO_IF(condition, "testLogger")
    #define TWARNING_IF(condition) CWARNING_IF(condition, "testLogger")
    #define TDEBUG_IF(condition) CDEBUG_IF(condition, "testLogger")
    #define TERROR_IF(condition) CERROR_IF(condition, "testLogger")
    #define TFATAL_IF(condition) CFATAL_IF(condition, "testLogger")
    #define TQA_IF(condition) CQA_IF(condition, "testLogger")
    #define TTRACE_IF(condition) CTRACE_IF(condition, "testLogger")
    #define TVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "testLogger")
    // Interval logs
    #define TINFO_EVERY_N(n) CINFO_EVERY_N(n, "testLogger")
    #define TWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "testLogger")
    #define TDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "testLogger")
    #define TERROR_EVERY_N(n) CERROR_EVERY_N(n, "testLogger")
    #define TFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "testLogger")
    #define TQA_EVERY_N(n) CQA_EVERY_N(n, "testLogger")
    #define TTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "testLogger")
    #define TVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "testLogger")
#endif // EASYLOGGINGPP_TEST_LOGGER_H

