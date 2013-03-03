#include "vehicle.h"

#include "../../easylogging++.h"

Vehicle::Vehicle(const std::string& manufacturer,
                 const std::string& model,
                 int year) :
                    manufacturer(manufacturer),
                    model(model),
                    year(year) {
   std::cout << "VEHICLE: ----> Initialized? " << ::easyloggingpp::internal::loggerInitialized << "\n";
   LINFO << "Logged from vehicle";
   std::cout << "VEHICLE: ----> Initialized? " << ::easyloggingpp::internal::loggerInitialized << "\n";
}
