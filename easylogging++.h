/***********************************************************************\
* easylogging++.h - Core of EasyLogging++                              *
*   EasyLogging++ v2.841                                                 *
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

#define _ENABLE_HINTS 1
#define _HINTS_TO_STANDARD_OUTPUT 1
#define _HINTS_TO_FILE 0

#define _ENABLE_STATUS 1
#define _STATUS_TO_STANDARD_OUTPUT 1
#define _STATUS_TO_FILE 0

#if _LOGGING_ENABLED
#if _WIN32 || _WIN64
 #define _WINDOWS
#endif //_WIN32 || _WIN64
#include <ctime>
#include <cstring>
#include <cstdlib>
#if _WINDOWS
 #include <direct.h> //digital mars compiler
 #include <windows.h>
#else
 #include <sys/stat.h>
#endif //_WINDOWS
#include <iostream>
#include <sstream>
#include <fstream>
namespace easyloggingpp {
//////////////////////////////////////////////
//   Configuration for logging             ///
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
* Flag to set whether to show username or not
*/
const bool SHOW_USERNAME = false;

/**
* Flag to set whether to show hostname or not
*/
const bool SHOW_HOSTNAME = false;

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
* Note: This should end with last slash and should be a fully qualified path. 
* Relative paths are not allowed
*/
const std::string CUSTOM_LOG_FILE_LOCATION = "logs/";

/**
 * Determines whether to show log when starting any time tracked function
 */
const bool SHOW_START_FUNCTION_LOG = false;

////////////////////////////////////////////////////////////////////
///         END OF CONFIGURATION FOR LOGGING                     ///
////////////////////////////////////////////////////////////////////
static const std::string kFinalFilename = (USE_CUSTOM_LOCATION ? CUSTOM_LOG_FILE_LOCATION : "") + LOG_FILENAME;
static std::string user;
static std::stringstream *logStream;
static bool toStandardOutput;
static bool toFile;
static const short kDateBufferSize = 25;
static char dateBuffer[kDateBufferSize];
static char dateFormat[kDateBufferSize];
static bool loggerInitialized = false;
static bool fileNotOpenedErrorDisplayed = false;

static inline void internalMessage(const std::string& message) {
    std::cout << std::endl << "[EasyLogging++] " << message << std::endl << std::endl;
}

static bool logPathExist(void) {
#if _WINDOWS
  DWORD fileType = GetFileAttributesA(::easyloggingpp::CUSTOM_LOG_FILE_LOCATION.c_str());
  if (fileType == INVALID_FILE_ATTRIBUTES) {
    return false;
  }
  return (fileType & FILE_ATTRIBUTE_DIRECTORY);
#else
  struct stat st;
  return (stat(::easyloggingpp::CUSTOM_LOG_FILE_LOCATION.c_str(), &st) == 0);
#endif
}

static void createLogPath(void) {
  if ((::easyloggingpp::USE_CUSTOM_LOCATION) && (::easyloggingpp::CUSTOM_LOG_FILE_LOCATION.size() > 0) && (!::easyloggingpp::logPathExist())) {
    int status = -1;
#if _WINDOWS
    std::string pathDelimiter = "\\";
#else
    std::string pathDelimiter = "/";
#endif
    std::string tempPath = CUSTOM_LOG_FILE_LOCATION;
    std::string dir = "";
    short foundAt = -1;
    std::string madeSoFar = tempPath.substr(0, 1) == pathDelimiter ? pathDelimiter : "";
    while ((foundAt = tempPath.find(pathDelimiter)) != std::string::npos) {
      dir = tempPath.substr(0, foundAt);
      if (dir != "") {
        madeSoFar += dir + pathDelimiter;
#if _WINDOWS
        status = _mkdir(madeSoFar.c_str());
#else
        status = mkdir(madeSoFar.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH); /* rwx,rwx,wx */
#endif
      }
      tempPath = tempPath.erase(0, foundAt + 1);
    }
    if (status == -1) {
      ::easyloggingpp::internalMessage("Unable to create log path [" + ::easyloggingpp::CUSTOM_LOG_FILE_LOCATION + "]");
    }
  }
}

static inline std::string getDateTime(void) {
  if (!(SHOW_DATE || SHOW_TIME)) return "";
#if _WINDOWS
  char* envDate = getenv("DATE");
  char* envTime = getenv("TIME");
  if ((envDate == NULL) || (envTime == NULL) || ((strcmp(envDate, "")) || (strcmp(envTime, "")))) {
#endif //_WINDOWS
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(::easyloggingpp::dateBuffer, ::easyloggingpp::kDateBufferSize, dateFormat, timeinfo);
#if _WINDOWS
  } else {
    if (::easyloggingpp::SHOW_DATE) {
      strcpy(::easyloggingpp::dateBuffer, envDate);
    }
    if (::easyloggingpp::SHOW_TIME) {
      if (::easyloggingpp::SHOW_DATE) {
        strcat(::easyloggingpp::dateBuffer, " ");
        strcat(::easyloggingpp::dateBuffer, envTime);
      } else {
        strcpy(::easyloggingpp::dateBuffer, envTime);
      }
    }
  }
#endif //_WINDOWS
  return std::string(::easyloggingpp::dateBuffer);
}

#ifndef __FILE__
 #define __FILE__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif //__FILE
#ifndef __LINE__
 #define __LINE__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif //_LINE__
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
 #define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
 #define __func__ __PRETTY_FUNCTION__
#else
 #define __func__ (SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO) ? NOT_SUPPORTED_STRING : ""
#endif //defined(_MSC_VER) && (_MSC_VER >= 1020)

static inline std::string getUsername(void) {
#if _WINDOWS
  char* username = getenv("USERNAME");
#else
  char* username = getenv("USER");
#endif //_WINDOWS
  if ((username == NULL) || ((strcmp(username, "") == 0))) {
    return std::string("");
  } else {
    return std::string(username);
  }
}

static inline std::string getHostname(void) {
#if _WINDOWS
  char* hostname = getenv("COMPUTERNAME");
#else
  char* hostname = getenv("HOSTNAME");
#endif //_WINDOWS
  if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
    return std::string("unknown-host");
  } else {
    return std::string(hostname);
  }
}

static inline void cleanStream(void) {
  ::easyloggingpp::logStream->str("");
}

static inline std::string colourful(const std::string& text, const std::string& colour, bool bold = false) {
#if __linux__
  short code = 30;
  if (colour == "black") code = 30;
  else if (colour == "red") code = 31;
  else if (colour == "green") code = 32;
  else if (colour == "yellow") code = 33;
  else if (colour == "blue") code = 34;
  else if (colour == "white") code = 37;
  std::stringstream finalText;
  finalText << "\033[" << (bold ? "1" : "0") << ";" << code << "m" << text << "\033[0m";
  return finalText.str();
#else
  return text;
#endif
}

static void init(void) {
  // Logger
  ::easyloggingpp::logStream = new std::stringstream();\
  // Path
  ::easyloggingpp::createLogPath();
  // Log file
  std::ofstream logFile(::easyloggingpp::kFinalFilename.c_str(), std::ofstream::out | std::ofstream::app);
  if (logFile.is_open()) {
    logFile.close();
  } else if (!fileNotOpenedErrorDisplayed) {
    ::easyloggingpp::internalMessage("Unable to open log file [" + ::easyloggingpp::kFinalFilename + "]");
    fileNotOpenedErrorDisplayed = true;
  }
  // Date format
  const char* dateFormatLocal = "%d/%m/%Y";
  const char* timeFormatLocal = "%H:%M:%S";
  if (::easyloggingpp::SHOW_DATE) strcpy(::easyloggingpp::dateFormat, dateFormatLocal);
  if (::easyloggingpp::SHOW_TIME) {
      if (::easyloggingpp::SHOW_DATE) {
          strcat(::easyloggingpp::dateFormat, " ");
          strcat(::easyloggingpp::dateFormat, timeFormatLocal);
      } else {
          strcpy(::easyloggingpp::dateFormat, timeFormatLocal);
      }
  }
  ::easyloggingpp::user = "";
  if (::easyloggingpp::SHOW_USERNAME)
    ::easyloggingpp::user = " [" + ::easyloggingpp::getUsername() + (::easyloggingpp::SHOW_HOSTNAME ? "" : "]");
  if (::easyloggingpp::SHOW_HOSTNAME)
    ::easyloggingpp::user += (::easyloggingpp::SHOW_USERNAME ? "@" : " [") + easyloggingpp::getHostname() + "]";
  loggerInitialized = true; 
}

static std::string readLog(void) {
  std::stringstream ss;
  if (::easyloggingpp::SAVE_TO_FILE) {
    std::ifstream logFile(::easyloggingpp::kFinalFilename.c_str(), std::ifstream::in);
    if (logFile.is_open()) {
      std::string line;
      while (logFile.good()) {
        std::getline(logFile, line);
        ss << line << std::endl;
      }
      logFile.close();
    } else {
      ss << "Error opening log file [" << ::easyloggingpp::kFinalFilename << "]";
    }
  } else {
    ss << "Logs are not being saved to file!";
  }
  return ss.str();
}

static void writeLog(void) {
  if ((::easyloggingpp::SHOW_STD_OUTPUT) && (::easyloggingpp::toStandardOutput)) {
    std::cout << ::easyloggingpp::logStream->str();
  }
  if ((!fileNotOpenedErrorDisplayed) && (::easyloggingpp::SAVE_TO_FILE) && (::easyloggingpp::toFile)) {
    std::ofstream logFile(::easyloggingpp::kFinalFilename.c_str(), std::ofstream::out | std::ofstream::app);
    logFile << ::easyloggingpp::logStream->str();
    logFile.close();
  }
  ::easyloggingpp::cleanStream();
}

#define WRITE_LOG(type, log)\
  if (!::easyloggingpp::loggerInitialized) {\
    ::easyloggingpp::init();\
  }\
  (*::easyloggingpp::logStream) << "[" << type << "]";\
  if (::easyloggingpp::SHOW_DATE || ::easyloggingpp::SHOW_TIME) {\
    (*::easyloggingpp::logStream) << " [" << ::easyloggingpp::getDateTime() << "]";\
  }\
  (*::easyloggingpp::logStream) << ::easyloggingpp::user;\
  if (::easyloggingpp::SHOW_LOG_FUNCTION) {\
    (*::easyloggingpp::logStream) << " [" << __func__ << "]";\
  }\
  if (::easyloggingpp::SHOW_LOG_LOCATION) {\
    (*easyloggingpp::logStream) << " [" << __FILE__ << ":" << __LINE__ <<"]";\
  }\
  (*::easyloggingpp::logStream) << " " << log;\
  (*::easyloggingpp::logStream) << std::endl;\
  if (type == "DEBUG") { ::easyloggingpp::toStandardOutput = _DEBUG_LOGS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _DEBUG_LOGS_TO_FILE; }\
  else if (type == "INFO") { ::easyloggingpp::toStandardOutput = _INFO_LOGS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _INFO_LOGS_TO_FILE; }\
  else if (type == "WARNING") { ::easyloggingpp::toStandardOutput = _WARNING_LOGS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _WARNING_LOGS_TO_FILE; }\
  else if (type == "ERROR") { ::easyloggingpp::toStandardOutput = _ERROR_LOGS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _ERROR_LOGS_TO_FILE; }\
  else if (type == "FATAL") { ::easyloggingpp::toStandardOutput = _FATAL_LOGS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _FATAL_LOGS_TO_FILE; }\
  else if (type == "PERFORMANCE") { ::easyloggingpp::toStandardOutput = _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _PERFORMANCE_LOGS_TO_FILE; }\
  else if (type == "HINT") { ::easyloggingpp::toStandardOutput = _HINTS_TO_STANDARD_OUTPUT; easyloggingpp::toFile = _HINTS_TO_FILE; }\
  else if (type == "STATUS") { ::easyloggingpp::toStandardOutput = _STATUS_TO_STANDARD_OUTPUT; ::easyloggingpp::toFile = _STATUS_TO_FILE; }\
  ::easyloggingpp::writeLog();
 
  #if _ENABLE_DEBUG_LOGS
    #define DEBUG(logStr) WRITE_LOG(std::string("DEBUG"),logStr)
  #else
    #define DEBUG(x)
  #endif //_ENABLE_DEBUG_LOGS
  #if _ENABLE_INFO_LOGS
    #define INFO(logStr) WRITE_LOG(std::string("INFO"),logStr)
  #else
    #define INFO(x)
  #endif //_ENABLE_INFO_LOGS
  #if _ENABLE_WARNING_LOGS
    #define WARNING(logStr) WRITE_LOG(std::string("WARNING"),logStr)
  #else
    #define WARNING(x)
  #endif //_ENABLE_WARNING_LOGS
  #if _ENABLE_ERROR_LOGS
    #define ERROR(logStr) WRITE_LOG(std::string("ERROR"),logStr)
  #else
    #define ERROR(x)
  #endif //_ENABLE_ERROR_LOGS
  #if _ENABLE_FATAL_LOGS
    #define FATAL(logStr) WRITE_LOG(std::string("FATAL"),logStr)
  #else
    #define FATAL(x)
  #endif //_ENABLE_FATAL_LOGS
  #if _ENABLE_PERFORMANCE_LOGS
    inline std::string formatSeconds(double secs) {
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
    #define PERFORMANCE(logStr) WRITE_LOG(std::string("PERFORMANCE"),logStr)
    #define START_FUNCTION_LOG "Executing [" << __func__ << "]"
    #define TIME_OUTPUT "Executed [" << __func__ << "] in [~ " << ::easyloggingpp::formatSeconds(difftime(functionEndTime,functionStartTime)) << "]"
    #define FUNC_SUB_COMMON_START { if (::easyloggingpp::SHOW_START_FUNCTION_LOG) { PERFORMANCE(START_FUNCTION_LOG) } time_t functionStartTime, functionEndTime; time(&functionStartTime);
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
  #if _ENABLE_HINTS
    #define HINT(logStr) WRITE_LOG(std::string("HINT"),logStr)
  #else
    #define HINT(x)
  #endif //_ENABLE_HINTS
  #if _ENABLE_STATUS
    #define STATUS(logStr) WRITE_LOG(std::string("STATUS"),logStr)
  #else
    #define STATUS(x)
  #endif //_ENABLE_STATUS
} //namespace easyloggingpp
#else
  #define DEBUG(x)
  #define INFO(x)
  #define WARNING(x)
  #define ERROR(x)
  #define FATAL(x)
  #define PERFORMANCE(x)
  #define HINT(x)
  #define STATUS(x)
  #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
  #define END_SUB }
  #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
  #define END_FUNC }
  #define RETURN(expr) return expr;
#endif //_LOGGING_ENABLED
#endif //EASYLOGGINGPP_H
