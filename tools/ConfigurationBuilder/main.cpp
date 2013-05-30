#include "maindialog.h"
#include <QApplication>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    w.show();
    
    return a.exec();
}
