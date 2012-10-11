/************************************************************************\
* easylogging++.h - Core of EasyLogging++                              *
*   EasyLogging++ v1.2                                                 *
*   Cross platform logging made easy for C++ applications              *
*   Author Majid Khan <mkhan3189@gmail.com>                            *
*   http://www.icplusplus.com                                          *
*   https://github.com/mkhan3189/EasyLoggingPP                         *
*                                                                      *
* This program is free software: you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation, version 3 of the License.              *
\***********************************************************************/
#ifndef EasyLoggingPP_LOGGING_H
#define EasyLoggingPP_LOGGING_H

/**
* 1 for enabled
* 0 for disabled
*/
#define _LOGGING_ENABLED 1

#define _ENABLE_DEBUG_LOGS 1
#define _ENABLE_INFO_LOGS 1
#define _ENABLE_WARNING_LOGS 1
#define _ENABLE_ERROR_LOGS 1
#define _ENABLE_PERFORMANCE_LOGS 1

#if _LOGGING_ENABLED
#include <iostream>
#include <sstream>
#include <fstream>
//////////////////////////////////////////////
//     Configuration for logging           ///
//////////////////////////////////////////////

/**
* Flag for showing log in standard output using std::cout
*/
const bool SHOW_STD_OUTPUT = true;

/**
* Flag to set whether to save log to file
*/
const bool SAVE_TO_FILE = true;

/**
* Flag to set whether to show date/time
*/
const bool SHOW_DATE_TIME = true;

/**
* Flag to set whether to show which function logged the output (some compiler dont support this)
*/
const bool SHOW_LOG_FUNCTION = false;

/**
* Flag to set whether to show which file logged the output and what line
*/
const bool SHOW_LOG_LOCATION = true;

/**
* Flag to set whether output value of NOT_SUPPORTED_STRING if extra info is not available on machine
*/
const bool SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO = false;

/**
* outputs if extra info is not available on machine and SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO is true
*/
const std::string NOT_SUPPORTED_STRING = "-not supported-";

/**
* If saving to file, this defines the filename
*/
const std::string LOG_FILENAME = "myeasylog.log";

/**
* Flag to set whether to save log file in custom location
*/
const bool USE_CUSTOM_LOCATION = false;

/**
* If using custom location, this is where custom location is picked up from.
* Note: This should end with last slash 
*/
const std::string CUSTOM_LOG_FILE_LOCATION = "";

/**
 * Determines whether to show log when starting any time tracked function
 */
const bool SHOW_START_FUNCTION_LOG = false;
////////////////////////////////////////////////////////////////////
///               END OF CONFIGURATION FOR LOGGING               ///
////////////////////////////////////////////////////////////////////


const bool EXTRA_INFO_ENABLED = SHOW_DATE_TIME || SHOW_LOG_FUNCTION || SHOW_LOG_LOCATION;
static std::stringstream *streamForEasyLoggingPP;

#ifndef __func__
 #define __func__ __PRETTY_FUNCTION__
#endif
#ifndef __TIMESTAMP__
 #define __TIMESTAMP__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif
#ifndef __FILE__
 #define __FILE__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif
#ifndef __LINE__
 #define __LINE__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif

inline static void write(std::stringstream* logStream){
    if (SHOW_STD_OUTPUT) {
        std::cout << logStream->str() << std::endl;
    }
    if (SAVE_TO_FILE) {
        std::string finalFilename = (USE_CUSTOM_LOCATION ? CUSTOM_LOG_FILE_LOCATION : "") + LOG_FILENAME;
        std::ofstream logFile(finalFilename.c_str(),
            std::ios::out | std::ios::app);
        logFile << logStream->str() << std::endl;
        logFile.close();
    }
    delete logStream;
    logStream = 0;
}
#define LOG(type,log) streamForEasyLoggingPP = new std::stringstream();\
    (*streamForEasyLoggingPP)<<"[" << type << "]";\
    if (SHOW_DATE_TIME) {\
    (*streamForEasyLoggingPP) << " ["<< __TIMESTAMP__ <<"]";\
    }\
    if (SHOW_LOG_FUNCTION) {\
    (*streamForEasyLoggingPP) << " [Func: "<< __func__ <<"]";\
    }\
    if (SHOW_LOG_LOCATION) {\
    (*streamForEasyLoggingPP) << " ["<< __FILE__ <<":"<< __LINE__ <<"]";\
    }\
    (*streamForEasyLoggingPP) << (EXTRA_INFO_ENABLED ? "\n" : "\t" ) << log;\
    write(streamForEasyLoggingPP);

  #if _ENABLE_DEBUG_LOGS
    #define DEBUG(logStr) LOG("DEBUG",logStr)
  #else
    #define DEBUG(x)
  #endif//_ENABLE_DEBUG_LOGS

  #if _ENABLE_INFO_LOGS
    #define INFO(logStr) LOG("INFO",logStr)
  #else
    #define INFO(x)
  #endif//_ENABLE_INFO_LOGS

  #if _ENABLE_WARNING_LOGS
    #define WARN(logStr) LOG("WARN",logStr)
  #else
    #define WARNING(x)
  #endif//_ENABLE_WARNING_LOGS

  #if _ENABLE_ERROR_LOGS
    #define ERR(logStr) LOG("ERROR",logStr)
  #else
    #define ERR(x)
  #endif//_ENABLE_ERROR_LOGS

  #if _ENABLE_PERFORMANCE_LOGS
    #include <time.h>
    #define PERF(logStr) LOG("PERFORMANCE",logStr)
    #define START_FUNCTION_LOG "Executing [" << __func__ << "]"
    #define TIME_OUTPUT "Executed [" << __func__ << "] in [~" << difftime (functionEndTime,functionStartTime) << " seconds]"
    #define FUNC_SUB_COMMON_START { if (SHOW_START_FUNCTION_LOG) { PERF(START_FUNCTION_LOG) } time_t functionStartTime,functionEndTime; time(&functionStartTime);
    #define FUNC_SUB_COMMON_END time(&functionEndTime); PERF(TIME_OUTPUT);
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START 
    #define END_SUB FUNC_SUB_COMMON_END }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START 
    #define END_FUNC FUNC_SUB_COMMON_END }
    #define RETURN(expr) FUNC_SUB_COMMON_END return expr;
  #else
    #define PERF(x)
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
    #define END_SUB }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
    #define END_FUNC }
    #define RETURN(expr) return expr;
  #endif //_ENABLE_PERFORMACE_LOGS
#else
  #define DEBUG(x)
  #define INFO(x)
  #define WARN(x)
  #define ERR(x)
  #define PERF(x)
#endif //_LOGGING

#endif //EasyLoggingPP_LOGGING_H
