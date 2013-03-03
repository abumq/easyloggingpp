#include "vehicle.h"

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {

   std::cout << "MAIN ----> Initialized? " << ::easyloggingpp::internal::loggerInitialized << "\n";
   LINFO << "Logged from main";
   std::cout << "MAIN ----> Initialized? " << ::easyloggingpp::internal::loggerInitialized << "\n";
   Vehicle vehicle("Toyota", "Corolla", 2013);
   _END_EASYLOGGINGPP
   return 0;
}
