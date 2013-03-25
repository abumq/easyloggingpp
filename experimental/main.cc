#include "easylogging++.h"
#include "normal-logs.h"
#include "container-logs.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
    normalLogs();
    containerLogs();
    return 0;
}
