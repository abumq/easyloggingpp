// Header for tools that sub-includes original header from src/ folder
// Will be replaced with original header in future
#ifndef EASYLOGGING_FOR_TOOLS_H
#define EASYLOGGING_FOR_TOOLS_H

#define _ELPP_QT_LOGGING
#define _ELPP_THREAD_SAFE
#define _ELPP_STOP_ON_FIRST_ASSERTION
#define _ELPP_STACKTRACE_ON_CRASH

#include "../../src/easylogging++.h"

#define RLOG(LEVEL) CLOG(LEVEL, "remote")
#define VRLOG(vlevel) CVLOG(vlevel, "remote")
// Conditional logs
#define RLOG_IF(condition, LEVEL) CLOG_IF(condition, LEVEL, "remote")
#define VRLOG_IF(condition, vlevel) CVLOG_IF(condition, vlevel, "remote")
// Interval logs
#define RLOG_EVERY_N(n, LEVEL) CLOG_EVERY_N(n, LEVEL, "remote")
#define VRLOG_EVERY_N(n, vlevel) CVLOG_EVERY_N(n, vlevel, "remote")

#endif // EASYLOGGING_FOR_SAMPLES_H
