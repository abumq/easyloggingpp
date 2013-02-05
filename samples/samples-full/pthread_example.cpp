/**
 * This file is part of EasyLogging++ samples
 * Demonstration of multithreaded application using pthread and C++0X
 * 
 * Compile this program using (if using gcc-c++):
 *     g++ -o bin/multithread_test.cpp.bin multithread_test.cpp -std=c++0x -pthread
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#include <pthread.h>
#include <string>
#include "../../easylogging++-full.h"

_INITIALIZE_EASYLOGGINGPP


void *write(void* thrId){
  char* threadId = (char*)thrId;
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

  INFO_IF(threadId == "2", "This log is only for thread 2 and is ran by thread #" << threadId);
}

int main(void)
{
     pthread_t thread1, thread2, thread3;
     int r1, r2, r3;
    /* Create independent threads each of which will execute function */

     r1 = pthread_create( &thread1, NULL, write, (void*)"1");
     r2 = pthread_create( &thread2, NULL, write, (void*)"2");
     r3 = pthread_create( &thread3, NULL, write, (void*)"3");

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 
     pthread_join(thread3, NULL); 

    exit(0);
}
