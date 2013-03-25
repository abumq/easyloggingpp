#ifndef VEHICLE_H
#define VEHICLE_H

#include <sstream>

class Vehicle {
    public:
        Vehicle(const std::string& make_, const std::string& model_, unsigned int year_ = 2013,
                    const std::string& version_ = "") :
            make_(make_), model_(model_), year_(year_), version_(version_) {}

        std::string toString(void) const {
            std::stringstream ss;
            ss << "[" << make_ << " " << model_ << " " << year_ << (version_.size() > 0 ? " " : "") << version_ << "]";
            return ss.str();
        }

    private:
        std::string make_;
        std::string model_;
        int year_;
        std::string version_;
};
#endif
