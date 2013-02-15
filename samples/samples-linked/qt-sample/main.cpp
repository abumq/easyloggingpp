/**
 * This file is part of EasyLogging++ samples
 * Demonstration of multithreaded application in C++ (Qt)
 * 
 * Compile this program using Qt
 *    qmake qt-sample.pro && make
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#include "../../../easylogging++.h"

#include "mythread.h"

_INITIALIZE_EASYLOGGINGPP


FUNC(int, main, (int argc, char** argv))   // Using FUNC for performance tracking
 _START_EASYLOGGINGPP(argc, argv)

 for (int i = 0; i < 10; ++i) { 
  MyThread t(i);
  t.start();
  t.wait();
 }

 _END_EASYLOGGINGPP
 RETURN(0);
END_FUNC(0)
