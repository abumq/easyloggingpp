
#include <QApplication>
#include "easylogging++.h"
#include "request_handler.h"
#include "getopt.h"

_INITIALIZE_EASYLOGGINGPP

std::string argsToString(int argc, char** argv);

const int kDefaultPort = 1592;

int main(int argc, char** argv) {

    CHECK(argc > 1) << "You must specify global configuration file.";
    QApplication a(argc, argv);
    _START_EASYLOGGINGPP(argc, argv);

    el::Loggers::configureFromGlobal("el-remote-logger-internal-logger.conf");
    std::string configurationFile;
    int port = kDefaultPort;
    int c;
    while ((c = getopt(argc, argv, const_cast<char*>("pc:"))) != EOF) {
        switch (c) {
        case 'p':
            port = atoi(currArg);
            LOG(INFO) << "Port: " << port;
            break;
        case 'c':
            configurationFile = std::string(currArg);
            if (configurationFile.empty()) {
                LOG(ERROR) << "Please select appropriate configuration file";
                exit(1);
            }
            LOG(INFO) << "Configuration file: " << configurationFile;
            break;
        default:
            break;
        }
    }

    LOG(INFO) << "Starting remote logger using parameters " << argsToString(argc, argv);

    RequestHandler requestHandler;
    requestHandler.start(port);

    return a.exec();
}

std::string argsToString(int argc, char** argv) {
    std::stringstream ss;
    for (int i = 1; i < argc; ++i)
        ss << "[" << argv[i] << "] ";
    return ss.str();
}
