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

#include "../../easylogging++.h"

#include "mythread.h"


_INITIALIZE_EASYLOGGINGPP

FUNC(int, main, (int argc, char* argv[]))   // Using FUNC for performance tracking
_START_EASYLOGGINGPP(argc, argv)

bool runThreads = false;

_QUALIFIED_LOGGER.injectNewLogType("PerformanceLogger", "PERFORMANCE");
CINFO("PerformanceLogger") << "test";

for (int i = 0; i < 9; ++i) {
    LTRACE_EVERY_N(2) << "This is a trace " << i;
}

if (runThreads) {
    for (int i = 0; i < 3; ++i) {
        MyThread t(i);
        t.start();
        t.wait();
    }
}

SDEBUG << "This is security logger for debug";

BINFO << "This is a business logger";

RETURN(0);
END_FUNC(0)
