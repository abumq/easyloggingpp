#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int, const char** ) {
    LOG(INFO) << "世界，你好";
    return 0;
}
