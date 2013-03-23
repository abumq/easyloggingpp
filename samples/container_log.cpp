/**
 * This file is part of EasyLogging++ samples
 * Demonstration of container logging using EasyLogging++
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include <vector>
#include <list>
#include "../easylogging++.h"
#if defined(QT_CORE_LIB) && !defined(_DO_NOT_SUPPORT_CPP_LIBRARIES)
#    include <QString>
#endif

_INITIALIZE_EASYLOGGINGPP

int main(void) {
    std::vector<std::string> v = { "string 1", "string 2" };
    LINFO << "Now I will print std::vector<std::string> and values are --> " << v << " <-- This is end of log";

    std::vector<int> intVec_ = { 1, 2, 3, 4, 5 };
    BINFO << "Business info log for int container " << intVec_;

    std::vector<bool> boolVec_ = { true, false, true, true, true, false };
    SWARNING << "Security warning log for bool container " << boolVec_;

#if defined(QT_CORE_LIB) && !defined(_DO_NOT_SUPPORT_CPP_LIBRARIES)
    std::vector<QString> qstringVec_;
    qstringVec_.push_back(QString("QString 1"));
    qstringVec_.push_back(QString("QString 2"));
    LINFO << "This will print vector of QString " << qstringVec_;
#endif
    std::list<std::string> list_;
    list_.push_back("String 1");
    list_.push_back("String 2");
    LINFO << "This will print std::list of std::string " << list_;

    return 0; 
}
