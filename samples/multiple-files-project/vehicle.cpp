#include "vehicle.h"

#include "../../easylogging++.h"

Vehicle::Vehicle(const std::string& manufacturer,
                 const std::string& model,
                 int year) :
                    manufacturer(manufacturer),
                    model(model),
                    year(year) {
   LINFO << "Logged from vehicle";
}
