CHANGE LOG - EasyLogging++
--------------------------

Change log was not kept before version 2.1.

#### 8.xx
 * 8.00:
    - Reviewed whole design and introduced some high performance classes to manage memory efficiently
    - Support for legacy log names removed
    - Introduced concept of dynamic configuration (see read me)
    - Support for libraries - no need to take extra care - just initialize and start logging (see issue #39)
    - Multiple desitinations for each logger and for each level now possible - fully configurable (see issue #40)
    - Introduced new way of logging by combining conditional and interval log (issue #36)
 * 8.01 & 8.02: Bug fixes
 * 8.03: Default log location is now `/tmp/logs/myeasylog.log`
 * 8.04: Fixed issue with uninitialized variable error on llvm-gcc-4.2
 * 8.05:
     - Fixes issue with setting std::ios_base::fmtflags to stream (issue #45)
     - Change the way extending library work - now user need to write left shift operator with `std::ostream` - see README for details
 * 8.06: Fixes some more gcc warnings
 * 8.07: Support for Qt5
 * 8.08: Changes `ELPP_MillisecondsLength` to `ELPP_MillisecondsWidth` (issue #49)
 * 8.09: `millisecondsLength` function is now changed to `millisecondsWidth`
 * 8.10: Added a note of potentially changed file and links to download original version
 * 8.11: Added `enablePerformanceTracking` in `Loggers`
 * 8.12: Fixed memory leak `getCurrentHost` and `getCurrentUser` in windows (thanks to Les Lewicki for reporting)
 * 8.13: Fixed computer name env var on windows
 * 8.15:
     - Introduced `ELPP_RollOutSize` configuration to roll out logs after certain size
     - Introduced `_ELPP_STRICT_ROLLOUT` macro to check for rollable files with each log. (Usage is only recommended in dev and QA)
     - Replaced macro NO-INIT and NO-COPY with class based
     - Refactored `reConfigureLogger` to `reconfigureLogger` and `resetAllLoggersConfigurations` to `reconfigureAllLoggers`
     - Introduced `Loggers::ConfigurationsReader::logRollOutSize()`
     - `Configurations` constructor does not set default value internally to prevent loss of configurations. Developers are asked to use `setToDefault()` to do so.
 * 8.16: Fixed return type for log rollout
 * 8.17: Fixes issue with performance tracking from 8.16
 * 8.18: Introduced `_ELPP_INTERNAL_INFO` to display internal information - see READ ME for details
 * 8.19: Fixes issue with rolling out log file
 * 8.20:
     - Fixes issue with rolling logs in other levels (Thanks to Les for reporting)
     - Performance improvement when log disabled and strict rolling (Thanks to Les)
 * 8.21: Fixes issue with rollout if level doesnt use dedicated filename
 * 8.22: Added Qt version check
 * 8.25: Stablized roll outs
 * 8.26:
     - ROLL OUT SIZE for each level (see issue #51)
     - Sets default roll out
 * 8.27: Fix formatting
 * 8.28: Fixes issue with format flags having same value
 * 8.29: Returning const ref configurations in ConfigurationsReader for performance
 * 8.30: Fixes issue with _ALWAYS_CLEAN_LOGS when reconfiguring logger
 * 8.31: Minor bug fix
 * 8.32:
     - Fixes race condition issue with roll out size
     - Removed support for `_ALWAYS_CLEAN_LOGS`
 * 8.33: Added back Qt 5 check
 * 8.35:
     - Fixed issue Roll out size usage cause lose loggers (issue #54) [Thanks to les]
     - Fixed multithreading issue for interval logs and custom loggers
     - Fixed warnings on VC++
 * 8.36: Fix for internal info
 * 8.37:
     - Warning fix for scoped lock
     - Renamed `SmartPointer<T>` to `ScopedPointer<T>`
 * 8.38: Minor internal namespace fixes
 * 8.39: Fixes warnings for int to size_t conversion
 * 8.40: Minor improvements + safeDelete(T*), fixed issue #55
 * 8.41:
     - Provides useful interfacing for external tools
     - Rollout size is not beta anymore
 * 8.45:
     - Renamed easyloggingpp::Level::... from ELPP_INFO to Info, ELPP_DEBUG to Debug etc.
     - Renamed easyloggingpp::ConfigurationType::... from ELPP_Enabled to Enabled, ELPP_ToFile to ToFile
     - Provides conversions from and to std::string for level and configuration type for external tools
 * 8.46:
     - Introduced `%thread` format specifier for logging thread ID
     - Explicit check for `__func__` to prevent potential compilation warnings
 * 8.47: Keeps OS evaluated macros defined
 * 8.48:
     - Fixes bug with configurating all loggers including TRACE level
     - Fixes std::thread issue for getting thread ID
 * 8.49: Fixed up issue with syscall undef
 * 8.50: Fixed issues with MinGW compile (issue #58)
 * 8.51: Fixes bash command issue when getting env variable
 * 8.52:
     - environment variable function improvements
     - NDK (android build) fixes
 * 8.55: Made configuration access faster by introducing `ConfigurationMap<T>` (issue #62)
 * 8.56: Android host name (issue #61)
 * 8.57: Issue with android host and username fixed
 * 8.58: Minor performance improvements around implicit and explicit casting
 * 8.59: Fix warnings by eclipse
 * 8.60: More warning fixes for eclipse
 * 8.61: Fixes issues with VC++ 2010
 * 8.65: Major performance improvements using pre-processors
 * 8.66: Fix level based disable logs
 * 8.70: Other logging libraries compatiable macros; e.g, `LOG(INFO) << "..."`
 * 8.71: Fix LOG_VERBOSE_EVERY_N macro
 * 8.72:
     - Added `CLOG(LEVEL, LoggerId)` macro for sensable name for custom loggers - these macro uses `C##LEVEL` macros
     - `LOG(LEVEL)` now uses newly `CLOG` macros
 * 8.75:
     - Code improvements for speed
     - Added `Loggers::setDefaultConfigurations` to configure existing and future loggers
 * 8.76:
     - Introduced `VLOG(verboseLevel)`, `CVLOG(verboseLevel, logger)`, `VLOG_IF`, `VLOG_EVERY_N`, CVLOG_IF`, `CVLOG_EVERY_N` for verbose logging to be more compatible with other major logging libraries
     - Introduced `VLOG_IS_ON(verboseLevel)` to check if specific verbose level is on
     - Some code improvements by inlining some code
 * 8.80:
     - Documented code that is used by user
     - Minor bug fixes
 * 8.82: Fixed major issue with reconfiguring loggers
 * 8.83: Reset old loggers (business, security, performance)
 * 8.85: Fixed LOG(ERROR) for some compilers (minGW)
 * 8.90:
     - All classes use fully qualified name from `internal namespace`
     - Removed unnecessary macro checks while undefining macros
     - Added `#undef`s for conditional and interval level based macros
     - Updated message when logger is not configured
 * 8.91:
     - Fixed up issues with 64-bit platforms ASM (issue #70)
     - Fixed issue with creating log file on new android devices (NDK)

#### 7.xx
 * 7.00:
    - Completely re-written with focus on performance and usability improvements (issue #27)
    - Code:
       - C++98 to support old applications as well
       - Now make full use of STL for performance improvement
       - New namespace easyloggingpp::internal::helper for internal use instead of C-like functions
       - Uses custom embedded mutex so does not have to worry about libraries availability (issue #28)
       - New reuseable macros 
    - New features:
       - New log types
          - `BINFO`, `BWARNING` ... etc, business loggers
          - `SINFO`, `SWARNING` ... etc, security loggers
          - `PINFO`, `PWARNING` ... etc, performance loggers
       - Inject new log types as per your requirements 
       - Added `easyloggingpp::VersionInfo` with formatted displayable information
    - Removed:
       - PERFORMANCE as severity level instead added it as log type with `PINFO << log;` or `PDEBUG << log` etc
       - Performance tracking disables with debug logs
       - _END_EASYLOGGINGPP is not needed anymore, everything is handled internally 
    - Improvements:
       - Now you dont need `_END_EASYLOGGINGPP` and dont need to worry about memory leaks, everything is done internally
       - Improved web page (icplusplus.com/tools/easylogging/)
    - Github issues closed:
       - Issue #27 Re-write whole code to improve performance
       - Issue #14 Make debug logs really when debugging
       - Issue #5 Test in win machine
       - Issue #28 Embed custom mutex class
       - Issue #29 Ability to inject new logger types
       - Issue #30 Introduce log types for type of logger 
       - Issue #31 Ditch PERFORMANCE as severity level, add it as log type
    - Licence: Changed to open source licence with full details within header

 * 7.01: Provides safe interface to use Register template outside EasyLogging++
 * 7.20: Performance tracking now tracks upto milliseconds
 * 7.21: Performance tracking is now exact not approx so got rid of ~ char
 * 7.22: Minor refactoring
 * 7.25:
     - Updated default log formats to make logs more easy to read
     - Fixed bug from 7.22
 * 7.26:
     - Updated default log format to align to make log easy to read, these log formats can be customized as per requirments
     - Updated log types format-output to prevent confusion with severity level
     - Single format specifier per severity level for performance improvement and error preventions.
 * 7.27:
     - Ability to check log counter position by introducing `_ELPP_COUNTER_POSITION`
     - Counter now gets reset every 100,000 instead of 5000 iterations.
 * 7.28: Fix date issue on RHEL for applications using Qt
 * 7.30:
      - Support for QString and other Qt based classes (QBool, qint*, QChar ...) *Container not supported as of yet*
      - Qt based classes have to be used with `_ELPP_EXPERIMENTAL`
 * 7.31:
      - Format source code
      - Standard vector (std::vector) for std::string and other primitive data types
 * 7.32:
      - Standard vector to support third party libraries if using, see sample for details (samples/container_log.cpp)
      - Primitive bool now logs true/false instead of 1/0
      - Container logs wraps quotes around each element
 * 7.33:
      - Support for std::list log
      - Fixed issue with post-include for QString
 * 7.35:
      - Support for `std::pair`, `std::map`, Qt based containers and `QPair`
      - Changed `_DO_NOT_SUPPORT_CPP_LIBRARIES` to `_DISABLE_CPP_THIRD_PARTY_LIBRARIES_LOGGING`
      - Introduced `_DISABLE_CPP_LIBRARIES_LOGGING` to disable containers and other classes logging support
 * 7.36: Raw array logging
 * 7.37: Support for container (vector, list) of pointers
 * 7.38: Fix for overloaded const containers
 * 7.39: No support for raw arrays any more instead support for pointer
 * 7.40: Disable performance tracking using `_ENABLE_PERFORMANCE_TRACKING`
 * 7.41: Major improvements around logging pointers and code clean up around containers
 * 7.42: Configurable severity type for performance tracking
 * 7.43: Improved comments
 * 7.45: Fixed all issues on windows (Visual C++ 8.0, 9.0, 10.0, 11.0)
 * 7.50:
      - Massive performance improvements by setting formats at initialize time
      - Introduced MILLISECONDS_LENGTH for UNIX
 * 7.55:
      - Improved multi-threading
      - Dropped support for power PC
      - Prevent potential naming conflicts with classes
      - Removed `using namespace` and naming explicitly
      - Better format by introducing internal::constants
 * 7.56: Simplified readibility
 * 7.58: Handle wide characters
 * 7.59: Improved performance by syncing using flush
 * 7.60:
      - Support for all STL containers, Qt containers and some deprecated GNU containers (issue #35)
      - Limits containers log for logging containers faster (issue #37)
 * 7.61: Improvements around EasyLogging++ design structure
 * 7.62: Improvements around overhead when logging is disabled.
 * 7.65:
      - Some massive improvements around removing orphan variables for multiple libs support
      - Mutex now part of Logger
      - Internal configs and user configs are now part of Logger and are used throughout via pointers for speed
      - Now compiler will not complained about multiple definitions errors but introduced conditional run-time error (see FAQ 2)
 * 7.66: Emerg release to fix writing to custom location
 * 7.67: Fixed undefined `_SUPPRESS_UNUSED_WARN` error
 * 7.68: Added application name support in format.

#### 6.xx
 * 6.00:
    - Changed the way of logging i.e, no parentheses required anymore (issue #26)
    - Naming conflicts for debug logs (issue #25)
    - Old names still supported with `_SUPPORT)_LEGACY_LOG_NAMES` macro (issue #25)
    - Removed STATUS and HINT log levels (issue #23)
    - Now supports full version only - linked version is ditched away (issue #24)
 * 6.01: Fixes from 6.00 changes
 * 6.02: Format update to simplify readibility
 * 6.03: Fixed memory leak from END_MAIN(..) while using performance tracker
 * 6.04: Failure fix when performance log is disabled
 * 6.10:
    - Revision 1.2 for unit tests
    - Fix some issues found by rev1.2 tests

#### 5.0
 * 5.00:
    - Support for multithreaded applications for C++0X / C++11 (issue #21)
    - Fixed up issue with `_ALWAYS_CLEAN_LOGS` (issue #22)
    - Fixed up bug with interval log where it was off by 1
    - Extended for linked and full type (see README at github for details)
 * 5.01: Fixed up compile failure if logs disabled for both linked and full
 * 5.02: Minor comment fixes for readibility
 * 5.03: Fixed bug with `_DISABLE_MUTEX`
 * 5.04: Date/time fix for windows (issue #4)
 * 5.05: Use QMutex when available
 * 5.06: Macro rename for mutex evaluation

#### 4.xx
 * 4.00:
    - Major improvement for multiple files project
    - Introduced `INITIALIZE_EASYLOGGINGPP`
 * 4.01:
    - Added inline doc
    - Fix issue with `TO_STANDARD_OUTPUT` segmentation fault
    - Added support for `--verbose` for level 9
 * 4.02: Minor naming fixes (refactoring)
 * 4.03: Added extra namespace to suppress `unused` warnings
 * 4.04:
    - Performance improvement when determining log format
    - Performance improvement for escape character in log format
 * 4.05: Performance improvement while building path
 * 4.06: Minor namespace fix
 * 4.07: Introduced `LOG_EVERY_N` (interval logging) for all log levels
 * 4.08:
    - Interval logging works well even in the same iteration
    - Introduced `::easyloggingpp::version` namespace for version info of current version
 * 4.09: Minor issue fix regarding multiple-definition error
 * 4.10: gcc warnings
 * 4.11: Registered counters lookup improvement
 * 4.12: Fully qualified names used
 * 4.13: Added partial compiler evaluation macros
 * 4.14: Return on first error while creating log path
 * 4.15: END_FUNC with return value now

#### 3.3
 * 3.30:
    - Added new `QA(..)` logs (issue #17)
    - Splits functions into namespaces (issue #18)
    - Fixed issue with helper functions when logs disabled
    - Fixed issue with compiling using LLVM on mac (issue #16)
 * 3.31: Fixes issue with `const char**` vs `char**` argv (issue #19)
 * 3.32: Tries harder (using `hostname`) to retrieve host name on ubuntu based linux.
 * 3.33: Fixed releaseMemory
 * 3.34: Type check for verbose log argument
 * 3.35: Memory leak issue when tracking performance (issue #20)
 * 3.36: Introduced MAIN, END_MAIN and RETURN_MAIN for memory release safety

#### 3.2
 * 3.20: Added conditional logging using `INFO_IF`, `DEBUG_IF`, etc.
 * 3.21: Code readibility improvements
 * 3.22: Introduced VERBOSE logging
 * 3.23: Simplified for new logs by creating LogType class
 * 3.24: Make sure `%vlevel` is only applicable to VERBOSE logs
 * 3.25: Minor improvements
 * 3.26: Minor improvements
 * 3.27: Fixed issue #15
 * 3.28: Fix for VERBOSE_IF
 * 3.29: Introduced `_END_EASYLOGGINGPP` to make valgrind happy
 
#### 3.1
 * 3.10: Removed comments around configuration to point to README
 * 3.11: Type / level constructor called within WRITE_LOG macro only 
 * 3.12: minor fixes around comments
 * 3.13: fixes for update.sh
 * 3.14: fix for windows compile failure, thanks to `codyzu`
 * 3.15: 
    - Added more control over disabling logs
    - Changed from `_DISABLE_EASYLOGGINGPP` to `_DISABLE_LOGS`
 * 3.16: Minor improvement
 * 3.17: Minor logic improvement
 * 3.18: Added support for regression testing to clean log every time you run application.
 * 3.19: Added escape character for log format

#### 3.0
 * Major improvements
 * Added format specifiers for each logging level
 * Issue#7 formatting logs
 * 3.01: Fix up path creation on mac
 * 3.02: Added slash as escape character in format
 * 3.03: Fixed bug for other OS than mac, linux or windows
 * 3.04: Got rid of new line character `%n` instead `\n` can be used
 * 3.05 and 3.06: Fixes for \n from 3.04
 * 3.07: Adds _DISABLE_EASYLOGGINGPP, macro to disable EasyLogging++ while compiling
 * 3.08: Fix for update.sh includes
 * 3.09 improvements around log file performance

#### 2.8
 * Added `update.sh` to update your old easylogging++.h without losing configuration
 * A lot of date improvements in terms of memory and performance efficiency
 * 2.843: Fixes milliseconds issue for linux only.
 * 2.844: Do not calculate milliseconds when SHOW_TIME is set to false
 * 2.845: Strict support for any other OS than linux or windows

#### 2.7
 * Fixed up log path creation issue to create whole path

#### 2.6
 * Added helper function `string readLog(void)`
 * Changed `WARN` to `WARNING` for warning logs

#### 2.5
 * Added _WIN64 macro checks for 64-bit windows machines
 * Issue#3 Force log file creation
 * Memory efficient approaches for writing logs

#### 2.3
 * Added host and username to be included in logs
 * Added `release.sh` for easy releaases

#### 2.2
 * Added PERFORMANCE, STATUS and HINTS logging levels

#### 2.1
 * Fixed time issues
