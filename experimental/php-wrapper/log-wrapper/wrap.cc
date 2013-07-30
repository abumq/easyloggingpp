#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void configure() {
  easyloggingpp::Loggers::setFilename("log/easy.log");
}

int main(int argc, char** argv) {
  if (argc < 3) return 1;
  configure();
  char* level = argv[1];
  std::string levelStr = std::string(level);
  if (levelStr == "INFO") LOG(INFO) << argv[2];
  else if (levelStr == "ERROR") LOG(ERROR) << argv[2];
  else if (levelStr == "WARNING") LOG(WARNING) << argv[2];
  else if (levelStr == "DEBUG") LOG(DEBUG) << argv[2];
  else std::cout << "COULD NOT LOG " << levelStr;
  return 0;
}
