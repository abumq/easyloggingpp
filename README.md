EasyLogging++
-------------

Extremely light-weight cross platform logging library for C++ applications

EasyLogging++ is extremely light-weight, easy-to-import, thread and type safe C++ logging library that is based on **single header file** for easy portability. It provides support for writing logs in your customized format, ability to log your own classes, multiple logging aspects including conditional, interval and verbose logging. It also provide support for logging third-party libraries, STL and third-party containers etc. Please check out [Why EasyLogging++](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#why-easylogging) section for further details.

## Why EasyLogging++
 * **Native C++ support (from C++98 to latest C++ standard)**
 * **Easily portable**
  - EasyLogging++ is based on just one header file that is enough for writing logs for you. All you need to do is include that header in your source code and initialize it with one line and you will be good to go!
  - It is based on source code rather than binary. So, no installation is required. As you include header into your C++ application, it gets compiled with it, so it goes with your project.
 * **Supports multiple OS with multiple architectures**
 * **[Extremely easy to use](https://github.com/mkhan3189/EasyLoggingPP/tree/master/samples)**
 * **Open Source**
 * **[Actively developed and maintained](https://github.com/mkhan3189/EasyLoggingPP/commits/master)**
 * **[Highly configurable logging](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#log-format)**
 * **[Ability to inject new loggers](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#log-types)**
 * **Different aspects of logs**
   EasyLogging++ has different aspects of logging that includes conditional logging, levelled-verbose logging and interval logging
 * **[Many additional features](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#additional-features)**
 * **[Thread safe](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#thread-safety)**
 * **Type safe**
 * **[Supports hierarchical logging](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#enabledisable-logging)**
    Which means that you can turn different parts of logging on or off depending on the requirements. EasyLogging++ uses power of preprocessor directives to allow developers to enable or disable all or certain logs. Disabling log will not cause any harm 
 * **[Performance tracking](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#performance-tracking)**
 * **Class and Structs Logging**
   EasyLogging++ supports logging [libraries' classes, containers](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#c-libraries-logging), and [your own classes](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#logging-your-own-class)

## Getting Started

[Download EasyLogging++](http://icplusplus.com/tools/easylogging/easyloggingpp.zip) and simply include and initialize:
```C++
#include "easylogging++.h"
// ** FOLLOWING LINE SHOULD BE USED ONCE AND ONLY ONCE IN WHOLE APPLICATION **
// ** THE BEST PLACE TO PUT THIS LINE IS IN main.cpp RIGHT AFTER INCLUDING easylogging++.h **
_INITIALIZE_EASYLOGGINGPP
```
EasyLogging++ comes with following severity levels of logging with complete control over each of the following:
```
  * INFO
  * DEBUG
  * WARNING
  * ERROR
  * FATAL
  * QA
  * TRACE
  * VERBOSE(level)
```

*NOTE: To support legacy logging, i.e, `INFO(..), WARNING(..) etc` define a macro `_SUPPORT_LEGACY_LOG_NAMES`. See [issue #25](https://github.com/mkhan3189/EasyLoggingPP/issues/25) for further details on this change*

See [simplest sample](https://github.com/mkhan3189/EasyLoggingPP/tree/master/samples/STL/very_basic.cpp)

## Examples
#### Basic Logging
 ```C++
 #include "easylogging++.h"
 _INITIALIZE_EASYLOGGINGPP
 int main(void) {
    BDEBUG << "Staring my EasyLogging++ program";
    unsigned int i = 0;
    BINFO << "Current value is " << i;
    BINFO << "Now the value has changed from " << i++ << " to " << i;
    BDEBUG << "End of my EasyLogging++ program";
 }
 ```
Output for above logging varies depending on format you set in configuration section of `easylogging++.h`. Here are some sample outputs;

###### Output (Format: `%type [%level] %log\n`)
```
business [DEBUG] Staring my EasyLogging++ program
business [INFO] Current value is 0
business [INFO] Now the value has changed from 0 to 1
business [DEBUG] End of my EasyLogging++ program
```
###### Output (Format: `[%level] [%loc] \n %log`)
```
[DEBUG] [/home/easyloggertest/main.cpp:3]
    Staring my EasyLogging++ program
[INFO] [/home/easyloggertest/main.cpp:5]
    Current value is 0
[INFO] [/home/easyloggertest/main.cpp:6]
    Now the value has changed from 0 to 1
[DEBUG] [/home/easyloggertest/main.cpp:7]
    End of my EasyLogging++ program

```
###### Output (Format: `[%level] [%datetime] [%func] [%loc] %log\n`)
```
[DEBUG] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:3] Staring my EasyLogging++ program
[INFO] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:5] Current value is 0
[INFO] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:6] Now the value has changed from 0 to 1
[DEBUG] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:7] End of my EasyLogging++ program

```
Note: `%func` format depends on compiler and is supported by Visual C++ and GNU C >= 2 only

See [Log Format](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#log-format) section for more details on different format specifiers

## Additional Features
#### Log Types
EasyLogging++ support different log types, by default four log types are injected.
 * Trivial Logger: Trivial logging unrelated to business logics or security issues / logics (`LOG`)
 * Business Logger: Logs related to business logics (`business`)
 * Security Logger: Logs related to security logics (`security`)
 * Performance Logger: Logs related to performance (`performance`)

You can specify log type in log output using format specifier `%type`

In addition to these log types, you may inject custom log types; e.g, `FinancialLogger` can be injected using
 ```C++
 _QUALIFIED_LOGGER.injectNewLogType("FinancialLogger", "finance");
 ```

And when using this custom logger use 
 ```C++
  CINFO("FinancialLogger") << "info log";
  CWARNING("FinancialLogger") << "warning log";
 ```

Log output will be something like:
 ```
  [finance] [INFO] [13/01/2013 17:21:09.571] info log
 ```

For format:
 `[%type] [%level] [%datetime] %log\n`

For your ease, once you inject the logger, you can define a macro; we recommend you use same style macro name as other macros, i.e, first letter starting with log type name followed by severity level. For example, for finance logger above you may use:
```C++
#define FINFO CINFO("FinancialLogger")
#define FWARNING CWARNING("FinancialLogger")
#define FDEBUG CDEBUG("FinancialLogger")
#define FERROR CERROR("FinancialLogger")
#define FFATAL CFATAL("FinancialLogger")
#define FQA CQA("FinancialLogger")
#define FTRACE CTRACE("FinancialLogger")
#define FVERBOSE(level) CVERBOSE(level, "FinancialLogger")
// Conditional logs
#define FINFO_IF(condition) CINFO_IF(condition, "FinancialLogger")
#define FWARNING_IF(condition) CWARNING_IF(condition, "FinancialLogger")
#define FDEBUG_IF(condition) CDEBUG_IF(condition, "FinancialLogger")
#define FERROR_IF(condition) CERROR_IF(condition, "FinancialLogger")
#define FFATAL_IF(condition) CFATAL_IF(condition, "FinancialLogger")
#define FQA_IF(condition) CQA_IF(condition, "FinancialLogger")
#define FTRACE_IF(condition) CQA_IF(condition, "FinancialLogger")
#define FVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "FinancialLogger")
// Interval logs
#define FINFO_EVERY_N(n) CINFO_EVERY_N(n, "FinancialLogger")
#define FWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "FinancialLogger")
#define FDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "FinancialLogger")
#define FERROR_EVERY_N(n) CERROR_EVERY_N(n, "FinancialLogger")
#define FFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "FinancialLogger")
#define FQA_EVERY_N(n) CQA_EVERY_N(n, "FinancialLogger")
#define FTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "FinancialLogger")
#define FVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "FinancialLogger")
```
and then use it normally;
```C++
FINFO << "This is newly injected financial log"
```

Note, for trivial log, log type output is `LOG`, you can turn this off by defining `_NO_TRIVIAL_TYPE_DISPLAY` and `%type` will be a placeholder for nothing.

######Trivial Logger
`LINFO`, `LDEBUG`, `LWARNING`, `LERROR`, `LFATAL`, `LQA`, `LTRACE`, `LVERBOSE`
######Business Logger
`BINFO`, `BDEBUG`, `BWARNING`, `BERROR`, `BFATAL`, `BQA`, `BTRACE`, `BVERBOSE`
######Security Logger
`SINFO`, `SDEBUG`, `SWARNING`, `SERROR`, `SFATAL`, `SQA`, `STRACE`, `SVERBOSE`
######Performance Logger
`PINFO`, `PDEBUG`, `PWARNING`, `PERROR`, `PFATAL`, `PQA`, `PTRACE`, `PVERBOSE`

*All loggers (including custom loggers) support all the aspect levels, e.g, `SINFO_IF(condition) << "log if condition is true"` or `BWARNING_EVERY_N(2) << "Warning every 2nd time this line is hit"` or `CINFO_IF(condition, "NAME") << "Log custom logger if condition is true"` etc.*

Version: 7.00+

#### Conditional Logging
You can use conditional logging for logs that can have simple / complex conditions. These logs are disabled / enabled with their respective logging level.
* `LDEBUG_IF(condition) << log`
* `LINFO_IF(condition) << log`
* `LWARNING_IF(condition) << log`
* `LERROR_IF(condition) << log`
* `LFATAL_IF(condition) << log`
* `LQA_IF(condition) log`
* `LTRACE_IF(condition) log`
* `LVERBOSE_IF(condition, level) << log`

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
You can log something every N times using `***_EVERY_N` where `***` represent different log levels. Following are the usable macros:
* `LDEBUG_EVERY_N(n) << log`
* `LINFO_EVERY_N(n) << log`
* `LWARNING_EVERY_N(n) << log`
* `LERROR_EVERY_N(n) << log`
* `LFATAL_EVERY_N(n) << log`
* `LVERBOSE_EVERY_N(n, level) << log`
* `LQA_EVERY_N(n) << log`

A typical example:
```C++
for (int i = 1; i <= 100; ++i) {
  LINFO_EVERY_N(5) << "This will be logged every 5th iteration");
}
```

At any time if you wish to check the counter position for a line, you may do it using `_ELPP_COUNTER_POSITION` that gets position for any interval log registered for the line. This is a macro that expands to finding the position. *Please note that counters do get reset at some point, as per current release, limit is set to `100,000` iterations. It used to be 5000 before v7.27.*

Version: 4.07+

 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/interval.cpp)

#### Cleaning Logs On Each Run
If you wish to clean log each time you run your C++ application, you can do this by defining macro `_ALWAYS_CLEAN_LOGS`. This is useful when you are doing regression testing on your application and always want to start with clean logs. It is also useful where keeping older logs are not necessary for example a session of game you wrote in C++ or a small utility software. See [issue #11](https://github.com/mkhan3189/EasyLoggingPP/issues/11) for further details on initial request.

As an example, you may compile your application as following if you wish to clean logs every time you execute application;
```
g++ main.cpp -o main-exec -D_ALWAYS_CLEAN_LOGS
```

 Version: 3.18+

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
###### Output (Format: `%type [%level] [%func] %log`)
 ```
 this is test
performance [DEBUG] Executed [void print(string)] in [0 ms]
performance [DEBUG] Executed [int sum(int, int)] in [0 ms]
Sum of 1 and 2 is 3
 ```
Please note, the function name information varies from compiler to compiler. Some support the whole signature (that is very useful in case of overloaded functions) while others support just function name. This gets hard at times when we have overloaded function or two classes (or namespace) having same function name. But in this kind of situation, EasyLogging++'s `SHOW_LOG_LOCATION` configuration is very useful that you will see in coming section `Configuration`.

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
  _START_EASYLOGGINGPP(argc, argv);
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
 * Make `_ENABLE_VERBOSE_LOGS` `0`

Just like other logs, you may choose the final location of verbose logs, i.e, file or standard output.

Also, log format for verbose logs have special format specifier, `%vlevel` that is placeholder for verbose logging level.

You may also run using `--verbose` to display maximum verbose logs (max level: 9)

 Version: 3.22+
 
 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/verbose.cpp)

#### Quality Assurance Logs
Quality assurance (QA) logs are supported by EasyLogging++ for application that are deployed in QA environments for testing purposes. These logs can provide extra information when working in QA and can be disabled in production without having to change the source code.

By default QA logs will not take affect and will only be logged in `_QUALITY_ASSURANCE` is defined, as an example, following program:
```C++
#include "easylogging++.h"
int main(void) {
  LQA << "I am log only for QA environment";
  return 0;
}
```
will log `QA` if program is compiled using following line at minimum (notice the `_QUALITY_ASSURANCE` macro):

`g++ main.cpp -o main-exec -D_QUALITY_ASSURANCE`

 Version: 3.30+

#### Escaping Log Format
Escape character used in EasyLogging++ is `E`. For example, to write following log
```
%level [DEBUG] [13/01/2013 17:21:09.571] Log message
```
Debug log format should look like:
`E%level [%level] [%datetime] %log`

#### Thread Safety
Since v7.0, EasyLogging++ has embedded mutex that is used to support multithreaded applications. Make sure you compile application right and use '-pthread` where needed.

Following are list of thread-safe functionalities:
 * Normal logging (all trivial, business, security, performance) using `LINFO << ...`, `LWARNING << ...`, `PINFO << ...` etc.
 * Conditional logging using `LINFO_IF(cond) << ...`, `LWARNING_IF(cond) << ...` etc
 * Interval logging using `LINFO_EVERY_N(n) << ...`, `LWARNING_EVERY_N(n) << ...` etc
 * Verbose logging using `LVERBOSE(verbose-level) << ...` (incl. conditional and interval verbose logging)
 * Helper functions

Sample has very well explained comment on each of above way of loggings.

*If you wish to force to disable multi-threading support for EasyLogging++ please define macro `_DISABLE_MUTEX`*

*For v5.0 - v7.00 only C++0x/C++11 and Qt applications are supported. For later versions, all the applications are supported regardless*

Version: 7.0+

 [View Sample 1 (std::thread)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/std_thread.cpp)

 [View Sample 2 (pthread)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/pthread.cpp)
 
 [View Sample 3 (QThread)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/Qt/basic/)

#### Read Log File
If you ever want to read log file from your application, you may do this by `easyloggingpp::helper::MyEasyLog::readLog()` that returns standard string containing the contents of current log file.

#### C++ Libraries Logging
EasyLogging++ is being improved on daily basis and goal is to have a complete support for logging in your C++ application with minimal code possible. Currently EasyLogging++ support following libraries and classes/templates;

 * STL
    - Enable by defining `_ELPP_STL_LOGGING`
    - Basic types supported: `string`, `wstring` (Always enabled)
    - Containers supported: `vector`, `list`, `deque`, `set`, `multiset`, `bitset`, `pair`, `map`, `multimap`, `queue`, `priority_queue`, `stack`
 * Qt
    - Enable by defining `_ELPP_QT_LOGGING`
    - Basic types supported: `QString`, `QChar`, `QBool`, `qint64`, `quint64`, `QStringRef`, `QLatin1String`
    - Containers supported: `QVector`, `QList`, `QMap`, `QMultiMap`, `QQueue`, `QPair`, `QSet`, `QHash`, `QMultiHash`, `QLinkedList`, `QStack`
 * Gnu
    - Enable by defining `_ELPP_GNUC_LOGGING`
    - Containers supported: `__gnu_cxx::slist`, `__gnu_cxx::hash_set`, `__gnu_cxx::multiset`

*You should enable logging in order to use it with EasyLogging++ by defining one (or more) of above mentioned macros during compilation or before including `easylogging++.h` file*

[View Sample 1 (STL)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/containers.cpp)

[View Sample 2 (Qt)](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/Qt/basic/main.cpp)

Version: 7.60+

#### Logging Your Own Class
There will be times when you would want to log your own class, just declare `toString() const` in your class. Return type of `toString()` can vary depending on what you want to log but it has to be some logable data type. Remember, `toString()` SHOULD BE const to prevent any value change.

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

        std::string toString(void) const {
            return "MyClass name is " + name();
        }
    private:
        std::string name_;
};

int main(void) {
    MyClass myClass("Awesome class");
    LINFO << myClass;

    return 0;
}
```

Will log out something like:

`14:32:47.031 INFO  [log] MyClass name is Awesome class`

Of course, above output varies with your log format configurations. The one above is result of `%time %level [%type] %log`

*Tip: Its always a good idea to wrap brackets around your class log to distinguish one class to another. See sample for details*

Version: 7.34+

[View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/STL/custom_class.cpp)

## Configuration
#### Enable/Disable Logging
By Default logging is enabled and you can use it in your aplication. There are few things that you might want to configure following in `easylogging++.h` header.

* `_LOGGING_ENABLED` macro enables or disables logging (`0` for disable `1` for enable)
* `_ENABLE_DEBUG_LOGS` macro enables or disables debugging logs (`0` for disable `1` for enable)
* `_ENABLE_INFO_LOGS` macro enables or disables info logs (`0` for disable `1` for enable)
* `_ENABLE_WARNING_LOGS` macro enables or disables warning logs (`0` for disable `1` for enable)
* `_ENABLE_ERROR_LOGS` macro enables or disables error logs (`0` for disable `1` for enable)
* `_ENABLE_FATAL_LOGS` macro enables or disables fatal logs (`0` for disable `1` for enable)
* `_ENABLE_VERBOSE_LOGS` macro enables or disables verbose logs (`0` for disable `1` for enable)
* `_ENABLE_QA_LOGS` macro enables or disables QA logs (`0` for disable `1` for enable)
* `_ENABLE_TRACE_LOGS` macro enables or disables TRACE logs (`0` for disable `1` for enable)

There is another way to disable logging that doesn't require modifying `easylogging++.h file`. This is done while compiling, define macro `_DISABLE_LOGS` and EasyLogging++ will be disabled.

As an example, if you are using g++
```
g++ main.cpp -o main-exec -D_DISABLE_LOGS
```

To disable level specific log while compiling here are macros to define;

* `_DISABLE_DEBUG_LOGS` (also disables performance tracking)
* `_DISABLE_INFO_LOGS`
* `_DISABLE_WARNING_LOGS`
* `_DISABLE_ERROR_LOGS`
* `_DISABLE_FATAL_LOGS`
* `_DISABLE_TRACE_LOGS`
* `_DISABLE_VERBOSE_LOGS`

As an example if you wish to disable just debug and status logs while `_ENABLE_DEBUG_LOGS` and `_ENABLE_STATUS` is set to 1 in `easylogging++.h`, you may compile with following line;
```
g++ main.cpp -o main-exec -D _DISABLE_DEBUG_LOGS -D _DISABLE_INFO_LOGS
```
This will disable debug logs and info logs in main-exec binary.

**Notes**
 - When the logging is turned off, it will not affect any code, it will not result in any compilation error, in fact, compiler will ignore those lines. Performance tracking will also be disabled.
 - QA logs will only be enabled when `_QUALITY_ASSURANCE` is defined. See [Quality Assurance](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#quality-assurance-logs) section for details.
 
#### Log Location By Log Level
Since v2.0+, EasyLogging++ has configuration for custom log locations, that means; for example you can choose to log `DEBUG`s to log file but not to standard output (e.g, terminal) while `INFO` to both standard output and log file.
This can be set by following configurations
* `_DEBUG_LOGS_TO_STANDARD_OUTPUT` to enable/disable debug logs to be shown in standard output (`0` for disable `1` for enable)
* `_DEBUG_LOGS_TO_FILE` to enable/disable saving debug logs to log file (`0` for disable `1` for enable)
* `_INFO_LOGS_TO_STANDARD_OUTPUT` to enable/disable info logs to be shown in standard output (`0` for disable `1` for enable)
* `_INFO_LOGS_TO_FILE` to enable/disable saving info logs to log file (`0` for disable `1` for enable)
* `_WARNING_LOGS_TO_STANDARD_OUTPUT` to enable/disable warning logs to be shown in standard output (`0` for disable `1` for enable)
* `_WARNING_LOGS_TO_FILE` to enable/disable saving debug warning to log file (`0` for disable `1` for enable)
* `_ERROR_LOGS_TO_STANDARD_OUTPUT` to enable/disable error logs to be shown in standard output (`0` for disable `1` for enable)
* `_ERROR_LOGS_TO_FILE` to enable/disable saving error logs to log file (`0` for disable `1` for enable)
* `_FATAL_LOGS_TO_STANDARD_OUTPUT` to enable/disable fatal logs to be shown in standard output (`0` for disable `1` for enable)
* `_FATAL_LOGS_TO_FILE` to enable/disable saving fatal logs to log file (`0` for disable `1` for enable)
* `_VERBOSE_LOGS_TO_STANDARD_OUTPUT` to enable/disable verbose logs to be shown in standard output (`0` for disable `1` for enable)
* `_VERBOSE_LOGS_TO_FILE` to enable/disable saving verbose logs to log file (`0` for disable `1` for enable)
* `_QA_LOGS_TO_STANDARD_OUTPUT` to enable/disable QA logs to be shown in standard output (`0` for disable `1` for enable)
* `_QA_LOGS_TO_FILE` to enable/disable saving QA logs to log file (`0` for disable `1` for enable)
* `_TRACE_LOGS_TO_STANDARD_OUTPUT` to enable/disable TRACE logs to be shown in standard output (`0` for disable `1` for enable)
* `_TRACE_LOGS_TO_FILE` to enable/disable saving TRACE logs to log file (`0` for disable `1` for enable)

#### Log Format
You can customize format of logging. Following format specifiers are currently supported by EasyLogging++
* `%type` Type of logging
* `%level` Level of logging
* `%vlevel` Verbose level [integer] only applicable for verbose logs
* Date/Time [Remember to use either one of above. Having `%date %time` for example, will result in failure.]
 - `%date` Date only
 - `%time` Time only
 - `%datetime` Date and Time
* `%user` Username currently running application
* `%host` Computer name / host name
* `%func` Function where log was written from
* `%loc` Location with filename and line number where log was written from
* `%log` Actual log
* `\n` New line
* `\t` Tab

**Note** Above format specifier can be used only once per severity level. If you define multiple specifiers, only first one will be resolved to its value and others will remain as they are. This is to improve performance and prevent potential formatting errors.

#### Log Format By Log Level
Since v3.0+, EasyLogging++ supports different format for different log level. This is set by following constants in `easylogging++.h` configuration section;
* `DEFAULT_LOG_FORMAT` Sets default format and is used by other levels unless explicitely set
* `DEBUG_LOG_FORMAT` Sets format used for `DEBUG` logs
* `INFO_LOG_FORMAT` Sets format used for `INFO` logs
* `WARNING_LOG_FORMAT` Sets format used for `WARNING` logs
* `ERROR_LOG_FORMAT` Sets format used for `ERROR` logs
* `FATAL_LOG_FORMAT` Sets format used for `FATAL` logs
* `VERBOSE_LOG_FORMAT` Sets format used for `VERBOSE` logs
* `QA_LOG_FORMAT` Sets format used for `QA` logs
* `TRACE_LOG_FORMAT` Sets format used for `TRACE` logs

The default format for each of above log level has been made default after careful analysis to improve readibility while investigating by looking at logs.

#### Other Configurations
* `SHOW_STD_OUTPUT` Flag for showing log in standard output (terminal or command prompt for example) 
* `SAVE_TO_FILE` Flag to set whether to save logs to file or not
* `LOG_FILENAME` If saving to file, this sets the filename
* `USE_CUSTOM_LOCATION` Flag to set whether log file is saved to custom location defined in `CUSTOM_LOG_FILE_LOCATION`
* `CUSTOM_LOG_FILE_LOCATION` This is where log file is saved if `USE_CUSTOM_LOCATION` is true. Relative paths are not allowed. This should end with slash
* `SHOW_START_FUNCTION_LOG` Determines whether to show log when starting any time tracked function
* `MILLISECONDS_LENGTH` Applicable only in UNIX based OS, sets the length of milliseconds. E.g, `3` will give milliseconds like `259`; `6` will give more detailed like `601766`

Version: 5.0+


#### Tested On
EasyLogging++ has been tested on following platforms (OS and compilers)

**Operating Systems**

![win7] Windows 7 (64-bit, Visual C++ 8.0, Visual C++ 9.0, Visual C++ 11.0)

![win8] Windows 8 (64-bit, Visual C++ 8.0, Visual C++ 9.0, Visual C++ 11.0)

![mac] Mac OSX (clang 3.1/Apple Clang Version 4.1 (LLVM 3.1))

![ubuntu] Ubuntu 12.04 / 12.10 (32-bit, 64-bit, g++ 4.6.3)

![scientificlinux] Scientific Linux 6.2 (64-bit, g++ 4.4)

![linuxmint] Linux Mint 14 (64-bit, g++ 4.7.2)

![android] Android 2.2+ (NDK)

**Compilers**

![gcc] GNU Compiler Collection (g++ 4.4, g++ 4.6.3, g++ 4.7.2)

![vcpp] Visual C++ (Visual C++ 8.0, Visual C++ 9.0, Visual C++ 11.0)

*EasyLogging++ is expected to be compatible with other linux distros and other compilers, but not listed here because it is not verified. Please feel free to contribute if you successfully compile it on any platform.*

#### Tips For Performance Improvement
* When you deploy your application for release and you are certain that you do not need to log standard output (terminal or command prompt), set `SHOW_STD_OUTPUT` to false

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
