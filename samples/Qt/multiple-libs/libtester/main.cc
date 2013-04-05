#include <QApplication>

#include <lib1.hh>
#include <lib2.hh>

_INITIALIZE_EASYLOGGINGPP   // Actually using from lib1.hh or lib2.hh
                            // To be precise its lib1.hh (since it included easylogging++ first)
                            // We can also include easylogging++.h here and wont cause any hard but
                            // I havent done it to demonstrate inclusion of header in lib's headers

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Lib1 l;
    Lib2 l2;
    LINFO << "This library implication initiated";
    
    return 0;
}
