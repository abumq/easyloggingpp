EasyLogging++
-------------

Single header based, extremely light-weight high performance logging library for C++ applications

EasyLogging++ is C++ logging library that is based on single header file. It is extremely light-weight, robust, fast performing, thread and type safe and consists of many built-in features. It provides ability to write logs in your own customized format. It also provide support for logging your classes, third-party libraries, STL and third-party containers etc.

**Please note: This read me is specific to v8.0+. For older versions please refer to [old read me](https://github.com/mkhan3189/EasyLoggingPP/blob/0f70c01323c408a8bbe187fa283334d01f90f94d/README.md) - [Download v7.68](http://icplusplus.com/tools/easylogging/releases/easyloggingpp_v7.68.zip)**

<pre>
<a href="#why-easylogging">Why EasyLogging++</a><br/>
<a href="#getting-started">Getting Started</a><br/>
<a href="#configuring">Configuring</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#configuration-file">Configuration File</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#inline-configurations">Inline Configurations</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#directly-using-easyloggingppconfigurations-class">Directly Using Class</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#configurations">Configurations</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#enable--disable-logs">Enable / Disable Logs</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#log-to-file">Log To File</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#log-to-standard-output">Log To Standard Output</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#log-filename">Log Filename</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#milliseconds-width">Milliseconds Width</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#performance-tracking">Performance Tracking</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#rolling-log-files">Rolling Log Files</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#logging-pattern">Logging Pattern</a>
<a href="#logging">Logging</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#writing-logs">Writing Logs</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#helper-functions">Helper Functions</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#registering-and-getting-existing-logger">Registering and getting existing logger</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#checking-loggers-configuration">Checking logger's configuration</a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#setting-application-arguments">Setting application arguments</a>
<a href="#features">Features</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#conditional-logging">Conditional Logging</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#interval-logging">Interval Logging</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#cleaning-logs-on-each-run">Cleaning Logs On Each Run</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#performance-tracking-1">Performance Tracking</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#verbose-logging">Verbose Logging<a/>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#quality-assurance-logging">Quality Assurance Logging</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#escaping-log-format">Escape Log Format</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#thread-safety">Thread Safety</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#c-libraries-logging">C++ Libraries Logging</a>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="#extending-the-library---logging-your-own-class">Extending the Library - Logging Your Own Class</a>
<a href="#important-macros">Important Macros</a>
<a href="#compatibility">Compatibility</a>
<a href="#tips-for-performance-improvement">Tips For Performance Improvement</a><br/>
</pre>

### Why EasyLogging++
 * Open source and 100% Free
 * Native C++ support (from C++98 to latest C++ standard)
 * Highly portable including most C++ compilers and Windows, most/all flavours of UNIX including Linux and Mac OS
 * Highly configurable
 * [Extremely easy to use](https://github.com/mkhan3189/EasyLoggingPP/tree/master/samples)
 * [Actively developed and maintained](https://github.com/mkhan3189/EasyLoggingPP/commits/master)
 * [Many additional features](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#features)
 * [Thread safe](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#thread-safety)
 * Type safe
 * Supports hierarchical logging
 * [Performance tracking](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#performance-tracking)
 * STL, Qt and extendable logging (Your own class' logging)

... and  list goes on! It is complete library wrapped into single header file that you can use in any C++ application.
<pre><a href="#easylogging">Goto Top</a></pre>
### Getting Started

You can get started with EasyLogging++ in three steps;
 * [Download](http://icplusplus.com/tools/easylogging/easyloggingpp.zip)
 * Include and initialize
 * Off you go

```C++
#include "easylogging++.h"
// ** FOLLOWING LINE SHOULD BE USED ONCE AND ONLY ONCE IN WHOLE APPLICATION **
// ** THE BEST PLACE TO PUT THIS LINE IS IN main.cpp RIGHT AFTER INCLUDING easylogging++.h **
_INITIALIZE_EASYLOGGINGPP
```
<pre><a href="#easylogging">Goto Top</a></pre>
### Configuring

When you start logging using default configurations, logs get written in your applications' executable path in windows (logs/myeasylog.log). For unix applications logs are in `/tmp/logs/myeasylog.log`. It is highly recommended to set it upfront via `easyloggingpp::Loggers::setFilename(filename)` to avoid any confusions.

You can configure your logger(s) in three different ways. You may choose whats best for you:

 * Configuration file
 * Inline configurations (from string)
 * Directly using `easyloggingpp::Configurations` class

#### Configuration file

Configuration can be imported using configuration files that have following format:

```
// Comment
* LEVEL:
   CONFIGURATION_NAME  =  CONFIGURATION_VALUE
```
Always start your configuration file by starting with `ALL` level. This sets configurations for all other levels and if you do not set any other level after wards, configurations from all is used. On the other hand if you set `ALL` at the end, all the configurations are overridden for other levels. This is because EasyLogging++ parses configuration file line by line.

```C++
* ALL: // We need to start level with star "*" and end with colon ":"
    FORMAT					=	"%level: %log"  // Quotes are not necessary but to make it more readable we wrap quotes around.
    FILENAME				= 	"logs/testLog.log"
    ENABLED					=	true
    TO_FILE					=	true
    TO_STANDARD_OUTPUT		=	false
    MILLISECONDS_WIDTH		=	3
    PERFORMANCE_TRACKING	=	false

// Following configuration only defines FORMAT for INFO, rest of the configurations are used from ALL configurations above
* INFO:
     FORMAT			=	"%datetime %level %log"
```
```C++
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, const char** argv) {
    easyloggingpp::Configurations confFromFile("myconfiguration_file");  // Load configuration from file
    easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile); // Re-configures all the loggers to current configuration file
    easyloggingpp::Configurations defaultConf;
    defaultConf.setToDefault();
    easyloggingpp::Loggers::reconfigureLogger("business", defaultConf); // Business logger uses default configurations
    LINFO << "Log using conf from file";  // Log message:  INFO: Log using conf from file
    BINFO << "Log using default file";    // Log message:  01/01/2013 00:00:00.551 INFO Log using default file

    return 0;
}
```
#### Inline configurations

Inline configuration means you can set configurations in `std::string`

```C++
    easyloggingpp::Configurations c;
    c.setToDefault();
    c.parseFromText("*ALL:\nFORMAT = %level");
```
And reconfigure your logger. Remember, configurations are parsed line-by-line so please make sure you add `\n` at the end of each line.

#### Directly using `easyloggingpp::Configurations` class

You can set configurations or reset configurations;

```C++
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, const char** argv) {
    easyloggingpp::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(easyloggingpp::Level::ELPP_INFO, easyloggingpp::ConfigurationType::ELPP_Format, "%datetime %level %log"); // Values are always std::string
    easyloggingpp::Loggers::reConfigureLogger("business", defaultConf); // Business logger uses default configurations
    BINFO << "Log using default file";    // Log message:  01/01/2013 00:00:00.551 INFO Log using default file
    // To set ALL configuraions you may use
    defaultConf.setAll(easyloggingpp::ConfigurationType::ELPP_Format, "%datetime %level %log");
    easyloggingpp::Loggers::reConfigureLogger("business", defaultConf); // Business logger uses default configurations
    return 0;
}
```

Configuration just needs to be set once. If you are happy with default configuration, you may use it as well.

#### Configurations

###### Enable / Disable Logs

To disable logs you may either set `easyloggingpp::ConfigurationType::ELPP_Enabled` to `true` or `false`. Alternatively, you may define one of following macros;
```
* _DISABLE_LOGS  (Disables all logs)
* _DISABLE_DEBUG_LOGS
* _DISABLE_INFO_LOGS (also disables performance tracking)
* _DISABLE_WARNING_LOGS
* _DISABLE_ERROR_LOGS
* _DISABLE_FATAL_LOGS
* _DISABLE_TRACE_LOGS
* _DISABLE_VERBOSE_LOGS
```

###### Log To File

Determines whether or not logs need to be written to log file. Configuration type: `ELPP_ToFile`

###### Log To Standard Output

Determines whether or not logs need to be written to standard output (terminal, command prompt etc). Configuration type: `ELPP_ToStandardOutput`

###### Log Filename

Determines where to write logs (if ToFile enabled). Configuration type: `ELPP_Filename`

###### Milliseconds Width

Determines the length of milliseconds (valid range: 3 - 6, default: 3) - only applicable for unix based. Configuration type: `ELPP_MillisecondsWidth`

###### Performance tracking

Determines whether or not performance tracking is enabled. This effects performanceLogger. Configuration type: `ELPP_PerformanceTracking`

###### Rolling Log Files

Besides `_ALWAYS_CLEAN_LOGS`, you can use configurations to roll out log files. You can set `ELPP_RollOutSize` to file size after which you wish log file to reset. Since this is part of configurations, it needs log reconfiguration. This happens with everytime you start your application. But if you wish for EasyLogging++ to roll out as application is running, you can do so by defining `_ELPP_STRICT_ROLLOUT`. This checks for rollout with every log you write. Remember, defining this macro is not recommended if you are concerned with performance. You 
can define this in dev and QA environments though.

```C++
easyloggingpp::Configurations c; // Initialize clean configurations
c.setAll(easyloggingpp::ConfigurationType::ELPP_RollOutSize, "2048"); // Roll out log files every 2KB
easyloggingpp::Loggers::reconfigureAllLoggers (c); // Re configure all loggers
```

*Note 1: Rollout size can hold values up to `unsigned long`*

**Note 2: This feature is currently in beta-mode so use it at your own risk**

Version: 8.15+

#### Logging Pattern

You can customize format of logging. Following format specifiers are currently supported by EasyLogging++

<table>
    <tr>
        <td><b>Format Specifier</b></td>
        <td><b>Description</b></td>
    </tr>
    <tr>
        <td>%logger</td>
        <td>Logger identifier</td>
    </tr>
    <tr>
        <td>%level</td>
        <td>Severity level (Info, Warning, Error, Debug etc.)</td>
    </tr>
    <tr>
        <td>%vlevel</td>
        <td>Verbocity level (Only applicable to verbose logs)</td>
    </tr>
    <tr>
        <td>%datetime</td>
        <td>Date/time</td>
    </tr>
    <tr>
        <td>%date</td>
        <td>Date only</td>
    </tr>
    <tr>
        <td>%time</td>
        <td>Time only</td>
    </tr>
    <tr>
        <td>%user</td>
        <td>Username currently running application</td>
    </tr>
    <tr>
        <td>%host</td>
        <td>Computer name that application is running on.</td>
    </tr>
    <tr>
        <td>%func</td>
        <td>Function where log was written from</td>
    </tr>
    <tr>
        <td>%loc</td>
        <td>Location with filename and line number where log was written from</td>
    </tr>
    <tr>
        <td>%log</td>
        <td>Log message</td>
    </tr>
    <tr>
        <td>\t</td>
        <td>Tab</td>
    </tr>
</table>

<pre><a href="#easylogging">Goto Top</a></pre>
### Logging

EasyLogging++ comes with following severity levels of logging with complete control over each of the following:
```
  * INFO
  * DEBUG
  * WARNING
  * ERROR
  * FATAL
  * QA
  * TRACE
  * VERBOSE
```

You can write logs either by using one of default loggers or define your custom one. 


#### Writing Logs

In order to start writing logs you will need to first initialize easylogging++ using:

```C++
#include "easylogging++.h"
// ** FOLLOWING LINE SHOULD BE USED ONCE AND ONLY ONCE IN WHOLE APPLICATION **
// ** THE BEST PLACE TO PUT THIS LINE IS IN main.cpp RIGHT AFTER INCLUDING easylogging++.h **
_INITIALIZE_EASYLOGGINGPP
```
You can start writing logs by simply using one of the following macros:

######Trivial Logger
`LINFO`, `LDEBUG`, `LWARNING`, `LERROR`, `LFATAL`, `LQA`, `LTRACE`, `LVERBOSE`
######Business Logger
`BINFO`, `BDEBUG`, `BWARNING`, `BERROR`, `BFATAL`, `BQA`, `BTRACE`, `BVERBOSE`
######Security Logger
`SINFO`, `SDEBUG`, `SWARNING`, `SERROR`, `SFATAL`, `SQA`, `STRACE`, `SVERBOSE`
######Performance Logger
`PINFO`, `PDEBUG`, `PWARNING`, `PERROR`, `PFATAL`, `PQA`, `PTRACE`, `PVERBOSE`

*All loggers (including newly registered) support all the aspects of logging, e.g, `SINFO_IF(condition) << "log if condition is true"` or `BWARNING_EVERY_N(2) << "Warning every 2nd time this line is hit"` or `CINFO_IF("mylogger") << "Log custom logger if condition is true"` etc.*


##### Helper Functions

###### Registering and getting existing logger

Normally you would not need to inject new loggers and you may use one of four existing ones but if you want to have a fully customized logger (that could be the case when you are writing a library or third-party support) you may as well do it;

`easyloggingpp` has two useful classes, `Logger` and `Loggers`. `Logger` is single entity of a logger. Where as `Loggers` is a static class that provides helper functions to get and manipulate loggers. Loggers in EasyLogging++ are identified by IDs that are unique To register a logger just call `easyloggingpp::Loggers::getLogger(identifier)`. This returns pointer of `easyloggingpp::Logger`. If logger already exist in "logger container", another logger will not be registered instead it will just get existing logger. You normally would not need to use `getLogger` to write a log, but to reconfigure a logger you might want to use it. To write log using one of newly registered loggers, use custom logger macro e.g,

```C++
CINFO("mylogger") << "This is log from my custom log";
```

Of course you may define custom macro to make it easy if you like.

If you wish to check list of registered loggers, you may do it by using `easyloggingpp::Loggers::getAllLogIdentifiers(std::vector<std::string>& listOfIds);` where listOfIds is the list to fill up with logger identifiers. You normally would not need to get a registered logger because all the functionalities that you can do from a logger's pointer, you can do it directly from `Loggers` class. If there is anything you can't do, there would be a reason for that; which is mostly security.

###### Checking logger's configuration

You can use `Loggers::ConfigurationsReader` to check certain configuration for a logger. This is a static class that contains functions that take logger identifier and level you want to check. Levels are the ones defined in `easyloggingpp::Level` class which is a static struct containing enum.

###### Setting application arguments

For some loggers e.g, verbose logging, EasyLogging++ requires to check application arguments. You can set this either by `_START_EASYLOGGINGPP(argc, argv)` macro or by using `easyloggingpp::Loggers::setApplicationArguments(argc, argv)`.
<pre><a href="#easylogging">Goto Top</a></pre>
### Features

#### Conditional Logging
You can use conditional logging for logs that can have simple / complex conditions. These logs are disabled / enabled with their respective logging level.

```C++
 // Using trivial logger
* LDEBUG_IF(condition) << log
* LINFO_IF(condition) << log
* LWARNING_IF(condition) << log
* LERROR_IF(condition) << log
* LFATAL_IF(condition) << log
* LQA_IF(condition) log
* LTRACE_IF(condition) log
* LVERBOSE_IF(condition, verbose-level) << log
 // Using business logger
* BDEBUG_IF(condition) << log
* BINFO_IF(condition) << log
* BWARNING_IF(condition) << log
* BERROR_IF(condition) << log
* BFATAL_IF(condition) << log
* BQA_IF(condition) log
* BTRACE_IF(condition) log
* BVERBOSE_IF(condition, verbose-level) << log
 // Using security logger
* SDEBUG_IF(condition) << log
* SINFO_IF(condition) << log
* SWARNING_IF(condition) << log
* SERROR_IF(condition) << log
* SFATAL_IF(condition) << log
* SQA_IF(condition) log
* STRACE_IF(condition) log
* SVERBOSE_IF(condition, verbose-level) << log
 // Using performance logger
* PDEBUG_IF(condition) << log
* PINFO_IF(condition) << log
* PWARNING_IF(condition) << log
* PERROR_IF(condition) << log
* PFATAL_IF(condition) << log
* PQA_IF(condition) log
* PTRACE_IF(condition) log
* PVERBOSE_IF(condition, verbose-level) << log
```
A typical example is as follow (taken from samples/STL/conditional.cpp)
```C++
  LINFO_IF(1 == 1) << "1 is equal to 1";
  // Or some complex condition
  LDEBUG_IF((1 == 2) || (5 == 5)) << "Something is right so I will print!";
  // verbose log
  LVERBOSE_IF(true, 1) <<  "Printing verbose level-1";
```
 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/conditional.cpp)

#### Interval Logging 
You can log something every N times using `xxx_EVERY_N` where `xxx` represent different log levels. Following are the usable macros:
```C++
 // Using trivial logger
* LDEBUG_EVERY_N(n) << log
* LINFO_EVERY_N(n) << log
* LWARNING_EVERY_N(n) << log
* LERROR_EVERY_N(n) << log
* LFATAL_EVERY_N(n) << log
* LVERBOSE_EVERY_N(n, level) << log
* LQA_EVERY_N(n) << log
 // Using business logger
* BDEBUG_EVERY_N(n) << log
* BINFO_EVERY_N(n) << log
* BWARNING_EVERY_N(n) << log
* BERROR_EVERY_N(n) << log
* BFATAL_EVERY_N(n) << log
* BQA_EVERY_N(n) << log
* BTRACE_EVERY_N(n) << log
* BVERBOSE_EVERY_N(n, verbose-level) << log
 // Using security logger
* SDEBUG_EVERY_N(n) << log
* SINFO_EVERY_N(n) << log
* SWARNING_EVERY_N(n) << log
* SERROR_EVERY_N(n) << log
* SFATAL_EVERY_N(n) << log
* SQA_EVERY_N(n) << log
* STRACE_EVERY_N(n) << log
* SVERBOSE_EVERY_N(n, verbose-level) << log
 // Using performance logger
* PDEBUG_EVERY_N(n) << log
* PINFO_EVERY_N(n) << log
* PWARNING_EVERY_N(n) << log
* PERROR_EVERY_N(n) << log
* PFATAL_EVERY_N(n) << log
* PQA_EVERY_N(n) << log
* PTRACE_EVERY_N(n) << log
* PVERBOSE_EVERY_N(n, verbose-level) << log
```

A typical example:
```C++
for (int i = 1; i <= 100; ++i) {
  LINFO_EVERY_N(5) << "This will be logged every 5th iteration";
}
```

At any time if you wish to check the counter position for a line, you may do it using `_ELPP_COUNTER_POSITION` that gets position for any interval log registered for the line. This is a macro that expands to finding the position. *Please note that counters do get reset at some point, as per current release, limit is set to `100,000` iterations. It used to be 5000 before v7.27.*

 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/interval.cpp)

#### Cleaning Logs On Each Run
If you wish to clean log each time you run your C++ application, you can do this by defining macro `_ALWAYS_CLEAN_LOGS`. This is useful when you are doing regression testing on your application and always want to start with clean logs. It is also useful where keeping older logs are not necessary for example a session of game you wrote in C++ or a small utility software. See [issue #11](https://github.com/mkhan3189/EasyLoggingPP/issues/11) for further details on initial request.

As an example, you may compile your application as following if you wish to clean logs every time you execute application;
```
g++ main.cpp -o main-exec -D_ALWAYS_CLEAN_LOGS
```
#### Performance Tracking 
 ```C++
 #include "easylogging++.h"
 _INITIALIZE_EASYLOGGINGPP
 SUB(print,(const std::string& input))
   /* sub-routine body */
   std::cout << input;
 END_SUB 
 
 FUNC(int,sum,(int x,int y))
   /* function body */
   RETURN(x+y);
 END_FUNC(0)
 
int main(void) {
    print("this is test");
    int sumResult = sum(1,2);
    LINFO << "Sum of 1 and 2 is " << sumResult;
}
 ```
 ```
 this is test
performance [INFO] Executed [void print(string)] in [0 ms]
performance [INFO] Executed [int sum(int, int)] in [0 ms]
Sum of 1 and 2 is 3
 ```
Above output is from compiler that supports `PRETTY_FUNCTION` like GNU C >= 2. Visual C++ will output just the function name i.e, `print` and `sum` in this case.

###### Some Notes on Performance Logging
* Make sure you have braces around `RETURN`

```C++
   if (condition) {
      RETURN(0);
   }
```
* To exit a subroutine, do not call `return;` instead, use `RETURN()`

```C++
  if (condition) {
     RETURN();
  }
```
* Use normal definition syntax for other types of functions

```C++
inline FUNC(int,sqrt,(int numb))
   ...
END_FUNC(return_value)

template <typename T>
static FUNC(T,sum,(T a,T b))
   ...
END_FUNC(return_value)
```

Note: You can specify the severity level and log type (recommended is `PerformanceLogger`) by setting `_PERFORMANCE_TRACKING_SEVERITY` in `easylogging++.h` to one of the reusable macros i.e, `PINFO`, `PDEBUG` etc.

To disable performance tracking at any time set `_ENABLE_PERFORMANCE_TRACKING` to `0`, otherwise `1`. Alternatively, define macro `_DISABLE_PERFORMANCE_TRACKING`.
 
#### Verbose Logging
To start using verbose logging you will need to have following right after your `int main(int, char**)` function `_START_EASYLOGGINGPP(argc, argv);`, so your main function will look something like
```C++
int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);
  ...
}
```

And when using verbose logging you will need to run your C++ application with argument `--v=` followed by verbose level.
When you want to write verbose log, you will use, `LVERBOSE(level) << log`

As an example

```C++
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv); // Alternatively you may do easyloggingpp::Loggers::setApplicationArguments(argc, argv);
  bool condition = true;
  LVERBOSE(1) << "I will be printed when this application is run using --v=1 or higher than 1 arguments";
  LVERBOSE(2) << "I will be printed when this application is run using --v=2 arguments";
  LVERBOSE_IF(condition, 1) << "I will be printed when condition is true as well as application is run using --v=1 or higher than 1 arguments";
}
```
Now compile your application normally:

`g++ main.cpp -o main-exec`

now run your application:

`./main-exec --v=1`

This will print:
```
I will be printed when this application is run using --v=1 or higher than 1 arguments
I will be printed when condition is true as well as application is run using --v=1 or higher than 1 arguments
```
and if you run application using following parameter;
`./main-exec --v=2`, all of the verbose logs will be printed.

You can disable verbose logs by many ways,
 * Do not run application using `--v` argument
 * Define `_DISABLE_VERBOSE_LOGS` i.e, `g++ main.cpp -o main-exec -D _DISABLE_VERBOSE_LOGS`

Just like other logs, you may choose the final location of verbose logs, i.e, file or standard output.

Also, log format for verbose logs have special format specifier, `%vlevel` that is placeholder for verbose logging level.

You may also run using `--verbose` to display maximum verbose logs (max level: 9)
 
 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/verbose.cpp)

#### Quality Assurance Logging
Quality assurance (QA) logs are supported by EasyLogging++ for application that are deployed in QA environments for testing purposes. These logs can provide extra information when working in QA and can be disabled in production without having to change the source code.

By default QA logs will not take affect and will only be logged if `_QUALITY_ASSURANCE` is defined, as an example, following program:
```C++
#include "easylogging++.h"
int main(void) {
  LQA << "I am log only for QA environment";
  return 0;
}
```
will log `QA` if program is compiled using following line at minimum (notice the `_QUALITY_ASSURANCE` macro):

`g++ main.cpp -o main-exec -D_QUALITY_ASSURANCE`

#### Escaping Log Format
Escape character used in EasyLogging++ is `E`. For example, to write following log
```
%level [DEBUG] [13/01/2013 17:21:09.571] Log message
```
Debug log format should look like:
`E%level [%level] [%datetime] %log`

#### Thread Safety
Make sure you compile application right and use '-pthread` where needed. Sample has very well explained comment on each of above way of loggings.

*If you wish to force to disable multi-threading support for EasyLogging++ please define macro `_DISABLE_MUTEX`*

 [View Sample 1 (std::thread)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/std_thread.cpp)

 [View Sample 2 (pthread)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/pthread.cpp)
 
 [View Sample 3 (QThread)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/Qt/basic/)

 [View Sample 4 (Visual C++)](https://github.com/mkhan3189/EasyLoggingPP/tree/master/samples/VC%2B%2B/VCPP2012_Win32_Multithreaded/)

#### C++ Libraries Logging
Currently EasyLogging++ support following libraries and classes/templates;

 * STL
    - Enable by defining `_ELPP_STL_LOGGING`
    - Basic types supported: `string`, `wstring` (Always enabled)
    - Containers supported: `vector`, `list`, `deque`, `set`, `multiset`, `bitset`, `pair`, `map`, `multimap`, `queue`, `priority_queue`, `stack`
 * Qt
    - Enable by defining `_ELPP_QT_LOGGING`
    - Basic types supported: `QString`, `QChar`, `QBool`, `qint64`, `quint64`, `QStringRef`, `QLatin1String`
    - Containers supported: `QVector`, `QList`, `QMap`, `QMultiMap`, `QQueue`, `QPair`, `QSet`, `QHash`, `QMultiHash`, `QLinkedList`, `QStack`

*You should enable logging in order to use it with EasyLogging++ by defining one (or more) of above mentioned macros during compilation or before including `easylogging++.h` file*

[View Sample 1 (STL)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/containers.cpp)

[View Sample 2 (Qt)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/Qt/basic/main.cpp)

#### Extending the Library - Logging Your Own Class
There will be times when you would want to log your own class, just define left shift operator that returns `std::ostream&` in your class. If you can use `std::cout` to log your class to standard output, you should be able to do it flawlessly with EasyLogging++

Example:
```C++
#include "easylogging++.h"
_INITIALIZE_EASYLOGGINGPP

class MyClass {
    public:
        MyClass(const std::string& name_) : name_(name_) {}

        std::string name(void) const {
            return name_;
        }
        void setName(const std::string& name_) {
            this->name_ = name_;
        }

        friend std::ostream& operator<<(std::ostream& stream_, const MyClass& myClass);
    private:
        std::string name_;
};

std::ostream& operator<<(std::ostream& stream_, const MyClass& myClass) {
    stream_ << "MyClass name is " << myClass.name();
    return stream_;
}

int main(void) {
    MyClass myClass("Awesome class");
    LINFO << myClass;

    return 0;
}
```

Will log out something like:

`14:32:47.031 INFO  MyClass name is Awesome class`

Of course, above output varies with your log format configurations. The one above is result of `%time %level %log`

<pre><a href="#easylogging">Goto Top</a></pre>

### Important Macros
Apart from already mentioned macros there are few that have not been mentioned yet. You may define these macros at time of compilation or before including header into your application, (of course at time of compilation is best to make sure that macro has affect). This is to change behaviour of easylogging++ as described below.

<table>
    <tr>
        <td><b>Macro</b></td>
        <td><b>Description</b></td>
    </tr>
    <tr>
        <td>_DISABLE_ELPP_ASSERT</td>
        <td>Disables internal assertion. This calls std::cerr</td>
    </tr>
    <tr>
        <td>_STOP_ON_FIRST_ELPP_ASSERTION</td>
        <td>Exits program on first internal assertion</td>
    </tr>
    <tr>
        <td>_DISABLE_MUTEX</td>
        <td>Not recommended but you may disable mutual exclusion for single threaded applications by defining this.</td>
    </tr>
    <tr>
        <td>_ELPP_INTERNAL_INFO</td>
        <td>Display internal information for EasyLogging++. Information like `cleaning log file` etc</td>
    </tr>
</table>

### Compatibility
EasyLogging++ has been tested on following platforms (OS and compilers)

**Operating Systems**

![win8] Windows 8 (64-bit, Visual C++ 8.0, 9.0, 11.0)

![win7] Windows 7 (64-bit, Visual C++ 8.0, 9.0, 11.0)

![mac] Mac OSX (clang 3.1/Apple Clang Version 4.1 (LLVM 3.1))

![ubuntu] Ubuntu 12.04 / 12.10 (32-bit, 64-bit, g++ 4.6.3)

![scientificlinux] Scientific Linux 6.2 (64-bit, g++ 4.4)

![linuxmint] Linux Mint 14 (64-bit, g++ 4.7.2)

![android] Android 2.2+ (NDK)

**Compilers**

![gcc] GNU Compiler Collection (g++) (4.2, 4.4, 4.6.3, 4.7.2)

![vcpp] Visual C++ (8.0, 9.0, 11.0)

![llvm] LLVM (3.1, 3.2)

*EasyLogging++ is expected to be compatible with other linux distros and other compilers, but not listed here because it is not verified. Please feel free to contribute if you successfully compile it on any platform.*
<pre><a href="#easylogging">Goto Top</a></pre>
#### Tips For Performance Improvement
EasyLogging++ has been tested several times a day for performances glitches. That being said, you can still improve performance in a lot of other ways that are following;

* When you deploy your application for release and you are certain that you do not need to log standard output (terminal or command prompt), set `TO_STANDARD_OUTPUT` to false in configurations
* Try to avoid complicated `ostream& operator<<` in your custom classes, as this gets called when you log a C++ class
* If your application is not multi-threaded, define `_DISABLE_MUTEX` to prevent overhead of multi-threading features, make sure you do not do this if you are writing library (in binary) because this can potentially affect application using your library.

<pre><a href="#easylogging">Goto Top</a></pre>
[ubuntu]: http://www.icplusplus.com/tools/easylogging/icons/ubuntu.png
[linuxmint]: http://www.icplusplus.com/tools/easylogging/icons/linux-mint.png
[scientificlinux]: http://www.icplusplus.com/tools/easylogging/icons/scientific-linux.png
[mac]: http://www.icplusplus.com/tools/easylogging/icons/mac-osx.png
[win7]: http://www.icplusplus.com/tools/easylogging/icons/windows7.png
[win8]: http://www.icplusplus.com/tools/easylogging/icons/windows8.png
[qt]: http://www.icplusplus.com/tools/easylogging/icons/qt.png
[gcc]: http://www.icplusplus.com/tools/easylogging/icons/gcc.png
[vcpp]: http://www.icplusplus.com/tools/easylogging/icons/vcpp.png
[android]: http://www.icplusplus.com/tools/easylogging/icons/android.png
[llvm]: http://www.icplusplus.com/tools/easylogging/icons/llvm.png
