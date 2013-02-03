#include "easylogging++.h"

namespace easyloggingpp {
namespace internal {


// Internal message from EasyLogging++. This is used as less number of times
// as possible to minimize annoying outputs.
inline void internalMessage(const std::string& message) {
    std::cout << std::endl << "[EasyLogging++] " << message << std::endl << std::endl;
}

void setAppArgs(int argc, char** argv) {
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
#endif // _VERBOSE_LOG
  }
}

void setAppArgs(int argc, const char** argv) {
  char** args = const_cast<char**>(argv);
  ::easyloggingpp::internal::setAppArgs(argc, args);
}


// Determines if log path exists or not.
bool logPathExist(void) {
#if _WINDOWS
  DWORD fileType = GetFileAttributesA(::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str());
  if (fileType == INVALID_FILE_ATTRIBUTES) {
    return false;
  }
  return (fileType & FILE_ATTRIBUTE_DIRECTORY);
#elif _LINUX || _MAC
  struct stat st;
  return (stat(::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str(), &st) == 0);
#endif // _WINDOWS
}

// Creates log path with read, write and execute permissions for
// all users except for 'no-read' for 'others'.
void createLogPath(void) {
#if _WINDOWS || _LINUX || _MAC
  if ((::easyloggingpp::configuration::USE_CUSTOM_LOCATION) &&
      (::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.size() > 0) &&
      (!::easyloggingpp::internal::logPathExist())) {
    int status = -1;
 #if _WINDOWS
    const char* pathDelimiter = "\\";
 #elif _LINUX || _MAC
    const char* pathDelimiter = "/";
 #endif // _WINDOWS
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
                     S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH); // rwx,rwx,wx
 #endif // _WINDOWS
      if (status == -1) {
        ::easyloggingpp::internal::internalMessage("Unable to create log path [" + fullPathToBuild + "]");
        return;
      }
      currentPath = strtok(NULL, pathDelimiter);
    }
    if (status == -1) {
      ::easyloggingpp::internal::internalMessage("Unable to create log path [" + ::easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION + "]");
    }
  }
#endif // _WINDOWS || _LINUX || _MAC
}

// Gets current date and time with milliseconds.
std::string getDateTime(void) {
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
#endif // _WINDOWS
  struct tm * timeInfo;
#if _WINDOWS
  timeInfo = localtime(&currTime);
#elif _LINUX || _MAC
  timeInfo = localtime(&currTime.tv_sec);
#endif // _WINDOWS
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
#endif // _LINUX || _MAC
  return std::string(::easyloggingpp::internal::dateBuffer);
}

// Runs command on terminal and returns the output.
// This is applicable only on linux and mac, for all other OS, an empty string is returned.
std::string getBashOutput(const char* command) {
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
#endif // _LINUX || _MAC
}

// Gets current username.
std::string getUsername(void) {
#if _WINDOWS
  char* username = getenv("USERNAME");
#elif _LINUX || _MAC
  char* username = getenv("USER");
#endif // _WINDOWS
  if ((username == NULL) || ((strcmp(username, "") == 0))) {
    // No username found by environment variable
    // Try harder by using bash command 'whoami' if on linux or mac
    return ::easyloggingpp::internal::getBashOutput("whoami");
  } else {
    return std::string(username);
  }
}

std::string getHostname(void) {
#if _WINDOWS
  char* hostname = getenv("COMPUTERNAME");
#elif _LINUX || _MAC
  char* hostname = getenv("HOSTNAME");
#endif // _WINDOWS
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

inline void cleanStream(void) {
  ::easyloggingpp::internal::tempStream.str("");
  ::easyloggingpp::internal::tempStream2.str("");
  if (::easyloggingpp::internal::logStream) {
    ::easyloggingpp::internal::logStream->str("");
  }
}


void releaseMemory(void) {
  _LOCK_MUTEX
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
  _UNLOCK_MUTEX
}

void updateDateFormat(void) {
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
void init(void) {
  if (!::easyloggingpp::internal::loggerInitialized) {
    // Logger
    ::easyloggingpp::internal::logStream = new std::stringstream();
    // Path
    ::easyloggingpp::internal::createLogPath();
    // Log file
    if (::easyloggingpp::configuration::SAVE_TO_FILE) {
      std::ios_base::openmode mode = std::ofstream::out | std::ofstream::app;
#if defined(_ALWAYS_CLEAN_LOGS)
      if (!::easyloggingpp::internal::alreadyCleanedLogFile) {
        mode = std::ofstream::out;
        ::easyloggingpp::internal::alreadyCleanedLogFile = true;
      }
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
#endif // _DEBUG_LOG
#if _INFO_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "INFO",
        ::easyloggingpp::configuration::INFO_LOG_FORMAT,
        _INFO_LOGS_TO_STANDARD_OUTPUT,
        _INFO_LOGS_TO_FILE
      )
    );
#endif // _INFO_LOG
#if _WARNING_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "WARNING",
        ::easyloggingpp::configuration::WARNING_LOG_FORMAT,
        _WARNING_LOGS_TO_STANDARD_OUTPUT,
        _WARNING_LOGS_TO_FILE
      )
    );
#endif // _WARNING_LOG
#if _ERROR_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "ERROR",
        ::easyloggingpp::configuration::ERROR_LOG_FORMAT,
        _ERROR_LOGS_TO_STANDARD_OUTPUT,
        _ERROR_LOGS_TO_FILE
      )
    );
#endif // _ERROR_LOG
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
#endif // _PERFORMANCE_LOG
#if _HINT_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "HINT",
        ::easyloggingpp::configuration::HINT_LOG_FORMAT,
        _HINT_TO_STANDARD_OUTPUT,
        _HINT_TO_FILE
      )
    );
#endif // _HINT_LOG
#if _STATUS_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "STATUS",
        ::easyloggingpp::configuration::STATUS_LOG_FORMAT,
        _STATUS_TO_STANDARD_OUTPUT,
        _STATUS_TO_FILE
      )
    );
#endif // _STATUS_LOG
#if _VERBOSE_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "VERBOSE",
        ::easyloggingpp::configuration::VERBOSE_LOG_FORMAT,
        _VERBOSE_LOGS_TO_STANDARD_OUTPUT,
        _VERBOSE_LOGS_TO_FILE
      )
    );
#endif // _VERBOSE_LOG
#if _QA_LOG
    ::easyloggingpp::internal::registeredLogTypes.push_back(
      ::easyloggingpp::internal::LogType(
        "QA",
        ::easyloggingpp::configuration::QA_LOG_FORMAT,
        _QA_LOGS_TO_STANDARD_OUTPUT,
        _QA_LOGS_TO_FILE
      )
    );
#endif // _QA_LOG
     ::easyloggingpp::internal::loggerInitialized = true;
   }
}

// Writes log safely after checking symbols availablility.
void writeLog(void) {
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
void updateFormatValue(const std::string& formatSpecifier, const std::string& value, std::string& currentFormat) {
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
void determineCommonLogFormat(const std::string& format) {
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
void determineLogFormat(const std::string& type) {
  ::easyloggingpp::internal::LogTypeConstIter logType(
    std::find(::easyloggingpp::internal::registeredLogTypes.begin(),
              ::easyloggingpp::internal::registeredLogTypes.end(),
              type)
  );
  if (logType != ::easyloggingpp::internal::registeredLogTypes.end()) {
    ::easyloggingpp::internal::determineCommonLogFormat(logType->format);
    ::easyloggingpp::internal::toStandardOutput = logType->toStandardOutput;
    ::easyloggingpp::internal::toFile = logType->toFile;
    return;
  }
}

// Builds log format. This function is entry point of writing log.
void buildFormat(const char* func, const char* file, const unsigned long int line, const std::string& type, int verboseLevel) {
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
#endif // _VERBOSE_LOG
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

// Registers the counter. This should not be called by itself since
// one counter can be registered only once and this is checked
// below in validateCounter(..)
void registerCounter(const ::easyloggingpp::internal::Counter& counter) {
  ::easyloggingpp::internal::registeredCounters.push_back(counter);
}

// Resets the counter when it reaches its limit to prevent any failure
// since internal counter (position) uses int for data type.
void resetCounter(::easyloggingpp::internal::CounterIter& counter, int n) {
  if (counter->position >= 5000) {
    counter->position = (n >= 1 ? 5000 % n : 0);
  }
}

// Validates the counter to see if it is valid to write the log for current iteration (n)
// This also registers and resets the counter position if neccessary. 
bool validateCounter(const char* filename, unsigned long int lineNumber, int n) {
  _LOCK_MUTEX
  ::easyloggingpp::internal::tempCounter.resetLocation(filename, lineNumber);
  bool result = false;
  ::easyloggingpp::internal::CounterIter counter(
     std::find(::easyloggingpp::internal::registeredCounters.begin(),
               ::easyloggingpp::internal::registeredCounters.end(),
               ::easyloggingpp::internal::tempCounter));
  if (counter == ::easyloggingpp::internal::registeredCounters.end()) {
    ::easyloggingpp::internal::registerCounter(::easyloggingpp::internal::tempCounter);
    counter = ::easyloggingpp::internal::registeredCounters.end() - 1;
  }
  if ((n >= 1) && (counter->position != 0) && (counter->position % n == 0)) {
    result = true;
  }
  ::easyloggingpp::internal::resetCounter(counter, n);
  ++counter->position;
  _UNLOCK_MUTEX
  return result;
}

#if _PERFORMANCE_LOG
    std::string formatSeconds(double secs) {
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
#endif // _PERFORMANCE_LOG
} // namespace internal

namespace helper {
  std::string readLog(void) {
   _LOCK_MUTEX
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
   _UNLOCK_MUTEX
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
