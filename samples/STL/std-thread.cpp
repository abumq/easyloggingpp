 //
 // This file is part of Easylogging++ samples 
 // Demonstration of multithreaded application in C++ (0x | 11) 
 // 
 // Revision: 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"
_INITIALIZE_EASYLOGGINGPP
#if _ELPP_USE_STD_THREADING
#include <thread>

void writeLogFromThread(int threadId) {
  // Following line will be logged with every thread
  LOG(INFO) << "This standard log is written by thread #" << threadId;

  // Following line will be logged with every thread only when --v=2 argument 
  // is provided, i.e, ./bin/multithread_test.cpp.bin --v=2
  VLOG(2) << "This is verbose level 2 logging from thread #" << threadId;
  CLOG(INFO, "performance") << "Writing using performance logger";
  // Following line will be logged only once from second running thread (which every runs second into 
  // this line because of interval 2)
  LOG_EVERY_N(2, WARNING) << "This will be logged only once from thread who every reaches this line first. Currently running from thread #" << threadId;

  for (int i = 1; i <= 100; ++i) {
     VLOG_IF(true, 2) << "Verbose condition for level 2";
     VLOG_EVERY_N(2, 3) << "Verbose level 3 log every 4th time. This is at " << i << " from thread #" << threadId;
     CLOG(INFO, "performance") << "Writing using performance logger";
     LOG(INFO) << "This standard log is written by thread #" << threadId;
  }
}

int main(int argc, char** argv) {  // Using FUNC for performance tracking
   _START_EASYLOGGINGPP(argc, argv);
   
   if (argc > 1 && strcmp(argv[1], "no-std") == 0)
   el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");

   TIMED_FUNC(std_thd_timer);

   // Create three thread and call writeLogFromThread()
   std::thread t1(writeLogFromThread, 1);
   std::thread t2(writeLogFromThread, 2);
   std::thread t3(writeLogFromThread, 3);
   t1.join();
   t2.join();
   t3.join();
 return 0;
}
#else
int main() {
  LOG(INFO) << "std::thread not supported for selected compiler";
}
#endif
