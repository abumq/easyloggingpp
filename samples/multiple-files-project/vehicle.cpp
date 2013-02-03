#include "vehicle.h"

#include "../../easylogging++-full.h"

Vehicle::Vehicle(const std::string& manufacturer,
                 const std::string& model,
                 int year) :
                    manufacturer(manufacturer),
                    model(model),
                    year(year) {
   std::cout << "VEHICLE: ----> Initialized? " << ::easyloggingpp::internal::loggerInitialized << "\n";
   INFO("Logged from vehicle");
   std::cout << "VEHICLE: ----> Initialized? " << ::easyloggingpp::internal::loggerInitialized << "\n";
}
