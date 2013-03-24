///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
//   easylogging++.h - Core of EasyLogging++                                     //
//                                                                               //
//   EasyLogging++ v7.36                                                         //
//   Cross platform logging made easy for C++ applications                       //
//   Author Majid Khan <mkhan3189@gmail.com>                                     //
//   http://www.icplusplus.com                                                   //
//   https://github.com/mkhan3189/EasyLoggingPP                                  //
//                                                                               //
//   Copyright (c) 2012-2013 Majid Khan                                          //
//                                                                               //
//   This software is provided 'as-is', without any express or implied           //
//   warranty. In no event will the authors be held liable for any damages       //
//   arising from the use of this software.                                      //
//                                                                               //
//   Permission is granted to anyone to use this software for any purpose,       //
//   including commercial applications, and to alter it and redistribute         //
//   it freely, subject to the following restrictions:                           //
//                                                                               //
//   1. The origin of this software must not be misrepresented; you must         //
//      not claim that you wrote the original software. If you use this          //
//      software in a product, an acknowledgment in the product documentation    //
//      would be appreciated but is not required.                                //
//                                                                               //
//   2. Altered source versions must be plainly marked as such, and must         //
//      not be misrepresented as being the original software.                    //
//                                                                               //
//   3. This notice may not be removed or altered from any source                //
//      distribution                                                             //
//                                                                               //
//   Part of this software uses/include code from TinyThread++                   //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

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
#define _DEBUG_LOGS_TO_STANDARD_OUTPUT 1
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

#define _ENABLE_VERBOSE_LOGS 1
#define _VERBOSE_LOGS_TO_STANDARD_OUTPUT 1
#define _VERBOSE_LOGS_TO_FILE 1

#define _ENABLE_QA_LOGS 1
#define _QA_LOGS_TO_STANDARD_OUTPUT 1
#define _QA_LOGS_TO_FILE 1

#define _ENABLE_TRACE_LOGS 1
#define _TRACE_LOGS_TO_STANDARD_OUTPUT 1
#define _TRACE_LOGS_TO_FILE 1

//
// High-level log evaluation
//
#if ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))
#    define _ENABLE_EASYLOGGING 1
#endif // ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))

//
// OS evaluation
//
// Windows
#if defined(_WIN32)
#    define _ELPP_OS_WINDOWS 1
#    define _ELPP_OS_WINDOWS_32 1
#endif // defined(_WIN32)
#if defined(_WIN64)
#    define _ELPP_OS_WINDOWS 1
#    define _ELPP_OS_WINDOWS_64 1
#endif // defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
#    define _ELPP_OS_LINUX 1
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
#    define _ELPP_OS_MAC 1
#endif // defined(__APPLE__)

#define _ELPP_OS_UNIX ((_ELPP_OS_LINUX || _ELPP_OS_MAC) && (!_ELPP_OS_WINDOWS))

//
// Log location macros
//
#if !defined(__FILE__)
#    define __FILE__ ""
#endif // !defined(__FILE__)
#if !defined(__LINE__)
#    define __LINE__ ""
#endif // !defined(__LINE__)
// Determine appropriate function macro according to current compiler
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#    define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
#   define __func__ __PRETTY_FUNCTION__
#else
#    ifdef __func__
#        undef __func__
#        define __func__ ""
#    else
#        define __func__ ""
#    endif
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)

//
// Compiler evaluation
//
// GNU
#if defined(__GNUC__)
#    if defined(__GXX_EXPERIMENTAL_CXX0X__)
#        define _CXX0X 1
#    endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// VC++ (http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx)
#if defined(_MSC_VER)
#    if (_MSC_VER == 1600)
#        define _CXX0X 1
#    elif (_MSC_VER == 1700)
#        define _CXX11 1
#    endif // (_MSC_VER == 1600)
#endif // defined(_MSC_VER)

#if (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
// Embedded fast_mutex (part of TinyThread++)
#ifndef _FAST_MUTEX_H_
#define _FAST_MUTEX_H_
#if !defined(_TTHREAD_PLATFORM_DEFINED_)
#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#define _TTHREAD_WIN32_
#else
#define _TTHREAD_POSIX_
#endif
#define _TTHREAD_PLATFORM_DEFINED_
#endif
#if (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))) || \
    (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) || 	 \
    (defined(__GNUC__) && (defined(__ppc__)))
#define _FAST_MUTEX_ASM_
#else
#define _FAST_MUTEX_SYS_
#endif

#if defined(_TTHREAD_WIN32_)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define __UNDEF_LEAN_AND_MEAN
#endif
#include <windows.h>
#define _WINDOWS_HEADER_INCLUDED_FROM_FAST_MUTEX_H // Not part of fastmutex
#ifdef __UNDEF_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef __UNDEF_LEAN_AND_MEAN
#endif
#else
#ifdef _FAST_MUTEX_ASM_
#include <sched.h>
#else
#include <pthread.h>
#endif
#endif
namespace tthread {
class fast_mutex {
public:
#if defined(_FAST_MUTEX_ASM_)
    fast_mutex() : mLock(0) {}
#else
    fast_mutex()
    {
#if defined(_TTHREAD_WIN32_)
        InitializeCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_init(&mHandle, NULL);
#endif
    }
#endif
#if !defined(_FAST_MUTEX_ASM_)
    ~fast_mutex()
    {
#if defined(_TTHREAD_WIN32_)
        DeleteCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_destroy(&mHandle);
#endif
    }
#endif
    inline void lock()
    {
#if defined(_FAST_MUTEX_ASM_)
        bool gotLock;
        do { gotLock = try_lock();
            if(!gotLock)
            {
#if defined(_TTHREAD_WIN32_)
                Sleep(0);
#elif defined(_TTHREAD_POSIX_)
                sched_yield();
#endif
            }
        } while(!gotLock);
#else
#if defined(_TTHREAD_WIN32_)
        EnterCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_lock(&mHandle);
#endif
#endif
    }
    inline bool try_lock()
    {
#if defined(_FAST_MUTEX_ASM_)
        int oldLock;
#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile ("movl $1,%%eax\n\txchg %%eax,%0\n\tmovl %%eax,%1\n\t" : "=m" (mLock), "=m" (oldLock) : : "%eax", "memory");
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &mLock;
        __asm {
            mov eax,1
                    mov ecx,ptrLock
                    xchg eax,[ecx]
                    mov oldLock,eax
        }
#elif defined(__GNUC__) && (defined(__ppc__))
        int newLock = 1;
        asm volatile ("\n1:\n\tlwarx  %0,0,%1\n\tcmpwi  0,%0,0\n\tbne-   2f\n\tstwcx. %2,0,%1\n\t"
                    "bne-   1b\n\tisync\n2:\n\t" : "=&r" (oldLock) : "r" (&mLock), "r" (newLock) : "cr0", "memory");
#endif
        return (oldLock == 0);
#else
#if defined(_TTHREAD_WIN32_)
        return TryEnterCriticalSection(&mHandle) ? true : false;
#elif defined(_TTHREAD_POSIX_)
        return (pthread_mutex_trylock(&mHandle) == 0) ? true : false;
#endif
#endif
    }
    inline void unlock()
    {
#if defined(_FAST_MUTEX_ASM_)
#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile ("movl $0,%%eax\n\txchg %%eax,%0\n\t" : "=m" (mLock) : : "%eax", "memory");
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &mLock;
        __asm {
            mov eax,0
                    mov ecx,ptrLock
                    xchg eax,[ecx]
        }
#elif defined(__GNUC__) && (defined(__ppc__))
        asm volatile ("sync\n\t" : : : "memory");
        mLock = 0;
#endif
#else
#if defined(_TTHREAD_WIN32_)
        LeaveCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_unlock(&mHandle);
#endif
#endif
    }
private:
#if defined(_FAST_MUTEX_ASM_)
    int mLock;
#else
#if defined(_TTHREAD_WIN32_)
    CRITICAL_SECTION mHandle;
#elif defined(_TTHREAD_POSIX_)
    pthread_mutex_t mHandle;
#endif
#endif
};
}
#endif // _FAST_MUTEX_H_
//
// Mutex specific initialization
//
#    define _ELPP_ENABLE_MUTEX 1
#    define _ELPP_MUTEX_SPECIFIC_INIT static tthread::fast_mutex mutex_;
#    define _ELPP_LOCK_MUTEX easyloggingpp::internal::mutex_.lock();
#    define _ELPP_UNLOCK_MUTEX easyloggingpp::internal::mutex_.unlock();
#else
#    define _ELPP_ENABLE_MUTEX 0
#    define _ELPP_MUTEX_SPECIFIC_INIT
#    define _ELPP_LOCK_MUTEX
#    define _ELPP_UNLOCK_MUTEX
#endif // (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
//
// Includes
//
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#if _ELPP_OS_WINDOWS
#    include <direct.h>
#    ifndef (_WINDOWS_HEADER_INCLUDED_FROM_FAST_MUTEX_H)
#        include <windows.h>
#    endif
#endif // _ELPP_OS_WINDOWS
#if _ELPP_OS_UNIX
#    include <sys/stat.h>
#    include <sys/time.h>
#endif // _ELPP_OS_UNIX
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#if !defined(_DISABLE_CPP_LIBRARIES_LOGGING)
// For logging STL based templates
#    include <list> // std::list
#    include <utility> // std::pair
#    include <map> // std::map
#endif // !defined(_DISABLE_CPP_LIBRARIES_LOGGING)
#if defined(QT_CORE_LIB) && !defined(_DISABLE_CPP_THIRD_PARTY_LIBRARIES_LOGGING) && !defined(_DISABLE_CPP_LIBRARIES_LOGGING)
// For logging Qt based classes & templates
#    include <QString>
#    include <QVector>
#    include <QList>
#    include <QPair>
#    include <QMap>
#endif // defined(QT_CORE_LIB) && !defined(_DISABLE_CPP_THIRD_PARTY_LIBRARIES_LOGGING) && !defined(_DISABLE_CUSTOM_CLASS_LOGGING)

namespace easyloggingpp {

namespace configurations {

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
// ===============|====================================================
//   %type        |   Log type, e.g, BusinessLogger, SecurityLogger etc
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
const std::string    DEFAULT_LOG_FORMAT       =    "%datetime %level  [%type] %log\n";
const std::string    DEBUG_LOG_FORMAT         =    "%datetime %level [%type] [%user@%host] [%func] [%loc] %log\n";
const std::string    INFO_LOG_FORMAT          =    DEFAULT_LOG_FORMAT;
const std::string    WARNING_LOG_FORMAT       =    DEFAULT_LOG_FORMAT;
const std::string    ERROR_LOG_FORMAT         =    "%datetime %level [%type] %log\n";
const std::string    FATAL_LOG_FORMAT         =    "%datetime %level [%type] %log\n";
const std::string    VERBOSE_LOG_FORMAT       =    "%datetime %level-%vlevel [%type] %log\n";
const std::string    QA_LOG_FORMAT            =    "%datetime %level    [%type] %log\n";
const std::string    TRACE_LOG_FORMAT         =    "%datetime %level [%type] [%func] [%loc] %log\n";

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

} // namespace configurations
} // namespace easyloggingpp

//
// Log level name outputs
//
#define _ELPP_INFO_LEVEL_OUTPUT      "INFO"
#define _ELPP_DEBUG_LEVEL_OUTPUT     "DEBUG"
#define _ELPP_WARNING_LEVEL_OUTPUT   "WARN"
#define _ELPP_ERROR_LEVEL_OUTPUT     "ERROR"
#define _ELPP_FATAL_LEVEL_OUTPUT     "FATAL"
#define _ELPP_VERBOSE_LEVEL_OUTPUT   "VER"
#define _ELPP_QA_LEVEL_OUTPUT        "QA"
#define _ELPP_TRACE_LEVEL_OUTPUT     "TRACE"
//
// Low-level log evaluation
//
#define _ELPP_DEBUG_LOG       ((_ENABLE_DEBUG_LOGS) && !defined(_DISABLE_DEBUG_LOGS) && (_ENABLE_EASYLOGGING) && ((defined(_DEBUG)) || (!defined(NDEBUG))))
#define _ELPP_INFO_LOG        ((_ENABLE_INFO_LOGS) && !defined(_DISABLE_INFO_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_WARNING_LOG     ((_ENABLE_WARNING_LOGS) && !defined(_DISABLE_WARNING_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_ERROR_LOG       ((_ENABLE_ERROR_LOGS) && !defined(_DISABLE_ERROR_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_FATAL_LOG       ((_ENABLE_FATAL_LOGS) && !defined(_DISABLE_FATAL_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_VERBOSE_LOG     ((_ENABLE_VERBOSE_LOGS) && !defined(_DISABLE_VERBOSE_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_QA_LOG          ((_ENABLE_QA_LOGS) && defined(_QUALITY_ASSURANCE) && (_ENABLE_EASYLOGGING))
#define _ELPP_TRACE_LOG       ((_ENABLE_TRACE_LOGS) && !defined(_DISABLE_TRACE_LOGS) && (_ENABLE_EASYLOGGING))

#if _ELPP_OS_UNIX
// Permissions for unix-based systems
#define _LOG_PERMS S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH
#endif // _ELPP_OS_UNIX

#define _SUPPRESS_UNUSED_WARN(x) (void)x

namespace easyloggingpp {

class VersionInfo {
public:
    // Minimal formatted displayable information
    static inline const std::string formattedInfo(void) {
        std::stringstream ss;
        ss << "EasyLogging++ v" << version() << " (" << releaseDate() << ")";
        ss << std::endl;
        ss << website();
        ss << std::endl;
        ss << copyright();
        return ss.str();
    }

    // Current version number
    static inline const std::string version(void) { return std::string("7.36"); }

    // Release date of current version
    static inline const std::string releaseDate(void) { return std::string("24-03-2013 1924hrs"); }

    // Original author and maintainer
    static inline const std::string author(void) { return std::string("Majid Khan <mkhan3189@gmail.com>"); }

    // Web link
    static inline const std::string website(void) { return std::string("http://tools.icplusplus.com/easylogging"); }

    // Link to source code
    static inline const std::string sourceCodeLink(void) { return std::string("https://github.com/mkhan3189/EasyLoggingPP"); }

    // Copyright information
    static inline const std::string copyright(void) { return std::string("Copyright (c) 2012 - 2013 Majid Khan"); }

    // Full licence
    static const std::string licence(void) {
        std::stringstream ss;
        ss << "   This software is provided 'as-is', without any express or implied" << std::endl;
        ss << "   warranty. In no event will the authors be held liable for any damages" << std::endl;
        ss << "   arising from the use of this software." << std::endl;
        ss << std::endl;
        ss << "   Permission is granted to anyone to use this software for any purpose," << std::endl;
        ss << "   including commercial applications, and to alter it and redistribute" << std::endl;
        ss << "   it freely, subject to the following restrictions:" << std::endl;
        ss << std::endl;
        ss << "   1. The origin of this software must not be misrepresented; you must" << std::endl;
        ss << "      not claim that you wrote the original software. If you use this" << std::endl;
        ss << "      software in a product, an acknowledgment in the product documentation" << std::endl;
        ss << "      would be appreciated but is not required." << std::endl;
        ss << std::endl;
        ss << "   2. Altered source versions must be plainly marked as such, and must" << std::endl;
        ss << "      not be misrepresented as being the original software." << std::endl;
        ss << std::endl;
        ss << "   3. This notice may not be removed or altered from any source" << std::endl;
        ss << "      distribution";
        return ss.str();
    }

private:
    // Prevent initialization
    VersionInfo(void);
    VersionInfo(const VersionInfo&);
    VersionInfo& operator=(const VersionInfo&);
}; // namespace VersionInfo

namespace internal {
_ELPP_MUTEX_SPECIFIC_INIT
namespace helper {
    // OSUtilities class specifically written for EasyLogging++
    // This class contains functionalities related to operating system
    class OSUtilities {
    public:
        // Runs command on terminal and returns the output.
        // This is applicable only on linux and mac, for all other OS, an empty string is returned.
        static std::string getBashOutput(const char* command_) {
            if (command_ == NULL) {
                return std::string();
            }
#if _ELPP_OS_UNIX
            FILE* proc = NULL;
            if ((proc = popen(command_, "r")) == NULL) {
                std::cerr << "\nUnable to run command [" << command_ << "]\n";
                return std::string();
            }
            char hBuff[4096];
            if (fgets(hBuff, sizeof(hBuff), proc) != NULL) {
                pclose(proc);
                if (hBuff[strlen(hBuff) - 1] == '\n') {
                    hBuff[strlen(hBuff) - 1] = '\0';
                }
                return std::string(hBuff);
            }
            return std::string();
#else
            return std::string();
#endif // _ELPP_OS_UNIX
        }

        // Gets current username.
        static std::string currentUser(void) {
#if _ELPP_OS_WINDOWS
            const char* username = getenv("USERNAME");
#elif _ELPP_OS_UNIX
            const char* username = getenv("USER");
#endif // _ELPP_OS_WINDOWS
            if ((username == NULL) || (!strcmp(username, ""))) {
                // Try harder on unix-based systems
                return OSUtilities::getBashOutput("whoami");
            } else {
                return std::string(username);
            }
        }

        // Gets current host name or computer name.
        static std::string currentHost(void) {
#if _ELPP_OS_WINDOWS
            const char* hostname = getenv("COMPUTERNAME");
#elif _ELPP_OS_UNIX
            const char* hostname = getenv("HOSTNAME");
#endif // _ELPP_OS_WINDOWS
            if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
                // Try harder on unix-based systems
                std::string hostnameStr = OSUtilities::getBashOutput("hostname");
                if (hostnameStr.empty()) {
                    return std::string("unknown-host");
                } else {
                    return hostnameStr;
                }
            } else {
                return std::string(hostname);
            }
        }

        // Determines whether or not provided path_ exist in current file system
        static inline bool pathExists(const char* path_) {
            if (path_ == NULL) {
                return false;
            }
#if _ELPP_OS_WINDOWS
            DWORD fileType = GetFileAttributesA(path_);
            if (fileType == INVALID_FILE_ATTRIBUTES) {
                return false;
            }
            return (fileType & FILE_ATTRIBUTE_DIRECTORY);
#elif _ELPP_OS_UNIX
            struct stat st;
            return (stat(path_, &st) == 0);
#endif // _ELPP_OS_WINDOWS
        }

        // Creates path as specified
        static bool createPath(const std::string& path_) {
            if (path_.empty()) {
                return false;
            }
            if (OSUtilities::pathExists(path_.c_str())) {
                return true;
            }
#   if _ELPP_OS_WINDOWS
            const char* pathDelim_ = "\\";
#   elif _ELPP_OS_UNIX
            const char* pathDelim_ = "/";
#   endif // _ELPP_OS_WINDOWS
            int status = -1;
            char* currPath_ = const_cast<char*>(path_.c_str());
            std::string buildingPath_;
            if (path_[0] == '/') {
                buildingPath_ = "/";
            }
            currPath_ = strtok(currPath_, pathDelim_);
            while (currPath_ != NULL) {
                buildingPath_.append(currPath_);
                buildingPath_.append(pathDelim_);
#   if _ELPP_OS_WINDOWS
                status = _mkdir(buildingPath_.c_str());
#   elif _ELPP_OS_UNIX
                status = mkdir(buildingPath_.c_str(), _LOG_PERMS);
#   endif // _ELPP_OS_WINDOWS
                currPath_ = strtok(NULL, pathDelim_);
            }
            if (status == -1) {
                return false;
            }
            return true;
        }

    private:
        // Prevent initilization
        OSUtilities(void);
        OSUtilities(const OSUtilities&);
        OSUtilities& operator=(const OSUtilities&);
    }; // class OSUtilities

    class LogManipulator {
    public:
        // Updates the formatSpecifier_ for currentFormat_ to value_ provided
        static void updateFormatValue(const std::string& formatSpecifier_,
                                      const std::string& value_,
                                      std::string& currentFormat_) {
            size_t foundAt = -1;
            while ((foundAt = currentFormat_.find(formatSpecifier_, foundAt + 1)) != std::string::npos){
                if (currentFormat_[foundAt > 0 ? foundAt - 1 : 0] == 'E') {
                    currentFormat_.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
                    ++foundAt;
                } else {
                    currentFormat_ = currentFormat_.replace(foundAt, formatSpecifier_.size(), value_);
                    return;
                }
            }
        }
    private:
        // Prevent initilization
        LogManipulator(void);
        LogManipulator(const LogManipulator&);
        LogManipulator& operator=(const LogManipulator&);
    }; // class LogManipulator

    class DateUtilities {
    public:
        enum kDateTimeFormat {
            kDateOnly,
            kTimeOnly,
            kDateTime
        };

        // Gets current date and time with milliseconds.
        static std::string getDateTime(unsigned int format_) {
            long milliSeconds = 0;
            const int kDateBuffSize_ = 30;
            const char* kTimeFormatLocal_ = "%H:%M:%S";
            const char* kDateFormatLocal_ = "%d/%m/%Y";
            char dateBuffer_[kDateBuffSize_] = "";
            char dateFormat_[kDateBuffSize_];
            char dateBufferOut_[kDateBuffSize_] = "";
            if (format_ == kDateOnly) {
                strcpy(dateFormat_, kDateFormatLocal_);
            } else if (format_ == kTimeOnly) {
                strcpy(dateFormat_, kTimeFormatLocal_);
            } else {
                strcpy(dateFormat_, kDateFormatLocal_);
                strcat(dateFormat_, " ");
                strcat(dateFormat_, kTimeFormatLocal_);
            }
#if _ELPP_OS_UNIX
            timeval currTime;
            gettimeofday(&currTime, NULL);
            if ((format_ == kDateTime) || (format_ == kTimeOnly)) {
                milliSeconds = currTime.tv_usec / 1000;
            }
            struct tm * timeInfo = localtime(&currTime.tv_sec);

            strftime(dateBuffer_, sizeof(dateBuffer_), dateFormat_, timeInfo);
            if ((format_ == kDateTime) || (format_ == kTimeOnly)) {
                sprintf(dateBufferOut_, "%s.%03ld", dateBuffer_, milliSeconds);
            }
#elif _ELPP_OS_WINDOWS
            if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", dateBuffer_, kDateBufferSize_) != 0) {
                static DWORD oldTick = GetTickCount();
                if ((format_ == kDateTime) || (format_ == kTimeOnly)) {
                    milliSeconds = (long)(GetTickCount() - oldTick) % 1000;
                    sprintf(dateBufferOut_, "%s.%03ld", dateBuffer_, milliSeconds);
                }
            }
#endif // _ELPP_OS_UNIX
            return std::string(dateBufferOut_);
        }

        static std::string formatMilliSeconds(double milliSeconds_) {
            double result = milliSeconds_;
            std::string unit = "ms";
            std::stringstream stream_;
            if (result > 1000.0f) {
                result /= 1000; unit = "seconds";
                if (result > 60.0f) {
                    result /= 60; unit = "minutes";
                    if (result > 60.0f) {
                        result /= 60; unit = "hours";
                        if (result > 24.0f) {
                            result /= 24; unit = "days";
                        }
                    }
                }
            }
            stream_ << result << " " << unit;
            return stream_.str();
        }

        static double getTimeDifference(timeval& endTime, timeval& startTime) {
             return static_cast<double>((((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec)) / 1000);
        }
    private:
        // Prevent initilization
        DateUtilities(void);
        DateUtilities(const DateUtilities&);
        DateUtilities& operator=(const DateUtilities&);
    }; // class DateUtilities
} // namespace helper

using namespace easyloggingpp::configurations;
using namespace easyloggingpp::internal::helper;

// Used internally as a register to keep records of 'Class' and provides underlying
// memory management
template<class Class, class Iterator, class Predicate>
class Register {
public:
    explicit Register(void) {
    }

    virtual ~Register(void) {
        unregisterAll();
    }

    template<typename T2>
    Class* get(const T2& t2_) {
        Iterator iter = std::find_if(list_.begin(), list_.end(), Predicate(t2_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }

    template<typename T2>
    inline bool exist(const T2& t_) {
        return (get(t_) != NULL);
    }

    inline size_t count(void) const {
        return list_.size();
    }

    inline bool empty(void) const {
        return list_.empty();
    }
protected:
    inline void registerNew(Class* c_) {
        list_.push_back(c_);
    }

    inline void unregisterAll(void) {
        if (!empty()) {
            std::for_each(list_.begin(), list_.end(), std::bind1st(std::mem_fun(&Register::unregister), this));
            list_.clear();
        }
    }

    inline void unregister(Class* c_) {
        if (c_) {
            delete c_;
            c_ = NULL;
        }
    }

    std::vector<Class*> list_;

private:
    // Prevent copy or assignment
    explicit Register(const Register&);
    Register& operator=(const Register&);
}; // class Register

// Represents a log type such as business logger, security logger etc.
class LogType {
public:
    typedef std::vector<LogType*>::const_iterator Iterator;

    explicit LogType(const std::string& name_) :
        name_(name_),
        logName_(logName_) {
    }

    explicit LogType(const std::string& name_,
                      const std::string& logName_) :
        name_(name_),
        logName_(logName_) {
    }

    inline std::string name(void) const {
        return name_;
    }

    inline std::string logName(void) const {
        return logName_;
    }

    class Predicate {
    public:
        explicit Predicate(const std::string& name_) :
            name_(name_)
        {
        }
        bool operator()(const LogType* logType_) {
            return ((logType_ != NULL) &&
                    (logType_->name_ == name_));
        }
    private:
        std::string name_;
    };
private:
    std::string name_;
    std::string logName_;
}; // class LogType

// Registered log types to be used as finding register while writing logs
class RegisteredLogTypes : public Register<LogType, LogType::Iterator, LogType::Predicate> {
public:
    explicit RegisteredLogTypes(void) {
        registerNew(new LogType("TrivialLogger", "log"));
        registerNew(new LogType("BusinessLogger", "business"));
        registerNew(new LogType("SecurityLogger", "security"));
        registerNew(new LogType("PerformanceLogger", "performance"));
    }

    inline bool inject(LogType *t_) {
        if (t_ && !exist(t_->name())) {
            registerNew(t_);
            return true;
        }
        return false;
    }
}; // class RegisteredLogTypes

// Represents severity level for log
class SeverityLevel {
public:
    typedef std::vector<SeverityLevel*>::const_iterator Iterator;

    explicit SeverityLevel(const std::string& name_,
                           const std::string& format_,
                           bool toStandardOutput_,
                           bool toFile_) :
        name_(name_),
        format_(format_),
        toStandardOutput_(toStandardOutput_),
        toFile_(toFile_) {
        LogManipulator::updateFormatValue("%level", name_, this->format_);
    }

    inline bool operator==(const std::string& name_) const {
        return this->name_ == name_;
    }

    inline std::string name(void) const {
        return name_;
    }

    inline std::string format(void) const {
        return format_;
    }

    inline bool toStandardOutput(void) const {
        return toStandardOutput_;
    }

    inline bool toFile(void) const {
        return toFile_;
    }

    class Predicate {
    public:
        explicit Predicate(const std::string& name_) :
            name_(name_)
        {
        }
        inline bool operator()(const SeverityLevel* level_) {
            return *level_ == name_;
        }

    private:
        std::string name_;
    };

private:
    std::string name_;
    std::string format_;
    bool toStandardOutput_;
    bool toFile_;
}; // class SeverityLevel

// All the registered severity levels used while writing logs
class RegisteredSeverityLevels : public Register<SeverityLevel, SeverityLevel::Iterator, SeverityLevel::Predicate> {
public:
    explicit RegisteredSeverityLevels(void)
    {
        registerNew(
                    new SeverityLevel(_ELPP_DEBUG_LEVEL_OUTPUT, DEBUG_LOG_FORMAT, _DEBUG_LOGS_TO_STANDARD_OUTPUT, _DEBUG_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_INFO_LEVEL_OUTPUT, INFO_LOG_FORMAT, _INFO_LOGS_TO_STANDARD_OUTPUT, _INFO_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_WARNING_LEVEL_OUTPUT, WARNING_LOG_FORMAT, _WARNING_LOGS_TO_STANDARD_OUTPUT, _WARNING_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_ERROR_LEVEL_OUTPUT, ERROR_LOG_FORMAT, _ERROR_LOGS_TO_STANDARD_OUTPUT, _ERROR_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_FATAL_LEVEL_OUTPUT, FATAL_LOG_FORMAT, _FATAL_LOGS_TO_STANDARD_OUTPUT, _FATAL_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_VERBOSE_LEVEL_OUTPUT, VERBOSE_LOG_FORMAT, _VERBOSE_LOGS_TO_STANDARD_OUTPUT, _VERBOSE_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_QA_LEVEL_OUTPUT, QA_LOG_FORMAT, _QA_LOGS_TO_STANDARD_OUTPUT, _QA_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel(_ELPP_TRACE_LEVEL_OUTPUT, TRACE_LOG_FORMAT, _TRACE_LOGS_TO_STANDARD_OUTPUT, _TRACE_LOGS_TO_FILE));
    }
}; // class RegisteredSeverityLevels

// Represents single counter for interval log
class LogCounter {
public:
    typedef std::vector<LogCounter*>::iterator Iterator;
    const static unsigned int kMax = 100000;

    explicit LogCounter(void) :
        file_(""),
        line_(0),
        position_(1) {
    }

    explicit LogCounter(const char* file_,
                        unsigned long int line_) :
        file_(file_),
        line_(line_),
        position_(1) {}

    inline void resetLocation(const char* file_,
                              unsigned long int line_) {
        this->file_ = file_;
        this->line_ = line_;
    }

    inline void reset(unsigned int n_) {
        if (position_ >= LogCounter::kMax) {
            position_ = (n_ >= 1 ? kMax % n_ : 0);
        }
        ++position_;
    }

    inline const char* file(void) const {
        return file_;
    }

    inline unsigned long int line(void) const {
        return line_;
    }

    inline unsigned int position(void) const {
        return position_;
    }

    class Predicate {
    public:
        explicit Predicate(const char* file_, unsigned long int line_)
            : file_(file_),
              line_(line_) {
        }
        inline bool operator()(const LogCounter* counter_) {
            return ((counter_ != NULL) &&
                    (counter_->file_ == file_) &&
                    (counter_->line_ == line_));
        }

    private:
        const char* file_;
        unsigned long int line_;
    };

private:
    const char* file_;
    unsigned long int line_;
    unsigned int position_;
}; // class LogCounter

// Represents all the registered counters. This registeration is done at run-time as log is being written
class RegisteredCounters : public Register<LogCounter, LogCounter::Iterator, LogCounter::Predicate>  {
public:
    bool valid(const char* file_, unsigned long int line_, unsigned int n_) {
        bool result_ = false;
        LogCounter* counter_ = get(file_, line_);
        if (counter_ == NULL) {
            registerNew(counter_ = new LogCounter(file_, line_));
        }
        if (n_ >= 1 && counter_->position() != 0 && counter_->position() % n_ == 0) {
            result_ = true;
        }
        counter_->reset(n_);
        return result_;
    }

    LogCounter* get(const char* file_, unsigned long int line_) {
        LogCounter::Iterator iter = std::find_if(list_.begin(), list_.end(), LogCounter::Predicate(file_, line_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }
}; // class RegisteredCounters

// Main logger that holds all the helper values and is used as an entry point of initialization
class Logger {
public:
    explicit Logger(void) :
        kFinalFilename_(USE_CUSTOM_LOCATION ?
                            CUSTOM_LOG_FILE_LOCATION + LOG_FILENAME:
                            LOG_FILENAME),
        kUser_(OSUtilities::currentUser()),
        kHost_(OSUtilities::currentHost()),
        initialized_(true),
        stream_(new std::stringstream()),
        logFile_(NULL),
        registeredLogTypes_(new RegisteredLogTypes()),
        registeredSeverityLevels_(new RegisteredSeverityLevels()),
        registeredLogCounters_(new RegisteredCounters()) {
        if (SAVE_TO_FILE) {
            fileGood_ = USE_CUSTOM_LOCATION ?
                        !LOG_FILENAME.empty() && OSUtilities::createPath(CUSTOM_LOG_FILE_LOCATION) :
                        !LOG_FILENAME.empty();
            if (fileGood_) {
#if (_ALWAYS_CLEAN_LOGS)
                logFile_ = new std::ofstream(kFinalFilename_.c_str(), std::ofstream::out);
#else
                logFile_ = new std::ofstream(kFinalFilename_.c_str(), std::ofstream::out | std::ofstream::app);
#endif

                if (logFile_->is_open()) {
                    logFile_->close();
                } else {
                    if (logFile_) {
                        delete logFile_;
                        logFile_ = NULL;
                    }
                    fileGood_ = false;
                }
            } else {
                std::cerr << "\nBad file for writing logs to [" << kFinalFilename_ << "] Please check the configurations\n";
            }
        }
    }

    virtual ~Logger(void) {
        if (stream_) {
            delete stream_;
            stream_ = NULL;
        }
        if (logFile_) {
            delete logFile_;
            logFile_ = NULL;
        }
        if (registeredLogTypes_) {
            delete registeredLogTypes_;
            registeredLogTypes_ = NULL;
        }
        if (registeredSeverityLevels_) {
            delete registeredSeverityLevels_;
            registeredSeverityLevels_ = NULL;
        }
        if (registeredLogCounters_) {
            delete registeredLogCounters_;
            registeredLogCounters_ = NULL;
        }
    }

    void setArgs(int argc, char** argv) {
        while (argc-- > 0) {
#if _ELPP_VERBOSE_LOG
            const unsigned short kMaxVerboseLevel = 9;
            // Look for --v=X argument
            if ((strlen(argv[argc]) >= 5) &&
                    (argv[argc][0] == '-') &&
                    (argv[argc][1] == '-') &&
                    (argv[argc][2] == 'v') &&
                    (argv[argc][3] == '=') &&
                    (isdigit(argv[argc][4]))) {
                // Current argument is --v=X
                // where X is a digit between 0-9
                appVerbose_ = static_cast<short>(atoi(argv[argc] + 4));
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
                appVerbose_ = kMaxVerboseLevel;
            }
            // Look for -v argument
            else if ((strlen(argv[argc]) == 2) &&
                     (argv[argc][0] == '-') &&
                     (argv[argc][1] == 'v')) {
                appVerbose_ = kMaxVerboseLevel;
            }
#else
            _SUPPRESS_UNUSED_WARN(argv);
            appVerbose_ = 0;
#endif // _ELPP_VERBOSE_LOG
        }
    }

    inline void setArgs(int argc, const char** argv) {
        char** args = const_cast<char**>(argv);
        setArgs(argc, args);
    }

    inline void buildLine(const std::string& logType_, const std::string& severityLevel_, const char* func_,
                          const char* file_, const unsigned long int line_, unsigned short verboseLevel_ = 0) {
        SeverityLevel* level_ = registeredSeverityLevels_->get(severityLevel_);
        currLogLine_ = level_->format();
        std::string formatSpecifier_ = "";
        std::string value_ = "";
        // DateTime
        unsigned int dateTimeFormat_ = 0;
        if (level_->format().find("%datetime") != std::string::npos) {
            dateTimeFormat_ = DateUtilities::kDateTime;
            formatSpecifier_ = "%datetime";
        } else if (level_->format().find("%date") != std::string::npos) {
            dateTimeFormat_ = DateUtilities::kDateOnly;
            formatSpecifier_ = "%date";
        } else if (level_->format().find("%time") != std::string::npos) {
            dateTimeFormat_ = DateUtilities::kTimeOnly;
            formatSpecifier_ = "%time";
        } else {
            dateTimeFormat_ = 0;
        }
        if (dateTimeFormat_ != 0) {
            value_ = DateUtilities::getDateTime (dateTimeFormat_);
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        // Type
        if (level_->format().find("%type") != std::string::npos) {
            LogType* type_ = registeredLogTypes_->get(logType_);
#ifdef _NO_TRIVIAL_TYPE_DISPLAY
            bool displayType_ = true;
            if (type_ && type_->name() == "TrivialLogger") {
                displayType_ = false;
            }

            if (displayType_) {
#endif // _NO_TRIVIAL_TYPE_DISPLAY
                if (type_) {
                    value_ = type_->logName();
                } else {
                    value_ = logType_;
                }
#ifdef _NO_TRIVIAL_TYPE_DISPLAY
            } else {
                value_ = "";
            }
#endif // _NO_TRIVIAL_TYPE_DISPLAY
            formatSpecifier_ = "%type";
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        // Location
        if (level_->format().find("%loc") != std::string::npos) {
            tempStream_ << file_ << ":" << line_;
            value_ = tempStream_.str();
            formatSpecifier_ = "%loc";
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        // Function
        if (level_->format().find("%func") != std::string::npos) {
            value_ = std::string(func_);
            formatSpecifier_ = "%func";
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        // User
        if (level_->format().find("%user") != std::string::npos) {
            formatSpecifier_ = "%user";
            LogManipulator::updateFormatValue(formatSpecifier_, kUser_, currLogLine_);
        }
        // Host
        if (level_->format().find("%host") != std::string::npos) {
            formatSpecifier_ = "%host";
            LogManipulator::updateFormatValue(formatSpecifier_, kHost_, currLogLine_);
        }
        // Log
        if (level_->format().find("%log") != std::string::npos) {
            formatSpecifier_ = "%log";
            LogManipulator::updateFormatValue(formatSpecifier_, stream_->str(), currLogLine_);
        }
        // Verbose specific log
        if (verboseLevel_ > 0) {
            // Verbose level
            tempStream_.str("");
            tempStream_ << verboseLevel_;
            value_ = tempStream_.str();
            formatSpecifier_ = "%vlevel";
            LogManipulator::updateFormatValue(formatSpecifier_, tempStream_.str(), currLogLine_);
        }
        write(level_);
    }

    inline void write(SeverityLevel* level_) {
        if (SHOW_STD_OUTPUT && level_->toStandardOutput()) {
            std::cout << currLogLine_;
        }
        if (SAVE_TO_FILE && fileGood() && level_->toFile()) {
            logFile_->open(kFinalFilename_.c_str(), std::ofstream::out | std::ofstream::app);
            (*logFile_) << currLogLine_;
            logFile_->close();
        }
        clear();
    }

    inline void clear(void) {
        stream_->str("");
        tempStream_.str("");
    }

    inline std::string applicationName(void) const {
        return applicationName_;
    }

    inline void setApplicationName(const std::string& applicationName_) {
        this->applicationName_ = applicationName_;
    }

    inline std::stringstream* stream(void) {
        return stream_;
    }

    inline RegisteredLogTypes* registeredLogTypes(void) {
        return registeredLogTypes_;
    }

    inline RegisteredSeverityLevels* registeredSeverityLevels(void) const {
        return registeredSeverityLevels_;
    }

    inline RegisteredCounters* registeredLogCounters(void) {
        return registeredLogCounters_;
    }

    inline bool fileGood(void) const {
        return fileGood_;
    }

    inline unsigned short appVerbose(void) const {
        return appVerbose_;
    }

    inline bool initialized(void) const {
        return initialized_;
    }

    inline bool injectNewLogType(const std::string& name_, const std::string& logName_) {
        LogType* logType_ = new LogType(name_, logName_);
        if (registeredLogTypes()->inject(logType_)) {
            return true;
        }
        delete logType_;
        logType_ = NULL;
        return false;
    }

    const std::string kFinalFilename_;
    const std::string kUser_;
    const std::string kHost_;
private:
    std::string applicationName_;
    bool initialized_;
    bool fileGood_;
    std::string currLogLine_;
    std::stringstream tempStream_;
    std::stringstream* stream_;
    std::ofstream* logFile_;
    RegisteredLogTypes* registeredLogTypes_;
    RegisteredSeverityLevels* registeredSeverityLevels_;
    RegisteredCounters* registeredLogCounters_;
    unsigned short appVerbose_;
}; // class Logger

//
// Helper macros
//
#define _ELPP_LOGGER easyloggingppLogger_
#define _QUALIFIED_LOGGER ::easyloggingpp::internal::_ELPP_LOGGER
#define _ELPP_STREAM_PTR _ELPP_LOGGER.stream()
#define _ELPP_STREAM *_ELPP_STREAM_PTR
#define _WRITE_ELPP_LOG(type_, level_, func_, file_, line_)                                \
    if (logAspect_ == kNormal) {                                                           \
        _ELPP_LOGGER.buildLine(type_, level_, func_, file_, line_);                        \
    } else if (logAspect_ == kConditional && condition_) {                                 \
    _ELPP_LOGGER.buildLine(type_, level_, func_, file_, line_);                            \
    } else if (logAspect_ == kInterval) {                                                  \
    if (_ELPP_LOGGER.registeredLogCounters()->valid(file_, line_, counter_)) {             \
        _ELPP_LOGGER.buildLine(type_, level_, func_, file_, line_);                        \
    }                                                                                      \
}
#define _ELPP_LOG_TO_STREAM _ELPP_STREAM << log_; return *this;
#define _ELPP_COUNTER _ELPP_LOGGER.registeredLogCounters()->get(__FILE__, __LINE__)
#define _ELPP_COUNTER_POSITION (_ELPP_COUNTER == NULL ? 0 : _ELPP_COUNTER->position())

extern easyloggingpp::internal::Logger _ELPP_LOGGER;

// Entry point to write log. All the macros are resolved to c'tor of this class
class LogWriter {
public:
    enum kLogAspect {
        kNormal,
        kConditional,
        kInterval
    };

    explicit LogWriter(kLogAspect logAspect_,
                       const std::string& logType_,
                       const std::string& severityLevel_,
                       const char* func_,
                       const char* file_,
                       const unsigned long int line_,
                       bool condition_ = true,
                       unsigned int verboseLevel_ = 0,
                       int counter_ = 0) :
        logAspect_(logAspect_),
        logType_(logType_),
        severityLevel_(severityLevel_),
        func_(func_),
        file_(file_),
        line_(line_),
        condition_(condition_),
        verboseLevel_(verboseLevel_),
        counter_(counter_) {
        _ELPP_LOCK_MUTEX;
    }

    ~LogWriter(void) {
        writeLog();
        _ELPP_UNLOCK_MUTEX;
    }

    inline LogWriter& operator<<(const std::string& log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(const std::wstring& log_) { _ELPP_STREAM << "(std::wstring could not be handled) " << log_.c_str(); return *this; }
    inline LogWriter& operator<<(char log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(bool log_) { _ELPP_STREAM << (log_ != 0 ? "true" : "false"); return *this; }
    inline LogWriter& operator<<(signed short log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(unsigned short log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(signed int log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(unsigned int log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(signed long log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(unsigned long log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(float log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(double log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(char* log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(const char* log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(const void* log_) { _ELPP_LOG_TO_STREAM }
    inline LogWriter& operator<<(long double log_) { _ELPP_LOG_TO_STREAM }
    template <class T>
    inline LogWriter& operator<<(const T& class_) {
        _ELPP_STREAM << class_.toString();
        return *this;
    }
    template <std::size_t N>
    struct type_of_size
    {
        typedef char type[N];
    };

    template <typename T, std::size_t Size>
    typename type_of_size<Size>::type& sizeof_array_helper(T(&)[Size]);

    #define sizeof_array(pArray) sizeof(sizeof_array_helper(pArray))

    template <class T>
    inline LogWriter& operator<<(T arr_[]) {
        _ELPP_STREAM << "(";
        size_t size_ = (sizeof arr_  / sizeof arr_[0]);
        for (size_t i = 0; i < size_; ++i) {
            operator << (arr_[i]);
            _ELPP_STREAM << (i < (size_ - 1) ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
#if !defined(_DISABLE_CPP_LIBRARIES_LOGGING)
    template <typename T>
    inline LogWriter& operator<<(std::vector<T>& vec_) {
        _ELPP_STREAM << "(";
        for (typename std::vector<T>::const_iterator it = vec_.begin(); it != vec_.end(); ++it) {
            _ELPP_STREAM << "\"";
            operator << (static_cast<T>(*it));
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (it < vec_.end() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(std::vector<T*>& vec_) {
        _ELPP_STREAM << "(";
        unsigned int index_ = 0;
        for (typename std::vector<T*>::const_iterator it = vec_.begin(); it != vec_.end(); ++it) {
            _ELPP_STREAM << "\"";
            T* t_ = *it;
            if (t_) {
                operator << (static_cast<T>(*t_));
            }
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (index_++ < vec_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(const std::vector<T>& vec_) {
        operator<<(const_cast<std::vector<T> >(vec_));
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(std::list<T>& list_) {
        _ELPP_STREAM << "(";
        unsigned int index_ = 0;
        for (typename std::list<T>::const_iterator it = list_.begin(); it != list_.end(); ++it) {
            _ELPP_STREAM << "\"";
            operator << (static_cast<T>(*it));
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (index_++ < list_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(std::list<T*>& list_) {
        _ELPP_STREAM << "(";
        unsigned int index_ = 0;
        for (typename std::list<T*>::const_iterator it = list_.begin(); it != list_.end(); ++it) {
            _ELPP_STREAM << "\"";
            T* t_ = *it;
            if (t_) {
                operator << (static_cast<T>(*t_));
            }
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (index_++ < list_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(const std::list<T>& list_) {
        operator<<(const_cast<std::list<T> >(list_));
        return *this;
    }
    template <class K, class V>
    inline LogWriter& operator<<(const std::pair<K, V>& pair_) {
        _ELPP_STREAM << "[";
        operator << (static_cast<K>(pair_.first));
        _ELPP_STREAM << ", ";
        operator << (static_cast<V>(pair_.second));
        _ELPP_STREAM << "]";
        return *this;
    }
    template <class K, class V>
    inline LogWriter& operator<<(const std::map<K, V>& map_) {
        _ELPP_STREAM << "[";
        int index_ = 0;
        for (typename std::map<K, V>::const_iterator it = map_.begin(); it != map_.end(); ++it) {
            operator << (*it);
            _ELPP_STREAM << (index_++ < map_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << "]";
        return *this;
    }
#endif // !defined(_DISABLE_LIBRARY_CLASS_LOGGING)
#if defined(QT_CORE_LIB) && !defined(_DISABLE_CPP_THIRD_PARTY_LIBRARIES_LOGGING) && !defined(_DISABLE_CPP_LIBRARIES_LOGGING)
    inline LogWriter& operator<<(const QString& log_) { _ELPP_STREAM << log_.toStdString(); return *this; }
    inline LogWriter& operator<<(const QStringRef& log_) { return operator<<(log_.toString()); }
    inline LogWriter& operator<<(qint64 log_) { _ELPP_STREAM << QString::number(log_).toStdString(); return *this; }
    inline LogWriter& operator<<(quint64 log_) { _ELPP_STREAM << QString::number(log_).toStdString(); return *this; }
    inline LogWriter& operator<<(QChar log_) { _ELPP_STREAM << log_.toAscii(); return *this; }
    inline LogWriter& operator<<(QBool log_) { _ELPP_STREAM << (bool(log_ != 0) ? "true" : "false"); return *this; }
    inline LogWriter& operator<<(const QLatin1String& log_) { _ELPP_STREAM << log_.latin1(); return *this; }
    template <typename T>
    inline LogWriter& operator<<(QList<T>& list_) {
        _ELPP_STREAM << "(";
        int index_ = 0;
        for (typename QList<T>::const_iterator it = list_.begin(); it != list_.end(); ++it) {
            _ELPP_STREAM << "\"";
            operator << (static_cast<T>(*it));
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (index_++ < list_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(QList<T*>& list_) {
        _ELPP_STREAM << "(";
        int index_ = 0;
        for (typename QList<T*>::const_iterator it = list_.begin(); it != list_.end(); ++it) {
            _ELPP_STREAM << "\"";
            T* t_ = *it;
            if (t_) {
                operator << (static_cast<T>(*t_));
            }
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (index_++ < list_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(const QList<T>& list_) {
        _ELPP_STREAM << "(";
        int index_ = 0;
        for (typename QList<T>::const_iterator it = list_.begin(); it != list_.end(); ++it) {
            _ELPP_STREAM << "\"";
            operator << (static_cast<T>(*it));
            _ELPP_STREAM << "\"";
            _ELPP_STREAM << (index_++ < list_.size() -1 ? ", " : "");
        }
        _ELPP_STREAM << ")";
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(QVector<T>& vec_) {
        operator<<(vec_.toList());
        return *this;
    }
    template <typename T>
    inline LogWriter& operator<<(const QVector<T>& vec_) {
        operator<<(const_cast<QVector<T> >(vec_));
        return *this;
    }
    template <class K, class V>
    inline LogWriter& operator<<(const QPair<K, V>& pair_) {
        _ELPP_STREAM << "[";
        operator << (static_cast<K>(pair_.first));
        _ELPP_STREAM << ", ";
        operator << (static_cast<V>(pair_.second));
        _ELPP_STREAM << "]";
        return *this;
    }
    template <class K, class V>
    inline LogWriter& operator<<(const QMap<K, V>& map_) {
        _ELPP_STREAM << "[";
        int index_ = 0;
        QList<K> keys = map_.keys();
        for (typename QList<K>::const_iterator it = keys.begin(); it != keys.end(); ++it) {
            _ELPP_STREAM << "[";
            operator << (static_cast<K>(*it));
            _ELPP_STREAM << ", ";
            operator << (static_cast<V>(map_.value(*it)));
            _ELPP_STREAM << "]";
            _ELPP_STREAM << (index_++ < map_.keys().size() -1 ? ", " : "");
        }
        _ELPP_STREAM << "]";
        return *this;
    }
#endif // defined(QT_CORE_LIB) && !defined(_DISABLE_CPP_THIRD_PARTY_LIBRARIES_LOGGING) && !defined(_DISABLE_CPP_LIBRARIES_LOGGING)
private:
    inline void writeLog(void) const {
        if (severityLevel_ == _ELPP_DEBUG_LEVEL_OUTPUT) {
#if (_ELPP_DEBUG_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_WARNING_LEVEL_OUTPUT) {
#if (_ELPP_WARNING_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_ERROR_LEVEL_OUTPUT) {
#if (_ELPP_ERROR_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_INFO_LEVEL_OUTPUT) {
#if (_ELPP_INFO_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_FATAL_LEVEL_OUTPUT) {
#if (_ELPP_FATAL_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_QA_LEVEL_OUTPUT) {
#if (_ELPP_QA_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_TRACE_LEVEL_OUTPUT) {
#if (_ELPP_TRACE_LOG)
            _WRITE_ELPP_LOG(logType_, severityLevel_, func_, file_, line_);
#endif
        } else if (severityLevel_ == _ELPP_VERBOSE_LEVEL_OUTPUT) {
#if (_ELPP_VERBOSE_LOG)
            if (logAspect_ == kNormal && _ELPP_LOGGER.appVerbose() >= verboseLevel_) {
                _ELPP_LOGGER.buildLine(logType_, severityLevel_, func_, file_, line_, verboseLevel_);
            } else if (logAspect_ == kConditional && condition_ && _ELPP_LOGGER.appVerbose() >= verboseLevel_) {
                _ELPP_LOGGER.buildLine(logType_, severityLevel_, func_, file_, line_, verboseLevel_);
            } else if (logAspect_ == kInterval && _ELPP_LOGGER.appVerbose() >= verboseLevel_) {
                if (_ELPP_LOGGER.registeredLogCounters()->valid(file_, line_, counter_)) {
                    _ELPP_LOGGER.buildLine(logType_, severityLevel_, func_, file_, line_, verboseLevel_);
                }
            }
#endif
        }
        _ELPP_LOGGER.clear();
    }
    unsigned int logAspect_;
    std::string logType_;
    std::string severityLevel_;
    const char* func_;
    const char* file_;
    const unsigned long int line_;
    bool condition_;
    unsigned int verboseLevel_;
    int counter_;
}; // class LogWriter

} // namespace internal

} // namespace easyloggingpp

//
// Performance tracking macros
//
#if _ELPP_DEBUG_LOG
#    define START_FUNCTION_LOG "Executing [" << __func__ << "]"
#    define TIME_OUTPUT "Executed [" << __func__ << "] in [" <<                                                 \
         easyloggingpp::internal::DateUtilities::formatMilliSeconds(                                            \
         easyloggingpp::internal::DateUtilities::getTimeDifference(functionEndTime, functionStartTime)) << "]"
#   define FUNC_SUB_COMMON_START {                                                                              \
        if (easyloggingpp::configurations::SHOW_START_FUNCTION_LOG) {                                           \
            PDEBUG << START_FUNCTION_LOG;                                                                       \
        }                                                                                                       \
        timeval functionStartTime, functionEndTime;                                                             \
        gettimeofday(&functionStartTime, NULL);
#    define FUNC_SUB_COMMON_END gettimeofday(&functionEndTime, NULL); PDEBUG << TIME_OUTPUT;
#    define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#    define END_SUB FUNC_SUB_COMMON_END }
#    define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#    define RETURN(return_value) FUNC_SUB_COMMON_END return return_value;
#    define END_FUNC(return_value) RETURN(return_value) }
#    define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#    define END_MAIN(return_value) FUNC_SUB_COMMON_END; return return_value; }
#    define RETURN_MAIN(exit_status) return exit_status;
#else
#    define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
#    define END_SUB }
#    define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
#    define END_FUNC(x) return x; }
#    define RETURN(expr) return expr;
#    define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#    define END_MAIN(x) return x; }
#    define RETURN_MAIN(exit_status) return exit_status;
#endif // _ELPP_DEBUG_LOG

namespace easyloggingpp {
namespace helper {

class MyEasyLog {
public:
    // Reads log from current log file an returns standard string
    static std::string readLog(void) {
        _ELPP_LOCK_MUTEX;
        std::stringstream ss;
        if (::easyloggingpp::configurations::SAVE_TO_FILE) {
            std::ifstream logFileReader(_QUALIFIED_LOGGER.kFinalFilename_.c_str(), std::ifstream::in);
            if (logFileReader.is_open()) {
                std::string line;
                while (logFileReader.good()) {
                    std::getline(logFileReader, line);
                    ss << line << std::endl;
                }
                logFileReader.close();
            } else {
                ss << "Error opening log file [" << _QUALIFIED_LOGGER.kFinalFilename_ << "]";
            }
        } else {
            ss << "Logs are not being saved to file!";
        }
        _ELPP_UNLOCK_MUTEX;
        return ss.str();
    }
}; // class MyEasyLog
} // namespace helper
} // namespace easyloggingpp

#define _ELPP_LOG_WRITER(_t, _l) LogWriter(LogWriter::kNormal, _t, _l, __func__, __FILE__, __LINE__)
#define _ELPP_LOG_WRITER_COND(_c, _t, _l) LogWriter(LogWriter::kConditional,_t, _l, __func__, __FILE__, __LINE__, _c)
#define _ELPP_LOG_WRITER_N(_n, _t, _l) LogWriter(LogWriter::kInterval,_t, _l, __func__, __FILE__, __LINE__, true, 0, _n)
//
// Custom injected loggers
//
// Normal loggers
#define CINFO(type_) _ELPP_LOG_WRITER(type_, _ELPP_INFO_LEVEL_OUTPUT)
#define CWARNING(type_) _ELPP_LOG_WRITER(type_, _ELPP_WARNING_LEVEL_OUTPUT)
#define CDEBUG(type_) _ELPP_LOG_WRITER(type_, _ELPP_DEBUG_LEVEL_OUTPUT)
#define CERROR(type_) _ELPP_LOG_WRITER(type_, _ELPP_ERROR_LEVEL_OUTPUT)
#define CFATAL(type_) _ELPP_LOG_WRITER(type_, _ELPP_FATAL_LEVEL_OUTPUT)
#define CQA(type_) _ELPP_LOG_WRITER(type_, _ELPP_QA_LEVEL_OUTPUT)
#define CTRACE(type_) _ELPP_LOG_WRITER(type_, _ELPP_TRACE_LEVEL_OUTPUT)
#define CVERBOSE(level, type_) LogWriter(LogWriter::kNormal,                                                \
    type_, _ELPP_VERBOSE_LEVEL_OUTPUT, __func__, __FILE__, __LINE__, true, level)
// Conditional logs
#define CINFO_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_INFO_LEVEL_OUTPUT)
#define CWARNING_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_WARNING_LEVEL_OUTPUT)
#define CDEBUG_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_DEBUG_LEVEL_OUTPUT)
#define CERROR_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_ERROR_LEVEL_OUTPUT)
#define CFATAL_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_FATAL_LEVEL_OUTPUT)
#define CQA_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_QA_LEVEL_OUTPUT)
#define CTRACE_IF(condition_, type_) _ELPP_LOG_WRITER_COND(condition_, type_, _ELPP_TRACE_LEVEL_OUTPUT)
#define CVERBOSE_IF(condition_, vlevel_, type_) LogWriter(LogWriter::kConditional,                           \
    type_, _ELPP_VERBOSE_LEVEL_OUTPUT, __func__, __FILE__, __LINE__, condition_, vlevel_)
// Interval logs
#define CINFO_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_INFO_LEVEL_OUTPUT)
#define CWARNING_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_WARNING_LEVEL_OUTPUT)
#define CDEBUG_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_DEBUG_LEVEL_OUTPUT)
#define CERROR_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_ERROR_LEVEL_OUTPUT)
#define CFATAL_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_FATAL_LEVEL_OUTPUT)
#define CQA_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_QA_LEVEL_OUTPUT)
#define CTRACE_EVERY_N(interval_, type_) _ELPP_LOG_WRITER_N(interval_, type_, _ELPP_TRACE_LEVEL_OUTPUT)
#define CVERBOSE_EVERY_N(interval_, level, type_) LogWriter(LogWriter::kInterval,                           \
    type_, _ELPP_VERBOSE_LEVEL_OUTPUT, __func__, __FILE__, __LINE__, true, level, interval_)
//
// Trivial Loggers
//
// Normal logs
#define LINFO CINFO("TrivialLogger")
#define LWARNING CWARNING("TrivialLogger")
#define LDEBUG CDEBUG("TrivialLogger")
#define LERROR CERROR("TrivialLogger")
#define LFATAL CFATAL("TrivialLogger")
#define LQA CQA("TrivialLogger")
#define LTRACE CTRACE("TrivialLogger")
#define LVERBOSE(level) CVERBOSE(level, "TrivialLogger")
// Conditional logs
#define LINFO_IF(condition) CINFO_IF(condition, "TrivialLogger")
#define LWARNING_IF(condition) CWARNING_IF(condition, "TrivialLogger")
#define LDEBUG_IF(condition) CDEBUG_IF(condition, "TrivialLogger")
#define LERROR_IF(condition) CERROR_IF(condition, "TrivialLogger")
#define LFATAL_IF(condition) CFATAL_IF(condition, "TrivialLogger")
#define LQA_IF(condition) CQA_IF(condition, "TrivialLogger")
#define LTRACE_IF(condition) CTRACE_IF(condition, "TrivialLogger")
#define LVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "TrivialLogger")
// Interval logs
#define LINFO_EVERY_N(n) CINFO_EVERY_N(n, "TrivialLogger")
#define LWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "TrivialLogger")
#define LDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "TrivialLogger")
#define LERROR_EVERY_N(n) CERROR_EVERY_N(n, "TrivialLogger")
#define LFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "TrivialLogger")
#define LQA_EVERY_N(n) CQA_EVERY_N(n, "TrivialLogger")
#define LTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "TrivialLogger")
#define LVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "TrivialLogger")
//
// Business Loggers
//
// Normal logs
#define BINFO CINFO("BusinessLogger")
#define BWARNING CWARNING("BusinessLogger")
#define BDEBUG CDEBUG("BusinessLogger")
#define BERROR CERROR("BusinessLogger")
#define BFATAL CFATAL("BusinessLogger")
#define BQA CQA("BusinessLogger")
#define BTRACE CTRACE("BusinessLogger")
#define BVERBOSE(level) CVERBOSE(level, "BusinessLogger")
// Conditional logs
#define BINFO_IF(condition) CINFO_IF(condition, "BusinessLogger")
#define BWARNING_IF(condition) CWARNING_IF(condition, "BusinessLogger")
#define BDEBUG_IF(condition) CDEBUG_IF(condition, "BusinessLogger")
#define BERROR_IF(condition) CERROR_IF(condition, "BusinessLogger")
#define BFATAL_IF(condition) CFATAL_IF(condition, "BusinessLogger")
#define BQA_IF(condition) CQA_IF(condition, "BusinessLogger")
#define BTRACE_IF(condition) CTRACE_IF(condition, "BusinessLogger")
#define BVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "BusinessLogger")
// Interval logs
#define BINFO_EVERY_N(n) CINFO_EVERY_N(n, "BusinessLogger")
#define BWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "BusinessLogger")
#define BDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "BusinessLogger")
#define BERROR_EVERY_N(n) CERROR_EVERY_N(n, "BusinessLogger")
#define BFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "BusinessLogger")
#define BQA_EVERY_N(n) CQA_EVERY_N(n, "BusinessLogger")
#define BTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "BusinessLogger")
#define BVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "BusinessLogger")
//
// Security Loggers
//
// Normal logs
#define SINFO CINFO("SecurityLogger")
#define SWARNING CWARNING("SecurityLogger")
#define SDEBUG CDEBUG("SecurityLogger")
#define SERROR CERROR("SecurityLogger")
#define SFATAL CFATAL("SecurityLogger")
#define SQA CQA("SecurityLogger")
#define STRACE CTRACE("SecurityLogger")
#define SVERBOSE(level) CVERBOSE(level, "SecurityLogger")
// Conditional logs
#define SINFO_IF(condition) CINFO_IF(condition, "SecurityLogger")
#define SWARNING_IF(condition) CWARNING_IF(condition, "SecurityLogger")
#define SDEBUG_IF(condition) CDEBUG_IF(condition, "SecurityLogger")
#define SERROR_IF(condition) CERROR_IF(condition, "SecurityLogger")
#define SFATAL_IF(condition) CFATAL_IF(condition, "SecurityLogger")
#define SQA_IF(condition) CQA_IF(condition, "SecurityLogger")
#define STRACE_IF(condition) CQA_IF(condition, "SecurityLogger")
#define SVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "SecurityLogger")
// Interval logs
#define SINFO_EVERY_N(n) CINFO_EVERY_N(n, "SecurityLogger")
#define SWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "SecurityLogger")
#define SDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "SecurityLogger")
#define SERROR_EVERY_N(n) CERROR_EVERY_N(n, "SecurityLogger")
#define SFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "SecurityLogger")
#define SQA_EVERY_N(n) CQA_EVERY_N(n, "SecurityLogger")
#define STRACE_EVERY_N(n) CTRACE_EVERY_N(n, "SecurityLogger")
#define SVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "SecurityLogger")
//
// Performance Loggers
//
// Normal logs
#define PINFO CINFO("PerformanceLogger")
#define PWARNING CWARNING("PerformanceLogger")
#define PDEBUG CDEBUG("PerformanceLogger")
#define PERROR CERROR("PerformanceLogger")
#define PFATAL CFATAL("PerformanceLogger")
#define PQA CQA("PerformanceLogger")
#define PTRACE CTRACE("PerformanceLogger")
#define PVERBOSE(level) CVERBOSE(level, "PerformanceLogger")
// Conditional logs
#define PINFO_IF(condition) CINFO_IF(condition, "PerformanceLogger")
#define PWARNING_IF(condition) CWARNING_IF(condition, "PerformanceLogger")
#define PDEBUG_IF(condition) CDEBUG_IF(condition, "PerformanceLogger")
#define PERROR_IF(condition) CERROR_IF(condition, "PerformanceLogger")
#define PFATAL_IF(condition) CFATAL_IF(condition, "PerformanceLogger")
#define PQA_IF(condition) CQA_IF(condition, "PerformanceLogger")
#define PTRACE_IF(condition) CQA_IF(condition, "PerformanceLogger")
#define PVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "PerformanceLogger")
// Interval logs
#define PINFO_EVERY_N(n) CINFO_EVERY_N(n, "PerformanceLogger")
#define PWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "PerformanceLogger")
#define PDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "PerformanceLogger")
#define PERROR_EVERY_N(n) CERROR_EVERY_N(n, "PerformanceLogger")
#define PFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "PerformanceLogger")
#define PQA_EVERY_N(n) CQA_EVERY_N(n, "PerformanceLogger")
#define PTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "PerformanceLogger")
#define PVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "PerformanceLogger")
// Legacy log macros
//
#ifdef _SUPPORT_LEGACY_LOG_NAMES
// Normal logs
#    define DEBUG(log_) LDEBUG << log_;
#    define INFO(log_) LINFO << log_;
#    define WARNING(log_) LWARNING << log_;
#    define ERROR(log_) LERROR << log_;
#    define FATAL(log_) LFATAL << log_;
#    define PERFORMANCE(log_) PINFO << log_;
#    define VERBOSE(vlevel_, log_) LVERBOSE(vlevel_) << log_;
#    define QA(log_) LQA << log_;
// Conditional logs
#    define DEBUG_IF(cond_, log_) LDEBUG_IF(cond_) << log_;
#    define INFO_IF(cond_, log_) LINFO_IF(cond_) << log_;
#    define WARNING_IF(cond_, log_) LWARNING_IF(cond_) << log_;
#    define ERROR_IF(cond_, log_) LERROR_IF(cond_) << log_;
#    define FATAL_IF(cond_, log_) LFATAL_IF(cond_) << log_;
#    define PERFORMANCE_IF(cond_, log_) PINFO_IF(cond_) << log_;
#    define VERBOSE_IF(cond_, vlevel_, log_) LVERBOSE_IF(cond_, vlevel_) << log_;
#    define QA_IF(cond_, log_) LQA << log_;
// Interval logs
#    define DEBUG_EVERY_N(n_, log_) LDEBUG_EVERY_N(n_) << log_;
#    define INFO_EVERY_N(n_, log_) LINFO_EVERY_N(n_) << log_;
#    define WARNING_EVERY_N(n_, log_) LWARNING_EVERY_N(n_) << log_;
#    define ERROR_EVERY_N(n_, log_) LERROR_EVERY_N(n_) << log_;
#    define FATAL_EVERY_N(n_, log_) LFATAL_EVERY_N(n_) << log_;
#    define PERFORMANCE_EVERY_N(n_, log_) PINFO_EVERY_N(n_) << log_;
#    define VERBOSE_EVERY_N(n_, vlevel_, log_) LVERBOSE_EVERY_N(n_, vlevel_) << log_;
#    define QA_EVERY_N(n_, log_) LQA_EVERY_N(n_) << log_;
#endif // _SUPPORT_LEGACY_LOG_NAMES

#define _START_EASYLOGGINGPP(argc, argv) \
    _ELPP_LOGGER.setArgs(argc, argv);

#define _INITIALIZE_EASYLOGGINGPP   \
    namespace easyloggingpp {       \
        namespace internal {        \
            Logger _ELPP_LOGGER;    \
        }                           \
    }

#define _END_EASYLOGGINGPP

using namespace easyloggingpp::internal;

#endif //EASYLOGGINGPP_H
