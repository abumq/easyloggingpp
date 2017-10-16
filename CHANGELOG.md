# Change Log

## [9.95.4] - 15-10-2017
### Added
- Install a pkg-config `.pc` file

## [9.95.3] - 13-10-2017
### Fixes
- Multithreading issue fixed raised from last release at log builder

## [9.95.2] - 12-06-2017
### Fixes
 - Build fix for kFreeBSD as suggested in issue #563
 - Fixed issue with deadlock on dispatch (see #571)
 - Fixed printf like logging with thread safety (see #572)

### Updates
 - Added support for AIX (thanks to @apollo13)

## [9.95.0] - 02-08-2017
### Added
 - Added NetBSD as unix [coypoop](https://github.com/muflihun/easyloggingpp/pull/548/commits)
 - Ignore `NDEBUG` or `_DEBUG` to determine whether debug logs should be enabled or not. Use `ELPP_DISABLE_DEBUG_LOGS`

### Fixes
 - Fix compile when `_USE_32_BIT_TIME_T` defined [gggin](https://github.com/muflihun/easyloggingpp/pull/542/files)
 - Fix invalid usage of safeDelete which can cause an error with valgrind [Touyote](https://github.com/muflihun/easyloggingpp/pull/544/files)
 - Add code to ensure no nullptr references [tepperly](https://github.com/muflihun/easyloggingpp/pull/512/files)

## [9.94.2] - 12-04-2017
### Added
 - CMake option to create static lib (thanks to @romariorios)
 - Ability to use UTC time using `ELPP_UTC_DATETIME` (thanks to @romariorios)
 - CMake module updated to support static lib

### Changes
 - Renamed long format specifiers to full names with padding for readbility

### Fixes
 - Fixed Android NDK build (thanks to @MoroccanMalinois)
 - Fix `ELPP_DISABLE_LOGS` not working in VS (thanks to @goloap) #365

## [9.94.1] - 25-02-2017
### Fixed
 - Fixes for `/W4` level warnings generated in MSVC compile (Thanks to [Falconne](https://github.com/Falconne))
 - Fixed links
 - Fixes removing default logger if other than `default`

### Changes
 - Changed documentation to mention `easylogging++.cc` in introduction and added links to features

## [9.94.0] - 14-02-2017
### Fixed
 - Fixed performance tracking time unit and calculations

### Added
 - Restored `ELPP_DEFAULT_LOGGER` and `ELPP_DEFAULT_PERFORMANCE_LOGGER`
 - `Helpers::getThreadName` for reading current thread name
 - Custom format specifier now has to return `std::string` instead
 - Merged `thread_name` with `thread` if thread name is available it's used otherwise ID is displayed

For older versions please refer to [https://github.com/muflihun/easyloggingpp/tree/master/doc](https://github.com/muflihun/easyloggingpp/tree/master/doc)
