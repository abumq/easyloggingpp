//
// This file is part of Easylogging++ samples
//
// Demonstration of multithreaded application using pthread
// 
// Compile this program using (if using gcc-c++ or intel or clang++):
//     [icpc | g++ | clang++] ./pthread.cpp -o bin/./pthread.cpp.bin -D_ELPP_THREAD_SAFE -std=c++0x -pthread -Wall -Wextra
// 
// Revision: 1.1
// @author mkhan3189
//

#include <pthread.h>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void *write(void* thrId){
  char* threadId = (char*)thrId;
  // Following line will be logged with every thread
  LOG(INFO) << "This standard log is written by thread #" << threadId;

  // Following line will be logged with every thread only when --v=2 argument 
  // is provided, i.e, ./bin/multithread_test.cpp.bin --v=2
  VLOG(2) << "This is verbose level 2 logging from thread #" << threadId;

  // Following line will be logged only once from second running thread (which every runs second into 
  // this line because of interval 2)
  LOG_EVERY_N(2, WARNING) << "This will be logged only once from thread who every reaches this line first. Currently running from thread #" << threadId;

  for (int i = 1; i <= 10; ++i) {
     VLOG_IF(true, 2) << "Verbose condition";
     VLOG_EVERY_N(2, 3) << "Verbose level 3 log every 4th time. This is at " << i << " from thread #" << threadId;
  }

  // Following line will be logged once with every thread because of interval 1 
  LOG_EVERY_N(1, INFO) << "This interval log will be logged with every thread, this one is from thread #" << threadId;

  LOG_IF(strcmp(threadId, "2") == 0, INFO) << "This log is only for thread 2 and is ran by thread #" << threadId;

  // Register 5 vague loggers
  for (int i = 1; i <= 5; ++i) {
     std::stringstream ss;
     ss << "logger" << i;
     el::Logger* logger = easyloggingpp::Loggers::getLogger(ss.str());
     LOG(INFO) << "Registered logger [" << *logger << "]";
  }
  CLOG(INFO, "logger1") << "Logging using new logger";
  CLOG(INFO, "no-logger") << "THIS SHOULD SAY LOGGER NOT REGISTERED YET"; // << -- NOTE THIS!

  // Check for log counters positions
  for (int i = 1; i <= 50; ++i) {
     LOG_EVERY_N(2, INFO) << "Counter pos: " << ELPP_COUNTER_POS;
  }
  LOG_EVERY_N(2, INFO) << "Counter pos: " << ELPP_COUNTER_POS;
  return NULL;
}

int main(int argc, char** argv)
{
     _START_EASYLOGGINGPP(argc, argv);
     pthread_t thread1, thread2, thread3;
    /* Create independent threads each of which will execute function */
     pthread_create( &thread1, NULL, write, (void*)"1");
     pthread_create( &thread2, NULL, write, (void*)"2");
     pthread_create( &thread3, NULL, write, (void*)"3");

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 
     pthread_join(thread3, NULL); 

    exit(0);
}
