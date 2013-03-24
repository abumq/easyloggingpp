/**
 * This file is part of EasyLogging++ samples
 * Demonstration of multithreaded application in C++ (Qt)
 *
 * Compile this program using Qt
 *    qmake qt-sample.pro && make
 *
 * Revision: 1.1
 * @author mkhan3189
 */

#include "../../easylogging++.h"

#include "mythread.h"
#include <QVector>

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    _START_EASYLOGGINGPP(argc, argv)

    bool runThreads = true;

    if (runThreads) {
        for (int i = 1; i <= 1; ++i) {
            MyThread t(i);
            t.start();
            t.wait();
        }
    }

    QVector<QString> stringsptrList;
    stringsptrList.push_back (QString("Test"));
    stringsptrList.push_back (QString("Test 2"));
    LINFO << stringsptrList;

    LVERBOSE(1) << "Verbose 1 ...";

    SDEBUG << "This is security logger for debug";

    BINFO << "This is a business logger";

    return 0;

}
