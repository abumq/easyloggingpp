///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
//   easylogging++.h - Core of EasyLogging++                                     //
//                                                                               //
//   EasyLogging++ v8.91                                                         //
//   Cross platform logging made easy for C++ applications                       //
//   Author Majid Khan <mkhan3189@gmail.com>                                     //
//   http://www.icplusplus.com/tools/easylogging                                 //
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
//  PLEASE NOTE: THIS FILE MAY BE CHANGED. TO GET ORIGINAL VERSION               //
//  EITHER DOWNLOAD IT FROM http://www.icplusplus.com/tools/easylogging/         //
//  OR PULL IT FROM https://github.com/mkhan3189/EasyLoggingPP (master branch)   //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H
//
// Log location macros
//
#if !defined(__FILE__)
#   define __FILE__ ""
#endif // !defined(__FILE__)
#if !defined(__LINE__)
#   define __LINE__ 0
#endif // !defined(__LINE__)
// Appropriate function macro
#if defined(__func__)
#   undef __func__
#endif // defined(__func__)
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   define __func__ __FUNCSIG__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
#   define __func__ __PRETTY_FUNCTION__
#elif defined(__clang__) && (__clang__ == 1)
#   define __func__ __PRETTY_FUNCTION__
#else
#   define __func__ ""
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)
//
// Compiler evaluation
// http://isocpp.org/blog/2013/05/gcc-4.8.1-released-c11-feature-complete
// http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx
//
// GNU
#if defined(__GNUC__)
#   define _ELPP_GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)
#   if defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define _ELPP_CXX0X 1
#   elif (_ELPP_GCC_VERSION >= 40801)
#      define _ELPP_CXX11 1
#   endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// VC++
#if defined(_MSC_VER)
#   if (_MSC_VER >= 1400) // VC++ 8.0
#      define _ELPP_CRT_DBG_WARNINGS 1
#   else
#      define _ELPP_CRT_DBG_WARNINGS 0
#   endif // (_MSC_VER >= 1400)
#   if (_MSC_VER == 1600)
#      define _ELPP_CXX0X 1
#   elif (_MSC_VER == 1700)
#      define _ELPP_CXX11 1
#   endif // (_MSC_VER == 1600)
#else
#   define _ELPP_CRT_DBG_WARNINGS 0
#endif // defined(_MSC_VER)
// Clang
#if defined(__clang__) && (__clang__ == 1)
#   define _ELPP_CLANG_VERSION (__clang_major__ * 10000 \
                                + __clang_minor__ * 100 \
                                + __clang_patchlevel__)
#   if (_ELPP_CLANG_VERSION >= 30300)
#      define _ELPP_CXX11 1
#   endif // (_ELPP_CLANG_VERSION >= 30300)
#endif // defined(__clang__) && (__clang__ == 1)
// MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
#   define _ELPP_MINGW 1
#else
#   define _ELPP_MINGW 0
#endif // defined(__MINGW32__) || defined(__MINGW64__)
#if defined(__ANDROID__)
#   define _ELPP_NDK 1
#else
#   define _ELPP_NDK 0
#endif // defined(__ANDROID__)
// Some special functions that are special for VC++
// This is to prevent CRT security warnings and to override deprecated methods but at the same time
// MinGW does not support some functions, so we need to make sure that proper function is used.
#if _ELPP_CRT_DBG_WARNINGS
#   define SPRINTF sprintf_s
#   define STRTOK(a,b,c) strtok_s(a,b,c)
#else
#   define SPRINTF sprintf
#   define STRTOK(a,b,c) strtok(a,b)
#endif
// std::thread availablity
#if defined(__GNUC__) && (!_ELPP_NDK) && (_ELPP_CXX0X || _ELPP_CXX11)
#   define _ELPP_STD_THREAD_AVAILABLE 1
#elif defined(_MSC_VER) && (!_ELPP_NDK) && (_ELPP_CXX11)
#   define _ELPP_STD_THREAD_AVAILABLE 1
#elif defined(__clang__) && (!_ELPP_NDK) && (__clang__ == 1) && (_ELPP_CXX11)
#   define _ELPP_STD_THREAD_AVAILABLE 1
#else
#   define _ELPP_STD_THREAD_AVAILABLE 0
#endif // defined(__GNUC__) && (_ELPP_CXX0X || _ELPP_CXX11)
// Qt
#if defined(QT_CORE_LIB)
#   if (defined(QT_VERSION) && QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#      define _ELPP_QT_5 1
#   else
#      define _ELPP_QT_5 0
#   endif // (defined(QT_VERSION) && QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#endif // defined(QT_CORE_LIB)
//
// High-level log evaluation
//
#if (defined(_DISABLE_LOGS))
#   define _ENABLE_EASYLOGGING 0
#else
#   define _ENABLE_EASYLOGGING 1
#endif // (!defined(_DISABLE_LOGS))
//
// OS evaluation
//
// Windows
#if defined(_WIN32) || defined(_WIN64)
#   define _ELPP_OS_WINDOWS 1
#else
#   define _ELPP_OS_WINDOWS 0
#endif // defined(_WIN32) || defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
#   define _ELPP_OS_LINUX 1
#else
#   define _ELPP_OS_LINUX 0
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
#   define _ELPP_OS_MAC 1
#else
#   define _ELPP_OS_MAC 0
#endif // defined(__APPLE__)
// Unix
#define _ELPP_OS_UNIX ((_ELPP_OS_LINUX || _ELPP_OS_MAC) && (!_ELPP_OS_WINDOWS))
// Assembly
#if (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))) ||     \
    (defined(_MSC_VER) && (defined(_M_IX86)))
#   define _ELPP_ASSEMBLY_SUPPORTED 1
#else
#   define _ELPP_ASSEMBLY_SUPPORTED 0
#endif
#if (!defined(_DISABLE_ELPP_ASSERT))
#   if (defined(_STOP_ON_FIRST_ELPP_ASSERTION))
#      define __EASYLOGGINGPP_ASSERT(expr, msg) if (!(expr)) { std::cerr << "EASYLOGGING++ ASSERTION FAILED (LINE: " << __LINE__ << ") [" #expr << "] with message \"" << msg << "\"" << std::endl; exit(1); }
#   else
#      define __EASYLOGGINGPP_ASSERT(expr, msg) if (!(expr)) { std::cerr << "EASYLOGGING++ ASSERTION FAILED (LINE: " << __LINE__ << ") [" #expr << "] with message \"" << msg << "\"" << std::endl; }
#   endif // (defined(_STOP_ON_FIRST_ELPP_ASSERTION))
#else
#   define __EASYLOGGINGPP_ASSERT(x, y)
#endif // (!defined(_DISABLE_ELPP_ASSERT))
#define __EASYLOGGINGPP_SUPPRESS_UNSED(x) (void)x;
#if _ELPP_OS_UNIX
// Log file permissions for unix-based systems
#   define _LOG_PERMS S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH
#endif // _ELPP_OS_UNIX
#if (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
#   define _ELPP_ENABLE_MUTEX 1
#else
#   define _ELPP_ENABLE_MUTEX 0
#endif // (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
#if (!defined(_DISABLE_DEBUG_LOGS) && (_ENABLE_EASYLOGGING) && ((defined(_DEBUG)) || (!defined(NDEBUG))))
#   define _ELPP_DEBUG_LOG 1
#else
#   define _ELPP_DEBUG_LOG 0
#endif // (!defined(_DISABLE_DEBUG_LOGS) && (_ENABLE_EASYLOGGING) && ((defined(_DEBUG)) || (!defined(NDEBUG))))
#if (!defined(_DISABLE_INFO_LOGS) && (_ENABLE_EASYLOGGING))
#   define _ELPP_INFO_LOG 1
#else
#   define _ELPP_INFO_LOG 0
#endif // (!defined(_DISABLE_INFO_LOGS) && (_ENABLE_EASYLOGGING))
#if (!defined(_DISABLE_WARNING_LOGS) && (_ENABLE_EASYLOGGING))
#   define _ELPP_WARNING_LOG 1
#else
#   define _ELPP_WARNING_LOG 0
#endif // (!defined(_DISABLE_WARNING_LOGS) && (_ENABLE_EASYLOGGING))
#if (!defined(_DISABLE_ERROR_LOGS) && (_ENABLE_EASYLOGGING))
#   define _ELPP_ERROR_LOG 1
#else
#   define _ELPP_ERROR_LOG 0
#endif // (!defined(_DISABLE_ERROR_LOGS) && (_ENABLE_EASYLOGGING))
#if (!defined(_DISABLE_FATAL_LOGS) && (_ENABLE_EASYLOGGING))
#   define _ELPP_FATAL_LOG 1
#else
#   define _ELPP_FATAL_LOG 0
#endif // (!defined(_DISABLE_FATAL_LOGS) && (_ENABLE_EASYLOGGING))
#if (defined(_QUALITY_ASSURANCE) && (_ENABLE_EASYLOGGING))
#   define _ELPP_QA_LOG 1
#else
#   define _ELPP_QA_LOG 0
#endif // (defined(_QUALITY_ASSURANCE) && (_ENABLE_EASYLOGGING))
#if (!defined(_DISABLE_TRACE_LOGS) && (_ENABLE_EASYLOGGING))
#   define _ELPP_TRACE_LOG 1
#else
#   define _ELPP_TRACE_LOG 0
#endif // (!defined(_DISABLE_TRACE_LOGS) && (_ENABLE_EASYLOGGING))
#if (!defined(_DISABLE_VERBOSE_LOGS) && (_ENABLE_EASYLOGGING))
#   define _ELPP_VERBOSE_LOG 1
#else
#   define _ELPP_VERBOSE_LOG 0
#endif // (!defined(_DISABLE_VERBOSE_LOGS) && (_ENABLE_EASYLOGGING))
#define ELPP_FOR_EACH(variableName, initialValue, operation, limit) unsigned int variableName = initialValue; \
                                                                    do { \
                                                                        operation   \
                                                                        variableName = variableName << 1; \
                                                                        if (variableName == 0) { ++variableName; } \
                                                                    } while (variableName <= limit)
#define ELPP_FOR_EACH_LEVEL(variableName, initialValue, operation) \
    ELPP_FOR_EACH(variableName, initialValue, operation, easyloggingpp::Level::kMaxValid)
#define ELPP_FOR_EACH_CONFIGURATION(variableName, initialValue, operation) \
    ELPP_FOR_EACH(variableName, initialValue, operation, easyloggingpp::ConfigurationType::kMaxValid)
// Includes
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cwchar>
#if _ELPP_NDK
#   include <sys/system_properties.h>
#endif // _ELPP_NDK
#if _ELPP_OS_UNIX
#   include <sys/stat.h>
#   include <sys/time.h>
#   if (_ELPP_ENABLE_MUTEX)
#      if (_ELPP_ASSEMBLY_SUPPORTED)
#         include <sched.h>
#      else
#         include <pthread.h>
#      endif // (_ELPP_ASSEMBLY_SUPPORTED)
#   endif // (_ELPP_ENABLE_MUTEX)
#elif _ELPP_OS_WINDOWS
#   include <direct.h>
#   include <Windows.h>
#endif // _ELPP_OS_UNIX
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#if (_ELPP_STD_THREAD_AVAILABLE)
#   include <thread>
#endif // _ELPP_STD_THREAD_AVAILABLE
#if defined(_ELPP_STL_LOGGING)
// For logging STL based templates
#   include <list>
#   include <utility>
#   include <queue>
#   include <deque>
#   include <set>
#   include <bitset>
#   include <stack>
#endif // defined(_ELPP_STL_LOGGING)
#if defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
// For logging Qt based classes & templates
#   include <QString>
#   include <QVector>
#   include <QList>
#   include <QPair>
#   include <QMap>
#   include <QQueue>
#   include <QSet>
#   include <QLinkedList>
#   include <QHash>
#   include <QMultiHash>
#   include <QStack>
#endif // defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
namespace easyloggingpp {
namespace internal {

class NoCopy {
protected:
    NoCopy(void) {}
private:
    NoCopy(const NoCopy&);
    NoCopy& operator=(const NoCopy&);
};

class StaticClass {
private:
    StaticClass(void);
    StaticClass(const StaticClass&);
    StaticClass& operator=(const StaticClass&);
};
} // namespace internal

struct Level : private internal::StaticClass {
public:
    enum {
        All = 0, Debug = 1, Info = 2, Warning = 4, Error = 8,
        Fatal = 16, Verbose = 32, QA = 64, Trace = 128, Unknown = 1010
    };

    static const unsigned int kMinValid = All;
    static const unsigned int kMaxValid = Trace;

    static std::string convertToString(unsigned int level_) {
        switch (level_) {
        case All:
            return std::string("ALL");
        case Debug:
            return std::string("DEBUG");
        case Info:
            return std::string("INFO");
        case Warning:
            return std::string("WARNING");
        case Error:
            return std::string("ERROR");
        case Fatal:
            return std::string("FATAL");
        case QA:
            return std::string("QA");
        case Verbose:
            return std::string("VERBOSE");
        case Trace:
            return std::string("TRACE");
        default:
            return std::string("UNKNOWN");
        }
    }

    static unsigned int convertFromString(const std::string& levelStr) {
        if (levelStr == "all" || levelStr == "ALL") return Level::All;
        if (levelStr == "debug" || levelStr == "DEBUG") return Level::Debug;
        if (levelStr == "info" || levelStr == "INFO") return Level::Info;
        if (levelStr == "warning" || levelStr == "WARNING") return Level::Warning;
        if (levelStr == "error" || levelStr == "ERROR") return Level::Error;
        if (levelStr == "fatal" || levelStr == "FATAL") return Level::Fatal;
        if (levelStr == "qa" || levelStr == "QA") return Level::QA;
        if (levelStr == "verbose" || levelStr == "VERBOSE") return Level::Verbose;
        if (levelStr == "trace" || levelStr == "TRACE") return Level::Trace;
        return Level::Unknown;
    }
};

struct ConfigurationType : private internal::StaticClass {
public:
    enum {
        Enabled = 0, ToFile = 1, ToStandardOutput = 2, Format = 4, Filename = 8,
        MillisecondsWidth = 16, PerformanceTracking = 32, RollOutSize = 64, Unknown = 1010
    };

    static const unsigned int kMinValid = Enabled;
    static const unsigned int kMaxValid = RollOutSize;

    static std::string convertToString(unsigned int configurationType_) {
        switch (configurationType_) {
        case Enabled:
            return std::string("ENABLED");
        case Filename:
            return std::string("FILENAME");
        case Format:
            return std::string("FORMAT");
        case ToFile:
            return std::string("TO_FILE");
        case ToStandardOutput:
            return std::string("TO_STANDARD_OUTPUT");
        case MillisecondsWidth:
            return std::string("MILLISECONDS_WIDTH");
        case PerformanceTracking:
            return std::string("PERFORMANCE_TRACKING");
        case RollOutSize:
            return std::string("ROLL_OUT_SIZE");
        default: return std::string("UNKNOWN");
        }
    }

    static unsigned int convertFromString(const std::string& configStr) {
        if (configStr == "enabled" || configStr == "ENABLED") return ConfigurationType::Enabled;
        if (configStr == "to_file" || configStr == "TO_FILE") return ConfigurationType::ToFile;
        if (configStr == "to_standard_output" || configStr == "TO_STANDARD_OUTPUT") return ConfigurationType::ToStandardOutput;
        if (configStr == "format" || configStr == "FORMAT") return ConfigurationType::Format;
        if (configStr == "filename" || configStr == "FILENAME") return ConfigurationType::Filename;
        if (configStr == "milliseconds_width" || configStr == "MILLISECONDS_WIDTH") return ConfigurationType::MillisecondsWidth;
        if (configStr == "performance_tracking" || configStr == "PERFORMANCE_TRACKING") return ConfigurationType::PerformanceTracking;
        if (configStr == "roll_out_size" || configStr == "ROLL_OUT_SIZE") return ConfigurationType::RollOutSize;
        return ConfigurationType::Unknown;
    }
};

namespace internal {
struct Aspect : private internal::StaticClass {
public:
    enum {
        Normal = 0, Conditional = 1, Interval = 2
    };
};

//!
//! Used internally. You should not need this class.
//!
class Constants : private internal::NoCopy {
public:
    Constants (void) :
        //
        // Log level name outputs
        //
        LOG_INFO_LEVEL_VALUE   ("INFO") ,
        LOG_DEBUG_LEVEL_VALUE  ("DEBUG"),
        LOG_WARNING_LEVEL_VALUE("WARN"),
        LOG_ERROR_LEVEL_VALUE  ("ERROR"),
        LOG_FATAL_LEVEL_VALUE  ("FATAL"),
        LOG_VERBOSE_LEVEL_VALUE("VER"),
        LOG_QA_LEVEL_VALUE     ("QA"),
        LOG_TRACE_LEVEL_VALUE  ("TRACE"),
        //
        // Format specifiers
        //
        APP_NAME_FORMAT_SPECIFIER      ("%app"),
        LOGGER_ID_FORMAT_SPECIFIER     ("%logger"),
        THREAD_ID_FORMAT_SPECIFIER     ("%thread"),
        LEVEL_FORMAT_SPECIFIER         ("%level"),
        DATE_ONLY_FORMAT_SPECIFIER     ("%date"),
        TIME_ONLY_FORMAT_SPECIFIER     ("%time"),
        DATE_TIME_FORMAT_SPECIFIER     ("%datetime"),
        LOCATION_FORMAT_SPECIFIER      ("%loc"),
        FUNCTION_FORMAT_SPECIFIER      ("%func"),
        USER_FORMAT_SPECIFIER          ("%user"),
        HOST_FORMAT_SPECIFIER          ("%host"),
        LOG_MESSAGE_FORMAT_SPECIFIER   ("%log"),
        VERBOSE_LEVEL_FORMAT_SPECIFIER ("%vlevel"),
        //
        // Others
        //
        NULL_POINTER                  ("nullptr"),
        FORMAT_SPECIFIER_ESCAPE_CHAR  ('E'),
        MAX_LOG_PER_CONTAINER         (100),
        MAX_LOG_PER_COUNTER           (100000),
        DEFAULT_MILLISECOND_OFFSET    (1000),
        MAX_VERBOSE_LEVEL             (9),
        CURRENT_VERBOSE_LEVEL         (0),  // Set dynamically from registeredLoggers
#if _ELPP_OS_UNIX
        PATH_SLASH                    ("/"),
#elif _ELPP_OS_WINDOWS
        PATH_SLASH                    ("\\"),
#endif // _ELPP_OS_UNIX,
        DEFAULT_LOG_FILENAME          ("myeasylog.log")
    {
        // Trivial logger configuration - only to set format (difference: not using %logger)
        std::stringstream ss;
        ss << " * ALL:\n";
        ss << "    FORMAT               =  %datetime %level  %log\n";
        ss << "* DEBUG:\n";
        ss << "    FORMAT               =  %datetime %level [%user@%host] [%func] [%loc] %log\n";
        // INFO and WARNING uses is defined by ALL
        ss << "* ERROR:\n";
        ss << "    FORMAT               =  %datetime %level %log\n";
        ss << "* FATAL:\n";
        ss << "    FORMAT               =  %datetime %level %log\n";
        ss << "* QA:\n";
        ss << "    FORMAT               =  %datetime %level    %log\n";
        ss << "* VERBOSE:\n";
        ss << "    FORMAT               =  %datetime %level-%vlevel %log\n";
        ss << "* TRACE:\n";
        ss << "    FORMAT               =  %datetime %level [%func] [%loc] %log\n";
        DEFAULT_LOGGER_CONFIGURATION = ss.str();
    } // C'tor
    //
    // Log level name outputs
    //
    const std::string LOG_INFO_LEVEL_VALUE;
    const std::string LOG_DEBUG_LEVEL_VALUE;
    const std::string LOG_WARNING_LEVEL_VALUE;
    const std::string LOG_ERROR_LEVEL_VALUE;
    const std::string LOG_FATAL_LEVEL_VALUE;
    const std::string LOG_VERBOSE_LEVEL_VALUE;
    const std::string LOG_QA_LEVEL_VALUE;
    const std::string LOG_TRACE_LEVEL_VALUE;
    //
    // Format specifiers
    //
    const std::string APP_NAME_FORMAT_SPECIFIER;
    const std::string LOGGER_ID_FORMAT_SPECIFIER;
    const std::string THREAD_ID_FORMAT_SPECIFIER;
    const std::string LEVEL_FORMAT_SPECIFIER;
    const std::string DATE_ONLY_FORMAT_SPECIFIER;
    const std::string TIME_ONLY_FORMAT_SPECIFIER;
    const std::string DATE_TIME_FORMAT_SPECIFIER;
    const std::string LOCATION_FORMAT_SPECIFIER;
    const std::string FUNCTION_FORMAT_SPECIFIER;
    const std::string USER_FORMAT_SPECIFIER;
    const std::string HOST_FORMAT_SPECIFIER;
    const std::string LOG_MESSAGE_FORMAT_SPECIFIER;
    const std::string VERBOSE_LEVEL_FORMAT_SPECIFIER;
    //
    // Others
    //
    const std::string     NULL_POINTER;
    const char            FORMAT_SPECIFIER_ESCAPE_CHAR;
    const unsigned int    MAX_LOG_PER_CONTAINER;
    const unsigned int    MAX_LOG_PER_COUNTER;
    const unsigned int    DEFAULT_MILLISECOND_OFFSET;
    const int             MAX_VERBOSE_LEVEL;
    int                   CURRENT_VERBOSE_LEVEL;
    const std::string     PATH_SLASH;
    const std::string     DEFAULT_LOG_FILENAME;
    std::string           DEFAULT_LOGGER_CONFIGURATION;

    enum kFormatFlags {
                        kDateOnly = 2,
                        kTimeOnly = 4,
                        kDateTime = 8,
                        kLoggerId = 16,
                        kLocation = 32,
                        kFunction = 64,
                        kUser = 128,
                        kHost = 256,
                        kLogMessage = 512,
                        kVerboseLevel = 1024,
                        kAppName = 2048,
                        kThreadId = 4096
                      };
}; // class Constants
namespace threading {

//!
//! To take care of shared resources in multi-threaded application. Used internally, you should not need it.
//!
class Mutex {
public:
#if _ELPP_ASSEMBLY_SUPPORTED
#   if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#      define _ELPP_MUTEX_LOCK_GNU_ASM(lf_, old_) "movl $1,%%eax\n"       \
    "\txchg %%eax,%0\n"   \
    "\tmovl %%eax,%1\n"   \
    "\t" : "=m" (lf_), "=m" (old_) : : "%eax", "memory"
#      define _ELPP_MUTEX_UNLOCK_GNU_ASM(lf_)     "movl $0,%%eax\n"                                \
    "\txchg %%eax,%0\n"                            \
    "\t" : "=m" (lf_) : : "%eax", "memory"
#   endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    Mutex(void) : lockerFlag_(0) {
    }
#else
    Mutex(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_init(&underlyingMutex_, NULL);
#   elif _ELPP_OS_WINDOWS
        InitializeCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
    }

    virtual ~Mutex(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_destroy(&underlyingMutex_);
#   elif _ELPP_OS_WINDOWS
        DeleteCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
    }
#endif // _ELPP_ASSEMBLY_SUPPORTED

    inline void lock(void) {
#if _ELPP_ASSEMBLY_SUPPORTED
        bool locked = false;
        while (!locked) {
            locked = tryLock();
            if (!locked) {
#   if _ELPP_OS_UNIX
                sched_yield();
#   elif _ELPP_OS_WINDOWS
                Sleep(0);
#   endif
            }
        }
#else
#   if _ELPP_OS_UNIX
        pthread_mutex_lock(&underlyingMutex_);
#   elif _ELPP_OS_WINDOWS
        EnterCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
    }

    inline bool tryLock(void) {
#if _ELPP_ASSEMBLY_SUPPORTED
        int oldLock_;
#   if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile (_ELPP_MUTEX_LOCK_GNU_ASM(lockerFlag_, oldLock_));
#   elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &lockerFlag_;
        __asm {
            mov eax,1
                    mov ecx,ptrLock
                    xchg eax,[ecx]
                    mov oldLock_,eax
        }
#   endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        return (oldLock_ == 0);
#else
#   if _ELPP_OS_UNIX
        return (pthread_mutex_trylock(&underlyingMutex_) == 0) ? true : false;
#   elif _ELPP_OS_WINDOWS
        return TryEnterCriticalSection(&underlyingMutex_) ? true : false;
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
    }

    inline void unlock(void) {
#if _ELPP_ASSEMBLY_SUPPORTED
#   if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile (_ELPP_MUTEX_UNLOCK_GNU_ASM(lockerFlag_));
#   elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &lockerFlag_;
        __asm {
            mov eax,0
                    mov ecx,ptrLock
                    xchg eax,[ecx]
        }
#   endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#else
#   if _ELPP_OS_UNIX
        pthread_mutex_unlock(&underlyingMutex_);
#   elif _ELPP_OS_WINDOWS
        LeaveCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
    }
private:
#if _ELPP_ASSEMBLY_SUPPORTED
    int lockerFlag_;
#else
#   if _ELPP_OS_UNIX
    pthread_mutex_t underlyingMutex_;
#   elif _ELPP_OS_WINDOWS
    CRITICAL_SECTION underlyingMutex_;
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
}; // class Mutex
//!
//! Scoped mutex that works same as C++11 <code>std::lock_guard<std::mutex></code>. Used internally, you should not use it.
//!
class ScopedLock : private internal::NoCopy {
public:
    explicit ScopedLock(Mutex& m_) {
        mutex_ = &m_;
        mutex_->lock();
    }

    virtual ~ScopedLock(void) {
        mutex_->unlock();
    }
private:
    Mutex* mutex_;
    ScopedLock(void);
}; // class ScopedLock

//!
//! \return ID of current thread. If std::thread is available it uses get_id() otherwise if on windows it uses
//!         GetCurrentThreadId() otherwise empty string. Used internally, you should not use it.
//!
inline std::string getCurrentThreadId(void) {
    std::stringstream ss;
#if (_ELPP_STD_THREAD_AVAILABLE)
    ss << std::this_thread::get_id();
#else
#   if (_ELPP_OS_WINDOWS)
    ss << GetCurrentThreadId();
#   endif // (_ELPP_OS_WINDOWS)
#endif
    return ss.str();
}

} // namespace threading
namespace utilities {

template <typename T>
inline void safeDelete(T*& pointer, bool checkNullity = true) {
    if (checkNullity && pointer == NULL) return;
    delete pointer;
    pointer = NULL;
}

//!
//! String utilities class used internally. You should not use it.
//!
class StringUtils : private internal::StaticClass {
public:
    static inline std::string trim(const std::string &str) {
        std::size_t s = str.find_first_not_of(" \n\r\t");
        std::size_t e = str.find_last_not_of(" \n\r\t");
        if ((s == std::string::npos) || (e == std::string::npos)) {
            return "";
        }
        else {
            return str.substr(s, e - s + 1);
        }
    }

    static inline bool startsWith(const std::string& str, const std::string& start) {
        return (str.length() >= start.length()) && (str.compare(0, start.length(), start) == 0);
    }

    static inline bool endsWith(const std::string& str, const std::string& end) {
        return (str.length() >= end.length()) && (str.compare(str.length() - end.length(), end.length(), end) == 0);
    }

    static inline std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    static inline std::string replaceAll(const std::string& str, const std::string& replaceWhat, const std::string& replaceWith) {
        if (replaceWhat == replaceWith)
            return str;
        std::string result = str;
        std::size_t foundAt = std::string::npos;
        while ((foundAt = result.find(replaceWhat)) != std::string::npos) {
            result.replace(foundAt, replaceWhat.length(), replaceWith);
        }
        return result;
    }

    static inline std::string stripAllWhiteSpaces(const std::string& str) {
        std::string result = replaceAll(str, " ", "");
        result = replaceAll(result, "\n", "");
        result = replaceAll(result, "\r", "");
        result = replaceAll(result, "\t", "");
        return result;
    }

    static inline void tolower(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
};

//!
//! Operating System utilities class used internally. You should not use it.
//!
class OSUtils : private internal::StaticClass {
public:
#if _ELPP_OS_WINDOWS
    static const char* getWindowsEnvironmentVariable(const char* variableName) {
        const DWORD bufferLen = 50;
        static char buffer[bufferLen];
        if (GetEnvironmentVariableA(variableName, buffer, bufferLen)) {
            return buffer;
        }
        return NULL;
    }
#endif // _ELPP_OS_WINDOWS
#if _ELPP_NDK
    static std::string getProperty(const char* prop) {
        char propVal[PROP_VALUE_MAX + 1];
        __system_property_get(prop, propVal);
        return std::string(propVal);
    }

    static std::string getDeviceName(void) {
        std::stringstream ss;
        std::string manufacturer = getProperty("ro.product.manufacturer");
        std::string model = getProperty("ro.product.model");
        if (manufacturer.empty() && model.empty()) {
            return std::string();
        }
        ss << manufacturer << " " << model;
        return ss.str();
    }
#endif // _ELPP_NDK
    // Runs command on terminal and returns the output.
    // This is applicable only on linux and mac, for all other OS, an empty string is returned.
    static const std::string getBashOutput(const char* command_) {
        if (command_ == NULL) {
            return std::string();
        }
#if _ELPP_OS_UNIX && !_ELPP_NDK
        FILE* proc = NULL;
        if ((proc = popen(command_, "r")) == NULL) {
            std::cerr << "\nUnable to run command [" << command_ << "]" << std::endl;
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

    static std::string getEnvironmentVariable(const char* variableName, const char* defaultVal, const char* alternativeBashCommand = NULL) {
#if _ELPP_OS_UNIX
        const char* val = getenv(variableName);
#elif _ELPP_OS_WINDOWS
        const char* val = getWindowsEnvironmentVariable(variableName);
#endif // _ELPP_OS_UNIX
        if ((val == NULL) || ((strcmp(val, "") == 0))) {
#if _ELPP_OS_UNIX
            // Try harder on unix-based systems
            std::string valBash = internal::utilities::OSUtils::getBashOutput(alternativeBashCommand);
            if (valBash.empty()) {
                return std::string(defaultVal);
            } else {
                return valBash;
            }
#elif _ELPP_OS_WINDOWS
            return std::string(defaultVal);
#endif // _ELPP_OS_WINDOWS
        }
        return std::string(val);
    }

    // Gets current username.
    static const std::string currentUser(void) {
#if _ELPP_OS_UNIX && !_ELPP_NDK
        return getEnvironmentVariable("USER", "user", "whoami");
#elif _ELPP_OS_WINDOWS
        return getEnvironmentVariable("USERNAME", "user");
#elif _ELPP_NDK
        return std::string("android");
#else
        return std::string();
#endif // _ELPP_OS_UNIX
    }

    // Gets current host name or computer name.
    static const std::string currentHost(void) {
#if _ELPP_OS_UNIX && !_ELPP_NDK
        return getEnvironmentVariable("HOSTNAME", "unknown-host", "hostname");
#elif _ELPP_OS_WINDOWS
        return getEnvironmentVariable("COMPUTERNAME", "unknown-host");
#elif _ELPP_NDK
        return getDeviceName();
#else
        return std::string();
#endif // _ELPP_OS_UNIX
    }

    // Determines whether or not provided path_ exist in current file system
    static inline bool pathExists(const char* path_) {
        if (path_ == NULL) {
            return false;
        }
#if _ELPP_OS_UNIX
        struct stat st;
        return (stat(path_, &st) == 0);
#elif _ELPP_OS_WINDOWS
        DWORD fileType = GetFileAttributesA(path_);
        if (fileType == INVALID_FILE_ATTRIBUTES) {
            return false;
        }
        return (fileType & FILE_ATTRIBUTE_DIRECTORY) == 0 ? false : true;
#endif // _ELPP_OS_UNIX
    }

    // Creates path as specified
    static bool createPath(const std::string& path_) {
        if (path_.empty()) {
            return false;
        }
        if (internal::utilities::OSUtils::pathExists(path_.c_str())) {
            return true;
        }
#if _ELPP_OS_UNIX
        const char* pathDelim_ = "/";
#elif _ELPP_OS_WINDOWS
        char pathDelim_[] = "\\";
#endif // _ELPP_OS_UNIX
        int status = -1;

        char* currPath_ = const_cast<char*>(path_.c_str());
        std::string buildingPath_ = std::string();
#if _ELPP_OS_UNIX
        if (path_[0] == '/') {
            buildingPath_ = "/";
        }
        currPath_ = STRTOK(currPath_, pathDelim_, 0);
#elif _ELPP_OS_WINDOWS
        // Use secure functions API
        char* nextTok_;
        currPath_ = STRTOK(currPath_, pathDelim_, &nextTok_);
#endif // _ELPP_OS_UNIX
        while (currPath_ != NULL) {
            buildingPath_.append(currPath_);
            buildingPath_.append(pathDelim_);
#if _ELPP_OS_UNIX
            status = mkdir(buildingPath_.c_str(), _LOG_PERMS);
            currPath_ = STRTOK(NULL, pathDelim_, 0);
#elif _ELPP_OS_WINDOWS
            status = _mkdir(buildingPath_.c_str());
            currPath_ = STRTOK(NULL, pathDelim_, &nextTok_);
#endif // _ELPP_OS_UNIX
        }
        if (status == -1) {
            return false;
        }
        return true;
    }

    static std::string getPathFromFilename(const std::string& fullPath_, internal::Constants* constants_) {
        if (fullPath_ == "" || fullPath_.find(constants_->PATH_SLASH) == std::string::npos) {
            return fullPath_;
        }
        std::size_t lastSlashAt = fullPath_.find_last_of(constants_->PATH_SLASH);
        if (lastSlashAt == 0) {
            return constants_->PATH_SLASH;
        }
        return fullPath_.substr(0, lastSlashAt + 1);
    }
}; // class OSUtils

//!
//! Contains static functions related to log manipulation used internally. You should not use it.
//!
class LogManipulator : private internal::StaticClass {
public:
    // Updates the formatSpecifier_ for currentFormat_ to value_ provided
    static void updateFormatValue(const std::string& formatSpecifier_,
                                  const std::string& value_, std::string& currentFormat_,
                                  internal::Constants* constants_) {
        std::size_t foundAt = std::string::npos;
        while ((foundAt = currentFormat_.find(formatSpecifier_, foundAt + 1)) != std::string::npos){
            if (currentFormat_[foundAt > 0 ? foundAt - 1 : 0] == constants_->FORMAT_SPECIFIER_ESCAPE_CHAR) {
                currentFormat_.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
                ++foundAt;
            } else {
                currentFormat_ = currentFormat_.replace(foundAt, formatSpecifier_.size(), value_);
                return;
            }
        }
    }
}; // class LogManipulator

//!
//! Contains utility functions related to date/time used internally. You should not use it.
//!
class DateUtils : private internal::StaticClass {
public:
#if _ELPP_OS_WINDOWS
    static void gettimeofday(struct timeval *tv) {
        if (tv != NULL) {
#   if defined(_MSC_EXTENSIONS)
            const unsigned __int64 delta_ = 11644473600000000Ui64;
#   else
            const unsigned __int64 delta_ = 11644473600000000ULL;
#   endif // defined(_MSC_EXTENSIONS)
            const double secOffSet = 0.000001;
            const unsigned long usecOffSet = 1000000;
            FILETIME fileTime_;
            GetSystemTimeAsFileTime(&fileTime_);
            unsigned __int64 present_ = 0;
            present_ |= fileTime_.dwHighDateTime;
            present_ = present_ << 32;
            present_ |= fileTime_.dwLowDateTime;
            present_ /= 10; // mic-sec
            // Subtract the difference
            present_ -= delta_;
            tv->tv_sec = static_cast<long>(present_ * secOffSet);
            tv->tv_usec = static_cast<long>(present_ % usecOffSet);
        }
    }
#endif // _ELPP_OS_WINDOWS

    // Gets current date and time with milliseconds.
    static std::string getDateTime(const std::string& bufferFormat_, unsigned int type_, internal::Constants* constants_, std::size_t milliSecondOffset_ = 1000) {
        long milliSeconds = 0;
        const int kDateBuffSize_ = 30;
        char dateBuffer_[kDateBuffSize_] = "";
        char dateBufferOut_[kDateBuffSize_] = "";
#if _ELPP_OS_UNIX
        bool hasTime_ = ((type_ & constants_->kDateTime) || (type_ & constants_->kTimeOnly));
        timeval currTime;
        gettimeofday(&currTime, NULL);
        if (hasTime_) {
            milliSeconds = currTime.tv_usec / milliSecondOffset_ ;
        }
        struct tm * timeInfo = localtime(&currTime.tv_sec);
        strftime(dateBuffer_, sizeof(dateBuffer_), bufferFormat_.c_str(), timeInfo);
        if (hasTime_) {
            SPRINTF(dateBufferOut_, "%s.%03ld", dateBuffer_, milliSeconds);
        } else {
            SPRINTF(dateBufferOut_, "%s", dateBuffer_);
        }
#elif _ELPP_OS_WINDOWS
        const char* kTimeFormatLocal_ = "HH':'mm':'ss";
        const char* kDateFormatLocal_ = "dd/MM/yyyy";
        if ((type_ & constants_->kDateTime) || (type_ & constants_->kDateOnly)) {
            if (GetDateFormatA(LOCALE_USER_DEFAULT, 0, 0, kDateFormatLocal_, dateBuffer_, kDateBuffSize_) != 0) {
                SPRINTF(dateBufferOut_, "%s", dateBuffer_);
            }
        }
        if ((type_ & constants_->kDateTime) || (type_ & constants_->kTimeOnly)) {
            if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, kTimeFormatLocal_, dateBuffer_, kDateBuffSize_) != 0) {
                milliSeconds = static_cast<long>(GetTickCount()) % milliSecondOffset_;
                if (type_ & constants_->kDateTime) {
                    SPRINTF(dateBufferOut_, "%s %s.%03ld", dateBufferOut_, dateBuffer_, milliSeconds);
                } else {
                    SPRINTF(dateBufferOut_, "%s.%03ld", dateBuffer_, milliSeconds);
                }
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

    static inline double getTimeDifference(const timeval& endTime_, const timeval& startTime_) {
        return static_cast<double>((((endTime_.tv_sec - startTime_.tv_sec) * 1000000) + (endTime_.tv_usec - startTime_.tv_usec)) / 1000);
    }
}; // class DateUtils
} // namespace utilities

//!
//! Internal repository base to manage memory on heap. Used internally, you should not use it.
//!
template<class Class, class Predicate>
class Registry {
public:
    Registry(void) {
    }

    virtual ~Registry(void) {
        unregisterAll();
    }

    Registry(const Registry& other_) {
        if (this != &other_) {
            unregisterAll();
            for (std::size_t i = 0; i < other_.list_.size(); ++i) {
                Class* curr_ = other_.list_.at(i);
                if (curr_) {
                    list_.push_back(new Class(*curr_));
                }
            }
        }
    }

    Registry& operator=(const Registry& other_) {
        if (this == &other_) {
            return *this;
        }
        unregisterAll();
        for (std::size_t i = 0; i < other_.list_.size(); ++i) {
            Class* curr_ = other_.list_.at(i);
            if (curr_) {
                list_.push_back(new Class(*curr_));
            }
        }
        return *this;
    }

    inline void registerNew(Class* c_) {
        list_.push_back(c_);
    }

    bool operator!=(const Registry<Class, Predicate>& other_) {
        if (list_.size() != other_.list_.size()) {
            return true;
        }
        for (std::size_t i = 0; i < list_.size(); ++i) {
            if (list_.at(i) != other_.list_.at(i)) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Registry<Class, Predicate>& other_) {
        if (list_.size() != other_.list_.size()) {
            return false;
        }
        for (std::size_t i = 0; i < list_.size(); ++i) {
            if (list_.at(i) != other_.list_.at(i)) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    Class* get(const T& t_) {
        Iterator iter = std::find_if(list_.begin(), list_.end(), Predicate(t_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }

    template<typename T, typename T2>
    Class* get(const T& t_, const T2& t2_) {
        Iterator iter = std::find_if(list_.begin(), list_.end(), Predicate(t_, t2_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }

    template<typename T>
    inline bool exist(const T& t_) {
        return (get(t_) != NULL);
    }

    inline std::size_t count(void) const {
        return list_.size();
    }

    inline bool empty(void) const {
        return list_.empty();
    }

    Class* at(std::size_t i) const {
        return list_.at(i);
    }

protected:
    typedef typename std::vector<Class*>::iterator Iterator;

    inline void unregisterAll(void) {
        if (!empty()) {
            std::for_each(list_.begin(), list_.end(), std::bind1st(std::mem_fun(&Registry::release), this));
            list_.clear();
        }
    }

    inline void unregister(Class*& c_) {
        if (c_) {
            Iterator iter = list_.begin();
            for (; iter != list_.end(); ++iter) {
                if (c_ == *iter) {
                    break;
                }
            }
            if (iter != list_.end() && *iter != NULL) {
                list_.erase(iter);
                internal::utilities::safeDelete(c_);
            }
        }
    }

    inline std::vector<Class*>& list(void) {
        return list_;
    }
private:
    std::vector<Class*> list_;

    inline void release(Class* c_) {
        internal::utilities::safeDelete(c_);
    }
}; // class Registry

//!
//! Scoped pointer used internally. You should not use it.
//!
template <typename T>
class ScopedPointer {
public:
    explicit ScopedPointer(T* ptr_ = 0) :
        ptr_(ptr_), referenceCounter_(0) {
        referenceCounter_ = new ReferenceCounter();
        referenceCounter_->increment();
    }

    ScopedPointer(const ScopedPointer<T>& scopedPointer_) :
        ptr_(scopedPointer_.ptr_), referenceCounter_(scopedPointer_.referenceCounter_) {
        referenceCounter_->increment();
    }

    ScopedPointer<T>& operator=(const ScopedPointer<T>& other_) {
        if (this != &other_)
        {
            validate();
            ptr_ = other_.ptr_;
            referenceCounter_ = other_.referenceCounter_;
            referenceCounter_->increment();
        }
        return *this;
    }

    virtual ~ScopedPointer(void) {
        validate();
    }

    T& operator*(void) {
        return *ptr_;
    }

    T* operator->(void) {
        return ptr_;
    }

    T* pointer(void) {
        return ptr_;
    }

    class ReferenceCounter {
    public:
        ReferenceCounter(void) : count_(0) {
        }

        ReferenceCounter& operator=(const ReferenceCounter& other_) {
            if (this != &other_) {
                count_ = other_.count_;
            }
            return *this;
        }

        void increment(void) {
            ++count_;
        }

        int decrement(void) {
            return this == NULL ? 0 : --count_;
        }

    private:
        int count_;
    };
private:
    T* ptr_;
    ReferenceCounter* referenceCounter_;

    void validate(void) {
        if(referenceCounter_->decrement() == 0) {
            internal::utilities::safeDelete(ptr_, false);
            internal::utilities::safeDelete(referenceCounter_, false);
        }
    }
};

//!
//! Class that represents single configuration.
//!
//! Single configuration has a level (easyloggingpp::Level), type (easyloggingpp::ConfigurationType)
//! and std::string based value. This value is later parsed into more appropriate data type depending on
//! type
//!
class Configuration {
public:
    //!
    //! Full constructor used to set initial value of configuration
    //! \param level_
    //! \param type_
    //! \param value_
    //!
    Configuration(unsigned int level_, unsigned int type_, const std::string& value_) :
        level_(level_),
        type_(type_),
        value_(value_) {
    }

    //!
    //! \return Level of current configuration
    //!
    unsigned int level(void) const {
        return level_;
    }

    //!
    //! \return Configuration type of current configuration
    //!
    unsigned int type(void) const {
        return type_;
    }

    //!
    //! \return String based configuration value
    //!
    std::string value(void) const {
        return value_;
    }

    //!
    //! Set string based configuration value
    //! \param value_ Value to set. Values have to be std::string; For boolean values use "true", "false", for any integral values
    //!        use them in quotes. They will be parsed when configuring
    //!
    void setValue(const std::string& value_) {
        this->value_ = value_;
    }

    //!
    //! Predicate used to find configuration from configuration repository. This is used internally.
    //!
    class Predicate {
    public:
        Predicate(unsigned int level_, unsigned int type_) :
            level_(level_),
            type_(type_) {
        }

        bool operator()(const Configuration* conf_) {
            return ((conf_ != NULL) && (conf_->level() == level_) && (conf_->type() == type_));
        }

    private:
        unsigned int level_;
        unsigned int type_;
    };
private:
    unsigned int level_;
    unsigned int type_;
    std::string value_;
};

} // namespace internal

//!
//! Configuration repository that represents configuration for single logger
//!
class Configurations : public internal::Registry<internal::Configuration, internal::Configuration::Predicate> {
public:
    //!
    //! Default constructor
    //!
    Configurations(void) :
        isFromFile_(false) {
    }

    //!
    //! Constructor used to set configurations via configuration file
    //! \param configurationFile_ Full path to configuration file
    //! \param base_ Configurations to base new configuration repository off. This value is used when you want to use
    //!        existing Configurations to base all the values and then set rest of configuration via configuration file.
    //!
    Configurations(const std::string& configurationFile_, Configurations* base_ = NULL) :
        configurationFile_(configurationFile_),
        isFromFile_(false) {
        parseFromFile(configurationFile_, base_);
    }

    //!
    //! Set configurations based on other configurations
    //! \param base_ Pointer to existing configurations.
    //!
    inline void setFromBase(Configurations* base_) {
        if (base_ == NULL || base_ == this) return;
        std::for_each(base_->list().begin(), base_->list().end(), std::bind1st(std::mem_fun(&Configurations::set), this));
    }

    //!
    //! Checks to see whether specified configuration type exist in this repository
    //! \param configurationType_ Configuration type to check against. Use easyloggingpp::ConfigurationType to prevent confusions
    //! \return True if exist, false otherwise
    //!
    inline bool contains(unsigned int configurationType_) {
        ELPP_FOR_EACH_CONFIGURATION(i, ConfigurationType::kMinValid,
                                    if (get(i, configurationType_) != NULL) {
                                        return true;
                                    }
                                    );
        return false;
    }

    //!
    //! Sets configuration for specified level_ and configurationType_. If configuration already exists for specified
    //! level and configuration type, value just gets updated.
    //! Remember, it is not recommended to set skip_ELPPALL_Check to false unless you know exactly what you are doing
    //! \param level_ Level to set configuration for. Use easyloggingpp::Level to prevent confusion
    //! \param configurationType_ Configuration type to set configuration against. Use easyloggingpp::ConfigurationType to prevent confusion
    //! \param value_ String based configuration value
    //! \param skipLEVEL_ALL Determines whether to skip 'easyloggingpp::Level::All'. This is skipped by default because setting
    //!        'All' may override configuration. Be careful with this.
    //!
    void set(unsigned int level_, unsigned int configurationType_, const std::string& value_, bool skipLEVEL_ALL = false) {
        if (value_ == "") return; // ignore empty values
        if ((configurationType_ == ConfigurationType::PerformanceTracking && level_ != Level::All) ||
                (configurationType_ == ConfigurationType::MillisecondsWidth && level_ != Level::All)) {
            // configurationType_ not applicable for this level_
            return;
        }
        internal::Configuration* conf_ = get(level_, configurationType_);
        if (conf_ == NULL) {
            registerNew(new internal::Configuration(level_, configurationType_, value_));
        } else {
            // Configuration already there, just update the value!
            conf_->setValue(value_);
        }
        if (!skipLEVEL_ALL && level_ == Level::All) {
            setAll(configurationType_, value_, true);
        }
    }

    //!
    //! Parse configuration from file.
    //! \param configurationFile_
    //! \param base_Configurations to base new configuration repository off. This value is used when you want to use
    //!        existing Configurations to base all the values and then set rest of configuration via configuration file.
    //! \return True if successfully parsed, false otherwise. You may define '_STOP_ON_FIRST_ELPP_ASSERTION' to make sure you
    //!         do not proceed without successful parse.
    //!
    bool parseFromFile(const std::string& configurationFile_, Configurations* base_ = NULL) {
        setFromBase(base_);
        std::ifstream fileStream_(configurationFile_.c_str(), std::ifstream::in);
        __EASYLOGGINGPP_ASSERT(fileStream_.is_open(), "Unable to open configuration file [" << configurationFile_ << "] for parsing.");
        bool parsedSuccessfully_ = false;
        std::string line = std::string();
        unsigned int currLevel = 0;
        while (fileStream_.good()) {
            std::getline(fileStream_, line);
            parsedSuccessfully_ = Parser::parseLine(line, currLevel, this);
            __EASYLOGGINGPP_ASSERT(parsedSuccessfully_, "Unable to parse configuration line: " << line);
        }
        isFromFile_ = true;
        return parsedSuccessfully_;
    }

    //!
    //! Parse configurations from configuration string. This configuration string has same syntax as configuration file contents. Make
    //! sure all the necessary new line characters are provided.
    //! \param configurationsString
    //! \return True if successfully parsed, false otherwise. You may define '_STOP_ON_FIRST_ELPP_ASSERTION' to make sure you
    //!         do not proceed without successful parse.
    //!
    bool parseFromText(const std::string& configurationsString) {
        bool parsedSuccessfully_ = false;
        std::string line = std::string();
        unsigned int currLevel = 0;
        std::vector<std::string> lines;
        internal::utilities::StringUtils::split(configurationsString, '\n', lines);
        for (std::size_t i = 0; i < lines.size(); ++i) {
            line = lines.at(i);
            parsedSuccessfully_ = Parser::parseLine(line, currLevel, this);
            __EASYLOGGINGPP_ASSERT(parsedSuccessfully_, "Unable to parse configuration line: " << line);
        }
        isFromFile_ = false;
        return parsedSuccessfully_;
    }

    //!
    //! Sets configurations to default configurations set by easylogging++.
    //! NOTE: This has nothing to do with Loggers::setDefaultConfigurations - thats completely different thing. This is
    //! library's own default format.
    //!
    void setToDefault(void) {
        setAll(ConfigurationType::Enabled, "true");
#if _ELPP_OS_UNIX
#   if _ELPP_NDK
        setAll(ConfigurationType::Filename, "/data/local/tmp/myeasylog.txt");
#   else
        setAll(ConfigurationType::Filename, "/tmp/logs/myeasylog.log");
#   endif // _ELPP_NDK
#elif _ELPP_OS_WINDOWS
        setAll(ConfigurationType::Filename, "logs\\myeasylog.log");
#endif // _ELPP_OS_UNIX
        setAll(ConfigurationType::ToFile, "true");
        setAll(ConfigurationType::ToStandardOutput, "true");
        setAll(ConfigurationType::MillisecondsWidth, "3");
        setAll(ConfigurationType::PerformanceTracking, "false");
        setAll(easyloggingpp::ConfigurationType::RollOutSize, "0");
        setAll(ConfigurationType::Format, "%datetime %level  [%logger] %log");
        set(Level::Debug, ConfigurationType::Format, "%datetime %level [%logger] [%user@%host] [%func] [%loc] %log");
        // INFO and WARNING are set to default by Level::ALL
        set(Level::Error, ConfigurationType::Format, "%datetime %level [%logger] %log");
        set(Level::Fatal, ConfigurationType::Format, "%datetime %level [%logger] %log");
        set(Level::Verbose, ConfigurationType::Format, "%datetime %level-%vlevel [%logger] %log");
        set(Level::QA, ConfigurationType::Format, "%datetime %level    [%logger] %log");
        set(Level::Trace, ConfigurationType::Format, "%datetime %level [%logger] [%func] [%loc] %log");
    }

    //!
    //! Sets configuration for all levels.
    //! Remember, it is not recommended to set skip_ELPPALL_Check to false unless you know exactly what you are doing
    //! \param configurationType_
    //! \param value_
    //! \param skipLEVEL_ALL Determines whether to skip 'easyloggingpp::Level::All'. This is skipped by default because setting
    //!        'All' may override configuration. Be careful with this.
    //!
    inline void setAll(unsigned int configurationType_, const std::string& value_, bool skipLEVEL_ALL = false) {
        if (!skipLEVEL_ALL) {
            set(Level::All, configurationType_, value_);
        }
        ELPP_FOR_EACH_LEVEL(i, Level::Debug,
                            set(i, configurationType_, value_);
                            );
    }

    //!
    //! Clears the repository.
    //! All the configurations are maintained on heap for faster access so if you are sure you will not use this
    //! repository and you have configured all the loggers against this or you have used this configuration for all the
    //! purposes you need it for, you may retain memory by using this method. If you do not do this, internal memory management
    //! does it itself at the end of application execution.
    //!
    inline void clear(void) {
        unregisterAll();
    }

    //!
    //! \return Returns configuration file used in parsing this configurations. If this repository was set manually or by text
    //!         this returns empty string.
    //!
    std::string configurationFile(void) const {
        return configurationFile_;
    }

    //!
    //! Parser used internally to parse configurations from file or text. You should not need this unless you are working on
    //! some tool for EasyLogging++
    //!
    class Parser : private internal::StaticClass {
    public:
        static void ignoreComments(std::string& line) {
            std::size_t foundAt = 0;
            std::size_t quotesStart = line.find("\"");
            std::size_t quotesEnd = std::string::npos;
            if (quotesStart != std::string::npos) {
                quotesEnd = line.find("\"", quotesStart + 1);
            }
            if ((foundAt = line.find("//")) != std::string::npos) {
                if (foundAt < quotesEnd) {
                    foundAt = line.find("//", quotesEnd + 1);
                }
                line = line.substr(0, foundAt);
            }
        }

        static inline bool isLevel(const std::string& line) {
            return internal::utilities::StringUtils::startsWith(line, "*");
        }

        static inline bool isConfig(const std::string& line) {
            std::size_t assignment = line.find('=');
            return line != "" &&
                    (line[0] >= 65 || line[0] <= 90 || line[0] >= 97 || line[0] <= 122) &&
                    (assignment != std::string::npos) &&
                    (line.size() > assignment);
        }

        static inline bool isComment(const std::string& line) {
            return internal::utilities::StringUtils::startsWith(line, "//");
        }

        static bool parseLine(std::string& line, unsigned int& currLevel, Configurations* conf) {
            std::string currLevelStr = std::string();
            unsigned int currConfig = 0;
            std::string currConfigStr = std::string();
            std::string currValue = std::string();
            line = internal::utilities::StringUtils::trim(line);
            if (isComment(line)) return true;
            ignoreComments(line);
            if (line == "") {
                // Comment ignored
                return true;
            }
            if (isLevel(line)) {
                currLevelStr = internal::utilities::StringUtils::stripAllWhiteSpaces(line);
                if (currLevelStr.size() <= 2) {
                    return true;
                }
                currLevelStr = currLevelStr.substr(1, currLevelStr.size() - 2);
                internal::utilities::StringUtils::tolower(currLevelStr);
                currLevel = Level::convertFromString(currLevelStr);
                return true;
            }
            if (isConfig(line)) {
                std::size_t assignment = line.find('=');
                currConfigStr = line.substr(0, assignment);
                currConfigStr = internal::utilities::StringUtils::stripAllWhiteSpaces(currConfigStr);
                internal::utilities::StringUtils::tolower(currConfigStr);
                currConfig = ConfigurationType::convertFromString(currConfigStr);
                currValue = line.substr(assignment + 1);
                currValue = internal::utilities::StringUtils::trim(currValue);
                std::size_t quotesStart = currValue.find("\"", 0);
                std::size_t quotesEnd = std::string::npos;
                if (quotesStart != std::string::npos) {
                    quotesEnd = currValue.find("\"", quotesStart + 1);
                }
                if (quotesStart != std::string::npos && quotesEnd != std::string::npos) {
                    // Quote provided - check and strip if valid
                    __EASYLOGGINGPP_ASSERT((quotesStart < quotesEnd), "Configuration error - No ending quote found in [" << currConfigStr << "]");
                    __EASYLOGGINGPP_ASSERT((quotesStart + 1 != quotesEnd), "Empty configuration value for [" << currConfigStr << "]");
                    if ((quotesStart != quotesEnd) && (quotesStart + 1 != quotesEnd)) {
                        // Explicit check in case if assertion is disabled
                        currValue = currValue.substr(quotesStart + 1, quotesEnd - 1);
                    }
                }
            }
            __EASYLOGGINGPP_ASSERT(currLevel != Level::Unknown, "Unrecognized severity level [" << currLevelStr << "]");
            __EASYLOGGINGPP_ASSERT(currConfig != ConfigurationType::Unknown, "Unrecognized configuration [" << currConfigStr << "]");
            if (currLevel == Level::Unknown || currConfig == ConfigurationType::Unknown) {
                return false; // unrecognizable level or config
            }
            conf->set(currLevel, currConfig, currValue);
            return true;
        }
    }; // class Parser
private:
    std::string configurationFile_;
    bool isFromFile_;
    internal::threading::Mutex mutex_;

    inline void set(internal::Configuration* conf_) {
        if (conf_ == NULL) return;
        set(conf_->level(), conf_->type(), conf_->value());
    }
}; // class Configurations

class Loggers;  // fwd declaration

namespace internal {

class RegisteredLoggers; // fwd declaration
class Writer;  // fwd declaration

//!
//! Configuration map used internally for faster access of configuration while executing.
//!
template <typename T>
class ConfigurationMap {
public:
    typedef typename std::pair<unsigned int, T> Entry;

    ConfigurationMap(void) {
        table = new Entry*[Level::kMaxValid + 1];
        for (unsigned int i = 0; i < (Level::kMaxValid + 1); ++i) {
            table[i] = NULL;
        }
        count = 0;
    }

    const T& get(unsigned int level_, bool forceGetLevel = false) {
        if (forceGetLevel || table[level_] != NULL) {
            if (table[level_] == NULL) {
                return default_;
            }
            return table[level_]->second;
        } else if (table[Level::All] != NULL) {
            return table[Level::All]->second;
        }
        return default_;
    }

    void set(unsigned int level_, const T& value) {
        // Unset any existing value for this level
        unset(level_);
        table[level_] = new Entry(level_, value);
        ++count;
    }

    void unset(unsigned int level_) {
        if (table[level_] != NULL) {
            internal::utilities::safeDelete(table[level_]);
            if (count > 0)
                --count;
        }
    }

    inline bool exist(unsigned int level_) const {
       return table[level_] != NULL;
    }

    inline bool exist(unsigned int level_, const T& value) {
       return get(level_, true) == value;
    }

    void clear(void) {
        for (unsigned int i = 0; i < (Level::kMaxValid + 1); ++i) {
            internal::utilities::safeDelete(table[i]);
        }
        delete[] table;
        count = 0;
    }

    virtual ~ConfigurationMap(void) {
        clear();
    }

    inline void setDefault(const T& default_) {
        this->default_ = default_;
    }

    inline std::size_t size(void) const {
        return count;
    }
private:
    Entry** table;
    std::size_t count;
    T default_;
};

//!
//! Configurations used internally that defines data type of each configuration from easyloggingpp::ConfigurationType
//!
class TypedConfigurations {
public:
    TypedConfigurations(const Configurations& configurations, internal::Constants* constants_) {
        this->constants_ = constants_;
        this->configurations_ = configurations;
        enabledMap_.setDefault(false);
        toFileMap_.setDefault(false);
        toStandardOutputMap_.setDefault(false);
        filenameMap_.setDefault("");
        logFormatMap_.setDefault("");
        dateFormatMap_.setDefault("");
        dateFormatSpecifierMap_.setDefault("");
        millisecondsWidthMap_.setDefault(3);
        performanceTrackingMap_.setDefault(false);
        fileStreamMap_.setDefault(NULL);
        formatFlagMap_.setDefault(0x0);
        rollOutSizeMap_.setDefault(0);
        parse(configurations);
    }

    virtual ~TypedConfigurations(void) {
        deleteFileStreams();
    }

    const Configurations& configurations(void) const {
        return configurations_;
    }
private:
    internal::ConfigurationMap<bool> enabledMap_;
    internal::ConfigurationMap<bool> toFileMap_;
    internal::ConfigurationMap<std::string> filenameMap_;
    internal::ConfigurationMap<bool> toStandardOutputMap_;
    internal::ConfigurationMap<std::string> logFormatMap_;
    internal::ConfigurationMap<std::string> dateFormatMap_;
    internal::ConfigurationMap<std::string> dateFormatSpecifierMap_;
    internal::ConfigurationMap<int> millisecondsWidthMap_;
    internal::ConfigurationMap<bool> performanceTrackingMap_;
    internal::ConfigurationMap<std::fstream*> fileStreamMap_;
    internal::ConfigurationMap<unsigned int> formatFlagMap_;
    internal::ConfigurationMap<std::size_t> rollOutSizeMap_;
    internal::Constants* constants_;
    Configurations configurations_;

    friend class Writer;
    friend class easyloggingpp::Loggers;

    inline bool enabled(unsigned int level_) {
        return enabledMap_.get(level_);
    }

    inline bool toFile(unsigned int level_) {
        return toFileMap_.get(level_);
    }

    inline const std::string& filename(unsigned int level_) {
        return filenameMap_.get(level_);
    }

    inline bool toStandardOutput(unsigned int level_) {
        return toStandardOutputMap_.get(level_);
    }

    inline const std::string& logFormat(unsigned int level_) {
        return logFormatMap_.get(level_);
    }

    inline const std::string& dateFormat(unsigned int level_) {
        return dateFormatMap_.get(level_);
    }

    inline const std::string& dateFormatSpecifier(unsigned int level_) {
        return dateFormatSpecifierMap_.get(level_);
    }

    inline int millisecondsWidth(unsigned int level_ = Level::All) {
        return millisecondsWidthMap_.get(level_);
    }

    inline bool performanceTracking(unsigned int level_ = Level::All) {
        return performanceTrackingMap_.get(level_);
    }

    inline std::fstream* fileStream(unsigned int level_) {
        return fileStreamMap_.get(level_);
    }

    inline std::size_t rollOutSize(unsigned int level_) {
        return rollOutSizeMap_.get(level_);
    }

    inline int formatFlag(unsigned int level_) {
        return formatFlagMap_.get(level_);
    }

    void parse(const Configurations& configurations_) {
        for (std::size_t i = 0; i < configurations_.count(); ++i) {
            Configuration* conf = configurations_.at(i);
            switch (conf->type()) {
            case ConfigurationType::Enabled:
                setValue(conf->level(), getBool(conf->value()), enabledMap_);
                break;
            case ConfigurationType::ToFile:
                setValue(conf->level(), getBool(conf->value()), toFileMap_);
                break;
            case ConfigurationType::Filename:
                insertFilename(conf->level(), conf->value());
                break;
            case ConfigurationType::ToStandardOutput:
                setValue(conf->level(), getBool(conf->value()), toStandardOutputMap_);
                break;
            case ConfigurationType::Format:
                determineFormats(conf->level(), conf->value());
                break;
            case ConfigurationType::MillisecondsWidth:
                if (conf->level() == Level::All) {
                    int origVal = getInt(conf->value());
                    int msl_;
#if _ELPP_OS_UNIX
                    switch (origVal) {
                    case 3:
                        msl_ = 1000;
                        break;
                    case 4:
                        msl_ = 100;
                        break;
                    case 5:
                        msl_ = 10;
                        break;
                    case 6:
                        msl_ = 1;
                        break;
                    default:
                        msl_ = constants_->DEFAULT_MILLISECOND_OFFSET;
                    }
#elif _ELPP_OS_WINDOWS
                    msl_ = 1000;
                    __EASYLOGGINGPP_SUPPRESS_UNSED(origVal);
#endif // _ELPP_OS_UNIX
                    setValue(conf->level(), msl_, millisecondsWidthMap_);
                }
                break;
            case ConfigurationType::PerformanceTracking:
                if (conf->level() == Level::All) {
                    setValue(conf->level(), getBool(conf->value()), performanceTrackingMap_);
                }
                break;
            case ConfigurationType::RollOutSize:
                setValue(conf->level(), static_cast<std::size_t>(getULong(conf->value())), rollOutSizeMap_);
                unsigned int validLevel_ = 0;
                std::string rolloutFilename_ = std::string();
                checkRollOuts(conf->level(), validLevel_, rolloutFilename_);
                break;
            }
        }
    }

    void determineFormats(unsigned int level_, const std::string& originalFormat) {
        unsigned int formatSpec = 0x0;
        if (originalFormat.find(constants_->APP_NAME_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kAppName;
        }
        if (originalFormat.find(constants_->LOGGER_ID_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kLoggerId;
        }
        if (originalFormat.find(constants_->THREAD_ID_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kThreadId;
        }
        if (originalFormat.find(constants_->LOCATION_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kLocation;
        }
        if (originalFormat.find(constants_->FUNCTION_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kFunction;
        }
        if (originalFormat.find(constants_->USER_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kUser;
        }
        if (originalFormat.find(constants_->HOST_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kHost;
        }
        if (originalFormat.find(constants_->LOG_MESSAGE_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kLogMessage;
        }
        if (originalFormat.find(constants_->VERBOSE_LEVEL_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kVerboseLevel;
        }
        if (originalFormat.find(constants_->DATE_TIME_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kDateTime;
            setValue(level_, constants_->DATE_TIME_FORMAT_SPECIFIER, dateFormatSpecifierMap_);
        } else if (originalFormat.find(constants_->DATE_ONLY_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kDateOnly;
            setValue(level_, constants_->DATE_ONLY_FORMAT_SPECIFIER, dateFormatSpecifierMap_);
        } else if (originalFormat.find(constants_->TIME_ONLY_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kTimeOnly;
            setValue(level_, constants_->TIME_ONLY_FORMAT_SPECIFIER, dateFormatSpecifierMap_);
        }
#if _ELPP_OS_UNIX
        const std::string kTimeFormatLocal_ = "%H:%M:%S";
        const std::string kDateFormatLocal_ = "%d/%m/%Y";
        std::string dateFormat;

        if (formatSpec & constants_->kDateOnly) {
            dateFormat = kDateFormatLocal_;
        } else if (formatSpec & constants_->kTimeOnly) {
            dateFormat = kTimeFormatLocal_;
        } else {
            std::stringstream ss;
            ss << kDateFormatLocal_ << " " << kTimeFormatLocal_;
            dateFormat = ss.str();
        }
        setValue(level_, dateFormat, dateFormatMap_);
#endif // _ELPP_OS_UNIX
        setValue(level_, formatSpec, formatFlagMap_);
        // Update %level
        std::string origFormatCopy = originalFormat;
        switch (level_) {
        case Level::Debug:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_DEBUG_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::Info:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_INFO_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::Warning:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_WARNING_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::Error:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_ERROR_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::Fatal:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_FATAL_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::Verbose:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_VERBOSE_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::QA:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_QA_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::Trace:
            internal::utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                                   constants_->LOG_TRACE_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        }
        setValue(level_, origFormatCopy + "\n", logFormatMap_);
    }

    void deleteFileStreams(void) {
        ELPP_FOR_EACH_LEVEL(i, Level::kMinValid,
                            removeFile(i);
                            );
    }

    // This is different since we need unique values
    void insertFilename(unsigned int level_, const std::string& fname_, bool forceNew = false) {
        std::string fnameFull = fname_;
        if (internal::utilities::StringUtils::endsWith(fnameFull, constants_->PATH_SLASH)) {
            fnameFull.append(constants_->DEFAULT_LOG_FILENAME);
        }
        std::string path_ = internal::utilities::OSUtils::getPathFromFilename(fnameFull, constants_);
        if (path_.size() < fnameFull.size()) {
            // Contains path - create it if it does not already exist
            internal::utilities::OSUtils::createPath(path_);
        }
        if (filenameMap_.size() == 0) {
            filenameMap_.set(Level::All, fnameFull);
            std::fstream *fsAll = newFileStream(fnameFull, forceNew);
            if (fsAll != NULL) {
                fileStreamMap_.set(Level::All, fsAll);
            }
            return;
        }
        ELPP_FOR_EACH_LEVEL(i, Level::kMinValid,
                       if (filenameMap_.exist(i, fnameFull)) {
                           return;
                       }
                       );
        filenameMap_.set(level_, fnameFull);
        // Just before we proceed and create new file stream we check for existing one on same level,
        // if we have existing one, we first delete it to prevent memory leak.
        std::fstream *fs = fileStreamMap_.get(level_, true);
        internal::utilities::safeDelete(fs);
        fileStreamMap_.unset(level_);
        fs = newFileStream(fnameFull, forceNew);
        if (fs != NULL) {
            fileStreamMap_.set(level_, fs);
        }
    }

    template <typename T>
    void setValue(unsigned int level_, const T& value_, internal::ConfigurationMap<T>& map_, bool skipLEVEL_ALL = false) {
        if (map_.size() == 0 && !skipLEVEL_ALL) {
            map_.set(Level::All, value_);
            return;
        }
        if (map_.exist(static_cast<unsigned int>(Level::All), value_)) {
            return;
        }
        map_.set(level_, value_);
    }

    std::fstream* newFileStream(const std::string& filename, bool forceNew = false) {
        std::fstream *fs = NULL;
        if (forceNew) {
            fs = new std::fstream(filename.c_str(), std::fstream::out);
        } else {
            fs = new std::fstream(filename.c_str(), std::fstream::out | std::fstream::app);
        }
        if (fs->is_open()) {
            fs->flush();
        } else {
            internal::utilities::safeDelete(fs, false);
            std::cerr << "Bad file [" << filename << "]" << std::endl;
            return NULL;
        }
        return fs;
    }

    void removeFile(unsigned int level_) {
        std::fstream* fs = fileStream(level_);
        if (!fs) {
            return;
        }
        if (fs->is_open()) {
            fs->close();
        }
        internal::utilities::safeDelete(fs, false);
        fileStreamMap_.unset(level_);
        filenameMap_.unset(level_);
    }

    unsigned long getULong(const std::string& confValue_) {
        bool valid = true;
        std::string trimmedVal = internal::utilities::StringUtils::trim(confValue_);
        if (trimmedVal.size() == 0) {
            valid = false;
            __EASYLOGGINGPP_SUPPRESS_UNSED(valid);
            __EASYLOGGINGPP_ASSERT(valid, "Configuration value not a valid integer " << trimmedVal);
        }
        for (std::size_t i = 0; i < trimmedVal.size(); ++i) {
            if (trimmedVal[i] < 48 || trimmedVal[i] > 57) {
                valid = false;
                break;
            }
        }
        __EASYLOGGINGPP_SUPPRESS_UNSED(valid);
        __EASYLOGGINGPP_ASSERT(valid, "Configuration value not a valid integer " << trimmedVal);
        return atol(confValue_.c_str());
    }

    inline int getInt(const std::string& confValue_) {
        return static_cast<int>(getULong(confValue_));
    }

    inline bool getBool(const std::string& confValue_) {
        std::string trimmedVal = internal::utilities::StringUtils::trim(confValue_);
        return (trimmedVal == "1" || trimmedVal == "true" || trimmedVal == "TRUE");
    }

    std::size_t getSizeOfFile(std::fstream *fs) {
        if (!fs) {
            return 0;
        }
        std::streampos currPos = fs->tellg();
        fs->seekg (0, fs->end);
        std::size_t size = static_cast<std::size_t>(fs->tellg());
        fs->seekg (currPos);
        return size;
    }

    bool checkRollOuts(unsigned int level_, unsigned int& validLevel_, std::string& fname_) {
        std::fstream* fs = fileStream(level_);
        std::size_t rollOutSize_ = rollOutSize(level_);
        if (rollOutSize_ != 0 && getSizeOfFile(fs) >= rollOutSize_) {
            fname_ = filename(level_);
#if defined(_ELPP_INTERNAL_INFO)
            std::cout << "Cleaning log file [" << fname_ << "]\n";
#endif // defined(_ELPP_INTERNAL_INFO)
            // Find and reset correct level. By correct level we mean the current
            // available level in fileStream because this level_ could actually be using
            // configurations from Level::All and you do not want to create a brand new
            // stream just because we are rolling log away
            validLevel_ = findValidLevel(fileStreamMap_, level_);
            forceReinitiateFile(validLevel_, fname_);
            return true;
        }
        return false;
    }

    template <typename T>
    inline unsigned int findValidLevel(internal::ConfigurationMap<T>& map_, unsigned int refLevel_) {
        return map_.exist(refLevel_) ? refLevel_ : static_cast<unsigned int>(Level::All);
    }

    inline void forceReinitiateFile(unsigned int level_, const std::string& filename_) {
        removeFile(level_);
        insertFilename(level_, filename_, true);
    }
};
} // namespace internal

//!
//! Represents single logger used to write log.
//!
class Logger {
public:
    //!
    //! Minimal constructor to set logger ID and constants. You should not use this constructor manually, instead use
    //! easyloggingpp::Loggers::getLogger
    //! \param uniqueIdentifier_ Logger ID that you will require to get logger from logger repository
    //! \param constants_ Use <code>easyloggingpp::internal::registeredLoggers->constants()</code>
    //!
    Logger(const std::string& uniqueIdentifier_, internal::Constants* constants_) :
            id_(uniqueIdentifier_),
            constants_(constants_),
            typedConfigurations_(NULL),
            stream_(new std::stringstream()) {
        Configurations defaultConfs;
        defaultConfs.setToDefault();
        configure(defaultConfs);
        userConfigurations_ = defaultConfs;
        defaultConfs.clear();
    }

    //!
    //! Full constructor to set logger ID, constants and configuration.
    //! \param uniqueIdentifier_ Logger ID that you will require to get logger from logger repository
    //! \param constants_ Use <code>easyloggingpp::internal::registeredLoggers->constants()</code>
    //! \param configurations Configurations to set logger against
    //!
    Logger(const std::string& uniqueIdentifier_, internal::Constants* constants_, const Configurations& configurations) :
            id_(uniqueIdentifier_),
            constants_(constants_),
            typedConfigurations_(NULL),
            stream_(new std::stringstream()) {
        configure(configurations);
    }

    virtual ~Logger(void) {
        internal::utilities::safeDelete(typedConfigurations_);
        internal::utilities::safeDelete(stream_);
    }

    //!
    //! \return Logger ID
    //!
    inline std::string id(void) const {
        return id_;
    }

    //!
    //! Configures logger against specified configurations
    //! \param configurations_
    //!
    void configure(const Configurations& configurations_) {
#if _ELPP_ENABLE_MUTEX
        internal::threading::ScopedLock slock_(mutex_);
        __EASYLOGGINGPP_SUPPRESS_UNSED(slock_);
#endif // _ELPP_ENABLE_MUTEX
        // Configuring uses existing configuration as starting point
        // and then sets configurations_ as base to prevent losing any
        // previous configurations
        Configurations base_ = userConfigurations_;
        if (userConfigurations_ != configurations_) {
            userConfigurations_ = configurations_;
            base_.setFromBase(const_cast<Configurations*>(&configurations_));
        }
        internal::utilities::safeDelete(typedConfigurations_);
        typedConfigurations_ = new internal::TypedConfigurations(base_, constants_);
        configured_ = true;
    }

    //!
    //! Reconfigures logger
    //!
    inline void reconfigure(void) {
        configure(this->userConfigurations_);
    }

    //!
    //! \return Application name for this logger
    //!
    inline std::string applicationName(void) const {
        return applicationName_;
    }


    //!
    //! Application name can vary from logger to logger. For example for a library application name may be different.
    //! This is whats used later when you use '%app' in log format
    //!
    inline void setApplicationName(const std::string& applicationName_) {
        this->applicationName_ = applicationName_;
    }

    //!
    //! \return Configurations that this logger is set against
    //!
    inline Configurations& configurations(void) {
        return userConfigurations_;
    }

    //!
    //! \return Whether or not logger is configured.
    //!
    inline bool configured(void) const {
        return configured_;
    }

    //!
    //! Predicate used in logger repository to find logger. This is used internally. You should not use it.
    //!
    class Predicate {
    public:
        explicit Predicate(const std::string& id_) :
            id_(id_) {
        }
        inline bool operator()(const Logger* logger_) {
            return ((logger_ != NULL) && (logger_->id() == id_));
        }
    private:
        std::string id_;
    };
private:
    std::string id_;
    internal::Constants* constants_;
    Configurations userConfigurations_;
    internal::TypedConfigurations* typedConfigurations_;
    std::stringstream* stream_;
    std::string applicationName_;
    bool configured_;
    internal::threading::Mutex mutex_;
    friend class internal::Writer;
    friend class Loggers;
    friend class internal::RegisteredLoggers;

    Logger(void);

    std::stringstream* stream(void) {
        return stream_;
    }

    inline void acquireLock(void) {
        mutex_.lock();
    }

    inline void releaseLock(void) {
        mutex_.unlock();
    }
};

namespace internal {
//!
//! Internal log counter used for interval logging
//!
class LogCounter : private internal::NoCopy {
public:
    explicit LogCounter(internal::Constants* constants_) :
        file_(""),
        line_(0),
        position_(1),
        constants_(constants_) {
    }

    LogCounter(const char* file_,
               unsigned long int line_,
               internal::Constants* constants_) :
        file_(file_),
        line_(line_),
        position_(1),
        constants_(constants_) {
    }

    virtual ~LogCounter(void) {
    }

    inline void resetLocation(const char* file_,
                              unsigned long int line_) {
        this->file_ = file_;
        this->line_ = line_;
    }

    inline void reset(std::size_t n_) {
        if (position_ >= constants_->MAX_LOG_PER_COUNTER) {
            position_ = (n_ >= 1 ? constants_->MAX_LOG_PER_COUNTER % n_ : 0);
        }
        ++position_;
    }

    inline const char* file(void) const {
        return file_;
    }

    inline unsigned long int line(void) const {
        return line_;
    }

    inline std::size_t position(void) const {
        return position_;
    }

    class Predicate {
    public:
        Predicate(const char* file_, unsigned long int line_)
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
    std::size_t position_;
    internal::Constants* constants_;
}; // class LogCounter

//!
//! Internal LogCounter repository
//!
class RegisteredCounters : public Registry<internal::LogCounter, internal::LogCounter::Predicate>  {
public:
    bool validate(const char* file_, unsigned long int line_, std::size_t n_, internal::Constants* constants_) {
#if _ELPP_ENABLE_MUTEX
        internal::threading::ScopedLock slock_(mutex_);
        __EASYLOGGINGPP_SUPPRESS_UNSED(slock_);
#endif // _ELPP_ENABLE_MUTEX
        bool result_ = false;
        internal::LogCounter* counter_ = get(file_, line_);
        if (counter_ == NULL) {
            registerNew(counter_ = new internal::LogCounter(file_, line_, constants_));
        }
        if (n_ >= 1 && counter_->position() != 0 && counter_->position() % n_ == 0) {
            result_ = true;
        }
        counter_->reset(n_);
        return result_;
    }
private:
    internal::threading::Mutex mutex_;
}; // class RegisteredCounters

//!
//! Internal logger repository. You should not access functionalities directly, you should use easyloggingpp::Loggers instead
//!
class RegisteredLoggers : public internal::Registry<Logger, Logger::Predicate> {
public:
    RegisteredLoggers(void) :
            constants_(new internal::Constants()),
            username_(internal::utilities::OSUtils::currentUser()),
            hostname_(internal::utilities::OSUtils::currentHost()),
            counters_(new internal::RegisteredCounters()) {
        defaultConfigurations_.setToDefault();
        Configurations conf;
        conf.setToDefault();
        conf.parseFromText(constants_->DEFAULT_LOGGER_CONFIGURATION);
        registerNew(new Logger("trivial", constants_, conf));
        registerNew(new Logger("business", constants_));
        registerNew(new Logger("security", constants_));
        Configurations confPerformance;
        confPerformance.setToDefault();
        confPerformance.setAll(ConfigurationType::PerformanceTracking, "true");
        registerNew(new Logger("performance", constants_, confPerformance));
    }

    virtual ~RegisteredLoggers(void) {
        internal::utilities::safeDelete(constants_);
        internal::utilities::safeDelete(counters_);
    }

    inline internal::Constants* constants(void) const {
        return constants_;
    }

    inline RegisteredCounters* counters(void) {
        return counters_;
    }

    inline bool validateCounter(const char* file_, unsigned long int line_, std::size_t n_) {
        return counters_->validate(file_, line_, n_, constants_);
    }
private:
    internal::Constants* constants_;
    std::string username_;
    std::string hostname_;
    internal::threading::Mutex mutex_;
    internal::RegisteredCounters* counters_;
    Configurations defaultConfigurations_;

    friend class Writer;
    friend class easyloggingpp::Loggers;

    inline const std::string& username(void) {
        return username_;
    }

    inline const std::string& hostname(void) {
        return hostname_;
    }

    inline void setDefaultConfigurations(const Configurations& configurations) {
        defaultConfigurations_.setFromBase(const_cast<Configurations*>(&configurations));
    }

    Logger* get(const std::string& id_, bool forceCreation_ = true) {
#if _ELPP_ENABLE_MUTEX
        internal::threading::ScopedLock slock_(mutex_);
        __EASYLOGGINGPP_SUPPRESS_UNSED(slock_);
#endif // _ELPP_ENABLE_MUTEX
        Logger* logger_ = internal::Registry<Logger, Logger::Predicate>::get(id_);
        if (logger_ == NULL && forceCreation_) {
            logger_ = new Logger(id_, constants_, defaultConfigurations_);
            registerNew(logger_);
        }
        return logger_;
    }

    inline void unregister(Logger*& logger_) {
#if _ELPP_ENABLE_MUTEX
        internal::threading::ScopedLock slock_(mutex_);
#endif // _ELPP_ENABLE_MUTEX
        internal::Registry<Logger, Logger::Predicate>::unregister(logger_);
    }

    inline void acquireLock(void) {
        mutex_.lock();
    }

    inline void releaseLock(void) {
        mutex_.unlock();
    }

    void setApplicationArguments(int argc, char** argv) {
        while (argc-- > 0) {
            // Look for --v=X argument
            if ((strlen(argv[argc]) >= 5) && (argv[argc][0] == '-') && (argv[argc][1] == '-') &&
                    (argv[argc][2] == 'v') && (argv[argc][3] == '=') && (isdigit(argv[argc][4]))) {
                // Current argument is --v=X
                // where X is a digit between 0-9
                constants_->CURRENT_VERBOSE_LEVEL = atoi(argv[argc] + 4);
            }
            // Look for -v argument
            else if ((strlen(argv[argc]) == 2) && (argv[argc][0] == '-') && (argv[argc][1] == 'v')) {
                constants_->CURRENT_VERBOSE_LEVEL = constants_->MAX_VERBOSE_LEVEL;
            }
            // Look for --verbose argument
            else if ((strlen(argv[argc]) == 9) && (argv[argc][0] == '-') && (argv[argc][1] == '-') &&
                     (argv[argc][2] == 'v') && (argv[argc][3] == 'e') && (argv[argc][4] == 'r') &&
                     (argv[argc][5] == 'b') && (argv[argc][6] == 'o') && (argv[argc][7] == 's') &&
                     (argv[argc][8] == 'e')) {
                constants_->CURRENT_VERBOSE_LEVEL = constants_->MAX_VERBOSE_LEVEL;
            }
        }
    }

    inline void setApplicationArguments(int argc, const char** argv) {
        setApplicationArguments(argc, const_cast<char**>(argv));
    }
};

extern internal::ScopedPointer<internal::RegisteredLoggers> registeredLoggers;
#if defined(_ELPP_STL_LOGGING)
namespace workarounds {
// There is workaround needed to loop through some stl containers. In order to do that, we need iterable containers
// of same type and provide iterator interface and pass it on to writeIterator().
// Remember, this is passed by value in constructor so that we dont change original containers.
// This operation is as expensive as O(class_.size()) or O(constants->MAX_LOG_PER_COUNTER) which ever is smaller.

//
// Abstract IterableContainer template that provides interface for iterable classes of type T
//
template <typename T, typename Container>
class IterableContainer {
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    IterableContainer(void){}
    virtual ~IterableContainer(void) {}
    iterator begin(void) { return getContainer().begin(); }
    iterator end(void) { return getContainer().end(); }
    const_iterator begin(void) const { return getContainer().begin(); }
    const_iterator end(void) const { return getContainer().end(); }
private:
    virtual Container& getContainer(void) = 0;
};

//
// Implements IterableContainer and provides iterable std::priority_queue class
//
template<typename T, typename Container = std::vector<T>, typename Comparator = std::less<typename Container::value_type> >
class IterablePriorityQueue : public IterableContainer<T, Container>, public std::priority_queue<T, Container, Comparator> {
public:
    IterablePriorityQueue(std::priority_queue<T, Container, Comparator> queue_) {
        std::size_t count_ = 0;
        while (++count_ < registeredLoggers->constants()->MAX_LOG_PER_CONTAINER && !queue_.empty()) {
            this->push(queue_.top());
            queue_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};

//
// Implements IterableContainer and provides iterable std::queue class
//
template<typename T, typename Container = std::deque<T> >
class IterableQueue : public IterableContainer<T, Container>, public std::queue<T, Container> {
public:
    IterableQueue(std::queue<T, Container> queue_) {
        std::size_t count_ = 0;
        while (++count_ < registeredLoggers->constants()->MAX_LOG_PER_CONTAINER && !queue_.empty()) {
            this->push(queue_.front());
            queue_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};

//
// Implements IterableContainer and provides iterable std::stack class
//
template<typename T, typename Container = std::deque<T> >
class IterableStack : public IterableContainer<T, Container>, public std::stack<T, Container> {
public:
    IterableStack(std::stack<T, Container> stack_) {
        std::size_t count_ = 0;
        while (++count_ < registeredLoggers->constants()->MAX_LOG_PER_CONTAINER && !stack_.empty()) {
            this->push(stack_.top());
            stack_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};
} // namespace workarounds
#endif //defined(_ELPP_STL_LOGGING)

#define _ELPP_STREAM(l) (*(l->stream()))

class NullWriter : private internal::NoCopy {
public:
    NullWriter(void) {}

    template <typename T>
    inline NullWriter& operator<<(const T&) {
        return *this;
    }
};

class Writer : private internal::NoCopy {
public:
    Writer(const std::string& loggerId_,
           unsigned int aspect_,
           unsigned int severity_,
           const char* func_,
           const char* file_,
           const unsigned long int line_,
           bool condition_ = true,
           int verboseLevel_ = 0,
           int counter_ = 0) :
        aspect_(aspect_),
        severity_(severity_),
        func_(func_),
        file_(file_),
        line_(line_),
        condition_(condition_),
        verboseLevel_(verboseLevel_),
        counter_(counter_),
        proceed_(true) {
        constants_ = registeredLoggers->constants();
        logger_ = registeredLoggers->get(loggerId_, false);
        if (logger_ == NULL) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Logger [" << loggerId_ << "] not registered or configured yet!");
            proceed_ = false;
        }
#if _ELPP_ENABLE_MUTEX
        registeredLoggers->acquireLock();
        mutex_.lock();
#endif // _ELPP_ENABLE_MUTEX

        if (proceed_) {
            proceed_ = logger_->typedConfigurations_->enabled(severity_);
        }
        if (proceed_) {
#if (defined(_ELPP_STRICT_ROLLOUT))
            checkRollOuts(severity_, logger_);
#endif // (defined(_ELPP_STRICT_ROLLOUT))
        }
        if (proceed_ && (severity_ == Level::Verbose)) {
            proceed_ = (verboseLevel_ <= constants_->CURRENT_VERBOSE_LEVEL);
        }
        if (proceed_ && (aspect_ == Aspect::Conditional)) {
            proceed_ = condition_;
        }
    }

    virtual ~Writer(void) {
        if (proceed_) {
            buildAndWriteLine();
        }
#if _ELPP_ENABLE_MUTEX
        registeredLoggers->releaseLock();
        mutex_.unlock();
#endif // _ELPP_ENABLE_MUTEX
    }

    inline Writer& operator<<(const std::string& log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(char log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(bool log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(signed short log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(unsigned short log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(signed int log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(unsigned int log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(signed long log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(unsigned long log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(float log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(double log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(char* log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(const char* log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(const void* log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(long double log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
        return *this;
    }
    inline Writer& operator<<(const std::wstring& log_) {
        if (!proceed_) { return *this; }
        return operator<<(log_.c_str());
    }
    inline Writer& operator<<(const wchar_t* log_) {
        if (!proceed_) { return *this; }
        if (log_ == NULL) {
            _ELPP_STREAM(logger_) << constants_->NULL_POINTER;
            return *this;
        }
        std::size_t len_ = wcslen(log_) + 1;
        char* buff_ = (char*)malloc(len_ + 1);
#   if _ELPP_OS_UNIX || (_ELPP_OS_WINDOWS && !_ELPP_CRT_DBG_WARNINGS)
        std::wcstombs(buff_, log_, len_);
#   elif _ELPP_OS_WINDOWS
        std::size_t convCount_ = 0;
        mbstate_t mbState_;
        ::memset((void*)&mbState_, 0, sizeof(mbState_));
        wcsrtombs_s(&convCount_, buff_, len_, &log_, len_, &mbState_);
#   endif // _ELPP_OS_UNIX
        _ELPP_STREAM(logger_) << buff_;
        free(buff_);
        return *this;
    }
#if defined(_ELPP_STL_LOGGING)
    template <typename T, typename Container>
    inline Writer& operator<<(const std::vector<T, Container>& vec_) {
        if (!proceed_) { return *this; }
        return writeIterator(vec_.begin(), vec_.end(), vec_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::list<T, Container>& list_) {
        if (!proceed_) { return *this; }
        return writeIterator(list_.begin(), list_.end(), list_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::deque<T, Container>& deque_) {
        if (!proceed_) { return *this; }
        return writeIterator(deque_.begin(), deque_.end(), deque_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::queue<T, Container>& queue_) {
        if (!proceed_) { return *this; }
        internal::workarounds::IterableQueue<T, Container> iterableQueue_ =
                static_cast<internal::workarounds::IterableQueue<T, Container> >(queue_);
        return writeIterator(iterableQueue_.begin(), iterableQueue_.end(), iterableQueue_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::stack<T, Container>& stack_) {
        if (!proceed_) { return *this; }
        internal::workarounds::IterableStack<T, Container> iterableStack_ =
                static_cast<internal::workarounds::IterableStack<T, Container> >(stack_);
        return writeIterator(iterableStack_.begin(), iterableStack_.end(), iterableStack_.size());
    }
    template <typename T, typename Container, typename Comparator>
    inline Writer& operator<<(const std::priority_queue<T, Container, Comparator>& priorityQueue_) {
        if (!proceed_) { return *this; }
        internal::workarounds::IterablePriorityQueue<T, Container, Comparator> iterablePriorityQueue_ =
                static_cast<internal::workarounds::IterablePriorityQueue<T, Container, Comparator> >(priorityQueue_);
        return writeIterator(iterablePriorityQueue_.begin(), iterablePriorityQueue_.end(), iterablePriorityQueue_.size());
    }
    template <typename T, typename Comparator, typename Container>
    inline Writer& operator<<(const std::set<T, Comparator, Container>& set_) {
        if (!proceed_) { return *this; }
        return writeIterator(set_.begin(), set_.end(), set_.size());
    }
    template <typename T, typename Comparator, typename Container>
    inline Writer& operator<<(const std::multiset<T, Comparator, Comparator>& set_) {
        if (!proceed_) { return *this; }
        return writeIterator(set_.begin(), set_.end(), set_.size());
    }
    template <typename First, typename Second>
    inline Writer& operator<<(const std::pair<First, Second>& pair_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "(";
        operator << (static_cast<First>(pair_.first));
        _ELPP_STREAM(logger_) << ", ";
        operator << (static_cast<Second>(pair_.second));
        _ELPP_STREAM(logger_) << ")";
        return *this;
    }
    template <std::size_t Size>
    inline Writer& operator<<(const std::bitset<Size>& bitset_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "[";
        _ELPP_STREAM(logger_) << bitset_.to_string();
        _ELPP_STREAM(logger_) << "]";
        return *this;
    }
    template <typename K, typename V, typename Comparator, typename Container>
    inline Writer& operator<<(const std::map<K, V, Comparator, Container>& map_) {
        if (!proceed_) { return *this; }
        return writeIterator(map_.begin(), map_.end(), map_.size());
    }
    template <typename K, typename V, typename Comparator, typename Container>
    inline Writer& operator<<(const std::multimap<K, V, Comparator, Container>& map_) {
        if (!proceed_) { return *this; }
        return writeIterator(map_.begin(), map_.end(), map_.size());
    }
#endif // defined(_ELPP_STL_LOGGING)
#if defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
    inline Writer& operator<<(const QString& log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_.toStdString();
        return *this;
    }
    inline Writer& operator<<(const QStringRef& log_) {
        if (!proceed_) { return *this; }
        return operator<<(log_.toString());
    }
    inline Writer& operator<<(qint64 log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << QString::number(log_).toStdString();
        return *this;
    }
    inline Writer& operator<<(quint64 log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << QString::number(log_).toStdString();
        return *this;
    }
    inline Writer& operator<<(QChar log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_.toLatin1();
        return *this;
    }
#   if (!_ELPP_QT_5)
    inline Writer& operator<<(QBool log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << (bool(log_ != 0) ? "true" : "false");
        return *this;
    }
#   endif // (!_ELPP_QT_5)
    inline Writer& operator<<(const QLatin1String& log_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_.latin1();
        return *this;
    }
    template <typename T>
    inline Writer& operator<<(const QList<T>& list_) {
        if (!proceed_) { return *this; }
        return writeIterator(list_.begin(), list_.end(), list_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QVector<T>& vec_) {
        if (!proceed_) { return *this; }
        return writeIterator(vec_.begin(), vec_.end(), vec_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QQueue<T>& queue_) {
        if (!proceed_) { return *this; }
        return writeIterator(queue_.begin(), queue_.end(), queue_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QSet<T>& set_) {
        if (!proceed_) { return *this; }
        return writeIterator(set_.begin(), set_.end(), set_.size());
    }
    template <typename First, typename Second>
    inline Writer& operator<<(const QPair<First, Second>& pair_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "(";
        operator << (static_cast<First>(pair_.first));
        _ELPP_STREAM(logger_) << ", ";
        operator << (static_cast<Second>(pair_.second));
        _ELPP_STREAM(logger_) << ")";
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMap<K, V>& map_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "[";
        QList<K> keys = map_.keys();
        typename QList<K>::const_iterator begin = keys.begin();
        typename QList<K>::const_iterator end = keys.end();
        int max_ = static_cast<int>(constants_->MAX_LOG_PER_CONTAINER); // to prevent warning
        for (int index_ = 0; begin != end && index_ < max_; ++index_, ++begin) {
            _ELPP_STREAM(logger_) << "(";
            operator << (static_cast<K>(*begin));
            _ELPP_STREAM(logger_) << ", ";
            operator << (static_cast<V>(map_.value(*begin)));
            _ELPP_STREAM(logger_) << ")";
            _ELPP_STREAM(logger_) << ((index_ < keys.size() -1) ? ", " : "");
        }
        if (begin != end) {
            _ELPP_STREAM(logger_) << " ...";
        }
        _ELPP_STREAM(logger_) << "]";
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMultiMap<K, V>& map_) {
        if (!proceed_) { return *this; }
        operator << (static_cast<QMap<K, V> >(map_));
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QHash<K, V>& hash_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "[";
        QList<K> keys = hash_.keys();
        typename QList<K>::const_iterator begin = keys.begin();
        typename QList<K>::const_iterator end = keys.end();
        int max_ = static_cast<int>(constants_->MAX_LOG_PER_CONTAINER); // prevent type warning
        for (int index_ = 0; begin != end && index_ < max_; ++index_, ++begin) {
            _ELPP_STREAM(logger_) << "(";
            operator << (static_cast<K>(*begin));
            _ELPP_STREAM(logger_) << ", ";
            operator << (static_cast<V>(hash_.value(*begin)));
            _ELPP_STREAM(logger_) << ")";
            _ELPP_STREAM(logger_) << ((index_ < keys.size() -1) ? ", " : "");
        }
        if (begin != end) {
            _ELPP_STREAM(logger_) << " ...";
        }
        _ELPP_STREAM(logger_) << "]";
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMultiHash<K, V>& multiHash_) {
        if (!proceed_) { return *this; }
        operator << (static_cast<QHash<K, V> >(multiHash_));
        return *this;
    }
    template <typename T>
    inline Writer& operator<<(const QLinkedList<T>& linkedList_) {
        if (!proceed_) { return *this; }
        return writeIterator(linkedList_.begin(), linkedList_.end(), linkedList_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QStack<T>& stack_) {
        if (!proceed_) { return *this; }
        return writeIterator(stack_.begin(), stack_.end(), stack_.size());
    }
#endif // defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
    template <class Class>
    inline Writer& operator<<(const Class& class_) {
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << class_;
        return *this;
    }
private:
    unsigned int aspect_;
    unsigned int severity_;
    const char* func_;
    const char* file_;
    const unsigned long int line_;
    bool condition_;
    int verboseLevel_;
    int counter_;
    Logger* logger_;
    std::stringstream tempss_;
    std::string currLine_;
    bool proceed_;
    internal::Constants* constants_;
    internal::threading::Mutex mutex_;

    friend class Logger;

    template<class Iterator>
    inline Writer& writeIterator(Iterator begin_, Iterator end_, std::size_t size_) {
        _ELPP_STREAM(logger_) << "[";
        for (std::size_t i = 0; begin_ != end_ && i < constants_->MAX_LOG_PER_CONTAINER; ++i, ++begin_) {
            operator << (*begin_);
            _ELPP_STREAM(logger_) << ((i < size_ - 1) ? ", " : "");
        }
        if (begin_ != end_) {
            _ELPP_STREAM(logger_) << " ...";
        }
        _ELPP_STREAM(logger_) << "]";
        return *this;
    }

    void buildAndWriteLine(void) {
        internal::RegisteredLoggers* rl_ = registeredLoggers.pointer();
        TypedConfigurations* conf_ = logger_->typedConfigurations_;
        unsigned int f_ = conf_->formatFlag(severity_); // format spec
        currLine_ = conf_->logFormat(severity_);
        std::string dateFormat = conf_->dateFormat(severity_);
        std::string fs_; // format specifier
        std::string v_; // value
        // App name
        if (f_ & constants_->kAppName) {
            v_ = logger_->applicationName();
            fs_ = constants_->APP_NAME_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Logger ID
        if (f_ & constants_->kLoggerId) {
            v_ = logger_->id();
            fs_ = constants_->LOGGER_ID_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Thread ID
        if (f_ & constants_->kThreadId) {
            std::stringstream ss;
            ss << threading::getCurrentThreadId();
            fs_ = constants_->THREAD_ID_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, ss.str(), currLine_, constants_);
        }
        // Date/Time
        if ((f_ & constants_->kDateOnly) || (f_ & constants_->kTimeOnly) || (f_ & constants_->kDateTime)) {
            v_ = internal::utilities::DateUtils::getDateTime(dateFormat,
                                                             f_, constants_, conf_->millisecondsWidth(Level::All));
            fs_ = conf_->dateFormatSpecifier(severity_);
            internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Function
        if (f_ & constants_->kFunction) {
            v_ = std::string(func_);
            fs_ = constants_->FUNCTION_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Location
        if (f_ & constants_->kLocation) {
            tempss_ << file_ << ":" << line_;
            fs_ = constants_->LOCATION_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, tempss_.str(), currLine_, constants_);
            tempss_.str("");
        }
        // User
        if (f_ & constants_->kUser) {
            v_ = rl_->username();
            fs_ = constants_->USER_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Host
        if (f_ & constants_->kHost) {
            v_ = rl_->hostname();
            fs_ = constants_->HOST_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Verbose level
        if ((severity_ == Level::Verbose) && (f_ & constants_->kVerboseLevel)) {
            tempss_ << verboseLevel_;
            fs_ = constants_->VERBOSE_LEVEL_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, tempss_.str(), currLine_, constants_);
        }
        // Log message
        if (f_ & constants_->kLogMessage) {
            fs_ = constants_->LOG_MESSAGE_FORMAT_SPECIFIER;
            internal::utilities::LogManipulator::updateFormatValue(fs_, logger_->stream()->str(), currLine_, constants_);
        }
        log();
    }

#if (defined(_ELPP_STRICT_ROLLOUT))
    bool checkRollOuts(unsigned int level_, Logger* baseLogger_) {
        unsigned int validLevel_ = 0;
        std::string rolledOutFile = std::string();
        if (baseLogger_->typedConfigurations_->checkRollOuts(level_, validLevel_, rolledOutFile)) {
            Logger* currLogger_ = NULL;
            for (unsigned int i = 0; i < registeredLoggers->count(); ++i) {
                currLogger_ = registeredLoggers->list().at(i);
                if (currLogger_ == baseLogger_)
                    continue;
                std::string fname = currLogger_->typedConfigurations_->filename(validLevel_);
                if (fname == rolledOutFile) {
                    currLogger_->typedConfigurations_->forceReinitiateFile(validLevel_, fname);
                }
            }
            return true;
        }
        return false;
    }
#endif // (defined(_ELPP_STRICT_ROLLOUT))

    inline void syncWritePointer(unsigned int level_, Logger* targetLogger_, std::fstream* baseStream_) {
        targetLogger_->acquireLock();
        targetLogger_->typedConfigurations_->fileStream(level_)->seekg(baseStream_->tellg());
        targetLogger_->releaseLock();
    }

    void safeWriteToFile(unsigned int level_, Logger* logger_, const std::string& line) {
        std::string baseFilename_ = logger_->typedConfigurations_->filename(level_);
        std::fstream* fstr = logger_->typedConfigurations_->fileStream(level_);
        (*fstr) << line;
        fstr->flush();
        Logger* currLogger_ = NULL;
        for (std::size_t i = 0; i < registeredLoggers->count(); ++i) {
            currLogger_ = registeredLoggers->list().at(i);
            if (currLogger_ == logger_)
                continue;
            std::string fname = currLogger_->typedConfigurations_->filename(level_);
            if (fname == baseFilename_) {
                syncWritePointer(level_, currLogger_, fstr);
            }
        }
    }

    void log(void) {
        if (logger_->stream_) {
            if (logger_->typedConfigurations_->toFile(severity_)) {
                safeWriteToFile(severity_, logger_, currLine_);
            }
            if (logger_->typedConfigurations_->toStandardOutput(severity_)) {
                std::cout << currLine_;
            }
            logger_->stream_->str("");
        }
    }
};
} // namespace internal

class VersionInfo : private internal::StaticClass {
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
    static inline const std::string version(void) { return std::string("8.91"); }

    // Release date of current version
    static inline const std::string releaseDate(void) { return std::string("12-07-2013 1243hrs"); }

    // Original author and maintainer
    static inline const std::string author(void) { return std::string("Majid Khan <mkhan3189@gmail.com>"); }

    // Web link
    static inline const std::string website(void) { return std::string("http://icplusplus.com/tools/easylogging"); }

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
}; // class VersionInfo

//!
//! \brief Helper class to manage loggers and configurations
//!
//! A static helper class for users of library. This class contains functions related to register
//! and configure logger/s
//!
class Loggers : private internal::StaticClass {
public:

    //!
    //! Get existing logger, if logger does not exist a newly created logger is returned
    //! \param identifier_ A unique ID for logger
    //! \return Pointer to easyloggingpp::Logger from logger repository
    //!
    static inline Logger* getLogger(const std::string& identifier_) {
        return internal::registeredLoggers->get(identifier_);
    }

    //!
    //! Reconfigures logger with easyloggingpp::Configurations
    //! \param logger_ Pointer to Logger to configure. You get use getLogger() to get pointer from logger repository
    //! \param configurations_ easyloggingpp::Configurations to configure logger against
    //! \return Updated pointer to Logger
    //!
    static inline Logger* reconfigureLogger(Logger* logger_, const Configurations& configurations_) {
        if (!logger_) return NULL;
        logger_->configure(configurations_);
        return logger_;
    }

    //!
    //! Reconfigures logger with easyloggingpp::Configurations
    //! \param identifier_ Logger ID
    //! \param configurations_ easyloggingpp::Configurations to configure logger against
    //! \return Updated pointer to Logger
    //!
    static inline Logger* reconfigureLogger(const std::string& identifier_, Configurations& configurations_) {
        Logger* logger_ = Loggers::getLogger(identifier_);
        Loggers::reconfigureLogger(logger_, configurations_);
        return logger_;
    }

    //!
    //! Reconfigures all loggers available in logger repository
    //! \param configurations_ easyloggingpp::Configurations to configure logger against
    //!
    static inline void reconfigureAllLoggers(Configurations& configurations_) {
        for (std::size_t i = 0; i < internal::registeredLoggers->count(); ++i) {
            Logger* l = internal::registeredLoggers->at(i);
            Loggers::reconfigureLogger(l, configurations_);
        }
    }

    //!
    //! Reconfigures all loggers for single configuration.
    //! \param configurationType_ Configuration type to update. Use easyloggingpp::ConfigurationType to prevent confusion
    //! \param value_ Value to set. Values have to be std::string; For boolean values use "true", "false", for any integral values
    //!        use them in quotes. They will be parsed when configuring
    //!
    static inline void reconfigureAllLoggers(unsigned int configurationType_, const std::string& value_) {
        for (std::size_t i = 0; i < internal::registeredLoggers->count(); ++i) {
            Logger* l = internal::registeredLoggers->at(i);
            l->configurations().setAll(configurationType_, value_);
            l->reconfigure();
        }
    }

    //!
    //! Sets default configurations. This configuration is used for future loggers.
    //! \param configurations
    //! \param configureExistingLoggers If true, all loggers are updated against provided configuration otherwise only future loggers
    //!        will be updated and all the existing loggers will use configurations that have been set previously.
    //!
    static inline void setDefaultConfigurations(Configurations& configurations, bool configureExistingLoggers = false) {
        internal::registeredLoggers->setDefaultConfigurations(configurations);
        if (configureExistingLoggers) {
            Loggers::reconfigureAllLoggers(configurations);
        }
    }

    //!
    //! Sets application arguments and uses them where needed. Example use is when application is run with '--v=X' or '-v', verbose logging
    //! turns on
    //! \param argc Argument count
    //! \param argv Argument value array pointer
    //!
    static inline void setApplicationArguments(int argc, char** argv) {
        internal::registeredLoggers->setApplicationArguments(argc, argv);
    }

    //!
    //! Sets application arguments and uses them where needed. Example use is when application is run with '--v=X' or '-v', verbose logging
    //! turns on
    //! \param argc
    //! \param argv
    //!
    static inline void setApplicationArguments(int argc, const char** argv) {
        internal::registeredLoggers->setApplicationArguments(argc, argv);
    }

    //!
    //! Disables all loggers
    //!
    static inline void disableAll(void) {
        reconfigureAllLoggers(ConfigurationType::Enabled, "false");
    }

    //!
    //! Enable all loggers
    //!
    static inline void enableAll(void) {
        reconfigureAllLoggers(ConfigurationType::Enabled, "true");
    }

    //!
    //! Reconfigure all loggers to write to single log file
    //! \param logFilename_ Full path to log file
    //!
    static inline void setFilename(const std::string& logFilename_) {
        reconfigureAllLoggers(ConfigurationType::Filename, logFilename_);
    }

    //!
    //! Reconfigure specified logger to write to specified log file
    //! \param logger_ Pointer to logger. You may use Loggers::get(id) to get pointer
    //! \param logFilename_ Full path to log file
    //!
    static inline void setFilename(Logger* logger_, const std::string& logFilename_) {
        if (!logger_) return;
        logger_->configurations().setAll(ConfigurationType::Filename, logFilename_);
        logger_->reconfigure();
    }

    //!
    //! Determines whether or not performance tracking is enabled
    //! \return True if enabled, false otherwise
    //!
    static inline bool performanceTrackingEnabled(void) {
        return performanceLogger()->typedConfigurations_->performanceTracking();
    }

    //!
    //! Disables performance tracking.
    //! Performance tracking is logged using 'performance' logger.
    //!
    static inline void disablePerformanceTracking(void) {
        Logger* l = Loggers::performanceLogger();
        l->configurations().setAll(ConfigurationType::PerformanceTracking, "false");
        l->reconfigure();
    }

    //!
    //! Enable performance tracking
    //! Performance tracking is logged using 'performance' logger.
    //!
    static inline void enablePerformanceTracking(void) {
        Logger* l = Loggers::performanceLogger();
        l->configurations().setAll(ConfigurationType::PerformanceTracking, "true");
        l->reconfigure();
    }

    //!
    //! Iterates through logger repository and puts IDs into listOfIds
    //! \param listOfIds (Passed by reference) Vector to fill up
    //!
    static inline void getAllLogIdentifiers(std::vector<std::string>& listOfIds) {
        listOfIds.clear();
        for (std::size_t i = 0; i < internal::registeredLoggers->count(); ++i) {
            listOfIds.push_back(internal::registeredLoggers->at(i)->id());
        }
    }

    //!
    //! \return Returns one of default loggers 'trivial' logger
    //!
    static inline Logger* trivialLogger(void) {
        return Loggers::getLogger("trivial");
    }

    //!
    //! \return Returns one of default loggers 'business' logger
    //!
    static inline Logger* businessLogger(void) {
        return Loggers::getLogger("business");
    }

    //!
    //! \return Returns one of default loggers 'security' logger
    //!
    static inline Logger* securityLogger(void) {
        return Loggers::getLogger("security");
    }

    //!
    //! \return Returns one of default loggers 'performance' logger
    //!
    static inline Logger* performanceLogger(void) {
        return Loggers::getLogger("performance");
    }

    //!
    //! Static class that contains static helper functions used to read configurations
    //!
    class ConfigurationsReader : private internal::StaticClass {
    public:
        static inline bool enabled(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->enabled(level_);
        }

        static inline bool enabled(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->enabled(level_);
        }

        static inline bool toFile(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->toFile(level_);
        }

        static inline bool toFile(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->toFile(level_);
        }

        static inline const std::string& filename(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->filename(level_);
        }

        static inline const std::string& filename(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->filename(level_);
        }

        static inline bool toStandardOutput(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->toStandardOutput(level_);
        }

        static inline bool toStandardOutput(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->toStandardOutput(level_);
        }

        static inline const std::string& logFormat(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->logFormat(level_);
        }

        static inline const std::string& logFormat(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->logFormat(level_);
        }

        static inline int millisecondsWidth(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->millisecondsWidth(level_);
        }

        static inline int millisecondsWidth(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->millisecondsWidth(level_);
        }

        static inline bool performanceTracking(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->performanceTracking(level_);
        }

        static inline bool performanceTracking(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->performanceTracking(level_);
        }

        static inline std::size_t logRollOutSize(Logger* logger_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(logger_ != NULL, "Invalid Logger provided - nullptr");
            return constConf(logger_)->rollOutSize(level_);
        }

        static inline std::size_t logRollOutSize(internal::TypedConfigurations* conf_, unsigned int level_ = Level::All) {
            __EASYLOGGINGPP_ASSERT(conf_ != NULL, "Invalid TypedConfigurations provided - nullptr");
            return conf_->rollOutSize(level_);
        }

    private:
        static inline internal::TypedConfigurations* constConf(Logger* logger_) {
            return logger_->typedConfigurations_;
        }
    }; // class ConfigurationsReader
private:
    internal::threading::Mutex mutex_;
};
//
// Helping Macros
//
// Performance tracking macros
#if ((!defined(_DISABLE_PERFORMANCE_TRACKING)) || (!defined(_DISABLE_INFO_LOGS)))
#   if _ELPP_OS_UNIX
#      define _ELPP_GET_CURR_TIME(tm) gettimeofday(tm, NULL);
#   elif _ELPP_OS_WINDOWS
#      define _ELPP_GET_CURR_TIME(tm) easyloggingpp::internal::utilities::DateUtils::gettimeofday(tm);
#   endif
#   define START_FUNCTION_LOG "Executing [" << __func__ << "]"
#   define TIME_OUTPUT "Executed [" << __func__ << "] in [" <<                    \
    easyloggingpp::internal::utilities::DateUtils::formatMilliSeconds(        \
    easyloggingpp::internal::utilities::DateUtils::getTimeDifference(functionEndTime, functionStartTime)) << "]"
#   define FUNC_SUB_COMMON_START { timeval functionStartTime, functionEndTime; _ELPP_GET_CURR_TIME(&functionStartTime)
#   define WRITE_FUNC_PERFORMANCE _ELPP_GET_CURR_TIME(&functionEndTime);            \
    if (easyloggingpp::Loggers::performanceTrackingEnabled()) { PINFO << TIME_OUTPUT; }
#   define FUNC_SUB_COMMON_END WRITE_FUNC_PERFORMANCE;
#   define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#   define END_SUB FUNC_SUB_COMMON_END }
#   define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#   define RETURN(return_value) FUNC_SUB_COMMON_END return return_value;
#   define END_FUNC(return_value) RETURN(return_value) }
#   define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#   define END_MAIN(return_value) FUNC_SUB_COMMON_END; return return_value; }
#   define RETURN_MAIN(exit_status) return exit_status;
#else
#   define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
#   define END_SUB }
#   define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
#   define END_FUNC(x) return x; }
#   define RETURN(expr) return expr;
#   define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#   define END_MAIN(x) return x; }
#   define RETURN_MAIN(exit_status) return exit_status;
#endif // ((!defined(_DISABLE_PERFORMANCE_TRACKING)) || (!defined(_DISABLE_INFO_LOGS)))

#define _ELPP_LOG_WRITER(_logger, _level) easyloggingpp::internal::Writer(\
    _logger, easyloggingpp::internal::Aspect::Normal, _level, __func__, __FILE__, __LINE__)
#define _ELPP_LOG_WRITER_COND(_c, _logger, _level) if (_c) easyloggingpp::internal::Writer(\
    _logger, easyloggingpp::internal::Aspect::Conditional, _level, __func__, __FILE__, __LINE__, _c)
#define _ELPP_LOG_WRITER_N(_n, _logger, _level) if (easyloggingpp::internal::registeredLoggers->validateCounter(\
    __FILE__, __LINE__, _n)) easyloggingpp::internal::Writer(_logger, easyloggingpp::internal::Aspect::Interval,\
    _level, __func__, __FILE__, __LINE__, true, 0, _n)
#undef VLOG_IS_ON
#define VLOG_IS_ON(verboseLevel) verboseLevel <= easyloggingpp::internal::registeredLoggers->constants()->CURRENT_VERBOSE_LEVEL
// Undef levels to support LOG(LEVEL)
#undef INFO
#undef DEBUG
#undef ERROR
#undef FATAL
#undef QA
#undef TRACE
#undef VERBOSE
//
// Custom loggers - macro names with levels - requires loggerId
//
// Undef existing
#undef CINFO
#undef CWARNING
#undef CDEBUG
#undef CERROR
#undef CFATAL
#undef ERROR
#undef CQA
#undef CTRACE
#undef CVERBOSE
#undef CINFO_IF
#undef CWARNING_IF
#undef CDEBUG_IF
#undef CERROR_IF
#undef CFATAL_IF
#undef ERROR_IF
#undef CQA_IF
#undef CTRACE_IF
#undef CVERBOSE_IF
#undef CINFO_EVERY_N
#undef CWARNING_EVERY_N
#undef CDEBUG_EVERY_N
#undef CERROR_EVERY_N
#undef CFATAL_EVERY_N
#undef ERROR_EVERY_N
#undef CQA_EVERY_N
#undef CTRACE_EVERY_N
#undef CVERBOSE_EVERY_N
// Normal logs
#if _ELPP_INFO_LOG
#   define CINFO(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::Info)
#else
#   define CINFO(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_INFO_LOG
#if _ELPP_WARNING_LOG
#   define CWARNING(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::Warning)
#else
#   define CWARNING(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_WARNING_LOG
#if _ELPP_DEBUG_LOG
#   define CDEBUG(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::Debug)
#else
#   define CDEBUG(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_DEBUG_LOG
#if _ELPP_ERROR_LOG
#   define CERROR(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::Error)
#else
#   define CERROR(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_ERROR_LOG
#if _ELPP_FATAL_LOG
#   define CFATAL(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::Fatal)
#else
#   define CFATAL(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_FATAL_LOG
#if _ELPP_QA_LOG
#   define CQA(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::QA)
#else
#   define CQA(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_QA_LOG
#if _ELPP_TRACE_LOG
#   define CTRACE(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::Trace)
#else
#   define CTRACE(loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_TRACE_LOG
#if _ELPP_VERBOSE_LOG
#   define CVERBOSE(vlevel_, loggerId) easyloggingpp::internal::Writer(loggerId, easyloggingpp::internal::Aspect::Normal,       \
       easyloggingpp::Level::Verbose, __func__, __FILE__, __LINE__, true, vlevel_)
#else
#   define CVERBOSE(vlevel_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_VERBOSE_LOG
// Conditional logs
#if _ELPP_INFO_LOG
#   define CINFO_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::Info)
#else
#   define CINFO_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_INFO_LOG
#if _ELPP_WARNING_LOG
#   define CWARNING_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::Warning)
#else
#   define CWARNING_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_WARNING_LOG
#if _ELPP_DEBUG_LOG
#   define CDEBUG_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::Debug)
#else
#   define CDEBUG_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_DEBUG_LOG
#if _ELPP_ERROR_LOG
#   define CERROR_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::Error)
#else
#   define CERROR_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_ERROR_LOG
#if _ELPP_FATAL_LOG
#   define CFATAL_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::Fatal)
#else
#   define CFATAL_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_FATAL_LOG
#if _ELPP_QA_LOG
#   define CQA_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::QA)
#else
#   define CQA_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_QA_LOG
#if _ELPP_TRACE_LOG
#   define CTRACE_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::Trace)
#else
#   define CTRACE_IF(condition_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_TRACE_LOG
#if _ELPP_VERBOSE_LOG
#   define CVERBOSE_IF(condition_, vlevel_, loggerId) if (condition_) easyloggingpp::internal::Writer(loggerId, easyloggingpp::internal::Aspect::Conditional,     \
       easyloggingpp::Level::Verbose, __func__, __FILE__, __LINE__, condition_, vlevel_)
#else
#   define CVERBOSE_IF(condition_, vlevel_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_VERBOSE_LOG
// Interval logs
#if _ELPP_INFO_LOG
#   define CINFO_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::Info)
#else
#   define CINFO_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_INFO_LOG
#if _ELPP_WARNING_LOG
#   define CWARNING_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::Warning)
#else
#   define CWARNING_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_WARNING_LOG
#if _ELPP_DEBUG_LOG
#   define CDEBUG_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::Debug)
#else
#   define CDEBUG_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_DEBUG_LOG
#if _ELPP_ERROR_LOG
#   define CERROR_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::Error)
#else
#   define CERROR_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_ERROR_LOG
#if _ELPP_FATAL_LOG
#   define CFATAL_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::Fatal)
#else
#   define CFATAL_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_FATAL_LOG
#if _ELPP_QA_LOG
#   define CQA_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::QA)
#else
#   define CQA_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_QA_LOG
#if _ELPP_TRACE_LOG
#   define CTRACE_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::Trace)
#else
#   define CTRACE_EVERY_N(interval_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_TRACE_LOG
#if _ELPP_VERBOSE_LOG
#   define CVERBOSE_EVERY_N(interval_, vlevel_, loggerId) if (easyloggingpp::internal::registeredLoggers->validateCounter(__FILE__, __LINE__, interval_)) \
       easyloggingpp::internal::Writer(loggerId, easyloggingpp::internal::Aspect::Interval,   \
       easyloggingpp::Level::Verbose, __func__, __FILE__, __LINE__, true, vlevel_, interval_)
#else
#   define CVERBOSE_EVERY_N(interval_, vlevel_, loggerId) easyloggingpp::internal::NullWriter()
#endif // _ELPP_VERBOSE_LOG
//
// Custom Loggers - Requires (level, loggerId)
//
// undef existing
#undef CLOG
#undef CLOG_VERBOSE
#undef CVLOG
#undef CLOG_IF
#undef CLOG_VERBOSE_IF
#undef CVLOG_IF
#undef CLOG_EVERY_N
#undef CLOG_VERBOSE_EVERY_N
#undef CVLOG_EVERY_N
// Normal logs
#define CLOG(LEVEL, loggerId) C##LEVEL(loggerId)
#define CLOG_VERBOSE(vlevel, loggerId) CVERBOSE(vlevel, loggerId)
#define CVLOG(vlevel, loggerId) CVERBOSE(vlevel, loggerId)
// Conditional logs
#define CLOG_IF(condition, LEVEL, loggerId) C##LEVEL##_IF(condition, loggerId)
#define CLOG_VERBOSE_IF(condition, vlevel, loggerId) CVERBOSE_IF(condition, vlevel, loggerId)
#define CVLOG_IF(condition, vlevel, loggerId) CVERBOSE_IF(condition, vlevel, loggerId)
// Interval logs
#define CLOG_EVERY_N(n, LEVEL, loggerId) C##LEVEL##_EVERY_N(n, loggerId)
#define CLOG_VERBOSE_EVERY_N(n, vlevel, loggerId) CVERBOSE_EVERY_N(n, vlevel, loggerId)
#define CVLOG_EVERY_N(n, vlevel, loggerId) CVERBOSE_EVERY_N(n, vlevel, loggerId)
//
// Default Loggers macro using CLOG(), CLOG_VERBOSE() and CVLOG() macros
//
// undef existing
#undef LOG
#undef LOG_VERBOSE
#undef VLOG
#undef LOG_IF
#undef LOG_VERBOSE_IF
#undef VLOG_IF
#undef LOG_EVERY_N
#undef LOG_VERBOSE_EVERY_N
#undef VLOG_EVERY_N
// Normal logs
#define LOG(LEVEL) CLOG(LEVEL, "trivial")
#define LOG_VERBOSE(vlevel) CLOG_VERBOSE(vlevel, "trivial")
#define VLOG(vlevel) CVLOG(vlevel, "trivial")
// Conditional logs
#define LOG_IF(condition, LEVEL) CLOG_IF(condition, LEVEL, "trivial")
#define LOG_VERBOSE_IF(condition, vlevel) CLOG_VERBOSE_IF(condition, vlevel, "trivial")
#define VLOG_IF(condition, vlevel) CVLOG_IF(condition, vlevel, "trivial")
// Interval logs
#define LOG_EVERY_N(n, LEVEL) CLOG_EVERY_N(n, LEVEL, "trivial")
#define LOG_VERBOSE_EVERY_N(n, vlevel) CLOG_VERBOSE_EVERY_N(n, vlevel, "trivial")
#define VLOG_EVERY_N(n, vlevel) CVLOG_EVERY_N(n, vlevel, "trivial")
//
// Default Loggers macro using C##LEVEL("trivial")
//
// undef existing
#undef LINFO
#undef LWARNING
#undef LDEBUG
#undef LERROR
#undef LFATAL
#undef LQA
#undef LTRACE
#undef LVERBOSE
#undef LINFO_IF
#undef LWARNING_IF
#undef LDEBUG_IF
#undef LERROR_IF
#undef LFATAL_IF
#undef LQA_IF
#undef LTRACE_IF
#undef LVERBOSE_IF
#undef LINFO_EVERY_N
#undef LWARNING_EVERY_N
#undef LDEBUG_EVERY_N
#undef LERROR_EVERY_N
#undef LFATAL_EVERY_N
#undef LQA_EVERY_N
#undef LTRACE_EVERY_N
#undef LVERBOSE_EVERY_N
// Normal logs
#define LINFO CINFO("trivial")
#define LWARNING CWARNING("trivial")
#define LDEBUG CDEBUG("trivial")
#define LERROR CERROR("trivial")
#define LFATAL CFATAL("trivial")
#define LQA CQA("trivial")
#define LTRACE CTRACE("trivial")
#define LVERBOSE(level) CVERBOSE(level, "trivial")
// Conditional logs
#define LINFO_IF(condition) CINFO_IF(condition, "trivial")
#define LWARNING_IF(condition) CWARNING_IF(condition, "trivial")
#define LDEBUG_IF(condition) CDEBUG_IF(condition, "trivial")
#define LERROR_IF(condition) CERROR_IF(condition, "trivial")
#define LFATAL_IF(condition) CFATAL_IF(condition, "trivial")
#define LQA_IF(condition) CQA_IF(condition, "trivial")
#define LTRACE_IF(condition) CTRACE_IF(condition, "trivial")
#define LVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "trivial")
// Interval logs
#define LINFO_EVERY_N(n) CINFO_EVERY_N(n, "trivial")
#define LWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "trivial")
#define LDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "trivial")
#define LERROR_EVERY_N(n) CERROR_EVERY_N(n, "trivial")
#define LFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "trivial")
#define LQA_EVERY_N(n) CQA_EVERY_N(n, "trivial")
#define LTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "trivial")
#define LVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "trivial")
//
// Default Loggers macro using C##LEVEL("business")
//
// undef existing
#undef BINFO
#undef BWARNING
#undef BDEBUG
#undef BERROR
#undef BFATAL
#undef BQA
#undef BTRACE
#undef BVERBOSE
#undef BINFO_IF
#undef BWARNING_IF
#undef BDEBUG_IF
#undef BERROR_IF
#undef BFATAL_IF
#undef BQA_IF
#undef BTRACE_IF
#undef BVERBOSE_IF
#undef BINFO_EVERY_N
#undef BWARNING_EVERY_N
#undef BDEBUG_EVERY_N
#undef BERROR_EVERY_N
#undef BFATAL_EVERY_N
#undef BQA_EVERY_N
#undef BTRACE_EVERY_N
#undef BVERBOSE_EVERY_N
// Normal logs
#define BINFO CINFO("business")
#define BWARNING CWARNING("business")
#define BDEBUG CDEBUG("business")
#define BERROR CERROR("business")
#define BFATAL CFATAL("business")
#define BQA CQA("business")
#define BTRACE CTRACE("business")
#define BVERBOSE(level) CVERBOSE(level, "business")
// Conditional logs
#define BINFO_IF(condition) CINFO_IF(condition, "business")
#define BWARNING_IF(condition) CWARNING_IF(condition, "business")
#define BDEBUG_IF(condition) CDEBUG_IF(condition, "business")
#define BERROR_IF(condition) CERROR_IF(condition, "business")
#define BFATAL_IF(condition) CFATAL_IF(condition, "business")
#define BQA_IF(condition) CQA_IF(condition, "business")
#define BTRACE_IF(condition) CTRACE_IF(condition, "business")
#define BVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "business")
// Interval logs
#define BINFO_EVERY_N(n) CINFO_EVERY_N(n, "business")
#define BWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "business")
#define BDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "business")
#define BERROR_EVERY_N(n) CERROR_EVERY_N(n, "business")
#define BFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "business")
#define BQA_EVERY_N(n) CQA_EVERY_N(n, "business")
#define BTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "business")
#define BVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "business")
//
// Default Loggers macro using C##LEVEL("security")
//
// undef existing
#undef SINFO
#undef SWARNING
#undef SDEBUG
#undef SERROR
#undef SFATAL
#undef SQA
#undef STRACE
#undef SVERBOSE
#undef SINFO_IF
#undef SWARNING_IF
#undef SDEBUG_IF
#undef SERROR_IF
#undef SFATAL_IF
#undef SQA_IF
#undef STRACE_IF
#undef SVERBOSE_IF
#undef SINFO_EVERY_N
#undef SWARNING_EVERY_N
#undef SDEBUG_EVERY_N
#undef SERROR_EVERY_N
#undef SFATAL_EVERY_N
#undef SQA_EVERY_N
#undef STRACE_EVERY_N
#undef SVERBOSE_EVERY_N
// Normal logs
#define SINFO CINFO("security")
#define SWARNING CWARNING("security")
#define SDEBUG CDEBUG("security")
#define SERROR CERROR("security")
#define SFATAL CFATAL("security")
#define SQA CQA("security")
#define STRACE CTRACE("security")
#define SVERBOSE(level) CVERBOSE(level, "security")
// Conditional logs
#define SINFO_IF(condition) CINFO_IF(condition, "security")
#define SWARNING_IF(condition) CWARNING_IF(condition, "security")
#define SDEBUG_IF(condition) CDEBUG_IF(condition, "security")
#define SERROR_IF(condition) CERROR_IF(condition, "security")
#define SFATAL_IF(condition) CFATAL_IF(condition, "security")
#define SQA_IF(condition) CQA_IF(condition, "security")
#define STRACE_IF(condition) CQA_IF(condition, "security")
#define SVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "security")
// Interval logs
#define SINFO_EVERY_N(n) CINFO_EVERY_N(n, "security")
#define SWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "security")
#define SDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "security")
#define SERROR_EVERY_N(n) CERROR_EVERY_N(n, "security")
#define SFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "security")
#define SQA_EVERY_N(n) CQA_EVERY_N(n, "security")
#define STRACE_EVERY_N(n) CTRACE_EVERY_N(n, "security")
#define SVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "security")
//
// Default Loggers macro using C##LEVEL("performance")
//
// undef existing
#undef PINFO
#undef PWARNING
#undef PDEBUG
#undef PERROR
#undef PFATAL
#undef PQA
#undef PTRACE
#undef PVERBOSE
#undef PINFO_IF
#undef PWARNING_IF
#undef PDEBUG_IF
#undef PERROR_IF
#undef PFATAL_IF
#undef PQA_IF
#undef PTRACE_IF
#undef PVERBOSE_IF
#undef PINFO_EVERY_N
#undef PWARNING_EVERY_N
#undef PDEBUG_EVERY_N
#undef PERROR_EVERY_N
#undef PFATAL_EVERY_N
#undef PQA_EVERY_N
#undef PTRACE_EVERY_N
#undef PVERBOSE_EVERY_N
// Normal logs
#define PINFO CINFO("performance")
#define PWARNING CWARNING("performance")
#define PDEBUG CDEBUG("performance")
#define PERROR CERROR("performance")
#define PFATAL CFATAL("performance")
#define PQA CQA("performance")
#define PTRACE CTRACE("performance")
#define PVERBOSE(level) CVERBOSE(level, "performance")
// Conditional logs
#define PINFO_IF(condition) CINFO_IF(condition, "performance")
#define PWARNING_IF(condition) CWARNING_IF(condition, "performance")
#define PDEBUG_IF(condition) CDEBUG_IF(condition, "performance")
#define PERROR_IF(condition) CERROR_IF(condition, "performance")
#define PFATAL_IF(condition) CFATAL_IF(condition, "performance")
#define PQA_IF(condition) CQA_IF(condition, "performance")
#define PTRACE_IF(condition) CQA_IF(condition, "performance")
#define PVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "performance")
// Interval logs
#define PINFO_EVERY_N(n) CINFO_EVERY_N(n, "performance")
#define PWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "performance")
#define PDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "performance")
#define PERROR_EVERY_N(n) CERROR_EVERY_N(n, "performance")
#define PFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "performance")
#define PQA_EVERY_N(n) CQA_EVERY_N(n, "performance")
#define PTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "performance")
#define PVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "performance")
// Undefine macros that are not needed anymore
#undef _ELPP_ASSEMBLY_SUPPORTED
#undef _ELPP_STREAM
#undef _ELPP_MUTEX_LOCK_GNU_ASM
#undef _ELPP_MUTEX_UNLOCK_GNU_ASM
#undef _ELPP_ENABLE_MUTEX
#undef _ENABLE_EASYLOGGING
#undef __EASYLOGGINGPP_SUPPRESS_UNSED
#undef _ELPP_DEBUG_LOG
#undef _ELPP_INFO_LOG
#undef _ELPP_WARNING_LOG
#undef _ELPP_ERROR_LOG
#undef _ELPP_FATAL_LOG
#undef _ELPP_QA_LOG
#undef _ELPP_VERBOSE_LOG
#undef _ELPP_TRACE_LOG
#undef _INITIALIZE_EASYLOGGINGPP
#undef _START_EASYLOGGINGPP
#undef _ELPP_COUNTER
#undef _ELPP_COUNTER_POSITION
#define _INITIALIZE_EASYLOGGINGPP                                 \
    namespace easyloggingpp {                                     \
        namespace internal {                                      \
            ScopedPointer<RegisteredLoggers> registeredLoggers(   \
                    new RegisteredLoggers());                     \
        }                                                         \
    }
#define _START_EASYLOGGINGPP(argc, argv) easyloggingpp::Loggers::setApplicationArguments(argc, argv);
#define _ELPP_COUNTER easyloggingpp::internal::registeredLoggers->counters()->get(__FILE__, __LINE__)
#define _ELPP_COUNTER_POSITION (_ELPP_COUNTER == NULL ? 0 : _ELPP_COUNTER->position())
} // easyloggingpp
#endif // EASYLOGGINGPP_H
