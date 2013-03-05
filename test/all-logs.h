
#include "easylogging++.h" // Include header


void writeLogs(void) {

  LINFO << "info"; 
  LDEBUG << "debug"; 
  LERROR << "error"; 
  LWARNING << "warning"; 
  LFATAL << "fatal"; 
  LQA << "qa"; 
  LPERFORMANCE << "performance"; 
  LVERBOSE(1) << "verbose 1"; 
  LVERBOSE(2) << "verbose 2"; 
  LVERBOSE(3) << "verbose 3"; 
  LVERBOSE(4) << "verbose 4"; 
  LVERBOSE(5) << "verbose 5"; 
  LVERBOSE(6) << "verbose 6"; 
  LVERBOSE(7) << "verbose 7"; 
  LVERBOSE(8) << "verbose 8"; 
  LVERBOSE(9) << "verbose 9"; 


  LINFO_IF(true) << "info";
  LDEBUG_IF(true) << "debug";
  LERROR_IF(true) << "error";
  LWARNING_IF(true) << "warning";
  LFATAL_IF(true) << "fatal";
  LQA_IF(true) << "qa";
  LPERFORMANCE_IF(true) << "performance";
  LVERBOSE_IF(true, 1) << "verbose 1";
  LVERBOSE_IF(true, 2) << "verbose 2";
  LVERBOSE_IF(true, 3) << "verbose 3";
  LVERBOSE_IF(true, 4) << "verbose 4";
  LVERBOSE_IF(true, 5) << "verbose 5";
  LVERBOSE_IF(true, 6) << "verbose 6";
  LVERBOSE_IF(true, 7) << "verbose 7";
  LVERBOSE_IF(true, 8) << "verbose 8"; 
  LVERBOSE_IF(true, 9) << "verbose 9";

  LVERBOSE_EVERY_N(1, 2) << "verbose-2 every 1";
  // Skipping other interval logs...
}
