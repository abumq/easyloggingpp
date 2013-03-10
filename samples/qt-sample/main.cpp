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

    if (runThreads) {
        for (int i = 1; i <= 1; ++i) {
            MyThread t(i);
            t.start();
            t.wait();
        }
    }

LINFO << easyloggingpp::VersionInfo::licence();

    LVERBOSE(1) << "Verbose ...";

    SDEBUG << "This is security logger for debug";

    BINFO << "This is a business logger";

    PTRACE << "Taking too long? No I dont think so";


  //  LINFO << OSUtilities::getBashOutput ("asdfasdf");

    RETURN(0);
    //_END_EASYLOGGINGPP

END_FUNC(0)
