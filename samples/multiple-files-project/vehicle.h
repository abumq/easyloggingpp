#ifndef _VEHICLE_H
#define _VEHICLE_H
#include <string>

class Vehicle {
  public:
    Vehicle(const std::string& manufacturer,
            const std::string& model,
            int year);
    std::string manufacturer;
    std::string model;
    int year; 
};
#endif
