//
// This file is part of Easylogging++ samples
//
// Custom format specifier to demonstrate usage of el::Helpers::installCustomFormatSpecifier
//
// Revision 1.1
// @author aparajita
//

#include "easylogging++.h"
#include <map>

INITIALIZE_EASYLOGGINGPP

enum ELogLevel : el::base::type::VerboseLevel {
    kLogLevel_Off = 0,
    kLogLevel_Error,
    kLogLevel_Warning,
    kLogLevel_Info,
    kLogLevel_Debug,
    kLogLevel_Verbose
};

static std::map<ELogLevel, std::string> sSeverityMap {
    { kLogLevel_Error,   "ouch!" },
    { kLogLevel_Warning, "oops" },
    { kLogLevel_Info,    "hey" },
    { kLogLevel_Debug,   "debugging" },
    { kLogLevel_Verbose, "loquacious" }
};

const char*
getSeverity(const el::LogMessage* message) {
    return sSeverityMap[static_cast<ELogLevel>(message->verboseLevel())].c_str();
}

int main(int argc, const char * argv[]) {
    // Install format specifier
    el::Helpers::installCustomFormatSpecifier(el::CustomFormatSpecifier("%severity", getSeverity));

    // Configure loggers
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime{%b %d %H:%m:%s}: [%severity] %msg");
    el::Loggers::setVerboseLevel(kLogLevel_Verbose);

    VLOG(kLogLevel_Error) << "This is an error";
    VLOG(kLogLevel_Warning) << "This is a warning";
    VLOG(kLogLevel_Info) << "This is info";
    VLOG(kLogLevel_Debug) << "This is debug";
    VLOG(kLogLevel_Verbose) << "This is verbose";

    // Uninstall custom format specifier
    el::Helpers::uninstallCustomFormatSpecifier("%severity");

    VLOG(kLogLevel_Error) << "This is an error";
    VLOG(kLogLevel_Warning) << "This is a warning";
    VLOG(kLogLevel_Info) << "This is info";
    VLOG(kLogLevel_Debug) << "This is debug";
    VLOG(kLogLevel_Verbose) << "This is verbose";

    return 0;
}
