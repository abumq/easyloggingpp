// Contains core of tests
// @author mkhan3189

#ifndef _EASYLOGGINGPP_TESTS_CORE_H
#define _EASYLOGGINGPP_TESTS_CORE_H

#include <cassert>
// ASSERT NOT LOGGER INITIALIZED
#define ANLI assert(::easyloggingpp::internal::loggerInitialized == false);
// ASSERT LOGGER INITIALIZED
#define ALI assert(::easyloggingpp::internal::loggerInitialized == true);

#endif
