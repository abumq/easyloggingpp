/*
 * A very basic usage of EasyLogging++
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h" // Include header

_INITIALIZE_EASYLOGGINGPP     // Initialize - Needed only once in your application

int main(int argc, char** argv) {
  _START_EASYLOGGINGPP(argc, argv);

  LINFO << "info"; 
  LDEBUG << "debug"; 
  LERROR << "error"; 
  LWARNING << "warning"; 
  LFATAL << "fatal"; 
  LQA << "qa"; 
  LPERFORMANCE << "performance"; 
  LVERBOSE(1) << "verbose 1"; 
  LVERBOSE(2) << "verbose 2"; 


  _END_EASYLOGGINGPP          // Release all memory - Needed only once in your application
}
