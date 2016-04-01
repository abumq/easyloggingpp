 //
 // This file is part of Easylogging++ samples
 //
 // Writes all logs (incl. debug version of logs i.e, DLOG etc) using default logger
 // We add logging flag `DisableApplicationAbortOnFatalLog` that prevents application abort on FATAL log
 //
 // Revision 1.2
 // @author mkhan3189
 //

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#define ANSI_COLOR_GREEN  "\x1b[38;2;0;255;0m" // first part is the escape sequence, 38 specifies 256 color mode, 2 is foreground color, then RGB followed by m
#define ANSI_COLOR_ORANGE "\x1b[38;2;255;128;0m"
#define ANSI_UNDERLINE    "\x1b[4m"

int main(int argc, char** argv) {
    START_EASYLOGGINGPP(argc, argv);
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
    el::Loggers::addFlag(el::LoggingFlag::SupportANSICodes);

    // You can uncomment following lines to take advantage of hierarchical logging
    // el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    // el::Loggers::setLoggingLevel(el::Level::Global);

    LOG(INFO);
    LOG(DEBUG);
    LOG(WARNING);
    LOG(ERROR);
    LOG(TRACE);
    VLOG(1);
    LOG(FATAL);

    DLOG(INFO);
    DLOG(DEBUG);
    DLOG(WARNING);
    DLOG(ERROR);
    DLOG(TRACE);
    DVLOG(1);
    DLOG(FATAL);
    LOG(INFO) << ANSI_COLOR_ORANGE << "This is orange";
    LOG(INFO) << ANSI_COLOR_GREEN << "This is green and " << ANSI_UNDERLINE << "this is additionally underlined";

    LOG(INFO) << "Turning off ANSI support";
    el::Loggers::removeFlag(el::LoggingFlag::SupportANSICodes);
    
    LOG_IF(true, INFO);
    LOG_IF(true, DEBUG);
    LOG_IF(true, WARNING);
    LOG_IF(true, ERROR);
    LOG_IF(true, TRACE);
    VLOG_IF(true, 1);
    LOG_IF(true, FATAL);

    LOG_EVERY_N(1, INFO);
    LOG_EVERY_N(1, DEBUG);
    LOG_EVERY_N(1, WARNING);
    LOG_EVERY_N(1, ERROR);
    LOG_EVERY_N(1, TRACE);
    VLOG_EVERY_N(1, 1);
    LOG_EVERY_N(1, FATAL);

    CHECK(1 == 1);
    CCHECK(1 == 1, "default");
    return 0;
}
