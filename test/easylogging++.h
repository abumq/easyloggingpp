// Header for test that sub-includes original header from src/ folder
#ifndef EASYLOGGING_FOR_TEST_H
#define EASYLOGGING_FOR_TEST_H

// We define these macros here for travis to pick up
#ifndef _ELPP_STOP_ON_FIRST_ASSERTION
#   define _ELPP_STOP_ON_FIRST_ASSERTION
#endif
#ifndef _ELPP_STL_LOGGING
#   define _ELPP_STL_LOGGING
#endif
#ifndef _ELPP_FORCE_ENV_VAR_FROM_BASH
#   define _ELPP_FORCE_ENV_VAR_FROM_BASH
#endif
#ifndef _ELPP_ENABLE_THREADING
#   define _ELPP_ENABLE_THREADING
#endif
#ifndef _ELPP_STACKTRACE_ON_CRASH
#   define _ELPP_STACKTRACE_ON_CRASH
#endif
#ifndef _ELPP_DISABLE_VMODULES_EXTENSION
#   define _ELPP_DISABLE_VMODULES_EXTENSION
#endif
#ifndef _ELPP_SYSLOG
#   define _ELPP_SYSLOG
#endif

#include "../src/easylogging++.h"
#endif // EASYLOGGING_FOR_SAMPLES_H
