EasyLogging++
===========

Cross platform logging made easy for C++ applications.

To use EasyLogging++ in your application, simple 
```C++
#include "easylogging++.h"
```

When ever you are writing code you may call any of four macros for logging
 * DEBUG(...)
 * INFO(...)
 * WARN(...)
 * ERR(...)

## Examples
#### Code
 ```C++
 #include "easylogging++.h"
 int main(void) {
    DEBUG("Staring my EasyLogging++ program");
    unsigned int i = 0;
    INFO("Current value is " << i);
    INFO("Now the value has changed from " << i++ << " to " << i);
    DEBUG("End of my EasyLoggin++ program");
 }
 ```
###### Output with no extra info
```
[DEBUG] Staring my EasyLogging++ program
[INFO] Current value is 0
[INFO] Now the value has changed from 0 to 1
[DEBUG] End of my EasyLoggin++ program
```
###### Output with SHOW_LOG_LOCATION but SHOW_DATE_TIME and SHOW_LOG_FUNCTION set to false
```
[DEBUG] [/home/easyloggertest/main.cpp:3]
Staring my EasyLogging++ program
[INFO] [/home/easyloggertest/main.cpp:4]
Current value is 0
[INFO] [/home/easyloggertest/main.cpp:5]
Now the value has changed from 0 to 1
[DEBUG] [/home/easyloggertest/main.cpp:6]
End of my EasyLoggin++ program

```
###### Output with SHOW_DATE_TIME, SHOW_LOG_LOCATION but and SHOW_LOG_FUNCTION set to false
```
[DEBUG] [Sun Sep 23 14:34:38 2012] [/home/easyloggertest/main.cpp:3]
Staring my EasyLogging++ program
[INFO] [Sun Sep 23 14:34:38 2012] [/home/easyloggertest/main.cpp:4]
Current value is 0
[INFO] [Sun Sep 23 14:34:38 2012] [/home/easyloggertest/main.cpp:5]
Now the value has changed from 0 to 1
[DEBUG] [Sun Sep 23 14:34:38 2012] [/home/easyloggertest/main.cpp:6]
End of my EasyLoggin++ program

```
Note: you have many other configurations to change your output. See following section for details

## Configuration
By Default logging is enabled and you can use it in your aplication. There are few things that you might want to configure.

* _LOGGING_ENABLED macro enables or disables logging. 
* _ENABLE_DEBUG_LOGS macro enables or disables debugging logs. 
* _ENABLE_INFO_LOGS macro enables or disables info logs. 
* _ENABLE_WARNING_LOGS macro enables or disables warning logs. 
* _ENABLE_ERROR_LOGS macro enables or disables error logs. 

#### Other Configurations
```C++
/**
* Flag for showing log in standard output using std::cout
*/
const bool SHOW_STD_OUTPUT = true;
/**
* Flag to set whether to save log to file
*/
const bool SAVE_TO_FILE = true;
/**
* Flag to set whether to show date/time
*/
const bool SHOW_DATE_TIME = false;
/**
* Flag to set whether to show which function logged the output (some compiler dont support this)
*/
const bool SHOW_LOG_FUNCTION = false;
/**
* Flag to set whether to show which file logged the output and what line
*/
const bool SHOW_LOG_LOCATION = true;
/**
* Flag to set whether output value of NOT_SUPPORTED_STRING if extra info is not available on machine
*/
const bool SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO = false;
/**
* outputs if extra info is not available on machine and SHOW_NOT_SUPPORTED_ON_NO_EXTRA_INFO is true
*/
const std::string NOT_SUPPORTED_STRING = "-not supported-";
/**
* If saving to file, this defines the filename
*/
const std::string LOG_FILENAME = "memory.log";
/**
* Flag to set whether to save log file in custom location
*/
const bool USE_CUSTOM_LOCATION = false;
/**
* If using custom location, this is where custom location is picked up from.
* Note: This should end with last slash 
*/
const std::string CUSTOM_LOG_FILE_LOCATION = "";

```