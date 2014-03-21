#include "mylib.hpp"
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int MyLib::runOnceHelper = runOnce();

int MyLib::runOnce() {
    el::Loggers::getLogger("mylib");
}

MyLib::MyLib() {
    LOG(INFO) << "---MyLib Constructor () ---";
}

MyLib::MyLib(int argc, char** argv) {
    _START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "---MyLib Constructor(int, char**) ---";
}

MyLib::~MyLib() {
    LOG(INFO) << "---MyLib Destructor---";
}


void MyLib::event(int a) {
    VLOG(1) << "MyLib::event start";
    LOG(INFO) << "Processing event [" << a << "]";
    VLOG(1) << "MyLib::event end";
}

el::base::type::StoragePointer MyLib::getEasyloggingStorage() {
        return el::Helpers::storage();
}
