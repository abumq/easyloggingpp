#include <QApplication>

#include <lib1.hh>
#include <lib2.hh>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Lib1 l;
    Lib2 l2;
    LINFO << "This library implication initiated";
    
    return 0;
}
