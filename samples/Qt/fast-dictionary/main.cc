#include "mainwindow.hh"
#include <QApplication>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TIMED_BLOCK(app, "app");

int main(int argc, char *argv[])
{
    _START_EASYLOGGINGPP(argc, argv);
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime{%d/%M/%y} %log");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    for (int i = 1; i <= 10; ++i) {
        LOG_EVERY_N(2, INFO) << ELPP_COUNTER_POS;
    }
    return a.exec();
}
