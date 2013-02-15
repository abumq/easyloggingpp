///////////////////////////////////////////////////////////////////////////
//                                                                       //
// easylogging++.h - Core of EasyLogging++ (requires easylogging++.cc)   //
//                                                                       //
//   EasyLogging++ v5.05                                                 //
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

// _LOGGING_ENABLED specifies whether or not writing logs are enabled.
// If this is set to 0, nothing will be logged. On the contrary, 1 means
// logs are enabled.
#define _LOGGING_ENABLED 1

// Following configurations are for each logging level, each with three
// parts; note: *** refers to log level in each of the following description.
//
// PART 1
// ======
// _ENABLE_***_LOGS specifies whether or not *** logs are enabled.
// This is similar to _LOGGING_ENABLED except the level effected is
// specific to config name only. 1 = enabled; 0 = disabled
//
// PART 2
// ======
// _***_LOGS_TO_STANDARD_OUTPUT specifies whether or not *** logs are enabled
// to be written to standard output. Standard output varies from OS to OS,
// typically it is terminal for linux and command prompt for windows.
// This will only effect corresponding log level.
//
// PART 3
// ======
// _***_LOGS_TO_FILE specifies whether or not *** logs are to be written to
// file. It is recommended to be always 1 i.e, enabled. If you wish some logs
// not be recorded to log file then you proabably want to disable those logs

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
#define _HINT_TO_FILE 1

#define _ENABLE_STATUS 1
#define _STATUS_TO_STANDARD_OUTPUT 1
#define _STATUS_TO_FILE 1

#define _ENABLE_VERBOSE_LOGS 1
#define _VERBOSE_LOGS_TO_STANDARD_OUTPUT 1
#define _VERBOSE_LOGS_TO_FILE 1

#define _ENABLE_QA_LOGS 1
#define _QA_LOGS_TO_STANDARD_OUTPUT 1
#define _QA_LOGS_TO_FILE 1

// Determine whether or not logging is enabled
// Use power of preprocessor directives to determine what to compile
// and what to ignore.
// If you are using g++ and wish to find out how does your program look like
// under the hood, use -E flag of g++ compiler that will expand all the macros
#if ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))

//
// OS evaluation
//
// Windows
#if defined(_WIN32)
 #define _WINDOWS 1
 #define _WINDOWS_32 1
#endif // defined(_WIN32)
#if defined(_WIN64)
 #define _WINDOWS 1
 #define _WINDOWS_64 1
#endif // defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
 #define _LINUX 1
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
 #define _MAC 1
#endif // defined(__APPLE__)

//
// Compiler evaluation
//
// GNU
#if defined(__GNUC__)
  #if defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define _CXX0X 1
  #endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// VC++ (http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx)
#if defined(_MSC_VER)
  #if (_MSC_VER == 1600)
    #define _CXX0X 1
  #elif (_MSC_VER == 1700)
    #define _CXX11 1
  #endif // (_MSC_VER == 1600)
#endif // defined(_MSC_VER)

#define __ENABLE_MACRO_EVALUATION (((_CXX0X || _CXX11)       || \
                                   (defined(QT_CORE_LIB)))   && \
                                   (!(defined(_DISABLE_MUTEX))))
//
// Mutex header evaluation
//
#if (__ENABLE_MACRO_EVALUATION)
  #if (defined(QT_CORE_LIB))
    // Use Qt library QMutex to handle multi-threading application
    #define MUTEX_HEADER <QMutex>
    #define MUTEX_TYPE QMutex
    #define _MUTEX_SPECIFIC_INIT MUTEX_TYPE mutex;
    #define _LOCK_MUTEX ::easyloggingpp::internal::mutex.lock();
    #define _UNLOCK_MUTEX ::easyloggingpp::internal::mutex.unlock();
    #define _USING_MUTEX 1
  #else
    // Use std::mutex
    // We need to be careful here and add few extra checks to make sure we have mutex header available.
    // I think we should do a comparison of C++ standards and make a list of supported pre-processors (macros)
    // for mutex headers for different compilers.
    #define MUTEX_HEADER <mutex>
    #define MUTEX_TYPE std::mutex
    #define _MUTEX_SPECIFIC_INIT MUTEX_TYPE mutex;
    #define _LOCK_MUTEX ::easyloggingpp::internal::mutex.lock();
    #define _UNLOCK_MUTEX ::easyloggingpp::internal::mutex.unlock();
    #define _USING_MUTEX 1
  #endif // (defined(QT_CORE_LIB)
#else
  #define _MUTEX_SPECIFIC_INIT
  #define _LOCK_MUTEX
  #define _UNLOCK_MUTEX
  #define _USING_MUTEX 0
#endif // (__ENABLE_MACRO_EVALUATION)

//
// Includes
//
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#if _WINDOWS
 #include <direct.h> // digital mars compiler
 #include <windows.h>
#endif // _WINDOWS
#if _LINUX || _MAC
 #include <sys/stat.h>
 #include <sys/time.h>
#endif // _LINUX || _MAC
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#if (_USING_MUTEX)
 #include MUTEX_HEADER
#endif // (__USING_MUTEX)

namespace easyloggingpp {
namespace configuration {

// This section contains configurations that are to set by developer.
// These sections can be splitted into two parts;
//
//   * Log formats
//   * Miscellaneous configurations
//
// First part contains all the formatting configuration for each log
// level. Developers are expected to only change the values and not
// data type or constant name.
// Format specifiers used are as following:
//
//  SPECIFIER     |                  DESCRIPTION
// ===============|==================================================
//   %level       |   Log level, e.g, INFO, DEBUG, ERROR etc
//   %datetime    |   Current date and time (while writing log)
//   %date        |   Current date only
//   %time        |   Current time only
//   %user        |   User running the application
//   %host        |   Host/computer name the application is running on
//   %func        |   Function of logging
//   %loc         |   Filename and line number of logging
//   %log         |   The actual log message
//   %vlevel      |   Verbose level (only applicable for VERBOSE logs)
//   \n           |   New line character
//   \t           |   Tab character
//
// Further reading on:
// https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#log-format

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

// Part 2 is miscellaneous configurations

// SHOW_STD_OUTPUT
//   High level configuration to determine whether or not to show log to standard
//   output i.e, terminal or command prompt. If this is set to false, logs will not
//   be shown to standard output regardless of log level setting _***_LOGS_TO_STANDARD_OUTPUT
//   Recommendation: true
const bool           SHOW_STD_OUTPUT          =    true;


// SAVE_TO_FILE
//   Same as SHOW_STD_OUTPUT but for saving to file. If this is false, logs will not
//   be written to file regardless of log level setting _***_LOGS_TO_FILE.
//   Be careful when you set this option to false
//   Recommendation: true
const bool           SAVE_TO_FILE             =    true;


// LOG_FILENAME
//   Filename of log file. This should only be filename and not the whole path.
//   Path is set in different configuration below (CUSTOM_LOG_FILE_LOCATION).
//   If custom location is not used, log will be saved in executable path.
const std::string    LOG_FILENAME             =    "myeasylog.log";


// CUSTOM_LOG_FILE_LOCATION
//   Path where log file should be saved. Configuration below (USE_CUSTOM_LOCATION)
//   must be set to true in order for this to take affect.
//   NOTES
//    * This location path should end with slash ( '/' for linux and '\' for windows)
//    * This has to be absolute path. Relative paths will not work
//   Recommendation: Set value according to your need - Do not leave empty
//   If you do not want to use this set USE_CUSTOM_LOCATION to false instead.
const std::string    CUSTOM_LOG_FILE_LOCATION =    "logs/";


// USE_CUSTOM_LOCATION
//   If this is true, logs will be saved to location set in configuration above
//   (CUSTOM_LOG_FILE_LOCATION). Default log location is application run path.
//   Recommendation: As required
const bool           USE_CUSTOM_LOCATION      =    true;

// SHOW_START_FUNCTION_LOG
//   When using performance logging, this determines whether or not to show
//   when a certain function has started executing.
//   Recommendation: false
const bool           SHOW_START_FUNCTION_LOG  =    false;

} // namespace configuration


//          ***********************************************
//     **   PLEASE DO NOT MODIFY ANY LINE BEYOND THIS POINT   **
//          ***********************************************

//
// Source code location macros
//
#if !defined(__FILE__)
 #define __FILE__ ""
#endif // !defined(__FILE__)
#if !defined(__LINE__)
 #define __LINE__ ""
#endif // !defined(__LINE__)
// Determine appropriate function macro according to current compiler
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
 #define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
 #define __func__ __PRETTY_FUNCTION__
#else
 #define __func__ ""
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)

// Finally determine which log levels are enabled and which are disabled.
// This is determined by _ENABLE_***_LOGS and _DISABLE_***_LOGS macros.
// These macros defined in following section is then used throughout the process
// of logging.
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

#if _VERBOSE_LOG
  #define _VERBOSE_SPECIFIC_INITIALIZATIONS int verboseLevel = -1;
#else
  #define _VERBOSE_SPECIFIC_INITIALIZATIONS
#endif // _VERBOSE_LOG

#if defined(_ALWAYS_CLEAN_LOGS)
  #define _ALWAYS_CLEAN_LOGS_SPECIFIC_INITIALIZATIONS bool alreadyCleanedLogFile = false;
#else
  #define _ALWAYS_CLEAN_LOGS_SPECIFIC_INITIALIZATIONS
#endif // defined(_ALWAYS_CLEAN_LOGS)

// EasyLogging++ uses a lot of extern symbols in order to keep using same values
// to prevent potential memory leaks and to improve performance by not initializing
// variables repeatedly. This include variables like username, hostname, streams
// and list of log types. In order to achieve this, following macro should be used
// once and only once in main.cpp file after all the includes in order to initialize
// extern symbols.
// Candidates for extern symbols are carefully chosen, the rest are static symbols.
#define _INITIALIZE_EASYLOGGINGPP namespace easyloggingpp {                                                 \
                                    namespace internal {                                                    \
                                      bool loggerInitialized = false;                                       \
                                      std::stringstream *logStream = NULL;                                  \
                                      std::ofstream *logFile = NULL;                                        \
                                      std::stringstream tempStream;                                         \
                                      std::stringstream tempStream2;                                        \
                                      std::vector< ::easyloggingpp::internal::LogType > registeredLogTypes; \
                                      ::easyloggingpp::internal::Counter tempCounter;                       \
                                      std::vector< ::easyloggingpp::internal::Counter > registeredCounters; \
                                      bool fileNotOpenedErrorDisplayed = false;                             \
                                      std::string user = "";                                                \
                                      std::string host = "";                                                \
                                      _VERBOSE_SPECIFIC_INITIALIZATIONS                                     \
                                      _ALWAYS_CLEAN_LOGS_SPECIFIC_INITIALIZATIONS                           \
                                      _MUTEX_SPECIFIC_INIT                                                  \
                                    }                                                                       \
                                  }

// When using log levels that require program arguments, for example VERBOSE logs require
// to see what VERBOSE levels to log by looking at --v=X argument or --verbose (for level 9)
// argument, following macro should be used.
#define _START_EASYLOGGINGPP(argc, argv) ::easyloggingpp::internal::setAppArgs(argc, argv);

// When program is exiting, following macro should be used in order to release all the memory
// used by internal symbols.
#define _END_EASYLOGGINGPP ::easyloggingpp::internal::releaseMemory();

namespace version {
  static const char* versionNumber = "5.05";
}

namespace internal {
//
// Static symbols
//
static const std::string kFinalFilename = (::easyloggingpp::configuration::USE_CUSTOM_LOCATION ?
                                           ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION :
                                           "") +
                                           ::easyloggingpp::configuration::LOG_FILENAME;
static bool showDateTime = ::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%datetime") != std::string::npos;
static bool showDate = (!::easyloggingpp::internal::showDateTime) &&
                       (::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%date") != std::string::npos);
static bool showTime = (!::easyloggingpp::internal::showDateTime) &&
                       (::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%time") != std::string::npos);
static bool showLocation = ::easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%loc") != std::string::npos;

static bool toStandardOutput;
static bool toFile;
static const short kDateBufferSize = 30;
static char dateBuffer[kDateBufferSize];
static char dateFormat[kDateBufferSize];
static std::string logFormat = "";
//
// Extern symbols
//
extern std::string user;
extern std::string host;
extern std::stringstream *logStream;
extern std::ofstream *logFile;
extern std::stringstream tempStream;
extern std::stringstream tempStream2;
extern bool loggerInitialized;
extern bool fileNotOpenedErrorDisplayed;
#if defined(_ALWAYS_CLEAN_LOGS)
extern bool alreadyCleanedLogFile;
#endif // defined(_ALWAYS_CLEAN_LOGS)
#if _VERBOSE_LOG
extern int verboseLevel;
#endif // _VERBOSE_LOG
#if _USING_MUTEX
extern MUTEX_TYPE mutex;
#endif // _USING_MUTEX

// Represents log type and configuration such as format and target
class LogType {
public:
  explicit LogType(const std::string& name_,
          const std::string& format_,
          bool toStandardOutput_,
          bool toFile_) :
            name(name_),
            format(format_),
            toStandardOutput(toStandardOutput_),
            toFile(toFile_) {}
  bool operator==(const std::string& name) const {
    return this->name == name;
  }
  bool operator!=(const std::string& name) const {
    return this->name != name;
  }
  std::string name;
  std::string format;
  bool toStandardOutput;
  bool toFile;
};

// Constant iterator for log type
typedef std::vector< ::easyloggingpp::internal::LogType >::const_iterator LogTypeConstIter;

// Represents all the log types in current context
extern std::vector< ::easyloggingpp::internal::LogType > registeredLogTypes;

// Represent a counter
class Counter {
public:
  explicit Counter(void) :
    filename(""),
    lineNumber(0),
    position(1) {}
  explicit Counter(const char* filename_,
                   unsigned long int lineNumber_) :
                     filename(filename_),
                     lineNumber(lineNumber_),
                     position(1) {}
  bool operator==(const Counter& other) {
    return ((this->filename == other.filename) &&
            (this->lineNumber == other.lineNumber));
  }
  bool operator!=(const Counter& other) {
    return ((this->filename != other.filename) &&
            (this->lineNumber != other.lineNumber));
  }
  void resetLocation(const char* filename_,
                     unsigned long int lineNumber_) {
    this->filename = filename_;
    this->lineNumber = lineNumber_;
  }
  const char* filename;
  unsigned long int lineNumber;
  unsigned int position;
};

// Iterator for counter
typedef std::vector< ::easyloggingpp::internal::Counter >::iterator CounterIter;

// Represents list of all registered counters
extern std::vector < ::easyloggingpp::internal::Counter > registeredCounters;

// Represents a temporary counter used to do fast lookups. This is defined so that
// temporary variables are not defined in every iteration. We just reset the
// location of this temporary counter and look it up.
extern ::easyloggingpp::internal::Counter tempCounter;


// Determines the arguments used by EasyLogging++ and store them into static and extern
// symbols where applicable.
// Specifically, looks for '--v=X' or '--verbose' arguments, where X is a digit between
// 0 and 9 and store the digit value into verboseLevel. The max verbose level is 9
// and this set when '--verbose' argument is provided. Priority is given to '--v=X' arguments
extern void setAppArgs(int argc, char** argv);

extern void setAppArgs(int argc, const char** argv);

// Release all the memory used by EasyLogging++.
extern void releaseMemory(void);

// Writes log safely after checking symbols availablility.
extern void writeLog(void);

// Builds log format. This function is entry point of writing log.
extern void buildFormat(const char* func, const char* file, const unsigned long int line, const std::string& type, int verboseLevel = -1);

// Validates the counter to see if it is valid to write the log for current iteration (n)
// This also registers and resets the counter position if neccessary. 
extern bool validateCounter(const char* filename, unsigned long int lineNumber, int n);

//
// Logging macros
//
#define WRITE_LOG(type, log)                                                        \
  _LOCK_MUTEX                                                                       \
  ::easyloggingpp::internal::tempStream2 << log;                                    \
  ::easyloggingpp::internal::buildFormat(__func__,                                  \
                                         __FILE__,                                  \
                                         __LINE__,                                  \
                                         std::string(type));                        \
  ::easyloggingpp::internal::writeLog();                                            \
  _UNLOCK_MUTEX

#define WRITE_VLOG(level, log)                                                      \
  _LOCK_MUTEX                                                                       \
  if (::easyloggingpp::internal::verboseLevel >= level) {                           \
    ::easyloggingpp::internal::tempStream2 << log;                                  \
    ::easyloggingpp::internal::buildFormat(__func__,                                \
                                           __FILE__,                                \
                                           __LINE__,                                \
                                           std::string("VERBOSE"),                  \
                                           level);                                  \
    ::easyloggingpp::internal::writeLog();                                          \
  }                                                                                 \
  _UNLOCK_MUTEX

#define WRITE_LOG_EVERY_N(type, n, log)                                             \
  if (::easyloggingpp::internal::validateCounter(__FILE__,                          \
                                                 __LINE__,                          \
                                                 n)) {                              \
    WRITE_LOG(type, log)                                                            \
  }

#define WRITE_VLOG_EVERY_N(n, level, log)                                           \
  if (::easyloggingpp::internal::validateCounter(__FILE__,                          \
                                                 __LINE__,                          \
                                                 n)) {                              \
    WRITE_VLOG(level, log)                                                          \
  }

  #if _DEBUG_LOG
    #define DEBUG(logMessage) WRITE_LOG("DEBUG",logMessage)
    #define DEBUG_IF(condition, logMessage) if (condition) { DEBUG(logMessage); }
    #define DEBUG_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("DEBUG", n, logMessage)
  #else
    #define DEBUG(x)
    #define DEBUG_IF(x, y)
    #define DEBUG_EVERY_N(x, y)
  #endif // _DEBUG_LOG

  #if _INFO_LOG
    #define INFO(logMessage) WRITE_LOG("INFO",logMessage)
    #define INFO_IF(condition, logMessage) if (condition) { INFO(logMessage); }
    #define INFO_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("INFO", n, logMessage)
  #else
    #define INFO(x)
    #define INFO_IF(x, y)
    #define INFO_EVERY_N(x, y)
  #endif // _INFO_LOG

  #if _WARNING_LOG
    #define WARNING(logMessage) WRITE_LOG("WARNING",logMessage)
    #define WARNING_IF(condition, logMessage) if (condition) { WARNING(logMessage); }
    #define WARNING_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("WARNING", n, logMessage)
  #else
    #define WARNING(x)
    #define WARNING_IF(x, y)
    #define WARNING_EVERY_N(x, y)
  #endif // _WARNING_LOG

  #if _ERROR_LOG
    #define ERROR(logMessage) WRITE_LOG("ERROR",logMessage)
    #define ERROR_IF(condition, logMessage) if (condition) { ERROR(logMessage); }
    #define ERROR_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("ERROR", n, logMessage)
  #else
    #define ERROR(x)
    #define ERROR_IF(x, y)
    #define ERROR_EVERY_N(x, y)
  #endif // _ERROR_LOG

  #if _FATAL_LOG
    #define FATAL(logMessage) WRITE_LOG("FATAL",logMessage)
    #define FATAL_IF(condition, logMessage) if (condition) { FATAL(logMessage); }
    #define FATAL_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("FATAL", n, logMessage)
  #else
    #define FATAL(x)
    #define FATAL_IF(x, y)
    #define FATAL_EVERY_N(x, y)
  #endif // _FATAL_LOG

  #if _PERFORMANCE_LOG
    extern std::string formatSeconds(double secs);
    #define PERFORMANCE(logMessage) WRITE_LOG("PERFORMANCE",logMessage)
    #define PERFORMANCE_IF(condition, logMessage) if (condition) { PERFORMANCE(logMessage); }
    #define PERFORMANCE_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("PERFORMANCE", n, logMessage)
    #define START_FUNCTION_LOG "Executing [" << __func__ << "]"
    #define TIME_OUTPUT "Executed [" << __func__ << "] in [~ " << \
                        ::easyloggingpp::internal::formatSeconds( \
                          difftime(functionEndTime,               \
                                   functionStartTime)             \
                        ) << "]"
    #define FUNC_SUB_COMMON_START { if (::easyloggingpp::configuration::SHOW_START_FUNCTION_LOG) {\
                                      PERFORMANCE(START_FUNCTION_LOG)                             \
                                    }                                                             \
                                    time_t functionStartTime, functionEndTime;                    \
                                    time(&functionStartTime);
    #define FUNC_SUB_COMMON_END time(&functionEndTime); PERFORMANCE(TIME_OUTPUT);
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
    #define END_SUB FUNC_SUB_COMMON_END }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
    #define RETURN(return_value) FUNC_SUB_COMMON_END return return_value;
    #define END_FUNC(return_value) RETURN(return_value) }
    #define MAIN(argc, argv) FUNC(int, main, (argc, argv))
    #define END_MAIN(return_value) _END_EASYLOGGINGPP END_FUNC(return_value)
    #define RETURN_MAIN(exit_status) _END_EASYLOGGINGPP return exit_status;
  #else
    #define PERFORMANCE(x)
    #define PERFORMANCE_IF(x, y)
    #define PERFORMANCE_EVERY_N(x, y)
    #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
    #define END_SUB }
    #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
    #define END_FUNC }
    #define RETURN(expr) return expr;
    #define MAIN(argc, argv) FUNC(int, main, (argc, argv))
    #define END_MAIN _END_EASYLOGGINGPP END_FUNC
    #define RETURN_MAIN(exit_status) _END_EASYLOGGINGPP return exit_status;
  #endif // _PERFORMANCE_LOG

  #if _HINT_LOG
    #define HINT(logMessage) WRITE_LOG("HINT",logMessage)
    #define HINT_IF(condition, logMessage) if (condition) { HINT(logMessage); }
    #define HINT_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("HINT", n, logMessage)
  #else
    #define HINT(x)
    #define HINT_IF(x, y)
    #define HINT_EVERY_N(x, y)
  #endif // _HINT_LOG

  #if _STATUS_LOG
    #define STATUS(logMessage) WRITE_LOG("STATUS",logMessage)
    #define STATUS_IF(condition, logMessage) if (condition) { STATUS(logMessage); }
    #define STATUS_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("STATUS", n, logMessage)
  #else
    #define STATUS(x)
    #define STATUS_IF(x, y)
    #define STATUS_EVERY_N(x, y)
  #endif // _STATUS_LOG

  #if _VERBOSE_LOG
    #define VERBOSE(level, logMessage) WRITE_VLOG(level, logMessage)
    #define VERBOSE_IF(condition, level, logMessage) if (condition) { VERBOSE(level, logMessage); }
    #define VERBOSE_EVERY_N(n, level, logMessage) WRITE_VLOG_EVERY_N(n, level, logMessage)
  #else
    #define VERBOSE(x, y)
    #define VERBOSE_IF(x, y, z)
    #define VERBOSE_EVERY_N(x, y, z)
  #endif // _VERBOSE_LOG

  #if _QA_LOG
    #define QA(logMessage) WRITE_LOG("QA",logMessage)
    #define QA_IF(condition, logMessage) if (condition) { QA(logMessage); }
    #define QA_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("QA", n, logMessage)
  #else
    #define QA(x)
    #define QA_IF(x, y)
    #define QA_EVERY_N(x, y)
  #endif // _QA_LOG
} // namespace internal
namespace helper {
  // Reads log from current log file an returns standard string
  extern std::string readLog(void);
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
  // Performance logs
  #define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
  #define END_SUB }
  #define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
  #define END_FUNC(x) }
  #define RETURN(expr) return expr;
  #define MAIN(argc, argv) FUNC(int, main, (argc, argv))
  #define END_MAIN(x) END_FUNC(x)
  #define RETURN_MAIN(exit_status) return exit_status;
  // Conditional logs
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
  // Interval logs
  #define DEBUG_EVERY_N(x, y)
  #define INFO_EVERY_N(x, y)
  #define WARNING_EVERY_N(x, y)
  #define ERROR_EVERY_N(x, y)
  #define FATAL_EVERY_N(x, y)
  #define PERFORMANCE_EVERY_N(x, y)
  #define HINT_EVERY_N(x, y)
  #define STATUS_EVERY_N(x, y)
  #define VERBOSE_EVERY_N(x, y, z)
  #define QA_EVERY_N(x, y)
  // Miscellaneous
  #define _INITIALIZE_EASYLOGGINGPP
  #define _START_EASYLOGGINGPP(x, y)
  #define _END_EASYLOGGINGPP
  // Helper functions
  #include <string>
  namespace easyloggingpp {
    namespace version {
      static const char* versionNumber = "5.05";
    }
    namespace helper {
      static std::string readLog() {
        return "";
      }
    } // namespace helper
  } // namespace easyloggingpp
#endif // ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))
#endif //EASYLOGGINGPP_H
