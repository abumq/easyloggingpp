/***********************************************************************\
* easylogging++.h - Core of EasyLogging++                              *
*   EasyLogging++ v2.1                                                 *
*   Cross platform logging made easy for C++ applications              *
*   Author Majid Khan <mkhan3189@gmail.com>                            *
*   http://www.icplusplus.com                                          *
*   https://github.com/mkhan3189/EasyLoggingPP                         *
*                                                                      *
* This program is free software: you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation, version 3 of the License.              *
\***********************************************************************/
#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H

/**
* 1 for enabled
* 0 for disabled
*/
#define _LOGGING_ENABLED 1

#define _ENABLE_DEBUG_LOGS 1
#define _DEBUG_LOGS_TO_STANDARD_OUTPUT 0
#define _DEBUG_LOGS_TO_FILE 1

#define _ENABLE_INFO_LOGS 1
#define _INFO_LOGS_TO_STANDARD_OUTPUT 1
#define _INFO_LOGS_TO_FILE 1

#define _ENABLE_WARNING_LOGS 1 
#define _WARNING_LOGS_TO_STANDARD_OUTPUT 1
#define _WARNING_LOGS_TO_FILE 1

#define _ENABLE_ERROR_LOGS 1 
#define _ERROR_LOGS_TO_STANDARD_OUTPUT 1
#define _ERROR_LOGS_TO_FILE 1

#define _ENABLE_FATAL_LOGS 1 
#define _FATAL_LOGS_TO_STANDARD_OUTPUT 1
#define _FATAL_LOGS_TO_FILE 1

#define _ENABLE_PERFORMANCE_LOGS 1
#define _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT 0
#define _PERFORMANCE_LOGS_TO_FILE 1

#if _LOGGING_ENABLED
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
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
* Flag to set whether to show date
*/
const bool SHOW_DATE = true;

/**
 * Flag to set whether to show time
*/
const bool SHOW_TIME = true;

/**
* Flag to set whether to show which file logged the output and what line
*/
const bool SHOW_LOG_LOCATION = false;

/**
* Flag to set whether to show which function logged the output
*/
const bool SHOW_LOG_FUNCTION = false;

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
const bool USE_CUSTOM_LOCATION = true;

/**
* If using custom location, this is where custom location is picked up from.
* Note: This should end with last slash.
* Example valid paths:
*     /home/dev_linux/logs/
*     ../../my_logs/
*     logs/
*     D:\\My_Dev_Windows\\Logs\\
* Example invalid paths:
*     ~/logs/
*     C:\
*/
const std::string CUSTOM_LOG_FILE_LOCATION = "logs/";

/**
 * Determines whether to show log when starting any time tracked function
 */
const bool SHOW_START_FUNCTION_LOG = false;

////////////////////////////////////////////////////////////////////
///               END OF CONFIGURATION FOR LOGGING               ///
////////////////////////////////////////////////////////////////////

const bool EXTRA_INFO_ENABLED = SHOW_DATE || SHOW_TIME || SHOW_LOG_LOCATION || SHOW_LOG_FUNCTION;
static std::stringstream *streamForEasyLoggingPP;
static bool ELPPtoStdOut;
static bool ELPPtoFile;
static char ELPPdateBuff[21];
inline static std::string getELPPDateTime(void) {
  if (!(SHOW_DATE || SHOW_TIME)) return "";
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  std::string format = "";
  if (SHOW_DATE) format += "%d/%m/%Y";
  if (SHOW_TIME) format += (std::string((SHOW_DATE ? " " : "")) + std::string("%H:%M:%S"));
  strftime (ELPPdateBuff,21,format.c_str(),timeinfo);
  std::string buffStr(ELPPdateBuff);
  return buffStr;
}
#ifndef __FILE__
 #define __FILE__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif
#ifndef __LINE__
 #define __LINE__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
 #define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
 #define __func__ __PRETTY_FUNCTION__
#else
 #define __func__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif
static void writeLogNow() {
    if (SHOW_STD_OUTPUT && ELPPtoStdOut) {
        std::cout << streamForEasyLoggingPP->str() << std::endl;
    }
    if (SAVE_TO_FILE && ELPPtoFile) {
        std::string finalFilename = (USE_CUSTOM_LOCATION ? CUSTOM_LOG_FILE_LOCATION : "") + LOG_FILENAME;
        std::ofstream logFile(finalFilename.c_str(),
            std::ofstream::out | std::ofstream::app);
        if (logFile.is_open()) {
            logFile << streamForEasyLoggingPP->str() << std::endl;
            logFile.close();
        } else {
            /* error opening log file */
        }
    }
    if (streamForEasyLoggingPP != 0) {
        delete streamForEasyLoggingPP;
        streamForEasyLoggingPP = 0;
    }
}
#define LOG(type,log) if (streamForEasyLoggingPP == 0) \
    { streamForEasyLoggingPP = new std::stringstream(); } \
    (*streamForEasyLoggingPP) << "[" << type << "]";\
    if (SHOW_DATE || SHOW_TIME) {\
      (*streamForEasyLoggingPP) << " [" << getELPPDateTime() << "]";\
    }\
    if (SHOW_LOG_FUNCTION) {\
      (*streamForEasyLoggingPP) << " [" << __func__ << "]";\
    }\
    if (SHOW_LOG_LOCATION) {\
      (*streamForEasyLoggingPP) << " [" << __FILE__ << ":" << __LINE__ <<"]";\
    }\
      (*streamForEasyLoggingPP) << " " << log;\
      if (type == "DEBUG") {ELPPtoStdOut = _DEBUG_LOGS_TO_STANDARD_OUTPUT; ELPPtoFile = _DEBUG_LOGS_TO_FILE;}\
      if (type == "INFO") {ELPPtoStdOut = _INFO_LOGS_TO_STANDARD_OUTPUT; ELPPtoFile = _INFO_LOGS_TO_FILE;}\
      if (type == "WARNING") {ELPPtoStdOut = _WARNING_LOGS_TO_STANDARD_OUTPUT; ELPPtoFile = _WARNING_LOGS_TO_FILE;}\
      if (type == "ERROR") {ELPPtoStdOut = _ERROR_LOGS_TO_STANDARD_OUTPUT; ELPPtoFile = _ERROR_LOGS_TO_FILE;}\
      if (type == "FATAL") {ELPPtoStdOut = _FATAL_LOGS_TO_STANDARD_OUTPUT; ELPPtoFile = _FATAL_LOGS_TO_FILE;}\
      if (type == "PERFORMANCE") {ELPPtoStdOut = _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT; ELPPtoFile = _PERFORMANCE_LOGS_TO_FILE;}\
    writeLogNow();
 
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
    #define ERROR(logStr) LOG("ERROR",logStr)
  #else
    #define ERROR(x)
  #endif//_ENABLE_ERROR_LOGS
  #if _ENABLE_FATAL_LOGS
    #define FATAL(logStr) LOG("FATAL",logStr)
  #else
    #define FATAL(x)
  #endif//_ENABLE_FATAL_LOGS
  #if _ENABLE_PERFORMANCE_LOGS
    inline static std::string formatELPPSeconds(double secs) {
        double result = secs;
        std::string unit = "seconds";
        std::stringstream ss;
        if (result > 60.0f) {result /= 60; unit = "minutes";
            if (result > 60.0f) {result /= 60; unit = "hours";
                if (result > 24.0f) {result /= 24; unit = "days";}
            }
        }
        ss << result << " " << unit;
        return ss.str();
    }
    #define PERFORMANCE(logStr) LOG("PERFORMANCE",logStr)
    #define START_FUNCTION_LOG "Executing [" << __func__ << "]"
    #define TIME_OUTPUT "Executed [" << __func__ << "] in [~ " << formatELPPSeconds(difftime(functionEndTime,functionStartTime)) << "]"
    #define FUNC_SUB_COMMON_START { if (SHOW_START_FUNCTION_LOG) { PERFORMANCE(START_FUNCTION_LOG) } time_t functionStartTime,functionEndTime; time(&functionStartTime);
    #define FUNC_SUB_COMMON_END time(&functionEndTime); PERFORMANCE(TIME_OUTPUT);
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START 
    #define END_SUB FUNC_SUB_COMMON_END }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START 
    #define END_FUNC FUNC_SUB_COMMON_END }
    #define RETURN(expr) FUNC_SUB_COMMON_END return expr;
  #else
    #define PERFORMANCE(x)
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
    #define END_SUB }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
    #define END_FUNC }
    #define RETURN(expr) return expr;
  #endif //_ENABLE_PERFORMANCE_LOGS
#else
  #define DEBUG(x)
  #define INFO(x)
  #define WARN(x)
  #define ERROR(x)
  #define FATAL(x)
  #define PERFORMANCE(x)
  #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
  #define END_SUB }
  #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
  #define END_FUNC }
  #define RETURN(expr) return expr;
#endif //_LOGGING_ENABLED
#endif //EASYLOGGINGPP_H
