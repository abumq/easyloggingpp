/**
 * This file is part of EasyLogging++ samples * Demonstration of multithreaded application in C++ (0x | 11) 
 * 
 * Compile this program using (if using gcc-c++):
 *     g++ -o bin/multithread_test.cpp.bin multithread_test.cpp -std=c++0x -pthread
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#include "easylogging++.h"

#if _ELPP_CXX0X || _ELPP_CXX11 // defined in easylogging++.h for C++0X standard
#include <thread>
#endif // _ELPP_CXX0X || _ELPP_CXX11

_INITIALIZE_EASYLOGGINGPP

void writeLogFromThread(int threadId) {
  // Following line will be logged with every thread
  LINFO << "This standard log is written by thread #" << threadId;

  // Following line will be logged with every thread only when --v=2 argument 
  // is provided, i.e, ./bin/multithread_test.cpp.bin --v=2
  LVERBOSE(2) << "This is verbose level 2 logging from thread #" << threadId;

  // Following line will be logged only once from second running thread (which every runs second into 
  // this line because of interval 2)
  LWARNING_EVERY_N(2) << "This will be logged only once from thread who every reaches this line first. Currently running from thread #" << threadId;

  for (int i = 1; i <= 10000; ++i) {
     LVERBOSE_IF(true, 2) << "Verbose condition for level 2";
     LVERBOSE_EVERY_N(2, 3) << "Verbose level 3 log every 4th time. This is at " << i << " from thread #" << threadId;
  }

  // Following line will be logged once with every thread because of interval 1 
  LINFO_EVERY_N(1) << "This interval log will be logged with every thread, this one is from thread #" << threadId;

  LINFO_IF(threadId == 2) << "This log is only for thread 2 and is ran by thread #" << threadId;
}

int main(int argc, char** argv) {  // Using FUNC for performance tracking
 _START_EASYLOGGINGPP(argc, argv);

 #if _ELPP_CXX0X || _ELPP_CXX11
   // Create three thread and call writeLogFromThread()
   std::thread t1(writeLogFromThread, 1);
   std::thread t2(writeLogFromThread, 2);
   std::thread t3(writeLogFromThread, 3);
   t1.join();
   t2.join();
   t3.join();
 #endif // _ELPP_CXX0X || _ELPP_CXX11
 return 0;
}
