# Change Log

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
