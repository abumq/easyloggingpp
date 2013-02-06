EasyLogging++
===========

Cross platform logging made easy for C++ applications.

To use EasyLogging++ in your application, simply include and initialize:
```C++
#include "easylogging++-full.h"
_INITIALIZE_EASYLOGGINGPP // Should be used once and only once in main.cpp after includes
```
*Alternatively include `easylogging++.h` and link it to `easylogging++.cc` at link time. This comment applies throughout this README and we will be using `easylogging++-full.h` in this read me but you may use `easylogging++.h` instead provided you compile the source file with it, [click here](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#examples-1) for further information on compiling the program with easylogging++ header and source both*

EasyLogging++ comes with following levels of logging with complete control over each of the following:
```
  DEBUG(...)
  INFO(...)
  WARN(...)
  ERROR(...)
  FATAL(...)
  PERFORMANCE(...)
  HINT(...)
  STATUS(...)
  VERBOSE(#, ...)
  QA(...)
```
## Why EasyLogging++
Answering this question can be sometimes hard but here are few reasons why you would want to use EasyLogging++ as logger for your C++ applications;
 * Native C++ support
 * Portablility
  - EasyLogging++ is based on just one header file that is enough for writing logs for you. All you need to do is include that header to your source and you will be good to go!
  - It is based on source code rather than binary. So, no installation is required. As you include header into your C++ application, it gets compiled with it.
  - It supports linux, windows and mac
 * [Easy Enable / Disable](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#enabledisable-logging)

    EasyLogging++ uses power of preprocessor directives to allow developers to enable or disable all or certain logs. Disabling log at `easylogging++-full.h` level will not cause any damage to compilation.
 * [Extremely easy to use](https://github.com/mkhan3189/EasyLoggingPP/tree/master/samples)
 * Open Source
 * [Actively developed and maintained](https://github.com/mkhan3189/EasyLoggingPP/commits/master)
 * [Additional features](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#additional-features)
 * [Multi-threaded application support](https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#support-for-multi-threaded-applications)

## Getting Started
In order to start logging follow these three steps:
 * Include `easylogging++-full.h` header
 * Initialize ONCE AND ONLY ONCE using `_INITIALIZE_EASYLOGGINGPP`. The best place to put this line is in the main file where main function is defined (usually called main.cpp). Remember, this should be placed only once in your application.
 * Start logging!

See [simplest sample](https://github.com/mkhan3189/EasyLoggingPP/tree/master/samples/samples-full/very_basic.cpp)

## Examples
#### Basic Logging
 ```C++
 #include "easylogging++-full.h"
 _INITIALIZE_EASYLOGGINGPP
 int main(void) {
    DEBUG("Staring my EasyLogging++ program");
    unsigned int i = 0;
    INFO("Current value is " << i);
    INFO("Now the value has changed from " << i++ << " to " << i);
    DEBUG("End of my EasyLogging++ program");
 }
 ```
Output for above logging varies depending on format you set in configuration section of `easylogging++-full.h`. Here are some sample outputs;

###### Output (Format: `[%level] %log`)
```
[DEBUG] Staring my EasyLogging++ program
[INFO] Current value is 0
[INFO] Now the value has changed from 0 to 1
[DEBUG] End of my EasyLogging++ program
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
###### Output (Format: `[%level] [%time] [%loc] \n %log`)
```
[DEBUG] [14:34:38] [/home/easyloggertest/main.cpp:3]
    Staring my EasyLogging++ program
[INFO] [14:34:38] [/home/easyloggertest/main.cpp:5]
    Current value is 0
[INFO] [14:34:38] [/home/easyloggertest/main.cpp:6]
    Now the value has changed from 0 to 1
[DEBUG] [14:34:38] [/home/easyloggertest/main.cpp:7]
    End of my EasyLogging++ program

```
###### Output (Format: `[%level] [%datetime] [%func] [%loc] \n %log`)
```
[DEBUG] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:3]
    Staring my EasyLogging++ program
[INFO] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:5]
    Current value is 0
[INFO] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:6]
    Now the value has changed from 0 to 1
[DEBUG] [13/01/2013 17:23:06.371] [int main(int,char**)] [/home/easyloggertest/main.cpp:7]
    End of my EasyLogging++ program

```
Note: `%func` format depends on compiler and is supported by Visual C++ and GNU C >= 2 only

## Additional Features
#### Conditional Logging
You can use conditional logging for logs that can have simple / complex conditions. These logs are disabled / enabled with their respective logging level.
* `DEBUG_IF(condition, log)`
* `INFO_IF(condition, log)`
* `WARNING_IF(condition, log)`
* `ERROR_IF(condition, log)`
* `FATAL_IF(condition, log)`
* `PERFORMANCE_IF(condition, log)`
* `HINT_IF(condition, log)`
* `STATUS_IF(condition, log)`
* `VERBOSE_IF(condition, level, log)`
* `QA_IF(condition, log)`

A typical example is as follow (taken from samples/samples-full/conditional_log.cpp)
```C++
  INFO_IF(1 == 1, "1 is equal to 1");
  // Or some complex condition
  DEBUG_IF((1 == 2) || (5 == 5)) , "Something is right so I will print!");
  // verbose log
  VERBOSE_IF(true, 1, "Printing verbose level-1");
```
 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/conditional_logs.cpp)

#### Interval Logging 
You can log something every N times using `***_EVERY_N` where `***` represent different log levels. Following are the usable macros:
* `DEBUG_EVERY_N(n, log)`
* `INFO_EVERY_N(n, log)`
* `WARNING_EVERY_N(n, log)`
* `ERROR_EVERY_N(n, log)`
* `FATAL_EVERY_N(n, log)`
* `PERFORMANCE_EVERY_N(n, log)`
* `HINT_EVERY_N(n, log)`
* `STATUS_EVERY_N(n, log)`
* `VERBOSE_EVERY_N(n, level, log)`
* `QA_EVERY_N(n, log)`

A typical example:
```C++
for (int i = 1; i <= 100; i++) {
  INFO_EVERY_N(5, "This will be logged every 5th iteration");
}
```

*Notes:* 
 * The performance is yet to be improved for interval logging.
 * These logs work well even in the same iteration; there is a seperate counter registered for each log per line per file.
 * If you happen to find any issue regarding this, please feel free to raise it on github

Version: 4.07+

 [View Sample 1](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/every_n_log.cpp)

 [View Sample 2](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/every_n_log_2.cpp)

#### Cleaning Logs On Each Run
If you wish to clean log each time you run your C++ application, you can do this by defining macro `_ALWAYS_CLEAN_LOGS`. This is useful when you are doing regression testing on your application and always want to start with clean logs. See [issue #11](https://github.com/mkhan3189/EasyLoggingPP/issues/11) for further details on initial request.

As an example, you may compile your application as following if you wish to clean logs every time you execute application;
```
g++ main.cpp -o main-exec -D _ALWAYS_CLEAN_LOGS
```

#### Performance Logging
 ```C++
 #include "easylogging++-full.h"
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
    std::cout << "Sum of 1 and 2 is " << sumResult;
}
 ```
###### Output (Format: `[%level] %log`)
 ```
 this is test
[PERFORMANCE] Executed [void print(string)] in [~0 seconds]
[PERFORMANCE] Executed [int sum(int, int)] in [~0 seconds]
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

Note: you have many other configurations to change your output. See following section for details

 [View Sample 1](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/time_tracker.cpp)
 
 [View Sample 2](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/time_waster.cpp)
 
#### Verbose Logging
Verbose logging is supported in EasyLogging++ v3.22+. To start using verbose logging you will need to have following right after your `int main(int, char**)` function `_START_EASYLOGGINGPP(argc, argv);`, so your main function will look something like
```C++
int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);
  ...
}
```

And when using verbose logging you will need to run your C++ application with argument `--v=` followed by verbose level.
When you want to write verbose log, you will use, `VERBOSE(level, log)`

As an example
```C++
#include "easylogging++-full.h"
int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);
  bool condition = true;
  VERBOSE(1, "I will be printed when this application is run using --v=1 or higher than 1 arguments");
  VERBOSE(2, "I will be printed when this application is run using --v=2 arguments");
  VERBOSE_IF(condition, 1, "I will be printed when condition is true as well as application is run using --v=1 or higher than 1 arguments");
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

 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/verbose_logs.cpp)
 
#### Releasing Memory
Although this part is not necessary for your C++ application because EasyLogging++ works in `singleton pattern way` but still for peace of mind of developers, you may release memory used by EasyLogging++ using `_END_EASYLOGGINGPP`. Keep in your mind, if you re-log using EasyLogging++ using one of `INFO(..)`, `DEBUG(..)` etc, memory will be re-allocated. Also, be sure EasyLogging++ is extensively tested for any memory leaks, but to make valgrind happy for your C++ application, make sure to have `_END_EASYLOGGINGPP` at end of application (probably main function).
```C++
int main(int argc, char** argv) {
  INFO("This is memory release test");
  _END_EASYLOGGINGPP //Memory released! Valgrind will be happy
}
```

###### Summary On When To Release Memory
There are only few points that will help you remember when to release memory using `_END_EASYLOGGINGPP` and when not.

 * Always release memory when you are done with your logging i.e, end of `main(..)` function before every return. Alternatively, you may use `RETURN_MAIN(exit_status)` to automatically release memory.
 * If you want to track performance on `main(..)` function, try using `MAIN(int argc, char** argv)` and `RETURN_MAIN(..)` (see sample 2 below)
 * Try to minimize using `_END_EASYLOGGINGPP` to minimize delete calls, use it in the end of main.
 * Last but not least, if you are not tracking `main(..)` function's performance, just use `_END_EASYLOGGINPP` once like all other [samples](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/).

 [View Sample 1](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/valgrind_happy.cpp)
 
 [View Sample 2](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/summary_memory_release.cpp)
 
#### Quality Assurance Logs
Quality assurance (QA) logs are supported by EasyLogging++ for application that are deployed in QA environments for testing purposes. These logs can provide extra information when working in QA and can be disabled in production without having to change the source code.

By default QA logs will not take affect and will only be logged in `_QUALITY_ASSURANCE` is defined, as an example, following program:
```C++
#include "easylogging++-full.h"
int main(void) {
  STATUS("Starting program...");
  QA("I am log only for QA environment");
  return 0;
}
```
will log `QA` if program is compiled using following line at minimum (notice the `_QUALITY_ASSURANCE` macro):

`g++ main.cpp -o main-exec -D _QUALITY_ASSURANCE`

 [View Sample](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/qa_logs.cpp)

#### Escaping Log Format
Escape character used in EasyLogging++ is `E`. For example, to write following log
```
%level [DEBUG] [13/01/2013 17:21:09.571] Log message
```
Debug log format should look like:
`E%level [%level] [%datetime] %log`

#### Support For Multi-threaded Applications
EasyLogging++ supports multi-threaded applications and uses power of `std::mutex` from C++0X / C++11 to do so. It locks any shared memory for writing logs and unlocks it once written. Everything is done under the hood and you don't need to worry about anything. You just lean back and keep writing logs without any worries.

Make sure you compile your program (that uses threads) using `-std=c++0x -pthread` (or c++11). Additionally, you may use `_CXX0X` and `_CXX11` macros from `easylogging++-full.h`, that are defined when compiling with C++0X or C++11 respectively, as used in corresponding sample.

Following are list of thread-safe functionalities:
 * Normal logging using `INFO(...)`, `WARNING(...)` etc
 * Conditional logging using `INFO_IF(..., ...)`, `WARNING_IF(..., ...)` etc
 * Interval logging using `INFO_EVERY_N(..., ...)`, `WARNING_EVERY_N(..., ...)` etc
 * Verbose logging using `VERBOSE(#, ...)` (incl. conditional and interval verbose logging)
 * Helper functions
 * Releasing memory

Sample has very well explained comment on each of above way of loggings.

*If you have issues in compiling the application, make notes of following*
 * EasyLogging++ multi-threading support is for g++ (with C++0X+) only.
 * If you wish to force to disable multi-threading please define macro `_DISABLE_MUTEX`
 * Please feel free to contribute, EasyLogging++ currently uses `std::mutex` but is happy to expand to make it more portable across other compilers and libraries.

Version: 5.0+

 [View Sample 1](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/multithread_test.cpp)

 [View Sample 2](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/pthread_example.cpp)

## Configuration
#### Enable/Disable Logging
By Default logging is enabled and you can use it in your aplication. There are few things that you might want to configure following in `easylogging++-full.h` header.

* `_LOGGING_ENABLED` macro enables or disables logging (`0` for disable `1` for enable)
* `_ENABLE_DEBUG_LOGS` macro enables or disables debugging logs (`0` for disable `1` for enable)
* `_ENABLE_INFO_LOGS` macro enables or disables info logs (`0` for disable `1` for enable)
* `_ENABLE_WARNING_LOGS` macro enables or disables warning logs (`0` for disable `1` for enable)
* `_ENABLE_ERROR_LOGS` macro enables or disables error logs (`0` for disable `1` for enable)
* `_ENABLE_FATAL_LOGS` macro enables or disables fatal logs (`0` for disable `1` for enable)
* `_ENABLE_PERFORMANCE_LOGS` macro enables or disables performance logs (`0` for disable `1` for enable)
* `_ENABLE_HINT` macro enables or disables hints (`0` for disable `1` for enable)
* `_ENABLE_STATUS` macro enables or disables status logs (`0` for disable `1` for enable)
* `_ENABLE_VERBOSE_LOGS` macro enables or disables verbose logs (`0` for disable `1` for enable)
* `_ENABLE_QA_LOGS` macro enables or disables QA logs (`0` for disable `1` for enable)

There is another way to disable logging that doesn't require modifying `easylogging++-full.h file`. This is done while compiling, define macro `_DISABLE_LOGS` and EasyLogging++ will be disabled.

As an example, if you are using g++
```
g++ main.cpp -o main-exec -D _DISABLE_LOGS
```

To disable level specific log while compiling here are macros to define;

* `_DISABLE_DEBUG_LOGS`
* `_DISABLE_INFO_LOGS`
* `_DISABLE_WARNING_LOGS`
* `_DISABLE_ERROR_LOGS`
* `_DISABLE_FATAL_LOGS`
* `_DISABLE_STATUS`
* `_DISABLE_HINT`
* `_DISABLE_PERFORMANCE_LOGS`
* `_DISABLE_VERBOSE_LOGS`

As an example if you wish to disable just debug and status logs while `_ENABLE_DEBUG_LOGS` and `_ENABLE_STATUS` is set to 1 in `easylogging++-full.h`, you may compile with following line;
```
g++ main.cpp -o main-exec -D _DISABLE_DEBUG_LOGS -D _DISABLE_STATUS
```
This will disable debug logs and status updates in main-exec binary.

*Notes*
 - When the logging is turned off, it will not affect any code, it will not result in any compilation error, in fact, compiler will ignore those lines. Even the functions defined using `SUB` and `FUNC` will behave normally as they would do otherwise when EasyLogging++ is not being used at all.
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
* `_PERFORMANCE_LOGS_TO_STANDARD_OUTPUT` to enable/disable performance logs to be shown in standard output (`0` for disable `1` for enable)
* `_PERFORMANCE_LOGS_TO_FILE` to enable/disable saving performance logs to log file (`0` for disable `1` for enable)
* `_HINT_TO_STANDARD_OUTPUT` to enable/disable hints to be shown in standard output (`0` for disable `1` for enable)
* `_HINT_TO_FILE` to enable/disable saving hints to log file (`0` for disable `1` for enable)
* `_STATUS_TO_STANDARD_OUTPUT` to enable/disable status logs to be shown in standard output (`0` for disable `1` for enable)
* `_STATUS_TO_FILE` to enable/disable saving status logs to log file (`0` for disable `1` for enable)
* `_VERBOSE_LOGS_TO_STANDARD_OUTPUT` to enable/disable verbose logs to be shown in standard output (`0` for disable `1` for enable)
* `_VERBOSE_LOGS_TO_FILE` to enable/disable saving verbose logs to log file (`0` for disable `1` for enable)
* `_QA_LOGS_TO_STANDARD_OUTPUT` to enable/disable QA logs to be shown in standard output (`0` for disable `1` for enable)
* `_QA_LOGS_TO_FILE` to enable/disable saving QA logs to log file (`0` for disable `1` for enable)

#### Log Format
You can customize format of logging. Following format specifiers are currently supported by EasyLogging++
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

*Note* Above format can be used once. If you define two `%level`s for example, only first one will take affect. This is for performance improvement.

#### Log Format By Log Level
Since v3.0+, EasyLogging++ supports different format for different log level. This is set by following constants in `easylogging++-full.h` configuration section;
* `DEFAULT_LOG_FORMAT` Sets default format and is used by other levels unless explicitely set
* `DEBUG_LOG_FORMAT` Sets format used for `DEBUG` logs
* `INFO_LOG_FORMAT` Sets format used for `INFO` logs
* `WARNING_LOG_FORMAT` Sets format used for `WARNING` logs
* `ERROR_LOG_FORMAT` Sets format used for `ERROR` logs
* `FATAL_LOG_FORMAT` Sets format used for `FATAL` logs
* `PERFORMANCE_LOG_FORMAT` Sets format used for `PERFORMANCE` logs
* `HINT_LOG_FORMAT` Sets format used for `HINT`s
* `STATUS_LOG_FORMAT` Sets format used for `STATUS` logs
* `VERBOSE_LOG_FORMAT` Sets format used for `VERBOSE` logs
* `QA_LOG_FORMAT` Sets format used for `QA` logs

#### Other Configurations
* `SHOW_STD_OUTPUT` Flag for showing log in standard output (terminal or command prompt for example) 
* `SAVE_TO_FILE` Flag to set whether to save logs to file or not
* `LOG_FILENAME` If saving to file, this sets the filename
* `USE_CUSTOM_LOCATION` Flag to set whether log file is saved to custom location defined in `CUSTOM_LOG_FILE_LOCATION`
* `CUSTOM_LOG_FILE_LOCATION` This is where log file is saved if `USE_CUSTOM_LOCATION` is true. Relative paths are not allowed. This should end with slash
* `SHOW_START_FUNCTION_LOG` Determines whether to show log when starting any time tracked function

#### Whats The Difference Between `easylogging++.h` and `easylogging++-full.h`
In simple words, `easylogging++.h` is a header that needs to be linked to `easylogging++.cc` in order to compile where as `easylogging++-full.h` is a complete EasyLogging++ with everything in one header.

Historically, we only supported single header in order to make logs easy but since more features are being added as time goes by, we have provided support for both linked headers and full headers. It's upto developer to choose which ever they prefer.

###### What Is Recommended
If you are developing a small application and want a quick logging support with minimum number of extra files, you can use `easylogging++-full.h` where as if your application is on relatively larger scale, we would recommend you use `easylogging++.h` and link the source file to it.

###### Examples
We have added samples for both [linked](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/samples-linked) and [full](https://github.com/mkhan3189/EasyLoggingPP/blob/master/samples/samples-full/samples-full) compile using g++ compiler. Both files are exactly the same except for `compile.sh` (line 33 and 35) where one is linked to source file and other one is not.

A typical compilation using g++ and linked-type would look something like:

`g++ my_prog.cpp easylogging++.cc -o my_prog_exe`

assuming `my_prog.cpp` has included and initialized `easylogging++.h`

where as compilation using g++ and full-type would look somehting like:

`g++ my_prog.cpp -o my_prog_exec`

###### Would Full Version Be Supported In Future?
Short answer: Yes;

Long answer: Although it is a little bit of more effort to support full as well as linked versions but it gives developers a wider choice and decide whats best for them. Both types will always be syncronized in terms of features but obviously you cannot use both at the same time (since both share same namespaces)

Version: 5.0+
