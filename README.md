
                                       ‫بسم الله الرَّحْمَنِ الرَّحِيمِ

![banner]

> **Manual For v9.93**

[![Build Status (Develop)](https://img.shields.io/travis/muflihun/easyloggingpp/develop.svg)](https://travis-ci.org/muflihun/easyloggingpp) (`develop`)

[![Build Status (Master)](https://img.shields.io/travis/muflihun/easyloggingpp.svg)](https://travis-ci.org/muflihun/easyloggingpp) (`master`)

[![Version](https://img.shields.io/github/release/muflihun/easyloggingpp.svg)](https://github.com/muflihun/easyloggingpp/releases/latest)

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/MuflihunDotCom/25)

[![Downloads](https://img.shields.io/github/downloads/muflihun/easyloggingpp/total.svg)](https://github.com/muflihun/easyloggingpp/releases/latest)

### Quick Links

  [![download] Latest Release](https://github.com/muflihun/easyloggingpp/releases/latest)
  
  [![notes] Release Notes](/doc/RELEASE-NOTES-v9.93)
 
  [![samples] Samples](/samples)

---

### Table of Contents
<pre>
<a href="#introduction">Introduction</a>
    <a href="#why-yet-another-library">Why yet another library</a>
    <a href="#features-at-a-glance">Features at a glance</a>
<a href="#getting-started">Getting Started</a>
    <a href="#download">Download</a>
    <a href="#quick-start">Quick Start</a>
    <a href="#install-optional">Install (Optional)</a>
    <a href="#setting-application-arguments">Setting Application Arguments</a>
<a href="#configuration">Configuration</a>
    <a href="#level">Level</a>
    <a href="#configure">Configure</a>
        <a href="#using-configuration-file">Using Configuration File</a>
        <a href="#using-elconfigurations-class">Using el::Configurations Class</a>
        <a href="#using-in-line-configurations">Using In line Configurations</a>
    <a href="#default-configurations">Default Configurations</a>
    <a href="#global-configurations">Global Configurations</a>
    <a href="#logging-format-specifiers">Logging Format Specifiers</a>
    <a href="#datetime-format-specifiers">Date/Time Format Specifiers</a>
    <a href="#custom-format-specifiers">Custom Format Specifiers</a>
    <a href="#logging-flags">Logging Flags</a>
    <a href="#application-arguments">Application Arguments</a>
    <a href="#configuration-macros">Configuration Macros</a>
    <a href="#reading-configurations">Reading Configurations</a>
<a href="#logging">Logging</a>
    <a href="#basic">Basic</a>
    <a href="#conditional-logging">Conditional Logging</a>
    <a href="#occasional-logging">Occasional Logging</a>
    <a href="#printf-like-logging">printf Like Logging</a>
    <a href="#verbose-logging">Verbose Logging</a>
        <a href="#basic-1">Basic</a>
        <a href="#conditional-and-occasional">Conditional and Occasional</a>
        <a href="#verbose-level">Verbose Level</a>
        <a href="#check-if-verbose-logging-is-on">Check If Verbose Logging Is On</a>
        <a href="#vmodule">VModule</a>
    <a href="#registering-new-loggers">Registering New Loggers</a>
    <a href="#unregister-loggers">Unregister Loggers</a>
    <a href="#populating-existing-logger-ids">Populating Existing Logger IDs</a>
    <a href="#sharing-logging-repository">Sharing Logging Repository</a>
<a href="#extra-features">Extra Features</a>
    <a href="#performance-tracking">Performance Tracking</a>
        <a href="#conditional-performance-tracking">Conditional Performance Tracking</a>
        <a href="#make-use-of-performance-tracking-data">Make Use of Performance Tracking Data</a>
    <a href="#log-file-rotating">Log File Rotating</a>
    <a href="#crash-handling">Crash Handling</a>
        <a href="#installing-custom-crash-handlers">Installing Custom Crash Handlers</a>
    <a href="#stacktrace">Stacktrace</a>
    <a href="#multi-threading">Multi-threading</a>
    <a href="#check-macros">CHECK Macros</a>
    <a href="#logging-perror">Logging perror()</a>
    <a href="#syslog">Using Syslog</a>
    <a href="#stl-logging">STL Logging</a>
        <a href="#supported-templates">Supported Templates</a>
    <a href="#qt-logging">Qt Logging</a>
    <a href="#boost-logging">Boost Logging</a>
    <a href="#wxwidgets-logging">wxWidgets Logging</a>
    <a href="#extending-library">Extending Library</a>
        <a href="#logging-your-own-class">Logging Your Own Class</a>
        <a href="#logging-third-party-class">Logging Third-party Class</a>
    <a href="#manually-flushing-and-rolling-log-files">Manually Flushing and Rolling Log Files</a>
    <a href="#log-dispatch-callback">Log Dispatch Callback</a>
    <a href="#logger-registration-callback">Logger Registration Callback</a>
    <a href="#asynchronous-logging">Asynchronous Logging</a>
    <a href="#helper-classes">Helper Classes</a>
<a href="#contribution">Contribution</a>
    <a href="#submitting-patches">Submitting Patches</a>
    <a href="#reporting-a-bug">Reporting a Bug</a>
<a href="#compatibility">Compatibility</a>
<a href="#licence">Licence</a>
<a href="#disclaimer">Disclaimer</a>
</pre>

# Introduction
Easylogging++ is single header, feature-rich, efficient logging library for C++ applications. It has been written keeping three things in mind: performance, management (setup, configure, logging, simplicity) and portability. Its highly configurable and extremely useful for small to large sized projects.
This manual is for Easylogging++ v9.93. For other versions please refer to corresponding [release](https://github.com/muflihun/easyloggingpp/releases) on github.

 [![top] Goto Top](#table-of-contents)
 
### Why yet another library
If you are working on a small utility or large project in C++, this library can be handy. Its based on single header and does not require linking or installation. You can import into your project as if its part of your project. This library has been designed with various thoughts in mind (i.e, portability, performance, usability, features and easy to setup).

Why yet another library? Well, answer is pretty straight forward, use it as if you wrote it so you can fix issues (if any) as you go or raise them on github. In addition to that, I have not seen any logging library based on single-header with such a design where you can configure on the go and get the same performance. I have seen other single-header logging libraries for C++ but either they use external libraries, e.g, boost, Qt to support certain features like threading, regular expression or date etc. This library has everything built-in to prevent usage of external libraries, not that I don't like those libraries, in fact I love them, but because not all projects use these libraries, I couldn't take risk of depending on them.

 [![top] Goto Top](#table-of-contents)
 
### Features at a glance
Easylogging++ is feature-rich containing many features that both typical and advanced developer will require while writing a software;
 * Highly configurable
 * Extremely fast
 * Thread and type safe
 * Cross-platform
 * Custom log patterns
 * Conditional and occasional logging
 * Performance tracking
 * Verbose logging
 * Crash handling
 * Helper CHECK macros
 * STL logging
 * Third-party library logging (Qt, boost, wxWidgets etc)
 * Extensible (Logging your own class or third-party class)
 * And many more...

 [![top] Goto Top](#table-of-contents)
 
# Getting Started
### Download
Download latest version from [Latest Release](https://github.com/muflihun/easyloggingpp/releases/latest)

For other releases, please visit [releases page](https://github.com/muflihun/easyloggingpp/releases). If you application does not support C++11, please consider using [v8.91](https://github.com/muflihun/easyloggingpp/tree/v8.91). This is stable version for C++98 and C++03, just lack some features.

 [![top] Goto Top](#table-of-contents)
 
### Quick Start
In order to get started with Easylogging++, you can follow three easy steps:
* Download latest version
* Include into your project (`easylogging++.h` and `easylogging++.cc`)
* Initialize using single macro... and off you go!

```c++
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
   LOG(INFO) << "My first info log using default logger";
   return 0;
}
```

Now compile using

```
g++ main.cc easylogging++.cc -o prog -std=c++11
```

That simple! Please note that `INITIALIZE_EASYLOGGINGPP` should be used once and once-only otherwise you will end up getting compilation errors. This is definiting several `extern` variables. This means it can be defined only once per application. Best place to put this initialization statement is in file where `int main(int, char**)` function is defined, right after last include statement.

### Install (Optional)
If you want to install this header system-wide, you can do so via:
```
mkdir build
cd build
cmake -Dtest=ON ../
make
make test
make install
```

With that said, you will still need `easylogging++.cc` file in order to compile. For header only, please check [v9.89](https://github.com/muflihun/easyloggingpp/releases/tag/9.89) and lower.

 [![top] Goto Top](#table-of-contents)
 
### Setting Application Arguments
It is always recommended to pass application arguments to Easylogging++. Some features of Easylogging++ require you to set application arguments, e.g, verbose logging to set verbose level or vmodules (explained later). In order to do that you can use helper macro or helper class;

```c++
int main(int argc, char* argv[]) {
   START_EASYLOGGINGPP(argc, argv);
   ...
}
```
 [![top] Goto Top](#table-of-contents)
 
# Configuration
### Level
In order to start configuring your logging library, you must understand severity levels. Easylogging++ deliberately does not use hierarchical logging in order to fully control what's enabled and what's not. That being said, there is still option to use hierarchical logging using `LoggingFlag::HierarchicalLogging`. Easylogging++ has following levels (ordered for hierarchical levels)

|   Level  |                 Description                                                                                                                                   |
|----------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Global   | Generic level that represents all levels. Useful when setting global configuration for all levels.                                                            |
| Trace    | Information that can be useful to back-trace certain events - mostly useful than debug logs.                                                                  |
| Debug    | Informational events most useful for developers to debug application. Only applicable if NDEBUG is not defined (for non-VC++) or _DEBUG is defined (for VC++).|
| Fatal    | Very severe error event that will presumably lead the application to abort.                                                                                   |
| Error    | Error information but will continue application to keep running.                                                                                              |
| Warning  | Information representing errors in application but application will keep running.                                                                             |
| Info     | Mainly useful to represent current progress of application.                                                                                                   |
| Verbose  | Information that can be highly useful and vary with verbose logging level. Verbose logging is not applicable to hierarchical logging.                         |
| Unknown  | Only applicable to hierarchical logging and is used to turn off logging completely.                                                                           |

 [![top] Goto Top](#table-of-contents)
 
### Configure
Easylogging++ is easy to configure. There are three possible ways to do so,
* Using configuration file
* Using el::Configurations class
* Using inline configuration

#### Using Configuration File
Configuration can be done by file that is loaded at runtime by `Configurations` class. This file has following format;
```
* LEVEL:
  CONFIGURATION NAME  = "VALUE" ## Comment
  ANOTHER CONFIG NAME = "VALUE"
```

Level name starts with a star (*) and ends with colon (:). It is highly recommended to start your configuration file with `Global` level so that any configuration not specified in the file will automatically use configuration from `Global`. For example, if you set `Filename` in `Global` and you want all the levels to use same filename, do not set it explicitly for each level, library will use configuration value from `Global` automatically.
Following table contains configurations supported by configuration file.

|   Configuration Name  |   Type   |                 Description                                                                                                                                                 |
|-----------------------|----------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `Enabled`               |   bool   | Determines whether or not corresponding level for logger is enabled. You may disable all logs by using `el::Level::Global`                                                |
| `To_File`               |   bool   | Whether or not to write corresponding log to log file                                                                                                                     |
| `To_Standard_Output`    |   bool   | Whether or not to write logs to standard output e.g, terminal or command prompt                                                                                           |
| `Format`                |   char*  | Determines format/pattern of logging for corresponding level and logger.                                                                                                  |
| `Filename`              |   char*  | Determines log file (full path) to write logs to for corresponding level and logger                                                                                       |
| `Subsecond_Precision`   |   uint   | Specifies subsecond precision (previously called 'milliseconds width'). Width can be within range (1-6)                                                                   |
| `Performance_Tracking`  |   bool   | Determines whether or not performance tracking is enabled. This does not depend on logger or level. Performance tracking always uses 'performance' logger unless specified|
| `Max_Log_File_Size`     |   size_t | If log file size of corresponding level is >= specified size, log file will be truncated.                                                                                 |
| `Log_Flush_Threshold`   |  size_t  | Specifies number of log entries to hold until we flush pending log data                                                                                                   |
	

Please do not use double-quotes anywhere in comment, you might end up in unexpected behaviour.

Sample Configuration File
```
* GLOBAL:
   FORMAT               =  "%datetime %msg"
   FILENAME             =  "/tmp/logs/my.log"
   ENABLED              =  true
   TO_FILE              =  true
   TO_STANDARD_OUTPUT   =  true
   SUBSECOND_PRECISION  =  6
   PERFORMANCE_TRACKING =  true
   MAX_LOG_FILE_SIZE    =  2097152 ## 2MB - Comment starts with two hashes (##)
   LOG_FLUSH_THRESHOLD  =  100 ## Flush after every 100 logs
* DEBUG:
   FORMAT               = "%datetime{%d/%M} %func %msg"
```

##### Explanation 
Configuration file contents in above sample is straightforward. We start with `GLOBAL` level in order to override all the levels. Any explicitly defined subsequent level will override configuration from `GLOBAL`. For example, all the levels except for `DEBUG` have the same format, i.e, datetime and log message. For `DEBUG` level, we have only date (with day and month), source function and log message. The rest of configurations for `DEBUG` are used from `GLOBAL`. Also, notice `{%d/%M}` in `DEBUG` format above, if you do not specify date format, default format is used. Default values of date/time is `%d/%M/%Y %h:%m:%s,%g` For more information on these format specifiers, please refer to [Date/Time Format Specifier](#datetime-format-specifiers) section below

##### Usage
```c++
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, const char** argv) {
    // Load configuration from file
    el::Configurations conf("/path/to/my-conf.conf");
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);
    // Now all the loggers will use configuration from file
}
```

 > Your configuration file can be converted to `el::Configurations` object (using constructor) that can be used where ever it is needed (like in above example).

 [![top] Goto Top](#table-of-contents)
 
#### Using el::Configurations Class
You can set configurations or reset configurations;
```c++
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, const char** argv) {
   el::Configurations defaultConf;
   defaultConf.setToDefault();
    // Values are always std::string
   defaultConf.set(el::Level::Info, 
            el::ConfigurationType::Format, "%datetime %level %msg");
    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);
    LOG(INFO) << "Log using default file";
    // To set GLOBAL configurations you may use
   defaultConf.setGlobally(
            el::ConfigurationType::Format, "%date %msg");
   el::Loggers::reconfigureLogger("default", defaultConf);
    return 0;
}
```

 > Configuration just needs to be set once. If you are happy with default configuration, you may use it as well.

 [![top] Goto Top](#table-of-contents)
 
#### Using In line Configurations
Inline configuration means you can set configurations in `std::string` but make sure you add all the new line characters etc. This is not recommended because it's always messy.
```c++
el::Configurations c;
c.setToDefault();
c.parseFromText("*GLOBAL:\n FORMAT = %level %msg");
```

 > Above code only sets Configurations object, you still need to re-configure logger/s using this configurations.

 [![top] Goto Top](#table-of-contents)
 
### Default Configurations
If you wish to have a configuration for existing and future loggers, you can use `el::Loggers::setDefaultConfigurations(el::Configurations& configurations, bool configureExistingLoggers = false)`. This is useful when you are working on fairly large scale, or using a third-party library that is already using Easylogging++. Any newly created logger will use default configurations. If you wish to configure existing loggers as well, you can set second argument to `true` (it defaults to `false`).

 [![top] Goto Top](#table-of-contents)
 
### Global Configurations
`Level::Global` is nothing to do with global configurations, it is concept where you can register configurations for all/or some loggers and even register new loggers using configuration file. Syntax of configuration file is:
```
-- LOGGER ID ## Case sensitive
  ## Everything else is same as configuration file


-- ANOTHER LOGGER ID
  ## Configuration for this logger
```

Logger ID starts with two dashes. Once you have written your global configuration file you can configure your all loggers (and register new ones) using single function;
```c++
int main(void) {
   // Registers new and configures it or
   // configures existing logger - everything in global.conf
   el::Loggers::configureFromGlobal("global.conf");
   // .. Your prog
   return 0;
}
```
Please note, it is not possible to register new logger using global configuration without defining its configuration. You must define at least single configuration. Other ways to register loggers are discussed in [Logging](#logging) section below.

 [![top] Goto Top](#table-of-contents)
 
### Logging Format Specifiers
You can customize format of logging using following specifiers:

|     Specifier   |                 Replaced By                                                                 |
|-----------------|---------------------------------------------------------------------------------------------|
| `%logger`       | Logger ID                                                                                   |
| `%thread`       | Thread ID - Uses std::thread if available, otherwise GetCurrentThreadId() on windows        |
| `%thread_name`  | Use `Helpers::setThreadName` to set name of current thread (where you run `setThreadName` from). See [Thread Names sample](/samples/STL/thread-names.cpp)|
| `%level`        | Severity level (Info, Debug, Error, Warning, Fatal, Verbose, Trace)                         |
| `%levshort`     | Severity level (Short version i.e, I for Info and respectively D, E, W, F, V, T)            |
| `%vlevel`       | Verbosity level (Applicable to verbose logging)                                             |
| `%datetime`     | Date and/or time - Pattern is customizable - see Date/Time Format Specifiers below          |
| `%user`         | User currently running application                                                          |
| `%host`         | Computer name application is running on                                                     |
| `%file`*         | File name of source file (Full path) - This feature is subject to availability of `__FILE__` macro of compiler                                                        |
| `%fbase`*        | File name of source file (Only base name)                                                   |
| `%line`*         | Source line number - This feature is subject to availability of `__LINE__` macro of compile |
| `%func`*         | Logging function                                                                            |
| `%loc`*          | Source filename and line number of logging (separated by colon)                             |
| `%msg`          | Actual log message                                                                          |
| `%`             | Escape character (e.g, %%level will write %level)                                           |

* Subject to compiler's availability of certain macros, e.g, `__LINE__`, `__FILE__` etc 

 [![top] Goto Top](#table-of-contents)
 
### Date/Time Format Specifiers
You can customize date/time format using following specifiers

|    Specifier    |                 Replaced By                                                                                      |
|-----------------|------------------------------------------------------------------------------------------------------------------|
| `%d`            | Day of month (zero-padded)                                                                                       |
| `%a`            | Day of the week - short (Mon, Tue, Wed, Thu, Fri, Sat, Sun)                                                      |
| `%A`            | Day of the week - long (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday)                          |
| `%M`            | Month (zero-padded)                                                                                              |
| `%b`            | Month - short (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec)                                       |
| `%B`            | Month - Long (January, February, March, April, May, June, July, August, September, October, November, December)  |
| `%y`            | Year - Two digit (13, 14 etc)                                                                                    |
| `%Y`            | Year - Four digit (2013, 2014 etc)                                                                               |
| `%h`            | Hour (12-hour format)                                                                                            |
| `%H`            | Hour (24-hour format)                                                                                            |
| `%m`            | Minute (zero-padded)                                                                                             |
| `%s`            | Second (zero-padded)                                                                                             |
| `%g`            | Subsecond part (precision is configured by ConfigurationType::SubsecondPrecision)                               |
| `%F`            | AM/PM designation                                                                                                |
| `%`             | Escape character                                                                                                 |

Please note, date/time is limited to `30` characters at most.

 [![top] Goto Top](#table-of-contents)

### Custom Format Specifiers

You can also specify your own format specifiers. In order to do that you can use `el::Helpers::installCustomFormatSpecifier`. A perfect example is `%ip_addr` for TCP server application;

```C++
const char* getIp(void) {
    return "192.168.1.1";
}

int main(void) {
    el::Helpers::installCustomFormatSpecifier(el::CustomFormatSpecifier("%ip_addr", getIp));
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level %ip_addr : %msg");
    LOG(INFO) << "This is request from client";
    return 0;
}
```

 [![top] Goto Top](#table-of-contents)
 
###Logging Flags
Form some parts of logging you can set logging flags; here are flags supported:

|     Flag                                               |                 Description                                                                                                                   |
|--------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------|
| `NewLineForContainer (1)`                              | Makes sure we have new line for each container log entry                                                                                      |
| `AllowVerboseIfModuleNotSpecified (2)`                 | Makes sure if -vmodule is used and does not specifies a module, then verbose logging is allowed via that module. Say param was -vmodule=main*=3 and a verbose log is being written from a file called something.cpp then if this flag is enabled, log will be written otherwise it will be disallowed. Note: having this defeats purpose of -vmodule                                 |
| `LogDetailedCrashReason (4)`                           | When handling crashes by default, detailed crash reason will be logged as well (Disabled by default) ([issue #90](https://github.com/muflihun/easyloggingpp/issues/90))                                                                                                                                                                                |
| `DisableApplicationAbortOnFatalLog (8)`                | Allows to disable application abortion when logged using FATAL level. Note that this does not apply to default crash handlers as application should be aborted after crash signal is handled. (Not added by default) ([issue #119](https://github.com/muflihun/easyloggingpp/issues/119))                                                                                                                                                                               |
| `ImmediateFlush (16)`                                  | Flushes log with every log-entry (performance sensative) - Disabled by default                                                                |
| `StrictLogFileSizeCheck (32)`                          | Makes sure log file size is checked with every log                                                                                            |
| `ColoredTerminalOutput (64)`                           | Terminal output will be colorful if supported by terminal.                                                                                            |
| `MultiLoggerSupport (128)`                             | Enables support for using multiple loggers to log single message. (E.g, `CLOG(INFO, "default", "network") << This will be logged using default and network loggers;`) |
| `DisablePerformanceTrackingCheckpointComparison (256)` | Disables checkpoint comparison |
| `DisableVModules (512)`                               | Disables usage of vmodules
| `DisableVModulesExtensions (1024)`                     | Disables vmodules extension. This means if you have a vmodule -vmodule=main*=4 it will cover everything starting with main, where as if you do not have this defined you will be covered for any file starting with main and ending with one of the following extensions; .h .c .cpp .cc .cxx .-inl-.h .hxx .hpp. Please note following vmodule is not correct -vmodule=main.=4 with this macro not defined because this will check for main..c, notice double dots. If you want this to be valid, have a look at logging flag above: AllowVerboseIfModuleNotSpecified '?' and '' wildcards are supported |
| `HierarchicalLogging (2048)`                          | Enables hierarchical logging. This is not applicable to verbose logging.|
| `CreateLoggerAutomatically (4096)`                          | Creates logger automatically when not available. |
| `AutoSpacing (8192)`                          | Automatically adds spaces. E.g, `LOG(INFO) << "DODGE" << "THIS!";` will output "DODGE THIS!"|
| `FixedTimeFormat (16384)`                          | Applicable to performace tracking only - this prevents formatting time. E.g, `1001 ms` will be logged as is, instead of formatting it as `1.01 sec`|

You can set/unset these flags by using static `el::Loggers::addFlag` and `el::Loggers::removeFlag`. You can check to see if certain flag is available by using `el::Loggers::hasFlag`, all these functions take strongly-typed enum `el::LoggingFlag`

 > You can set these flags by using `--logging-flags` command line arg. You need to enable this functionality by defining macro `ELPP_LOGGING_FLAGS_FROM_ARG` (You will need to make sure to use `START_EASYLOGGINGPP(argc, argv)` to configure arguments).

 > You can also set default (initial) flags using `ELPP_DEFAULT_LOGGING_FLAGS` and set numerical value for initial flags

 [![top] Goto Top](#table-of-contents)

### Application Arguments
Following table will explain all command line arguments that you may use to define certain behaviour; You will need to initialize application arguments by using `START_EASYLOGGINGPP(argc, argv)` in your `main(int, char**)` function.

|        Argument            |                                      Description                                        |
|----------------------------|-----------------------------------------------------------------------------------------|
| `-v`                       | Activates maximum verbosity                                                             |
| `--v=2`                    | Activates verbosity upto verbose level 2 (valid range: 0-9)                             |
| `--verbose`                | Activates maximum verbosity                                                             |
| `-vmodule=MODULE_NAME`     | Activates verbosity for files starting with main to level 1, the rest of the files depend on logging flag `AllowVerboseIfModuleNotSpecified` Please see Logging Flags section above. Two modules can be separated by comma. Please note vmodules are last in order of precedence of checking arguments for verbose logging, e.g, if we have -v in application arguments before vmodules, vmodules will be ignored.                                                                                                               |
| `--logging-flags=3`        | Sets logging flag. In example `i.e, 3`, it sets logging flag to `NewLineForContainer` and `AllowVerboseIfModuleNotSpecified`. See logging flags section above for further details and values. See macros section to disable this function.                                                                   |
| `--default-log-file=FILE`  |Sets default log file for existing and future loggers. You may want to consider defining `ELPP_NO_DEFAULT_LOG_FILE` to prevent creation of default empty log file during pre-processing. See macros section to disable this function.                                                                           |

 [![top] Goto Top](#table-of-contents)

### Configuration Macros
Some of logging options can be set by macros, this is a thoughtful decision, for example if we have `ELPP_THREAD_SAFE` defined, all the thread-safe functionalities are enabled otherwise disabled (making sure over-head of thread-safety goes with it). To make it easy to remember and prevent possible conflicts, all the macros start with `ELPP_`

NOTE: All the macros either need to be defined before `#include "easylogging++"` - but this gets hard and unreadable if project is getting bigger so we recommend you define all these macros using `-D` option of compiler, for example in case of `g++` you will do `g++ source.cpp ... -DELPP_SYSLOG -DELPP_THREAD_SAFE ...`

|   Macro Name                             |                 Description                                                                                                                        |
|------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------|
| `ELPP_DEBUG_ASSERT_FAILURE`             | Aborts application on first assertion failure. This assertion is due to invalid input e.g, invalid configuration file etc.                         |
| `ELPP_UNICODE`                          | Enables Unicode support when logging. Requires `START_EASYLOGGINGPP`                 |
| `ELPP_THREAD_SAFE`                      | Enables thread-safety - make sure -lpthread linking for linux.                                                                                     |
| `ELPP_FORCE_USE_STD_THREAD`             | Forces to use C++ standard library for threading (Only useful when using `ELPP_THREAD_SAFE`            |
| `ELPP_FEATURE_CRASH_LOG`              | Applicable to GCC only. Enables stacktrace on application crash                                                                                    |
| `ELPP_DISABLE_DEFAULT_CRASH_HANDLING`   | Disables default crash handling. You can use el::Helpers::setCrashHandler to use your own handler.                                                 |
| `ELPP_DISABLE_LOGS`                     | Disables all logs - (preprocessing)                                                                                                                |
| `ELPP_DISABLE_DEBUG_LOGS`               | Disables debug logs - (preprocessing)                                                                                                              |
| `ELPP_DISABLE_INFO_LOGS`                | Disables info logs - (preprocessing)                                                                                                               |
| `ELPP_DISABLE_WARNING_LOGS`             | Disables warning logs - (preprocessing)                                                                                                            |
| `ELPP_DISABLE_ERROR_LOGS`               | Disables error logs - (preprocessing)                                                                                                              |
| `ELPP_DISABLE_FATAL_LOGS`               | Disables fatal logs - (preprocessing)                                                                                                              |
| `ELPP_DISABLE_VERBOSE_LOGS`             | Disables verbose logs - (preprocessing)                                                                                                            |
| `ELPP_DISABLE_TRACE_LOGS`               | Disables trace logs - (preprocessing)                                                                                                              |
| `ELPP_FORCE_ENV_VAR_FROM_BASH`          | If environment variable could not be found, force using alternative bash command to find value, e.g, `whoami` for username. (DO NOT USE THIS MACRO WITH `LD_PRELOAD` FOR LIBRARIES THAT ARE ALREADY USING Easylogging++ OR YOU WILL END UP IN STACK OVERFLOW FOR PROCESSES (`popen`) (see [issue #87](https://github.com/muflihun/easyloggingpp/issues/87) for details))                                                                                                                                                                                       |
| `ELPP_DEFAULT_LOG_FILE`                 | Full filename where you want initial files to be created. You need to embed value of this macro with quotes, e.g, `-DELPP_DEFAULT_LOG_FILE='"logs/el.gtest.log"'` Note the double quotes inside single quotes, double quotes are the values for `const char*` and single quotes specifies value of macro                                                                                 |
| `ELPP_NO_LOG_TO_FILE`                 | Disable logging to file initially|
| `ELPP_NO_DEFAULT_LOG_FILE`              | If you dont want to initialize library with default log file, define this macro. But be sure to configure your logger with propery log filename or you will end up getting heaps of errors when trying to log to file (and `TO_FILE` is configured to `true`)                                                                                                              |
| `ELPP_FRESH_LOG_FILE`              | Never appends log file whenever log file is created (Use with care as it may cause some unexpected result for some users)                                                  |
| `ELPP_DEBUG_ERRORS`                    | If you wish to find out internal errors raised by Easylogging++ that can be because of configuration or something else, you can enable them by defining this macro. You will get your errors on standard output i.e, terminal or command prompt.                                                                                                                                             |
| `ELPP_DISABLE_CUSTOM_FORMAT_SPECIFIERS` | Forcefully disables custom format specifiers                                                                                                       |
| `ELPP_DISABLE_LOGGING_FLAGS_FROM_ARG`   | Forcefully disables ability to set logging flags using command-line arguments                                                                      |
| `ELPP_DISABLE_LOG_FILE_FROM_ARG`        | Forcefully disables ability to set default log file from command-line arguments                                                                    |
| `ELPP_WINSOCK2`        | On windows system force to use `winsock2.h` instead of `winsock.h` when `WIN32_LEAN_AND_MEAN` is defined                                                                    |
| `ELPP_CUSTOM_COUT` (advanced)     | Resolves to a value e.g, `#define ELPP_CUSTOM_COUT qDebug()` or `#define ELPP_CUSTOM_COUT std::cerr`. This will use the value for standard output (instead of using `std::cout`|
| `ELPP_CUSTOM_COUT_LINE` (advanced) | Used with `ELPP_CUSTOM_COUT` to define how to write a log line with custom cout. e.g, `#define ELPP_CUSTOM_COUT_LINE(msg) QString::fromStdString(msg).trimmed()` |
| `ELPP_NO_CHECK_MACROS`             | Do not define the *CHECK* macros                                                                                                                  |
| `ELPP_NO_DEBUG_MACROS`             | Do not define the *DEBUG* macros                                                                                                                  |

 [![top] Goto Top](#table-of-contents)
 
### Reading Configurations
If you wish to read configurations of certain logger, you can do so by using `typedConfigurations()` function in Logger class.
```c++
el::Logger* l = el::Loggers::getLogger("default");
bool enabled = l->typedConfigurations()->enabled(el::Level::Info);
// Or to read log format/pattern
std::string format = 
        l->typedConfigurations()->logFormat(el::Level::Info).format();
```

 [![top] Goto Top](#table-of-contents)
 
# Logging
Logging in easylogging++ is done using collection of macros. This is to make it easier for user and to prevent them knowing about unnecessary greater details of how things are done.

### Basic
You are provided with two basic macros that you can use in order to write logs:
* `LOG(LEVEL)`
* `CLOG(LEVEL, logger ID)`

`LOG` uses 'default' logger while in CLOG (Custom LOG) you specify the logger ID. For LEVELs please refer to Configurations - Levels section above. Different loggers might have different configurations depending on your need, you may as well write custom macro to access custom logger. You also have different macros for verbose logging that is explained in section below.
Here is very simple example of using these macros after you have initialized easylogging++.
```c++
LOG(INFO) << "This is info log";
CLOG(ERROR, "performance") << "This is info log using performance logger";
```

There is another way to use same macro i.e, `LOG` (and associated macros). This is that you define macro `ELPP_DEFAULT_LOGGER` and `ELPP_CURR_FILE_PERFORMANCE_LOGGER_ID` with logger ID that is already registered, and now when you use `LOG` macro, it automatically will use specified logger instead of `default` logger. Please note that this should be defined in source file instead of header file. This is so that when we include header we dont accidently use invalid logger.

A quick example is here
```c++
#ifndef ELPP_DEFAULT_LOGGER
#   define ELPP_DEFAULT_LOGGER "update_manager"
#endif
#ifndef ELPP_CURR_FILE_PERFORMANCE_LOGGER_ID
#   define ELPP_CURR_FILE_PERFORMANCE_LOGGER_ID ELPP_DEFAULT_LOGGER
#endif
#include "easylogging++.h"
UpdateManager::UpdateManager {
    _TRACE; // Logs using LOG(TRACE) provided logger is already registered - i.e, update_manager
    LOG(INFO) << "This will log using update_manager logger as well";
}
```

```c++
#include "easylogging++.h"
UpdateManager::UpdateManager {
    _TRACE; // Logs using LOG(TRACE) using default logger because no `ELPP_DEFAULT_LOGGER` is defined unless you have it in makefile
}
```

 > You can also write logs by using `Logger` class directly. This feature is available on compilers that support variadic templates. You can explore more by looking at `samples/STL/logger-log-functions.cpp`.

 [![top] Goto Top](#table-of-contents)
 
### Conditional Logging
Easylogging++ provides certain aspects of logging, one these aspects is conditional logging, i.e, log will be written only if certain condition fulfils. This comes very handy in some situations. 
Helper macros end with _IF;
* `LOG_IF(condition, LEVEL)`
* `CLOG_IF(condition, LEVEL, logger ID)`


#### Some examples:
```c++
LOG_IF(condition, INFO) << "Logged if condition is true";

LOG_IF(false, WARNING) << "Never logged";
CLOG_IF(true, INFO, "performance") << "Always logged (performance logger)"
```

Same macros are available for verbose logging with `V` in the beginning, i.e, `VLOG_IF` and `CVLOG_IF`. see verbose logging section below for further information. You may have as complicated conditions as you want depending on your need.

 [![top] Goto Top](#table-of-contents)
 
### Occasional Logging
Occasional logging is another useful aspect of logging with Easylogging++. This means a log will be written if it's hit certain times or part of certain times, e.g, every 10th hit or 100th hit or 2nd hit.
Helper macros end with `_EVERY_N`;
* `LOG_EVERY_N(n, LEVEL)`
* `CLOG_EVERY_N(n, LEVEL, logger ID)`

#### Other Hit Counts Based Logging
There are some other ways of logging as well based on hit counts. These useful macros are
* `LOG_AFTER_N(n, LEVEL)`; Only logs when we have reached hit counts of `n`
* `LOG_N_TIMES(n, LEVEL)`; Logs n times

#### Some examples:
```c++
for (int i = 1; i <= 10; ++i) {
   LOG_EVERY_N(2, INFO) << "Logged every second iter";
}
// 5 logs written; 2, 4, 6, 7, 10

for (int i = 1; i <= 10; ++i) {
   LOG_AFTER_N(2, INFO) << "Log after 2 hits; " << i;
}
// 8 logs written; 3, 4, 5, 6, 7, 8, 9, 10

for (int i = 1; i <= 100; ++i) {
   LOG_N_TIMES(3, INFO) << "Log only 3 times; " << i;
}
// 3 logs writter; 1, 2, 3
```

 > Same versions of macros are available for `DEBUG` only mode, these macros start with `D` (for debug) followed by the same name. e.g, `DLOG` to log only in debug mode (i.e, when `_DEBUG` is defined or `NDEBUG` is undefined)

 [![top] Goto Top](#table-of-contents)
 
### `printf` Like Logging
For compilers that support C++11's variadic templates, ability to log like "printf" is available. This is done by using `Logger` class. This feature is thread and type safe (as we do not use any macros like `LOG(INFO)` etc)

This is done in two steps:
 1. Pulling registered logger using `el::Loggers::getLogger(<logger_id>);`
 2. Using one of logging functions
 
The only difference from `printf` is that logging using these functions require `%v` for each arg (This is for type-safety); instead of custom format specifiers. You can escape this by `%%v`

Following are various function signatures:
 * `info(const char*, const T&, const Args&...)`
 * `
