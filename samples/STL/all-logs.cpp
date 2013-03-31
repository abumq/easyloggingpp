
#include "easylogging++.h" // Include header
_INITIALIZE_EASYLOGGINGPP

void trivialLogs(void) {

  LINFO << "info"; 
  LDEBUG << "debug"; 
  LERROR << "error"; 
  LWARNING << "warning"; 
  LFATAL << "fatal"; 
  LQA << "qa"; 
  LTRACE << "trace";
  LVERBOSE(1) << "verbose 1"; 
  LVERBOSE(2) << "verbose 2"; 
  LVERBOSE(3) << "verbose 3"; 
  LVERBOSE(4) << "verbose 4"; 
  LVERBOSE(5) << "verbose 5"; 
  LVERBOSE(6) << "verbose 6"; 
  LVERBOSE(7) << "verbose 7"; 
  LVERBOSE(8) << "verbose 8"; 
  LVERBOSE(9) << "verbose 9"; 

  LINFO_IF(true) << "conditional info";
  LDEBUG_IF(true) << "conditional debug";
  LERROR_IF(true) << "conditional error";
  LWARNING_IF(true) << "conditional warning";
  LFATAL_IF(true) << "conditional fatal";
  LQA_IF(true) << "conditiona qa";
  LTRACE_IF(true) << "conditional trace";
  LVERBOSE_IF(true, 1) << "conditional verbose 1";
  LVERBOSE_IF(true, 2) << "conditional verbose 2";
  LVERBOSE_IF(true, 3) << "conditional verbose 3";
  LVERBOSE_IF(true, 4) << "conditional verbose 4";
  LVERBOSE_IF(true, 5) << "conditional verbose 5";
  LVERBOSE_IF(true, 6) << "conditional verbose 6";
  LVERBOSE_IF(true, 7) << "conditional verbose 7";
  LVERBOSE_IF(true, 8) << "conditional verbose 8"; 
  LVERBOSE_IF(true, 9) << "conditional verbose 9";

  LINFO_EVERY_N(1) << "Info every 1";
  LWARNING_EVERY_N(1) << "Warning every 1";
  LDEBUG_EVERY_N(1) << "Debug every 1";
  LFATAL_EVERY_N(1) << "Fatal every 1";
  LQA_EVERY_N(1) << "QA every 1";
  LTRACE_EVERY_N(1) << "Trace every 1";
  LVERBOSE_EVERY_N(2, 1) << "Verbose every 1 level 2";

}

void businessLogs(void) {
  BINFO << "info"; 
  BDEBUG << "debug"; 
  BERROR << "error"; 
  BWARNING << "warning"; 
  BFATAL << "fatal"; 
  BQA << "qa"; 
  BTRACE << "trace"; 
  BVERBOSE(1) << "verbose 1"; 
  BVERBOSE(2) << "verbose 2"; 
  BVERBOSE(3) << "verbose 3"; 
  BVERBOSE(4) << "verbose 4"; 
  BVERBOSE(5) << "verbose 5"; 
  BVERBOSE(6) << "verbose 6"; 
  BVERBOSE(7) << "verbose 7"; 
  BVERBOSE(8) << "verbose 8"; 
  BVERBOSE(9) << "verbose 9"; 

  BINFO_IF(true) << "conditional info";
  BDEBUG_IF(true) << "conditional debug";
  BERROR_IF(true) << "conditional error";
  BWARNING_IF(true) << "conditional warning";
  BFATAL_IF(true) << "conditional fatal";
  BQA_IF(true) << "conditiona qa";
  BTRACE_IF(true) << "conditional trace";
  BVERBOSE_IF(true, 1) << "conditional verbose 1";
  BVERBOSE_IF(true, 2) << "conditional verbose 2";
  BVERBOSE_IF(true, 3) << "conditional verbose 3";
  BVERBOSE_IF(true, 4) << "conditional verbose 4";
  BVERBOSE_IF(true, 5) << "conditional verbose 5";
  BVERBOSE_IF(true, 6) << "conditional verbose 6";
  BVERBOSE_IF(true, 7) << "conditional verbose 7";
  BVERBOSE_IF(true, 8) << "conditional verbose 8"; 
  BVERBOSE_IF(true, 9) << "conditional verbose 9";

  BINFO_EVERY_N(1) << "Info every 1";
  BWARNING_EVERY_N(1) << "Warning every 1";
  BDEBUG_EVERY_N(1) << "Debug every 1";
  BFATAL_EVERY_N(1) << "Fatal every 1";
  BQA_EVERY_N(1) << "QA every 1";
  BTRACE_EVERY_N(1) << "Trace every 1";
  BVERBOSE_EVERY_N(2, 1) << "Verbose every 1 level 2";
}

void securityLogs(void) {
  SINFO << "info"; 
  SDEBUG << "debug"; 
  SERROR << "error"; 
  SWARNING << "warning"; 
  SFATAL << "fatal"; 
  SQA << "qa"; 
  STRACE << "trace"; 
  SVERBOSE(1) << "verbose 1"; 
  SVERBOSE(2) << "verbose 2"; 
  SVERBOSE(3) << "verbose 3"; 
  SVERBOSE(4) << "verbose 4"; 
  SVERBOSE(5) << "verbose 5"; 
  SVERBOSE(6) << "verbose 6"; 
  SVERBOSE(7) << "verbose 7"; 
  SVERBOSE(8) << "verbose 8"; 
  SVERBOSE(9) << "verbose 9"; 

  SINFO_IF(true) << "conditional info";
  SDEBUG_IF(true) << "conditional debug";
  SERROR_IF(true) << "conditional error";
  SWARNING_IF(true) << "conditional warning";
  SFATAL_IF(true) << "conditional fatal";
  SQA_IF(true) << "conditiona qa";
  STRACE_IF(true) << "conditional trace";
  SVERBOSE_IF(true, 1) << "conditional verbose 1";
  SVERBOSE_IF(true, 2) << "conditional verbose 2";
  SVERBOSE_IF(true, 3) << "conditional verbose 3";
  SVERBOSE_IF(true, 4) << "conditional verbose 4";
  SVERBOSE_IF(true, 5) << "conditional verbose 5";
  SVERBOSE_IF(true, 6) << "conditional verbose 6";
  SVERBOSE_IF(true, 7) << "conditional verbose 7";
  SVERBOSE_IF(true, 8) << "conditional verbose 8"; 
  SVERBOSE_IF(true, 9) << "conditional verbose 9";

  SINFO_EVERY_N(1) << "Info every 1";
  SWARNING_EVERY_N(1) << "Warning every 1";
  SDEBUG_EVERY_N(1) << "Debug every 1";
  SFATAL_EVERY_N(1) << "Fatal every 1";
  SQA_EVERY_N(1) << "QA every 1";
  STRACE_EVERY_N(1) << "Trace every 1";
  SVERBOSE_EVERY_N(2, 1) << "Verbose every 1 level 2";
}

void performanceLogs(void) {
  PINFO << "info"; 
  PDEBUG << "debug"; 
  PERROR << "error"; 
  PWARNING << "warning"; 
  PFATAL << "fatal"; 
  PQA << "qa"; 
  PTRACE << "trace"; 
  PVERBOSE(1) << "verbose 1"; 
  PVERBOSE(2) << "verbose 2"; 
  PVERBOSE(3) << "verbose 3"; 
  PVERBOSE(4) << "verbose 4"; 
  PVERBOSE(5) << "verbose 5"; 
  PVERBOSE(6) << "verbose 6"; 
  PVERBOSE(7) << "verbose 7"; 
  PVERBOSE(8) << "verbose 8"; 
  PVERBOSE(9) << "verbose 9"; 

  PINFO_IF(true) << "conditional info";
  PDEBUG_IF(true) << "conditional debug";
  PERROR_IF(true) << "conditional error";
  PWARNING_IF(true) << "conditional warning";
  PFATAL_IF(true) << "conditional fatal";
  PQA_IF(true) << "conditiona qa";
  PTRACE_IF(true) << "conditional trace";
  PVERBOSE_IF(true, 1) << "conditional verbose 1";
  PVERBOSE_IF(true, 2) << "conditional verbose 2";
  PVERBOSE_IF(true, 3) << "conditional verbose 3";
  PVERBOSE_IF(true, 4) << "conditional verbose 4";
  PVERBOSE_IF(true, 5) << "conditional verbose 5";
  PVERBOSE_IF(true, 6) << "conditional verbose 6";
  PVERBOSE_IF(true, 7) << "conditional verbose 7";
  PVERBOSE_IF(true, 8) << "conditional verbose 8"; 
  PVERBOSE_IF(true, 9) << "conditional verbose 9";

  PINFO_EVERY_N(1) << "Info every 1";
  PWARNING_EVERY_N(1) << "Warning every 1";
  PDEBUG_EVERY_N(1) << "Debug every 1";
  PFATAL_EVERY_N(1) << "Fatal every 1";
  PQA_EVERY_N(1) << "QA every 1";
  PTRACE_EVERY_N(1) << "Trace every 1";
  PVERBOSE_EVERY_N(2, 1) << "Verbose every 1 level 2";
}

int main(void) {
  trivialLogs();
  businessLogs();
  securityLogs();
  performanceLogs();
}
