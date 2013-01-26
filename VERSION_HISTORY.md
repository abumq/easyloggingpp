VERSION HISTORY - EasyLogging++
===============================

History was not kept before version 2.1.

#### 4.0
 * 4.00
   - Major improvement for multiple files project
   - Introduced `INITIALIZE_EASYLOGGINGPP`
 * 4.01
   - Added inline doc
   - Fix issue with `TO_STANDARD_OUTPUT` segmentation fault
   - Added support for `--verbose` for level 9
 * 4.02: Minor naming fixes (refactoring)

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
