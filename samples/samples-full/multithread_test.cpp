/**
 * This file is part of EasyLogging++ samples
 * Demonstration of multithreaded application in C++ (0x | 11) 
 * 
 * Compile this program using (if using gcc-c++):
 *     g++ -o bin/multithread_test.cpp.bin multithread_test.cpp -std=c++0x -pthread
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#include "../../easylogging++-full.h"

#if _CXX0X || _CXX11 // defined in easylogging++.h for C++0X standard
#include <thread>
#endif // _CXX0X || _CXX11

_INITIALIZE_EASYLOGGINGPP

void writeLogFromThread(int threadId){
  // Following line will be logged with every thread
  INFO("This standard log is written by thread #" << threadId);

  // Following line will be logged with every thread only when --v=2 argument 
  // is provided, i.e, ./bin/multithread_test.cpp.bin --v=2
  VERBOSE(2, "This is verbose level 2 logging from thread #" << threadId);

  // Following line will be logged only once from second running thread (which every runs second into 
  // this line because of interval 2)
  WARNING_EVERY_N(2, "This will be logged only once from thread who every reaches this line first. Currently running from thread #" << threadId);

  // Following line will be logged once with every thread because of interval 1 
  INFO_EVERY_N(1, "This interval log will be logged with every thread, this one is from thread #" << threadId);

  INFO_IF(threadId == 2, "This log is only for thread 2 and is ran by thread #" << threadId);
}

int main(int argc, char** argv) {
 _START_EASYLOGGINGPP(argc, argv)
 #if _CXX0X || _CXX11
   // Create three thread and call writeLogFromThread()
   std::thread t1(writeLogFromThread, 1);
   std::thread t2(writeLogFromThread, 2);
   std::thread t3(writeLogFromThread, 3);
   t1.join();
   t2.join();
   t3.join();
 #endif // _CXX0X || _CXX11
   _END_EASYLOGGINGPP
   return 0;
}
