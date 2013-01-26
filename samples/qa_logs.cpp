/*
 * This file is part of EasyLogging++ samples
 * Demonstration of quality assurance logging
 * @author mkhan3189
 */
#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  INFO("This is demo for QA logs");
  QA("I will only be printed if _QUALITY_ASSURANCE is defined");
  _END_EASYLOGGINGPP
  return 0;
}
