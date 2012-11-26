EasyLogging++
===========

Cross platform logging made easy for C++ applications.

To use EasyLogging++ in your application, simply:
```C++
#include "easylogging++.h"
```

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
```

## Examples
#### Basic Logging
 ```C++
 #include "easylogging++.h"
 int main(void) {
    DEBUG("Staring my EasyLogging++ program");
    unsigned int i = 0;
    INFO("Current value is " << i);
    INFO("Now the value has changed from " << i++ << " to " << i);
    DEBUG("End of my EasyLogging++ program");
 }
 ```
Output for above logging varies depending on format you set in configuration section of `easylogging++.h`. Here are some sample outputs;

###### Output (Format: `[%level] %log`)
```
[DEBUG] Staring my EasyLogging++ program
[INFO] Current value is 0
[INFO] Now the value has changed from 0 to 1
[DEBUG] End of my EasyLogging++ program
```
###### Output (Format: `[%level] [%loc] %n %log`)
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
###### Output (Format: `[%level] [%time] [%loc] %n %log`)
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
###### Output (Format: `[%level] [%datetime] [%func] [%loc] %n %log`)
```
[DEBUG] [Sep 23 2012 14:34:38] [int main(int,char**)] [/home/easyloggertest/main.cpp:3]
    Staring my EasyLogging++ program
[INFO] [Sep 23 2012 14:34:38] [int main(int,char**)] [/home/easyloggertest/main.cpp:5]
    Current value is 0
[INFO] [Sep 23 2012 14:34:38] [int main(int,char**)] [/home/easyloggertest/main.cpp:6]
    Now the value has changed from 0 to 1
[DEBUG] [Sep 23 2012 14:34:38] [int main(int,char**)] [/home/easyloggertest/main.cpp:7]
    End of my EasyLogging++ program

```
Note: `%func` format depends on compiler and is supported by Visual C++ and GNU C >= 2 only
#### Performance Logging
 ```C++
 #include "easylogging++.h"
 SUB(print,(const std::string& input))
   /* sub-routine body */
   std::cout << input;
 END_SUB 
 
 FUNC(int,sum,(int x,int y))
   /* function body */
   RETURN(x+y);
 END_FUNC 
 
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

##### Some Notes on Performance Logging
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
END_FUNC

template <typename T>
static FUNC(T,sum,(T a,T b))
   ...
END_FUNC
```

Note: you have many other configurations to change your output. See following section for details

## Configuration
#### Enable/Disable Logging
By Default logging is enabled and you can use it in your aplication. There are few things that you might want to configure.

* `_LOGGING_ENABLED` macro enables or disables logging (`0` for disable `1` for enable)
* `_ENABLE_DEBUG_LOGS` macro enables or disables debugging logs (`0` for disable `1` for enable)
* `_ENABLE_INFO_LOGS` macro enables or disables info logs (`0` for disable `1` for enable)
* `_ENABLE_WARNING_LOGS` macro enables or disables warning logs (`0` for disable `1` for enable)
* `_ENABLE_ERROR_LOGS` macro enables or disables error logs (`0` for disable `1` for enable)
* `_ENABLE_FATAL_LOGS` macro enables or disables fatal logs (`0` for disable `1` for enable)
* `_ENABLE_PERFORMANCE_LOGS` macro enables or disables performance logs (`0` for disable `1` for enable)
* `_ENABLE_HINTS` macro enables or disables hints (`0` for disable `1` for enable)
* `_ENABLE_STATUS` macro enables or disables status logs (`0` for disable `1` for enable)

*Note*, when the logging is turned off, it will not affect any code, it will not result in any compilation error, in fact, compiler will ignore those lines. Even the functions defined using `SUB` and `FUNC` will behave normally as they would do otherwise when EasyLogging++ is not being used at all.

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
* `_HINTS_TO_STANDARD_OUTPUT` to enable/disable hints to be shown in standard output (`0` for disable `1` for enable)
* `_HINTS_TO_FILE` to enable/disable saving hints to log file (`0` for disable `1` for enable)
* `_STATUS_TO_STANDARD_OUTPUT` to enable/disable status logs to be shown in standard output (`0` for disable `1` for enable)
* `_STATUS_TO_FILE` to enable/disable saving status logs to log file (`0` for disable `1` for enable)

#### Log Format
You can customize format of logging. Following format specifiers are currently supported by EasyLogging++
* `%level` Level of logging
* Date/Time [Remember to use either one of above. Having `%date %time` for example, will result in failure.]
 - `%date` Date only
 - `%time` Time only
 - `%datetime` Date and Time
* `%user` Username currently running application
* `%host` Computer name / host name
* `%func` Function where log was written from
* `%loc` Location with filename and line number where log was written from
* `%log` Actual log
* `%n` New line

*Note* Above format can be used once. If you define two `%level`s for example, only first one will take affect. This is for performance improvement.

#### Log Format By Log Level
Since v3.0+, EasyLogging++ supports different format for different log level. This is set by following constants in `easylogging++.h` configuration section;
* `DEFAULT_LOG_FORMAT` Sets format used for default logs
* `DEBUG_LOG_FORMAT` Sets format used for `DEBUG` logs
* `INFO_LOG_FORMAT` Sets format used for `INFO` logs
* `WARNING_LOG_FORMAT` Sets format used for `WARNING` logs
* `ERROR_LOG_FORMAT` Sets format used for `ERROR` logs
* `FATAL_LOG_FORMAT` Sets format used for `FATAL` logs
* `PERFORMANCE_LOG_FORMAT` Sets format used for `PERFORNANCE` logs
* `HINT_LOG_FORMAT` Sets format used for `HINT`s
* `STATUS_LOG_FORMAT` Sets format used for `STATUS` logs

#### Other Configurations
* `SHOW_STD_OUTPUT` Flag for showing log in standard output (terminal or command prompt for example) 
* `SAVE_TO_FILE` Flag to set whether to save logs to file or not
* `LOG_FILENAME` If saving to file, this sets the filename
* `USE_CUSTOM_LOCATION` Flag to set whether log file is saved to custom location defined in `CUSTOM_LOG_FILE_LOCATION`
* `CUSTOM_LOG_FILE_LOCATION` This is where log file is saved if `USE_CUSTOM_LOCATION` is true. Relative paths are not allowed. This should end with slash
* `SHOW_START_FUNCTION_LOG` Determines whether to show log when starting any time tracked function

#### Modifiable Sections
`easylogging++.h` contains modifiable sections that you can modify. This includes configuration and enabling/disabling certain logs as mentioned above. Please do not modify any code other than the ones in modifiable sections, unless you really know what you are doing. This may cause `update.sh` to stop working.
## UPDATING EasyLogging++
If you are already using older version of EasyLogging++ and would like to update to newer version without losing your previous configurations like your log storage, log format or what you log etc, you can use script called `update.sh`. This script retains configuration from older files and creates new `easylogging++.h` file that you can re-import to your project without losing your configuration and without having any compile errors.
This script takes three parameters:
 * Current File : The current file that is being used in your project and you would like to change. e.g, `/dev/myproject/using/easylogging/src/easylogging++.h`
 * Target File : The new filename that you would like for your new file. e.g, `/dev/myproject/using/easylogging/src/new_easylogging++.h`
 * New Version File : This is the file that you would like to use source from. Mostly, this is the newer version. e.g, `/home/me/Downloads/easylogging++.h` if you dowloaded new file to Downloads. If you download from icplusplus.com, you might want to unzip before you run the script.

*Note* This will only work with EasyLogging++ 3.0+
