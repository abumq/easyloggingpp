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

    LOG(TRACE) << "Starting LogViewer";

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
    return a.exec();
}
