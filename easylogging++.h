///////////////////////////////////////////////////////////////////////////
//                                                                       //
// easylogging++.h - Core of EasyLogging++                               //
//   EasyLogging++ v3.21                                                 //
//   Cross platform logging made easy for C++ applications               //
//   Author Majid Khan <mkhan3189@gmail.com>                             //
//   http://www.icplusplus.com                                           //
//   https://github.com/mkhan3189/EasyLoggingPP                          //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, version 3 of the Licence.               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                         MODIFIABLE SECTION                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////
///                                                              ///
///                 END OF MODIFIABLE SECTION                    ///
///                                                              ///
///      *** DO NOT MODIFY ANY LINE BELOW THIS POINT ***         ///
///                  EXCEPT CONFIGURATION                        ///
///                                                              ///
////////////////////////////////////////////////////////////////////

#if ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))

//
// OS evaluation
//
// Windows
#if defined(_WIN32)
 #define _WINDOWS 1
 #define _WINDOWS_32 1
#endif //defined(_WIN32)
#if defined(_WIN64)
 #define _WINDOWS 1
 #define _WINDOWS_64 1
#endif //defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
 #define _LINUX 1
#endif //(defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
 #if TARGET_OS_MAC
  #define _MAC 1
 #endif //TARGET_OS_MAC
#endif //defined(__APPLE__)

//
// Includes
//
#include <ctime>
#include <cstring>
#include <cstdlib>
#if _WINDOWS
 #include <direct.h> //digital mars compiler
 #include <windows.h>
#endif //_WINDOWS
#if _LINUX || _MAC
 #include <sys/stat.h>
 #include <sys/time.h>
#endif //_LINUX || _MAC
#include <iostream>
#include <sstream>
#include <fstream>

namespace easyloggingpp {

///////////////////////////////////////////////////////////////////////
///                                                                 ///
///                   CONFIGURATION FOR LOGGING                     ///
///                                                                 ///
///                       MODIFIABLE SECTION                        ///
///                                                                 ///
///////////////////////////////////////////////////////////////////////


// FOR DETAILS ON FOLLOWING CONFIGURATION PLEASE SEE README AT:
// https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md

const std::string DEFAULT_LOG_FORMAT = "[%level] [%datetime] %log\n";
const std::string DEBUG_LOG_FORMAT = "[%level] [%datetime] [%user@%host] [%func] [%loc] %log\n";
const std::string INFO_LOG_FORMAT = DEFAULT_LOG_FORMAT;
const std::string WARNING_LOG_FORMAT = DEFAULT_LOG_FORMAT;
const std::string ERROR_LOG_FORMAT = DEFAULT_LOG_FORMAT;
const std::string FATAL_LOG_FORMAT = DEFAULT_LOG_FORMAT;
const std::string PERFORMANCE_LOG_FORMAT = DEFAULT_LOG_FORMAT;
const std::string HINT_LOG_FORMAT = DEFAULT_LOG_FORMAT;
const std::string STATUS_LOG_FORMAT = DEFAULT_LOG_FORMAT;

const bool SHOW_STD_OUTPUT = true;
const bool SAVE_TO_FILE = true;
const std::string LOG_FILENAME = "myeasylog.log";
const bool USE_CUSTOM_LOCATION = true;
const std::string CUSTOM_LOG_FILE_LOCATION = "logs/";
const bool SHOW_START_FUNCTION_LOG = false;

////////////////////////////////////////////////////////////////////
///                                                              ///
///                    END OF CONFIGURATION                      ///
///                                                              ///
///   *** PLEASE DO NOT MODIFY ANY LINE BELOW THIS POINT ***     ///
///                                                              ///
////////////////////////////////////////////////////////////////////

//
// Source code location macros
//
#if !defined(__FILE__)
 #define __FILE__ ""
#endif //!defined(__FILE__)
#if !defined(__LINE__)
 #define __LINE__ ""
#endif //!defined(__LINE__)
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
 #define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
 #define __func__ __PRETTY_FUNCTION__
#else
 #define __func__ ""
#endif //defined(_MSC_VER) && (_MSC_VER >= 1020)

//
// Log levels
//
#define _DEBUG_LOG       ((_ENABLE_DEBUG_LOGS) && !defined(_DISABLE_DEBUG_LOGS))
#define _INFO_LOG        ((_ENABLE_INFO_LOGS) && !defined(_DISABLE_INFO_LOGS))
#define _WARNING_LOG     ((_ENABLE_WARNING_LOGS) && !defined(_DISABLE_WARNING_LOGS))
#define _ERROR_LOG       ((_ENABLE_ERROR_LOGS) && !defined(_DISABLE_ERROR_LOGS))
#define _PERFORMANCE_LOG ((_ENABLE_PERFORMANCE_LOGS) && !defined(_DISABLE_PERFORMANCE_LOGS))
#define _STATUS_LOG      ((_ENABLE_STATUS) && !defined(_DISABLE_STATUS))
#define _HINT_LOG        ((_ENABLE_HINTS) && !defined(_DISABLE_HINTS))
#define _FATAL_LOG       ((_ENABLE_FATAL_LOGS) && !defined(_DISABLE_FATAL_LOGS))

//
// Static fields
//
static const std::string kFinalFilename = (::easyloggingpp::USE_CUSTOM_LOCATION ? ::easyloggingpp::CUSTOM_LOG_FILE_LOCATION : "") + ::easyloggingpp::LOG_FILENAME;
static bool showDateTime = ::easyloggingpp::DEFAULT_LOG_FORMAT.find("%datetime") != std::string::npos;
static bool showDate = (!::easyloggingpp::showDateTime) && (::easyloggingpp::DEFAULT_LOG_FORMAT.find("%date") != std::string::npos);
static bool showTime = (!::easyloggingpp::showDateTime) && (::easyloggingpp::DEFAULT_LOG_FORMAT.find("%time") != std::string::npos);
static bool showLocation = ::easyloggingpp::DEFAULT_LOG_FORMAT.find("%loc") != std::string::npos;
static std::string user;
static std::string host;
static std::stringstream *logMessageeam = NULL;
static std::ofstream *logFile = NULL;
static std::stringstream tempStream;
static std::stringstream tempStream2;
static bool toStandardOutput;
static bool toFile;
static const short kDateBufferSize = 25;
static char dateBuffer[kDateBufferSize];
static char dateFormat[kDateBufferSize];
static bool loggerInitialized = false;
static bool fileNotOpenedErrorDisplayed = false;
static std::string logFormat = "";

//
// Internal functions
//
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
#elif _LINUX || _MAC
  struct stat st;
  return (stat(::easyloggingpp::CUSTOM_LOG_FILE_LOCATION.c_str(), &st) == 0);
#endif //_WINDOWS
}

static void createLogPath(void) {
#if _WINDOWS || _LINUX || _MAC
  if ((::easyloggingpp::USE_CUSTOM_LOCATION) && (::easyloggingpp::CUSTOM_LOG_FILE_LOCATION.size() > 0) && (!::easyloggingpp::logPathExist())) {
    int status = -1;
 #if _WINDOWS
    std::string pathDelimiter = "\\";
 #elif _LINUX || _MAC
    std::string pathDelimiter = "/";
 #endif //_WINDOWS
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
 #elif _LINUX || _MAC
        status = mkdir(madeSoFar.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH); /* rwx,rwx,wx */
 #endif //_WINDOWS
      }
      tempPath = tempPath.erase(0, foundAt + 1);
    }
    if (status == -1) {
      ::easyloggingpp::internalMessage("Unable to create log path [" + ::easyloggingpp::CUSTOM_LOG_FILE_LOCATION + "]");
    }
  }
#else
  ::easyloggingpp::internalMessage("Unable to create log path [" + ::easyloggingpp::CUSTOM_LOG_FILE_LOCATION + "]");
#endif //_WINDOWS || _LINUX || _MAC
}

static inline std::string getDateTime(void) {
  if (!(::easyloggingpp::showDateTime || ::easyloggingpp::showDate || ::easyloggingpp::showTime)) return "";
#if _WINDOWS
    time_t currTime;
    time(&currTime);
#elif _LINUX || _MAC
    timeval currTime;
    gettimeofday(&currTime, NULL);
    int milliSeconds = 0;
    if ((::easyloggingpp::showDateTime) || (::easyloggingpp::showTime)) {
      milliSeconds = currTime.tv_usec / 1000;
    }
#endif //_WINDOWS
    struct tm * timeInfo;
#if _WINDOWS
    timeInfo = localtime(&currTime);
#elif _LINUX || _MAC
    timeInfo = localtime(&currTime.tv_sec);
#endif //_WINDOWS
    strftime(::easyloggingpp::dateBuffer, ::easyloggingpp::kDateBufferSize, ::easyloggingpp::dateFormat, timeInfo);
#if _LINUX || _MAC
    if ((::easyloggingpp::showDateTime) || (::easyloggingpp::showTime)) {
      sprintf(::easyloggingpp::dateBuffer, "%s.%d", ::easyloggingpp::dateBuffer, milliSeconds);
    }
#endif //_LINUX || _MAC
  return std::string(::easyloggingpp::dateBuffer);
}

static inline std::string getUsername(void) {
#if _WINDOWS
  char* username = getenv("USERNAME");
#elif _LINUX || _MAC
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
#elif _LINUX || _MAC
  char* hostname = getenv("HOSTNAME");
#endif //_WINDOWS
  if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
    return std::string("unknown-host");
  } else {
    return std::string(hostname);
  }
}

static inline void cleanStream(void) {
  ::easyloggingpp::tempStream.str("");
  ::easyloggingpp::tempStream2.str("");
  ::easyloggingpp::logMessageeam->str("");
}

static inline void updateDateFormat(void) {
  const char* dateFormatLocal = "%d/%m/%Y";
  const char* timeFormatLocal = "%H:%M:%S";
  if (::easyloggingpp::showDate) {
    strcpy(::easyloggingpp::dateFormat, dateFormatLocal);
  } else if (::easyloggingpp::showTime) {
    strcpy(::easyloggingpp::dateFormat, timeFormatLocal);
  } else if (::easyloggingpp::showDateTime) {
    strcpy(::easyloggingpp::dateFormat, dateFormatLocal);
    strcat(::easyloggingpp::dateFormat, " ");
    strcat(::easyloggingpp::dateFormat, timeFormatLocal);
  }
}

static void init(void) {
  if (!::easyloggingpp::loggerInitialized) {
    // Logger
    if (::easyloggingpp::SHOW_STD_OUTPUT) {
      ::easyloggingpp::logMessageeam = new std::stringstream();
    }
    // Path
    ::easyloggingpp::createLogPath();
    // Log file
    if (::easyloggingpp::SAVE_TO_FILE) {
#if defined(_ALWAYS_CLEAN_LOGS)
        std::ios_base::openmode mode = std::ofstream::out;
#else
        std::ios_base::openmode mode = std::ofstream::out | std::ofstream::app;
#endif
      ::easyloggingpp::logFile = new std::ofstream(::easyloggingpp::kFinalFilename.c_str(), mode);
      if ((!::easyloggingpp::fileNotOpenedErrorDisplayed) && (!::easyloggingpp::logFile->is_open())) {
        ::easyloggingpp::internalMessage("Unable to open log file [" + ::easyloggingpp::kFinalFilename + "]");
        ::easyloggingpp::fileNotOpenedErrorDisplayed = true;
      }
    }
    // Date format
    ::easyloggingpp::updateDateFormat();
    // Username and host
    ::easyloggingpp::user = ::easyloggingpp::getUsername();
    ::easyloggingpp::host = ::easyloggingpp::getHostname();
    ::easyloggingpp::loggerInitialized = true;
  } 
}

static std::string readLog(void) {
  std::stringstream ss;
  if (::easyloggingpp::SAVE_TO_FILE) {
    std::ifstream logFileReader(::easyloggingpp::kFinalFilename.c_str(), std::ifstream::in);
    if (logFileReader.is_open()) {
      std::string line;
      while (logFileReader.good()) {
        std::getline(logFileReader, line);
        ss << line << std::endl;
      }
      logFileReader.close();
    } else {
      ss << "Error opening log file [" << ::easyloggingpp::kFinalFilename << "]";
    }
  } else {
    ss << "Logs are not being saved to file!";
  }
  return ss.str();
}

static void writeLog(void) {
  if ((::easyloggingpp::logMessageeam) && (::easyloggingpp::toStandardOutput)) {
    std::cout << ::easyloggingpp::logMessageeam->str();
  }
  if ((!::easyloggingpp::fileNotOpenedErrorDisplayed) && (::easyloggingpp::logFile) && (::easyloggingpp::toFile)) {
    ::easyloggingpp::logFile->open(::easyloggingpp::kFinalFilename.c_str(), std::ofstream::out | std::ofstream::app);
    (*::easyloggingpp::logFile) << ::easyloggingpp::logMessageeam->str();
    ::easyloggingpp::logFile->close();
  }
  ::easyloggingpp::cleanStream();
}

static void updateFormatValue(const std::string& formatSpecifier, const std::string& value, std::string& currentFormat) {
  size_t foundAt = -1;
  while ((foundAt = currentFormat.find(formatSpecifier, foundAt + 1)) != std::string::npos){
    if (currentFormat.substr(foundAt > 0 ? foundAt - 1 : 0, 1) == "E") {
      currentFormat = currentFormat.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
      foundAt++;
    } else {
      currentFormat = currentFormat.replace(foundAt, formatSpecifier.size(), value);
      continue; 
    }
  }
}

static void determineCommonLogFormat(const std::string& format) {
  ::easyloggingpp::logFormat = format;
  ::easyloggingpp::showDateTime = format.find("%datetime") != std::string::npos;
  if (!::easyloggingpp::showDateTime) {
    ::easyloggingpp::showDate = (format.find("%date") != std::string::npos);
    ::easyloggingpp::showTime = (format.find("%time") != std::string::npos);
  }
  ::easyloggingpp::showLocation = format.find("%loc") != std::string::npos;
  ::easyloggingpp::updateDateFormat();
}

#define LOG_FORMATTER(typeLHS, typeRHS, format, logToStandardOutput, logToFile)\
  if (typeLHS == typeRHS) {\
    ::easyloggingpp::determineCommonLogFormat(format);\
    ::easyloggingpp::toStandardOutput = logToStandardOutput;\
    ::easyloggingpp::toFile = logToFile;\
    return;\
  }

static void determineLogFormat(const std::string& type) {
  LOG_FORMATTER(type, "DEBUG", ::easyloggingpp::DEBUG_LOG_FORMAT, _DEBUG_LOGS_TO_STANDARD_OUTPUT, _DEBUG_LOGS_TO_FILE)
  LOG_FORMATTER(type, "INFO", ::easyloggingpp::INFO_LOG_FORMAT, _INFO_LOGS_TO_STANDARD_OUTPUT, _INFO_LOGS_TO_FILE)
  LOG_FORMATTER(type, "WARNING", ::easyloggingpp::WARNING_LOG_FORMAT, _WARNING_LOGS_TO_STANDARD_OUTPUT, _WARNING_LOGS_TO_FILE)
  LOG_FORMATTER(type, "ERROR", ::easyloggingpp::ERROR_LOG_FORMAT, _ERROR_LOGS_TO_STANDARD_OUTPUT, _ERROR_LOGS_TO_FILE)
  LOG_FORMATTER(type, "FATAL", ::easyloggingpp::FATAL_LOG_FORMAT, _FATAL_LOGS_TO_STANDARD_OUTPUT, _FATAL_LOGS_TO_FILE)
  LOG_FORMATTER(type, "PERFORMANCE", ::easyloggingpp::PERFORMANCE_LOG_FORMAT, _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT, _PERFORMANCE_LOGS_TO_FILE)
  LOG_FORMATTER(type, "HINT", ::easyloggingpp::HINT_LOG_FORMAT, _HINTS_TO_STANDARD_OUTPUT, _HINTS_TO_FILE)
  LOG_FORMATTER(type, "STATUS", ::easyloggingpp::STATUS_LOG_FORMAT, _STATUS_TO_STANDARD_OUTPUT, _STATUS_TO_FILE)
}

static void buildFormat(const char* func, const char* file, const unsigned long int line, const std::string& type) {
  ::easyloggingpp::init();
  ::easyloggingpp::determineLogFormat(type);
  ::easyloggingpp::updateFormatValue("%level", type, ::easyloggingpp::logFormat);
  if (::easyloggingpp::showDateTime) {
    ::easyloggingpp::updateFormatValue("%datetime", ::easyloggingpp::getDateTime(), ::easyloggingpp::logFormat);
  } else if (::easyloggingpp::showDate) {
    ::easyloggingpp::updateFormatValue("%date", ::easyloggingpp::getDateTime(), ::easyloggingpp::logFormat);
  } else if (::easyloggingpp::showTime) {
    ::easyloggingpp::updateFormatValue("%time", ::easyloggingpp::getDateTime(), ::easyloggingpp::logFormat);
  }
  ::easyloggingpp::updateFormatValue("%func", std::string(func), ::easyloggingpp::logFormat);
  if (::easyloggingpp::showLocation) {
    ::easyloggingpp::tempStream << file << ":" << line; 
    ::easyloggingpp::updateFormatValue("%loc", ::easyloggingpp::tempStream.str(), ::easyloggingpp::logFormat);
  }
  ::easyloggingpp::updateFormatValue("%user", ::easyloggingpp::user, ::easyloggingpp::logFormat);
  ::easyloggingpp::updateFormatValue("%host", ::easyloggingpp::host, ::easyloggingpp::logFormat);
  ::easyloggingpp::updateFormatValue("%log", ::easyloggingpp::tempStream2.str(), ::easyloggingpp::logFormat);
  (*::easyloggingpp::logMessageeam) << logFormat;
}

//
// Logging macros
//
#define WRITE_LOG(type, log)\
  ::easyloggingpp::tempStream2 << log;\
  ::easyloggingpp::buildFormat(__func__, __FILE__, __LINE__, std::string(type));\
  ::easyloggingpp::writeLog();
 
  #if _DEBUG_LOG
    #define DEBUG(logMessage) WRITE_LOG("DEBUG",logMessage)
    #define DEBUG_IF(condition, logMessage) if (condition) { DEBUG(logMessage); }
  #else
    #define DEBUG(x)
    #define DEBUG_IF(x, y)
  #endif //_DEBUG_LOG

  #if _INFO_LOG
    #define INFO(logMessage) WRITE_LOG("INFO",logMessage)
    #define INFO_IF(condition, logMessage) if (condition) { INFO(logMessage); }
  #else
    #define INFO(x)
    #define INFO_IF(x, y) 
  #endif //_INFO_LOG

  #if _WARNING_LOG
    #define WARNING(logMessage) WRITE_LOG("WARNING",logMessage)
    #define WARNING_IF(condition, logMessage) if (condition) { WARNING(logMessage); }
  #else
    #define WARNING(x)
    #define WARNING_IF(x, y)
  #endif //_WARNING_LOG

  #if _ERROR_LOG
    #define ERROR(logMessage) WRITE_LOG("ERROR",logMessage)
    #define ERROR_IF(condition, logMessage) if (condition) { ERROR(logMessage); }
  #else
    #define ERROR(x)
    #define ERROR_IF(x, y)
  #endif //_ERROR_LOG

  #if _FATAL_LOG
    #define FATAL(logMessage) WRITE_LOG("FATAL",logMessage)
    #define FATAL_IF(condition, logMessage) if (condition) { FATAL(logMessage); }
  #else
    #define FATAL(x)
    #define FATAL_IF(x, y)
  #endif //_FATAL_LOG

  #if _PERFORMANCE_LOG
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
    #define PERFORMANCE(logMessage) WRITE_LOG("PERFORMANCE",logMessage)
    #define PERFORMANCE_IF(condition, logMessage) if (condition) { PERFORMANCE(logMessage); }
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
    #define PERFORMANCE_IF(x, y)
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
    #define END_SUB }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
    #define END_FUNC }
    #define RETURN(expr) return expr;
  #endif //_PERFORMANCE_LOG

  #if _HINT_LOG
    #define HINT(logMessage) WRITE_LOG("HINT",logMessage)
    #define HINT_IF(condition, logMessage) if (condition) { HINT(logMessage); }
  #else
    #define HINT(x)
    #define HINT_IF(x, y)
  #endif //_HINT_LOG

  #if _STATUS_LOG
    #define STATUS(logMessage) WRITE_LOG("STATUS",logMessage)
    #define STATUS_IF(condition, logMessage) if (condition) { STATUS(logMessage); }
  #else
    #define STATUS(x)
    #define STATUS_IF(x, y)
  #endif //_STATUS_LOG

} //namespace easyloggingpp
#else
  // Essentials
  #define DEBUG(x)
  #define INFO(x)
  #define WARNING(x)
  #define ERROR(x)
  #define FATAL(x)
  #define PERFORMANCE(x)
  #define HINT(x)
  #define STATUS(x)
  // Performance specific
  #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
  #define END_SUB }
  #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
  #define END_FUNC }
  #define RETURN(expr) return expr;
  // Conditional
  #define DEBUG_IF(x, y)
  #define INFO_IF(x, y)
  #define WARNING_IF(x, y)
  #define ERROR_IF(x, y)
  #define FATAL_IF(x, y)
  #define PERFORMANCE_IF(x, y)
  #define HINT_IF(x, y)
  #define STATUS_IF(x, y)
#endif //((_LOGGING_ENABLED) && !defined(_DISABLE_EASYLOGGINGPP))
#endif //EASYLOGGINGPP_H
