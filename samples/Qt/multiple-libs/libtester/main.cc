#include <QApplication>

#include "easylogging++.h"
#include <lib1.hh>
#include <lib2.hh>

_INITIALIZE_EASYLOGGINGPP


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Lib1 l;
   Lib2 l2;
    LINFO << "This library initiated";
    
    return 0;
}
