/**
 * This file is part of EasyLogging++ samples
 * Demonstration of logging your own class
 *
 * Revision: 1.0
 * @author mkhan3189
 */
#include <sstream>
#include <vector>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class Vehicle {
    public:
        Vehicle(const std::string& make_, const std::string& model_, unsigned int year_ = 2013,
                    const std::string& version_ = "") :
            make_(make_), model_(model_), year_(year_), version_(version_) {}

        friend std::ostream& operator<<(std::ostream& w, const Vehicle& v);
    private:
        std::string make_;
        std::string model_;
        int year_;
        std::string version_;
};

std::ostream& operator<<(std::ostream& w, const Vehicle& v) {
    w << "(" << v.make_ << " " << v.model_ << " " << v.year_ << (v.version_.size() > 0 ? " " : "") << v.version_ << ")";
    return w;
}

int main(void) {

    Vehicle vehicle1("Land Rover", "Discovery 4", 2013, "TD HSE");
    Vehicle vehicle2("Honda", "Accord", 2013, "V6 Luxury");
    Vehicle vehicle3("Honda", "Accord", 2010);

    BINFO << "We have vehicles available: " << vehicle1  << " " << vehicle2 << " " << vehicle3;

    std::vector<Vehicle*> vehicles;
    vehicles.push_back(&vehicle1);
    vehicles.push_back(&vehicle2);
    vehicles.push_back(&vehicle3);
    LINFO << "Now printing whole vector of pointers";
    LINFO << vehicles;

    std::vector<Vehicle> vehiclesStack;
    vehiclesStack.push_back(vehicle1);
    vehiclesStack.push_back(vehicle2);
    vehiclesStack.push_back(vehicle3);
    LINFO << "Now printing whole vector of classes";
    LINFO << vehiclesStack;


    return 0;
}

