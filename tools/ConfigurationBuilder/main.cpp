#include "maindialog.h"
#include <QApplication>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace easyloggingpp;

int main(int argc, char *argv[])
{
    _START_EASYLOGGINGPP(argc, argv);
    Configurations c;
    c.setToDefault();
#if _ELPP_OS_UNIX
    c.parseFromFile("../ConfigurationBuilder/log-conf/unix.log");
#elif _ELPP_OS_WINDOWS
    c.parseFromFile("..\\ConfigurationBuilder\\log-conf\\win.log");
#endif // _ELPP_OS_UNIX
    Loggers::reconfigureAllLoggers(c);

    LOG(TRACE) << "Starting application using arguments [" << argv[0] << "]";

    QApplication a(argc, argv);
    MainDialog w;
    w.show();
    int result = a.exec();
    LOG(TRACE) << "Exiting application";
    return result;
}
