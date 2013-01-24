///////////////////////////////////////////////////////////////////////////
//                                                                       //
// easylogging++.h - Core of EasyLogging++                               //
//   EasyLogging++ v3.32                                                 //
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

#define _ENABLE_HINT 1
#define _HINT_TO_STANDARD_OUTPUT 1
#define _HINT_TO_FILE 0

#define _ENABLE_STATUS 1
#define _STATUS_TO_STANDARD_OUTPUT 1
#define _STATUS_TO_FILE 1

#define _ENABLE_VERBOSE_LOGS 1 
#define _VERBOSE_LOGS_TO_STANDARD_OUTPUT 1
#define _VERBOSE_LOGS_TO_FILE 1

#define _ENABLE_QA_LOGS 1
#define _QA_LOGS_TO_STANDARD_OUTPUT 1
#define _QA_LOGS_TO_FILE 1

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
 #define _MAC 1
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
#include <string>
#include <list>
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
namespace configuration {

// FOR DETAILS ON FOLLOWING CONFIGURATION PLEASE SEE README AT:
// https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md

const std::string    DEFAULT_LOG_FORMAT       =    "[%level] [%datetime] %log\n";
const std::string    DEBUG_LOG_FORMAT         =    "[%level] [%datetime] [%user@%host] [%func] [%loc] %log\n";
const std::string    INFO_LOG_FORMAT          =    DEFAULT_LOG_FORMAT;
const std::string    WARNING_LOG_FORMAT       =    DEFAULT_LOG_FORMAT;
const std::string    ERROR_LOG_FORMAT         =    DEFAULT_LOG_FORMAT;
const std::string    FATAL_LOG_FORMAT         =    DEFAULT_LOG_FORMAT;
const std::string    PERFORMANCE_LOG_FORMAT   =    DEFAULT_LOG_FORMAT;
const std::string    HINT_LOG_FORMAT          =    DEFAULT_LOG_FORMAT;
const std::string    STATUS_LOG_FORMAT        =    DEFAULT_LOG_FORMAT;
const std::string    VERBOSE_LOG_FORMAT       =    "[%level-%vlevel] [%datetime] %log\n";
const std::string    QA_LOG_FORMAT            =    DEFAULT_LOG_FORMAT;

const bool           SHOW_STD_OUTPUT          =    true;
const bool           SAVE_TO_FILE             =    true;
const std::string    LOG_FILENAME             =    "myeasylog.log";
const bool           USE_CUSTOM_LOCATION      =    true;
const std::string    CUSTOM_LOG_FILE_LOCATION =    "logs/";
const bool           SHOW_START_FUNCTION_LOG  =    false;

} // namespace configuration
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
#define _HINT_LOG        ((_ENABLE_HINT) && !defined(_DISABLE_HINT))
#define _FATAL_LOG       ((_ENABLE_FATAL_LOGS) && !defined(_DISABLE_FATAL_LOGS))
#define _VERBOSE_LOG     ((_ENABLE_VERBOSE_LOGS) && !defined(_DISABLE_VERBOSE_LOGS))
#define _QA_LOG          ((_ENABLE_QA_LOGS) && defined(_QUALITY_ASSURANCE))

// Application arguments based logs
#define _START_EASYLOGGINGPP(argc, argv) ::easyloggingpp::internal::setAppArgs(argc, argv);
#define _END_EASYLOGGINGPP ::easyloggingpp::internal::releaseMemory();

namespace internal {
//
// Static fields
//
static const std::string kFinalFilename = (::easyloggingpp::configuration::USE_CUSTOM_LOCATION ? ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION : "") + ::easyloggingpp::configuration::LOG_FILENAME;
static bool showDateTime = ::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%datetime") != std::string::npos;
static bool showDate = (!::easyloggingpp::internal::showDateTime) && (::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%date") != std::string::npos);
static bool showTime = (!::easyloggingpp::internal::showDateTime) && (::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%time") != std::string::npos);
static bool showLocation = ::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%loc") != std::string::npos;
static std::string user;
static std::string host;
static std::stringstream *logStream = NULL;
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
#if _VERBOSE_LOG
static int verboseLevel = -1;
#endif //_VERBOSE_LOG
class LogType {
public:
  LogType(const std::string& name_,
          const std::string& format_,
          bool toStandardOutput_,
          bool toFile_) :
            name(name_),
            format(format_),
            toStandardOutput(toStandardOutput_),
            toFile(toFile_) {}
  std::string name;
  std::string format;
  bool toStandardOutput;
  bool toFile;
};
static std::list< ::easyloggingpp::internal::LogType > logTypes;

//
// Internal functions
//
static inline void internalMessage(const std::string& message) {
    std::cout << std::endl << "[EasyLogging++] " << message << std::endl << std::endl;
}

static inline void setAppArgs(int argc, char** argv) {
  while (argc-- > 0) {
#if _VERBOSE_LOG
    if ((strlen(argv[argc]) >= 5) 
     && (argv[argc][0] == '-')
     && (argv[argc][1] == '-')
     && (argv[argc][2] == 'v')
     && (argv[argc][3] == '=')) {
       ::easyloggingpp::internal::verboseLevel = atoi(argv[argc] + 4);
    }
#endif //_VERBOSE_LOG
  }
}

static inline void setAppArgs(int argc, const char** argv) {
  char** args = const_cast<char**>(argv);
  setAppArgs(argc, args);
}

static bool logPathExist(void) {
#if _WINDOWS
  DWORD fileType = GetFileAttributesA(::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str());
  if (fileType == INVALID_FILE_ATTRIBUTES) {
    return false;
  }
  return (fileType & FILE_ATTRIBUTE_DIRECTORY);
#elif _LINUX || _MAC
  struct stat st;
  return (stat(::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str(), &st) == 0);
#endif //_WINDOWS
}

static void createLogPath(void) {
#if _WINDOWS || _LINUX || _MAC
  if ((::easyloggingpp::configuration::USE_CUSTOM_LOCATION)
   && (::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.size() > 0)
   && (!::easyloggingpp::internal::logPathExist())) {
    int status = -1;
 #if _WINDOWS
    std::string pathDelimiter = "\\";
 #elif _LINUX || _MAC
    std::string pathDelimiter = "/";
 #endif //_WINDOWS
    std::string tempPath = ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION;
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
      ::easyloggingpp::internal::internalMessage("Unable to create log path [" + ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION + "]");
    }
  }
#else
  ::easyloggingpp::internal::internalMessage("Unable to create log path [" + ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION + "]");
#endif //_WINDOWS || _LINUX || _MAC
}

static inline std::string getDateTime(void) {
  if (!(::easyloggingpp::internal::showDateTime || ::easyloggingpp::internal::showDate || ::easyloggingpp::internal::showTime)) return "";
#if _WINDOWS
    time_t currTime;
    time(&currTime);
#elif _LINUX || _MAC
    timeval currTime;
    gettimeofday(&currTime, NULL);
    int milliSeconds = 0;
    if ((::easyloggingpp::internal::showDateTime) || (::easyloggingpp::internal::showTime)) {
      milliSeconds = currTime.tv_usec / 1000;
    }
#endif //_WINDOWS
    struct tm * timeInfo;
#if _WINDOWS
    timeInfo = localtime(&currTime);
#elif _LINUX || _MAC
    timeInfo = localtime(&currTime.tv_sec);
#endif //_WINDOWS
    strftime(::easyloggingpp::internal::dateBuffer, ::easyloggingpp::internal::kDateBufferSize, ::easyloggingpp::internal::dateFormat, timeInfo);
#if _LINUX || _MAC
    if ((::easyloggingpp::internal::showDateTime) || (::easyloggingpp::internal::showTime)) {
      sprintf(::easyloggingpp::internal::dateBuffer, "%s.%d", ::easyloggingpp::internal::dateBuffer, milliSeconds);
    }
#endif //_LINUX || _MAC
  return std::string(::easyloggingpp::internal::dateBuffer);
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
#if _LINUX || _MAC
  FILE* hostnameProc = popen("hostname", "r");
  if (hostnameProc != NULL) {
    const short hBuffMaxSize = 20;
    char hBuff[hBuffMaxSize];
    fgets(hBuff, hBuffMaxSize, hostnameProc);
    pclose(hostnameProc);
    short actualHBuffSize = strlen(hBuff);
    if (actualHBuffSize > 0) {
      if (hBuff[actualHBuffSize - 1] == '\n') {
        hBuff[actualHBuffSize - 1] = '\0';
      }
      return std::string(hBuff);
    }
  }
#endif
    return std::string("unknown-host");
  } else {
    return std::string(hostname);
  }
}

static inline void cleanStream(void) {
  ::easyloggingpp::internal::tempStream.str("");
  ::easyloggingpp::internal::tempStream2.str("");
  ::easyloggingpp::internal::logStream->str("");
}

static inline void releaseMemory(void) {
  ::easyloggingpp::internal::cleanStream();
  delete ::easyloggingpp::internal::logFile;
  delete ::easyloggingpp::internal::logStream;
  ::easyloggingpp::internal::loggerInitialized = false;
}

static inline void updateDateFormat(void) {
  const char* dateFormatLocal = "%d/%m/%Y";
  const char* timeFormatLocal = "%H:%M:%S";
  if (::easyloggingpp::internal::showDate) {
    strcpy(::easyloggingpp::internal::dateFormat, dateFormatLocal);
  } else if (::easyloggingpp::internal::showTime) {
    strcpy(::easyloggingpp::internal::dateFormat, timeFormatLocal);
  } else if (::easyloggingpp::internal::showDateTime) {
    strcpy(::easyloggingpp::internal::dateFormat, dateFormatLocal);
    strcat(::easyloggingpp::internal::dateFormat, " ");
    strcat(::easyloggingpp::internal::dateFormat, timeFormatLocal);
  }
}

static void init(void) {
  if (!::easyloggingpp::internal::loggerInitialized) {
    // Logger
    if (::easyloggingpp::configuration::SHOW_STD_OUTPUT) {
      ::easyloggingpp::internal::logStream = new std::stringstream();
    }
    // Path
    ::easyloggingpp::internal::createLogPath();
    // Log file
    if (::easyloggingpp::configuration::SAVE_TO_FILE) {
#if defined(_ALWAYS_CLEAN_LOGS)
        std::ios_base::openmode mode = std::ofstream::out;
#else
        std::ios_base::openmode mode = std::ofstream::out | std::ofstream::app;
#endif //defined(_ALWAYS_CLEAN_LOGS)
      ::easyloggingpp::internal::logFile = new std::ofstream(::easyloggingpp::internal::kFinalFilename.c_str(), mode);
      if ((!::easyloggingpp::internal::fileNotOpenedErrorDisplayed) && (!::easyloggingpp::internal::logFile->is_open())) {
        ::easyloggingpp::internal::internalMessage("Unable to open log file [" + ::easyloggingpp::internal::kFinalFilename + "]");
        ::easyloggingpp::internal::fileNotOpenedErrorDisplayed = true;
      } else {
        ::easyloggingpp::internal::logFile->close();
      }
    }
    // Date format
    ::easyloggingpp::internal::updateDateFormat();
    // Username and host
    ::easyloggingpp::internal::user = ::easyloggingpp::internal::getUsername();
    ::easyloggingpp::internal::host = ::easyloggingpp::internal::getHostname();
    // Different log levels
#if _DEBUG_LOG
     logTypes.push_back(LogType("DEBUG", ::easyloggingpp::configuration::DEBUG_LOG_FORMAT, _DEBUG_LOGS_TO_STANDARD_OUTPUT, _DEBUG_LOGS_TO_FILE));
#endif //_DEBUG_LOG
#if _INFO_LOG
     logTypes.push_back(LogType("INFO", ::easyloggingpp::configuration::INFO_LOG_FORMAT, _INFO_LOGS_TO_STANDARD_OUTPUT, _INFO_LOGS_TO_FILE));
#endif //_INFO_LOG
#if _WARNING_LOG
     logTypes.push_back(LogType("WARNING", ::easyloggingpp::configuration::WARNING_LOG_FORMAT, _WARNING_LOGS_TO_STANDARD_OUTPUT, _WARNING_LOGS_TO_FILE));
#endif //_WARNING_LOG
#if _ERROR_LOG
     logTypes.push_back(LogType("ERROR", ::easyloggingpp::configuration::ERROR_LOG_FORMAT, _ERROR_LOGS_TO_STANDARD_OUTPUT, _ERROR_LOGS_TO_FILE));
#endif //_ERROR_LOG
#if _FATAL_LOG
     logTypes.push_back(LogType("FATAL", ::easyloggingpp::configuration::FATAL_LOG_FORMAT, _FATAL_LOGS_TO_STANDARD_OUTPUT, _FATAL_LOGS_TO_FILE));
#endif //_FATAL_LOG
#if _PERFORMANCE_LOG
     logTypes.push_back(LogType("PERFORMANCE", ::easyloggingpp::configuration::PERFORMANCE_LOG_FORMAT, _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT, _PERFORMANCE_LOGS_TO_FILE));
#endif //_PERFORMANCE_LOG
#if _HINT_LOG
     logTypes.push_back(LogType("HINT", ::easyloggingpp::configuration::HINT_LOG_FORMAT, _HINT_TO_STANDARD_OUTPUT, _HINT_TO_FILE));
#endif //_HINT_LOG
#if _STATUS_LOG
     logTypes.push_back(LogType("STATUS", ::easyloggingpp::configuration::STATUS_LOG_FORMAT, _STATUS_TO_STANDARD_OUTPUT, _STATUS_TO_FILE));
#endif //_STATUS_LOG
#if _VERBOSE_LOG
     logTypes.push_back(LogType("VERBOSE", ::easyloggingpp::configuration::VERBOSE_LOG_FORMAT, _VERBOSE_LOGS_TO_STANDARD_OUTPUT, _VERBOSE_LOGS_TO_FILE));
#endif //_VERBOSE_LOG
#if _QA_LOG
     logTypes.push_back(LogType("QA", ::easyloggingpp::configuration::QA_LOG_FORMAT, _QA_LOGS_TO_STANDARD_OUTPUT, _QA_LOGS_TO_FILE));
#endif //_QA_LOG
     ::easyloggingpp::internal::loggerInitialized = true;
   }
}

static inline void writeLog(void) {
  if ((::easyloggingpp::internal::logStream) && (::easyloggingpp::internal::toStandardOutput)) {
    std::cout << ::easyloggingpp::internal::logStream->str();
  }
  if ((!::easyloggingpp::internal::fileNotOpenedErrorDisplayed)
   && (::easyloggingpp::internal::logStream)
   && (::easyloggingpp::internal::logFile)
   && (::easyloggingpp::internal::toFile)) {
    ::easyloggingpp::internal::logFile->open(::easyloggingpp::internal::kFinalFilename.c_str(), std::ofstream::out | std::ofstream::app);
    (*::easyloggingpp::internal::logFile) << ::easyloggingpp::internal::logStream->str();
    ::easyloggingpp::internal::logFile->close();
  }
  ::easyloggingpp::internal::cleanStream();
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
  ::easyloggingpp::internal::logFormat = format;
  ::easyloggingpp::internal::showDateTime = format.find("%datetime") != std::string::npos;
  if (!::easyloggingpp::internal::showDateTime) {
    ::easyloggingpp::internal::showDate = (format.find("%date") != std::string::npos);
    ::easyloggingpp::internal::showTime = (format.find("%time") != std::string::npos);
  }
  ::easyloggingpp::internal::showLocation = format.find("%loc") != std::string::npos;
  ::easyloggingpp::internal::updateDateFormat();
}

static void determineLogFormat(const std::string& type) {
  for (std::list< ::easyloggingpp::internal::LogType >::iterator it = logTypes.begin();
       it != logTypes.end();
       ++it) {
    if (type == it->name) {
      ::easyloggingpp::internal::determineCommonLogFormat(it->format);
      ::easyloggingpp::internal::toStandardOutput = it->toStandardOutput;
      ::easyloggingpp::internal::toFile = it->toFile;
      return;
    }
  }
}

static void buildFormat(const char* func, const char* file, const unsigned long int line, const std::string& type, int verboseLevel = -1) {
  ::easyloggingpp::internal::init();
  ::easyloggingpp::internal::determineLogFormat(type);
  ::easyloggingpp::internal::updateFormatValue("%level", type, ::easyloggingpp::internal::logFormat);
#if _VERBOSE_LOG
  if (verboseLevel != -1) {
    ::easyloggingpp::internal::tempStream << verboseLevel;
    ::easyloggingpp::internal::updateFormatValue("%vlevel", ::easyloggingpp::internal::tempStream.str(), ::easyloggingpp::internal::logFormat);
    ::easyloggingpp::internal::tempStream.str("");
  }
#endif //_VERBOSE_LOG
  if (::easyloggingpp::internal::showDateTime) {
    ::easyloggingpp::internal::updateFormatValue("%datetime", ::easyloggingpp::internal::getDateTime(), ::easyloggingpp::internal::logFormat);
  } else if (::easyloggingpp::internal::showDate) {
    ::easyloggingpp::internal::updateFormatValue("%date", ::easyloggingpp::internal::getDateTime(), ::easyloggingpp::internal::logFormat);
  } else if (::easyloggingpp::internal::showTime) {
    ::easyloggingpp::internal::updateFormatValue("%time", ::easyloggingpp::internal::getDateTime(), ::easyloggingpp::internal::logFormat);
  }
  ::easyloggingpp::internal::updateFormatValue("%func", std::string(func), ::easyloggingpp::internal::logFormat);
  if (::easyloggingpp::internal::showLocation) {
    ::easyloggingpp::internal::tempStream << file << ":" << line;
    ::easyloggingpp::internal::updateFormatValue("%loc", ::easyloggingpp::internal::tempStream.str(), ::easyloggingpp::internal::logFormat);
  }
  ::easyloggingpp::internal::updateFormatValue("%user", ::easyloggingpp::internal::user, ::easyloggingpp::internal::logFormat);
  ::easyloggingpp::internal::updateFormatValue("%host", ::easyloggingpp::internal::host, ::easyloggingpp::internal::logFormat);
  ::easyloggingpp::internal::updateFormatValue("%log", ::easyloggingpp::internal::tempStream2.str(), ::easyloggingpp::internal::logFormat);
  (*::easyloggingpp::internal::logStream) << logFormat;
}

//
// Logging macros
//
#define WRITE_LOG(type, log)\
  ::easyloggingpp::internal::tempStream2 << log;\
  ::easyloggingpp::internal::buildFormat(__func__, __FILE__, __LINE__, std::string(type));\
  ::easyloggingpp::internal::writeLog();

#define WRITE_VLOG(level, log)\
  if (::easyloggingpp::internal::verboseLevel >= level) {\
    ::easyloggingpp::internal::tempStream2 << log;\
    ::easyloggingpp::internal::buildFormat(__func__, __FILE__, __LINE__, std::string("VERBOSE"), level);\
    ::easyloggingpp::internal::writeLog();\
  }

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
    #define TIME_OUTPUT "Executed [" << __func__ << "] in [~ " << ::easyloggingpp::internal::formatSeconds(difftime(functionEndTime,functionStartTime)) << "]"
    #define FUNC_SUB_COMMON_START { if (::easyloggingpp::configuration::SHOW_START_FUNCTION_LOG) { PERFORMANCE(START_FUNCTION_LOG) } time_t functionStartTime, functionEndTime; time(&functionStartTime);
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

  #if _VERBOSE_LOG
    #define VERBOSE(level, logMessage) WRITE_VLOG(level, logMessage)
    #define VERBOSE_IF(condition, level, logMessage) if (condition) { VERBOSE(level, logMessage); }
  #else
    #define VERBOSE(x, y)
    #define VERBOSE_IF(x, y, z)
  #endif //_VERBOSE_LOG

  #if _QA_LOG
    #define QA(logMessage) WRITE_LOG("QA",logMessage)
    #define QA_IF(condition, logMessage) if (condition) { QA(logMessage); }
  #else
    #define QA(x)
    #define QA_IF(x, y)
  #endif //_QA_LOG
} // namespace internal
namespace helper {
  static std::string readLog(void) {
   std::stringstream ss;
   if (::easyloggingpp::configuration::SAVE_TO_FILE) {
     std::ifstream logFileReader(::easyloggingpp::internal::kFinalFilename.c_str(), std::ifstream::in);
     if (logFileReader.is_open()) {
       std::string line;
       while (logFileReader.good()) {
         std::getline(logFileReader, line);
         ss << line << std::endl;
       }
       logFileReader.close();
     } else {
       ss << "Error opening log file [" << ::easyloggingpp::internal::kFinalFilename << "]";
     }
   } else {
     ss << "Logs are not being saved to file!";
   }
  return ss.str();
  }
} // namespace helper
} // namespace easyloggingpp
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
  #define VERBOSE(x, y)
  #define QA(x)
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
  #define VERBOSE_IF(x, y, z)
  #define QA_IF(x, y)
  // Miscellaneous
  #define _START_EASYLOGGINGPP(x, y)
  #define _END_EASYLOGGINGPP
  // Helper functions
  #include <string>
  namespace easyloggingpp {
    namespace helper {
      std::string readLog() {
        return "";
      }
    } // namespace helper
  } // namespace easyloggingpp
#endif //((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))
#endif //EASYLOGGINGPP_H
