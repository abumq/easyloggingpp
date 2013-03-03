/**
 * This file is part of EasyLogging++ samples
 * Demonstration of quality assurance logging
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  LINFO << "This is demo for QA logs";
  LQA << "I will only be printed if _QUALITY_ASSURANCE is defined";
  _END_EASYLOGGINGPP
  return 0;
}
