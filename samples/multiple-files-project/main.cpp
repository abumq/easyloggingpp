#include "vehicle.h"

#include "../../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {

   LINFO << "Logged from main";
   Vehicle vehicle("Toyota", "Corolla", 2013);
   return 0;
}
