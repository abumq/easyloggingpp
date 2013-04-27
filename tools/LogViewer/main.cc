#include "mainwindow.hh"
#include <QApplication>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    easyloggingpp::Loggers::setApplicationArguments(argc, argv);

    // Configure all loggers
    easyloggingpp::Configurations viewerConf("../LogViewer/log.conf");
    easyloggingpp::Loggers::reconfigureAllLoggers(viewerConf);

    LTRACE << "Starting LogViewer";

    easyloggingpp::Loggers::setFilename("/tmp/logs/tmp.log");
    LINFO << "This";
    easyloggingpp::Loggers::setFilename(easyloggingpp::Loggers::trivialLogger(), "/tmp/logs/tmptr.log");
    LINFO << "This 2";

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
    return a.exec();
}
