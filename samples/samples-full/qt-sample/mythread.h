#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "../../../easylogging++-full.h"

class MyThread : public QThread {
  Q_OBJECT
  public:
    MyThread(int id) : threadId(id) {}
  private:
    int threadId;
  protected:
    void run() {
      INFO("Writing from a thread " << threadId);

      VERBOSE(2, "This is verbose level 2 logging from thread #" << threadId);

      // Following line will be logged only once from second running thread (which every runs second into 
      // this line because of interval 2)
      WARNING_EVERY_N(2, "This will be logged only once from thread who every reaches this line first. Currently running from thread #" << threadId);

      // Following line will be logged once with every thread because of interval 1 
      INFO_EVERY_N(1, "This interval log will be logged with every thread, this one is from thread #" << threadId);

      INFO_IF(threadId == 2, "This log is only for thread 2 and is ran by thread #" << threadId);
    }
};
#endif
