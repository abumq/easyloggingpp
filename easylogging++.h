///////////////////////////////////////////////////////////////////////////
//                                                                       //
// easylogging++.h - Core of EasyLogging++                               //
//   EasyLogging++ v4.10                                                 //
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
#include <cctype>
#if _WINDOWS
 #include <direct.h> //digital mars compiler
 #include <windows.h>
#endif //_WINDOWS
#if _LINUX || _MAC
 #include <sys/stat.h>
 #include <sys/time.h>
#endif //_LINUX || _MAC
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

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
//   %datetime    |   Both date and time of log
//   %date        |   Only date
//   %time        |   Only time
//   %user        |   User running the application
//   %host        |   Host/computer name the application is running on
//   %func        |   Function of logging
//   %loc         |   Filename and line number of logging
//   %log         |   The actual log message
//   %vlevel      |   Verbose level (only application for VERBOSE logs)
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
//   Path is set in different configuration below.
const std::string    LOG_FILENAME             =    "invisible-handcuffs.log";


// CUSTOM_LOG_FILE_LOCATION
//   Path where log file should be saved. Configuration below (USE_CUSTOM_LOCATION)
//   must be set to true in order for this to take affect.
//   NOTES
//    * This location path should end with slash ( '/' for linux and '\' for windows)
//    * This has to be absolute path. Relative paths will not work
//   Recommendation: Set value
const std::string    CUSTOM_LOG_FILE_LOCATION =    "/home/mkhan/Logs/";


// USE_CUSTOM_LOCATION
//   If this is true, logs will be saved to location set in configuration above
//   (CUSTOM_LOG_FILE_LOCATION). Default log location is application run path.
//   Recommendation: true
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
#endif //!defined(__FILE__)
#if !defined(__LINE__)
 #define __LINE__ ""
#endif //!defined(__LINE__)
// Determine appropriate function macro according to current compiler
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
 #define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
 #define __func__ __PRETTY_FUNCTION__
#else
 #define __func__ ""
#endif //defined(_MSC_VER) && (_MSC_VER >= 1020)

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
                                      int verboseLevel = -1;                                                \
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
  static const char* versionNumber = "4.10";
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
static const short kDateBufferSize = 25;
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
#if _VERBOSE_LOG
extern int verboseLevel;
#endif //_VERBOSE_LOG

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

// Represents all the log types in current context
extern std::vector< ::easyloggingpp::internal::LogType > registeredLogTypes;

// Represent a counter
class Counter {
public:
  explicit Counter(void) :
    filename(""),
    lineNumber(0),
    position(0) {}
  explicit Counter(const char* filename_,
                   unsigned long int lineNumber_) :
                     filename(filename_),
                     lineNumber(lineNumber_),
                     position(0) {}
  bool operator==(const Counter& other) {
    return ((this->filename == other.filename) &&
            (this->lineNumber == other.lineNumber));
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

// Represets a temporary counter used to do lookups. This is defined so that
// temporary variables are not defined in every iteration. We just reset the
// location of this temporary counter and look it up.
extern ::easyloggingpp::internal::Counter tempCounter;

// Represents list of all registered counters
extern std::vector < ::easyloggingpp::internal::Counter > registeredCounters;

// Internal message from EasyLogging++. This is used as less number of times
// as possible to minimize annoying outputs.
static inline void internalMessage(const std::string& message) {
    std::cout << std::endl << "[EasyLogging++] " << message << std::endl << std::endl;
}

// Determines the arguments used by EasyLogging++ and store them into static and extern
// symbols where applicable.
// Specifically, looks for '--v=X' or '--verbose' arguments, where X is a digit between
// 0 and 9 and store the digit value into verboseLevel. The max verbose level is 9
// and this set when '--verbose' argument is provided. Priority is given to '--v=X' arguments
static void setAppArgs(int argc, char** argv) {
  while (argc-- > 0) {
#if _VERBOSE_LOG
    const int kMaxVerboseLevel = 9;
    // Look for --v=X argument
    if ((strlen(argv[argc]) >= 5) &&
        (argv[argc][0] == '-') &&
        (argv[argc][1] == '-') &&
        (argv[argc][2] == 'v') &&
        (argv[argc][3] == '=') &&
        (isdigit(argv[argc][4]))) {
      // Current argument is --v=X
      // where X is a digit between 0-9
      ::easyloggingpp::internal::verboseLevel = atoi(argv[argc] + 4);
    }
    // Look for --verbose argument
    else if ((strlen(argv[argc]) == 9) &&
             (argv[argc][0] == '-') &&
             (argv[argc][1] == '-') &&
             (argv[argc][2] == 'v') &&
             (argv[argc][3] == 'e') &&
             (argv[argc][4] == 'r') &&
             (argv[argc][5] == 'b') &&
             (argv[argc][6] == 'o') &&
             (argv[argc][7] == 's') &&
             (argv[argc][8] == 'e')) {
      ::easyloggingpp::internal::verboseLevel = kMaxVerboseLevel;
    }
#endif //_VERBOSE_LOG
  }
}

static void setAppArgs(int argc, const char** argv) {
  char** args = const_cast<char**>(argv);
  ::easyloggingpp::internal::setAppArgs(argc, args);
}

// Determines if log path exists or not.
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

// Creates log path with read, write and execute permissions for
// all users except for 'no-read' for 'others'.
static void createLogPath(void) {
#if _WINDOWS || _LINUX || _MAC
  if ((::easyloggingpp::configuration::USE_CUSTOM_LOCATION) &&
      (::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.size() > 0) &&
      (!::easyloggingpp::internal::logPathExist())) {
    int status = -1;
 #if _WINDOWS
    const char* pathDelimiter = "\\";
 #elif _LINUX || _MAC
    const char* pathDelimiter = "/";
 #endif //_WINDOWS
    std::string fullPathToBuild =
          ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION[0] == '/' ?
            pathDelimiter :
            "";
    char* currentPath = const_cast<char*>(::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str());
    currentPath = strtok(currentPath,
                         pathDelimiter);
    while (currentPath != NULL) {
      fullPathToBuild = fullPathToBuild + currentPath + pathDelimiter;
 #if _WINDOWS
      status = _mkdir(fullPathToBuild.c_str());
 #elif _LINUX || _MAC
      status = mkdir(fullPathToBuild.c_str(),
                     S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH); /* rwx,rwx,wx */
 #endif //_WINDOWS
      currentPath = strtok(NULL, pathDelimiter);
    }
    if (status == -1) {
      ::easyloggingpp::internal::internalMessage("Unable to create log path [" + ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION + "]");
    }
  }
#endif //_WINDOWS || _LINUX || _MAC
}

// Gets current date and time with milliseconds.
static std::string getDateTime(void) {
  if (!(::easyloggingpp::internal::showDateTime ||
        ::easyloggingpp::internal::showDate ||
        ::easyloggingpp::internal::showTime))
    return "";
#if _WINDOWS
  time_t currTime;
  time(&currTime);
#elif _LINUX || _MAC
  timeval currTime;
  gettimeofday(&currTime, NULL);
  int milliSeconds = 0;
  if ((::easyloggingpp::internal::showDateTime) ||
      (::easyloggingpp::internal::showTime)) {
    milliSeconds = currTime.tv_usec / 1000;
  }
#endif //_WINDOWS
  struct tm * timeInfo;
#if _WINDOWS
  timeInfo = localtime(&currTime);
#elif _LINUX || _MAC
  timeInfo = localtime(&currTime.tv_sec);
#endif //_WINDOWS
  strftime(::easyloggingpp::internal::dateBuffer,
           ::easyloggingpp::internal::kDateBufferSize,
           ::easyloggingpp::internal::dateFormat, timeInfo);
#if _LINUX || _MAC
  if ((::easyloggingpp::internal::showDateTime) ||
      (::easyloggingpp::internal::showTime)) {
    sprintf(::easyloggingpp::internal::dateBuffer,
            "%s.%d",
            ::easyloggingpp::internal::dateBuffer,
            milliSeconds);
  }
#endif //_LINUX || _MAC
  return std::string(::easyloggingpp::internal::dateBuffer);
}

// Runs command on terminal and returns the output.
// This is applicable only on linux and mac, for all other OS, an empty string is returned.
static std::string getBashOutput(const char* command) {
#if _LINUX || _MAC
  FILE* proc = popen(command, "r");
  if (proc != NULL) {
    const short hBuffMaxSize = 20;
    char hBuff[hBuffMaxSize];
    fgets(hBuff, hBuffMaxSize, proc);
    pclose(proc);
    short actualHBuffSize = strlen(hBuff);
    if (actualHBuffSize > 0) {
      if (hBuff[actualHBuffSize - 1] == '\n') {
        hBuff[actualHBuffSize - 1] = '\0';
      }
      return std::string(hBuff);
    }
    return "";
  } else {
    return "";
  }
#else
    return "";
#endif
}

// Gets current username.
static std::string getUsername(void) {
#if _WINDOWS
  char* username = getenv("USERNAME");
#elif _LINUX || _MAC
  char* username = getenv("USER");
#endif //_WINDOWS
  if ((username == NULL) || ((strcmp(username, "") == 0))) {
    // No username found by environment variable
    // Try harder by using bash command 'whoami' if on linux or mac
    return ::easyloggingpp::internal::getBashOutput("whoami");
  } else {
    return std::string(username);
  }
}

// Gets current host name or computer name.
static std::string getHostname(void) {
#if _WINDOWS
  char* hostname = getenv("COMPUTERNAME");
#elif _LINUX || _MAC
  char* hostname = getenv("HOSTNAME");
#endif //_WINDOWS
  if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
    // No host name found by environment variable
    // Try harder by using bash command 'hostname' if on linux or mac
    std::string strHostname = easyloggingpp::internal::getBashOutput("hostname");
    if (strHostname == "") {
      // Still nothing found, return 'unknown-host'
      return std::string("unknown-host");
    } else {
      return strHostname;
    }
  } else {
    return std::string(hostname);
  }
}

// Clean all the streams.
static inline void cleanStream(void) {
  ::easyloggingpp::internal::tempStream.str("");
  ::easyloggingpp::internal::tempStream2.str("");
  if (::easyloggingpp::internal::logStream) {
    ::easyloggingpp::internal::logStream->str("");
  }
}

// Release all the memory used by EasyLogging++.
static inline void releaseMemory(void) {
  if (::easyloggingpp::internal::loggerInitialized) {
    ::easyloggingpp::internal::cleanStream();
    if (::easyloggingpp::internal::logFile) {
      delete ::easyloggingpp::internal::logFile;
      ::easyloggingpp::internal::logFile = NULL;
    }
    if (::easyloggingpp::internal::logStream) {
      delete ::easyloggingpp::internal::logStream;
      ::easyloggingpp::internal::logStream = NULL;
    }
    ::easyloggingpp::internal::loggerInitialized = false;
  }
}

// Determine what is being shown for date/time and update dateFormat symbol accordingly.
static void updateDateFormat(void) {
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

// Initialize logger, this is where all the memories are allocated and uses loggerInitialized
// symbol to determine whether or not to allocate memory. This function also looks at high
// level configurations like SHOW_STD_OUTPUT and SAVE_TO_FILE and allocate memory to whats
// needed.
static void init(void) {
  if (!::easyloggingpp::internal::loggerInitialized) {
    // Logger
    ::easyloggingpp::internal::logStream = new std::stringstream();
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
      if ((!::easyloggingpp::internal::fileNotOpenedErrorDisplayed) &&
          (!::easyloggingpp::internal::logFile->is_open())) {
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
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "DEBUG",
        ::easyloggingpp::configuration::DEBUG_LOG_FORMAT,
        _DEBUG_LOGS_TO_STANDARD_OUTPUT,
        _DEBUG_LOGS_TO_FILE
      )
    );
#endif //_DEBUG_LOG
#if _INFO_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "INFO",
        ::easyloggingpp::configuration::INFO_LOG_FORMAT,
        _INFO_LOGS_TO_STANDARD_OUTPUT,
        _INFO_LOGS_TO_FILE
      )
    );
#endif //_INFO_LOG
#if _WARNING_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "WARNING",
        ::easyloggingpp::configuration::WARNING_LOG_FORMAT,
        _WARNING_LOGS_TO_STANDARD_OUTPUT,
        _WARNING_LOGS_TO_FILE
      )
    );
#endif //_WARNING_LOG
#if _ERROR_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "ERROR",
        ::easyloggingpp::configuration::ERROR_LOG_FORMAT,
        _ERROR_LOGS_TO_STANDARD_OUTPUT,
        _ERROR_LOGS_TO_FILE
      )
    );
#endif //_ERROR_LOG
#if _FATAL_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "FATAL",
        ::easyloggingpp::configuration::FATAL_LOG_FORMAT,
        _FATAL_LOGS_TO_STANDARD_OUTPUT,
        _FATAL_LOGS_TO_FILE
      )
    );
#endif //_FATAL_LOG
#if _PERFORMANCE_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "PERFORMANCE",
        ::easyloggingpp::configuration::PERFORMANCE_LOG_FORMAT,
        _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT,
        _PERFORMANCE_LOGS_TO_FILE
      )
    );
#endif //_PERFORMANCE_LOG
#if _HINT_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "HINT",
        ::easyloggingpp::configuration::HINT_LOG_FORMAT,
        _HINT_TO_STANDARD_OUTPUT,
        _HINT_TO_FILE
      )
    );
#endif //_HINT_LOG
#if _STATUS_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "STATUS",
        ::easyloggingpp::configuration::STATUS_LOG_FORMAT,
        _STATUS_TO_STANDARD_OUTPUT,
        _STATUS_TO_FILE
      )
    );
#endif //_STATUS_LOG
#if _VERBOSE_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "VERBOSE",
        ::easyloggingpp::configuration::VERBOSE_LOG_FORMAT,
        _VERBOSE_LOGS_TO_STANDARD_OUTPUT,
        _VERBOSE_LOGS_TO_FILE
      )
    );
#endif //_VERBOSE_LOG
#if _QA_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "QA",
        ::easyloggingpp::configuration::QA_LOG_FORMAT,
        _QA_LOGS_TO_STANDARD_OUTPUT,
        _QA_LOGS_TO_FILE
      )
    );
#endif //_QA_LOG
     ::easyloggingpp::internal::loggerInitialized = true;
   }
}

// Writes log safely after checking symbols availablility.
static void writeLog(void) {
  if ((::easyloggingpp::configuration::SHOW_STD_OUTPUT) &&
      (::easyloggingpp::internal::logStream) &&
      (::easyloggingpp::internal::toStandardOutput)) {
    std::cout << ::easyloggingpp::internal::logStream->str();
  }
  if ((::easyloggingpp::configuration::SAVE_TO_FILE) &&
      (!::easyloggingpp::internal::fileNotOpenedErrorDisplayed) &&
      (::easyloggingpp::internal::logStream) &&
      (::easyloggingpp::internal::logFile) &&
      (::easyloggingpp::internal::toFile)) {
    ::easyloggingpp::internal::logFile->open(::easyloggingpp::internal::kFinalFilename.c_str(),
                                             std::ofstream::out | std::ofstream::app);
    (*::easyloggingpp::internal::logFile) << ::easyloggingpp::internal::logStream->str();
    ::easyloggingpp::internal::logFile->close();
  }
  ::easyloggingpp::internal::cleanStream();
}

// Updates the format specifier to value in log format
// This is used to build log for writing to standard output or to file.
static void updateFormatValue(const std::string& formatSpecifier, const std::string& value, std::string& currentFormat) {
  size_t foundAt = -1;
  while ((foundAt = currentFormat.find(
            formatSpecifier,
            foundAt + 1)
         ) != std::string::npos){
    if (currentFormat[foundAt > 0 ? foundAt - 1 : 0] == 'E') {
      currentFormat.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
      foundAt++;
    } else {
      currentFormat = currentFormat.replace(foundAt, formatSpecifier.size(), value);
      continue;
    }
  }
}

// Determines format for format specifiers common across all the log formats.
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

// Iterates through log types andd find the one matching with current type
static void determineLogFormat(const std::string& type) {
  std::vector< ::easyloggingpp::internal::LogType >::const_iterator it(
    std::find(::easyloggingpp::internal::registeredLogTypes.begin(),
         ::easyloggingpp::internal::registeredLogTypes.end(),
         type)
  );
  if (it != ::easyloggingpp::internal::registeredLogTypes.end()) {
    ::easyloggingpp::internal::determineCommonLogFormat(it->format);
    ::easyloggingpp::internal::toStandardOutput = it->toStandardOutput;
    ::easyloggingpp::internal::toFile = it->toFile;
    return;
  }
}

// Builds log format. This function is entry point of writing log.
static void buildFormat(const char* func, const char* file, const unsigned long int line, const std::string& type, int verboseLevel = -1) {
  ::easyloggingpp::internal::init();
  ::easyloggingpp::internal::determineLogFormat(type);
  ::easyloggingpp::internal::updateFormatValue("%level",
                                               type,
                                               ::easyloggingpp::internal::logFormat);
#if _VERBOSE_LOG
  if (verboseLevel != -1) {
    ::easyloggingpp::internal::tempStream << verboseLevel;
    ::easyloggingpp::internal::updateFormatValue("%vlevel",
                                                 ::easyloggingpp::internal::tempStream.str(),
                                                 ::easyloggingpp::internal::logFormat);
    ::easyloggingpp::internal::tempStream.str("");
  }
#endif //_VERBOSE_LOG
  if (::easyloggingpp::internal::showDateTime) {
    ::easyloggingpp::internal::updateFormatValue("%datetime",
                                                 ::easyloggingpp::internal::getDateTime(),
                                                 ::easyloggingpp::internal::logFormat);
  } else if (::easyloggingpp::internal::showDate) {
    ::easyloggingpp::internal::updateFormatValue("%date",
                                                 ::easyloggingpp::internal::getDateTime(),
                                                 ::easyloggingpp::internal::logFormat);
  } else if (::easyloggingpp::internal::showTime) {
    ::easyloggingpp::internal::updateFormatValue("%time",
                                                 ::easyloggingpp::internal::getDateTime(),
                                                 ::easyloggingpp::internal::logFormat);
  }
  ::easyloggingpp::internal::updateFormatValue("%func",
                                               std::string(func),
                                               ::easyloggingpp::internal::logFormat);
  if (::easyloggingpp::internal::showLocation) {
    ::easyloggingpp::internal::tempStream << file << ":" << line;
    ::easyloggingpp::internal::updateFormatValue("%loc",
                                                 ::easyloggingpp::internal::tempStream.str(),
                                                 ::easyloggingpp::internal::logFormat);
  }
  ::easyloggingpp::internal::updateFormatValue("%user",
                                               ::easyloggingpp::internal::user,
                                               ::easyloggingpp::internal::logFormat);
  ::easyloggingpp::internal::updateFormatValue("%host",
                                               ::easyloggingpp::internal::host,
                                               ::easyloggingpp::internal::logFormat);
  ::easyloggingpp::internal::updateFormatValue("%log",
                                               ::easyloggingpp::internal::tempStream2.str(),
                                               ::easyloggingpp::internal::logFormat);
  if (::easyloggingpp::internal::logStream) {
    (*::easyloggingpp::internal::logStream) << logFormat;
  }
}

// Registers the counter for current line and file
// Note: This can be made better in terms of performance. At the moment this is called
// with every counter log which is not good because this means it looks for counter
// with every iteration. Additionally, this is bad in a way because this creates
static void registerCounter(const ::easyloggingpp::internal::Counter& counter) {
  std::vector< ::easyloggingpp::internal::Counter >::const_iterator it(
      std::find(::easyloggingpp::internal::registeredCounters.begin(),
                ::easyloggingpp::internal::registeredCounters.end(),
                counter));
  if (it == ::easyloggingpp::internal::registeredCounters.end()) {
    ::easyloggingpp::internal::registeredCounters.push_back(counter);
  }
}

// Resets the counter when it reaches its limit to prevent any failure
// since internal counter (position) uses int for data type.
static void resetCounter(std::vector< ::easyloggingpp::internal::Counter >::iterator& it, int n) {
  if (it->position >= 5000) {
    it->position = (n >= 1 ? 5000 % n : 0);
  }
}

// Validates the counter to see if it is valid to write the log for current iteration (n)
// This also registers and resets the counter position accordingly.
// This has a lot of space of improvement. It looks up for the counter with every iteration
static bool validateCounter(const char* filename, unsigned long int lineNumber, int n) {
  ::easyloggingpp::internal::tempCounter.resetLocation(filename, lineNumber);
  ::easyloggingpp::internal::registerCounter(::easyloggingpp::internal::tempCounter);
  bool result = false;
  std::vector< ::easyloggingpp::internal::Counter >::iterator it(
    std::find(::easyloggingpp::internal::registeredCounters.begin(),
              ::easyloggingpp::internal::registeredCounters.end(),
              ::easyloggingpp::internal::tempCounter));
  if (it != ::easyloggingpp::internal::registeredCounters.end()) {
    if (n >= 1 && it->position != 0 && it->position % n == 0) {
      result = true;
    }
    ::easyloggingpp::internal::resetCounter(it, n);
    ++it->position;
  }
  return result;
}

//
// Logging macros
//
#define WRITE_LOG(type, log)                                                        \
  ::easyloggingpp::internal::tempStream2 << log;                                    \
  ::easyloggingpp::internal::buildFormat(__func__,                                  \
                                         __FILE__,                                  \
                                         __LINE__,                                  \
                                         std::string(type));                        \
  ::easyloggingpp::internal::writeLog();

#define WRITE_VLOG(level, log)                                                      \
  if (::easyloggingpp::internal::verboseLevel >= level) {                           \
    ::easyloggingpp::internal::tempStream2 << log;                                  \
    ::easyloggingpp::internal::buildFormat(__func__,                                \
                                           __FILE__,                                \
                                           __LINE__,                                \
                                           std::string("VERBOSE"),                  \
                                           level);                                  \
    ::easyloggingpp::internal::writeLog();                                          \
  }

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
  #endif //_DEBUG_LOG

  #if _INFO_LOG
    #define INFO(logMessage) WRITE_LOG("INFO",logMessage)
    #define INFO_IF(condition, logMessage) if (condition) { INFO(logMessage); }
    #define INFO_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("INFO", n, logMessage)
  #else
    #define INFO(x)
    #define INFO_IF(x, y)
    #define INFO_EVERY_N(x, y)
  #endif //_INFO_LOG

  #if _WARNING_LOG
    #define WARNING(logMessage) WRITE_LOG("WARNING",logMessage)
    #define WARNING_IF(condition, logMessage) if (condition) { WARNING(logMessage); }
    #define WARNING_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("WARNING", n, logMessage)
  #else
    #define WARNING(x)
    #define WARNING_IF(x, y)
    #define WARNING_EVERY_N(x, y)
  #endif //_WARNING_LOG

  #if _ERROR_LOG
    #define ERROR(logMessage) WRITE_LOG("ERROR",logMessage)
    #define ERROR_IF(condition, logMessage) if (condition) { ERROR(logMessage); }
    #define ERROR_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("ERROR", n, logMessage)
  #else
    #define ERROR(x)
    #define ERROR_IF(x, y)
    #define ERROR_EVERY_N(x, y)
  #endif //_ERROR_LOG

  #if _FATAL_LOG
    #define FATAL(logMessage) WRITE_LOG("FATAL",logMessage)
    #define FATAL_IF(condition, logMessage) if (condition) { FATAL(logMessage); }
    #define FATAL_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("FATAL", n, logMessage)
  #else
    #define FATAL(x)
    #define FATAL_IF(x, y)
    #define FATAL_EVERY_N(x, y)
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
    #define END_FUNC FUNC_SUB_COMMON_END }
    #define RETURN(expr) FUNC_SUB_COMMON_END return expr;
    #define MAIN(argc, argv) FUNC(int, main, (argc, argv))
    #define END_MAIN _END_EASYLOGGINGPP END_FUNC
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
  #endif //_PERFORMANCE_LOG

  #if _HINT_LOG
    #define HINT(logMessage) WRITE_LOG("HINT",logMessage)
    #define HINT_IF(condition, logMessage) if (condition) { HINT(logMessage); }
    #define HINT_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("HINT", n, logMessage)
  #else
    #define HINT(x)
    #define HINT_IF(x, y)
    #define HINT_EVERY_N(x, y)
  #endif //_HINT_LOG

  #if _STATUS_LOG
    #define STATUS(logMessage) WRITE_LOG("STATUS",logMessage)
    #define STATUS_IF(condition, logMessage) if (condition) { STATUS(logMessage); }
    #define STATUS_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("STATUS", n, logMessage)
  #else
    #define STATUS(x)
    #define STATUS_IF(x, y)
    #define STATUS_EVERY_N(x, y)
  #endif //_STATUS_LOG

  #if _VERBOSE_LOG
    #define VERBOSE(level, logMessage) WRITE_VLOG(level, logMessage)
    #define VERBOSE_IF(condition, level, logMessage) if (condition) { VERBOSE(level, logMessage); }
    #define VERBOSE_EVERY_N(n, level, logMessage) WRITE_VLOG_EVERY_N(n, level, logMessage)
  #else
    #define VERBOSE(x, y)
    #define VERBOSE_IF(x, y, z)
    #define VERBOSE_EVERY_N(x, y, z)
  #endif //_VERBOSE_LOG

  #if _QA_LOG
    #define QA(logMessage) WRITE_LOG("QA",logMessage)
    #define QA_IF(condition, logMessage) if (condition) { QA(logMessage); }
    #define QA_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("QA", n, logMessage)
  #else
    #define QA(x)
    #define QA_IF(x, y)
    #define QA_EVERY_N(x, y)
  #endif //_QA_LOG
} // namespace internal
namespace helper {
  // Reads log from current log file an returns standard string
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

// Following namespace is useless and is ONLY there to supress
// warnings of unused symbols. These symbols include conditional
// and helper functions. Please do not use these functions.
namespace unusedwarningsuppresser {
class UnusedWarningSupresser {
private:
  void suppressAll(void) {
     std::string readLogWarningSupress = ::easyloggingpp::helper::readLog();
     const char* argv[1];
     argv[1] = "easylogging++ warning suppresser";
     ::easyloggingpp::internal::setAppArgs(0, argv);
     ::easyloggingpp::internal::buildFormat("suppress",
                                            "suppress",
                                            1,
                                            "suppress");
     ::easyloggingpp::internal::writeLog();
     std::cout << ::easyloggingpp::version::versionNumber;
     ::easyloggingpp::internal::validateCounter("", 0, 0);
  }
};
} // warningsuppresser
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
  #define MAIN(argc, argv) FUNC(int, main, (argc, argv))
  #define END_MAIN END_FUNC
  #define RETURN_MAIN(exit_status) return exit_status;
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
  // Every N
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
    namespace helper {
      static std::string readLog() {
        return "";
      }
    } // namespace helper
  } // namespace easyloggingpp
#endif //((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))
#endif //EASYLOGGINGPP_H
