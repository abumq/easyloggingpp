 //
 // This file is part of Easylogging++ samples 
 // 
 // Revision: 1.0
 // @author mkhan3189
 //

#define _ELPP_STRICT_SIZE_CHECK

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

static unsigned int idx;

void rolloutHandler(const char* filename, std::size_t size) {
   // SHOULD NOT LOG ANYTHING HERE BECAUSE LOG FILE IS CLOSED!
   std::cout << "************** Rolling out [" << filename << "] because it reached [" << size << "]" << std::endl;

   // BACK IT UP
   std::stringstream ss;
   ss << "mv " << filename << " bin/log-backup-" << ++idx;
   system(ss.str().c_str());
}

int main(int argc, char** argv) {
   idx = 0;

   el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "/tmp/logs/max-size.log");
   el::Loggers::reconfigureAllLoggers(el::ConfigurationType::MaxLogFileSize, "100");
   el::Helpers::installPreRollOutHandler(rolloutHandler);

   for (int i = 0; i < 100; ++i)
       LOG(INFO) << "Test";
   return 0;
}
