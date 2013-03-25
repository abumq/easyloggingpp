#ifndef CONTAINER_LOGS_H
#define CONTAINER_LOGS_H

#include "easylogging++.h"
#include "vehicle.h"

void vectorLogs() {
  std::vector<std::string> stringVec;
  std::vector<std::string*> stringPtrVec;
  std::vector<Vehicle> vehicleVec;
  std::vector<Vehicle*> vehiclePtrVec;
  stringVec.push_back("stringVec");
  stringPtrVec.push_back(new std::string("stringPtrVec"));
  vehicleVec.push_back(Vehicle("Honda", "Accord", 2013, "vehicleVec")); 
  vehiclePtrVec.push_back(new Vehicle("Honda", "Accord", 2013, "vehiclePtrVec"));
  LINFO << "stringVec : " << stringVec; 
  LINFO << "stringPtrVec : " << stringPtrVec; 
  LINFO << "vehicleVec : " << vehicleVec; 
  LINFO << "vehiclePtrVec : " << vehiclePtrVec; 
}

void listLogs() {
  std::list<std::string> stringList;
  std::list<std::string*> stringPtrList;
  std::list<Vehicle> vehicleList;
  std::list<Vehicle*> vehiclePtrList;
  stringList.push_back("stringList");
  stringPtrList.push_back(new std::string("stringPtrList"));
  vehicleList.push_back(Vehicle("Honda", "Accord", 2013, "vehicleList"));
  vehiclePtrList.push_back(new Vehicle("Honda", "Accord", 2013, "vehiclePtrList"));
  LINFO << "stringList : " << stringList;
  LINFO << "stringPtrList : " << stringPtrList;
  LINFO << "vehicleList : " << vehicleList;
  LINFO << "vehiclePtrList : " << vehiclePtrList;
}

void containerLogs() {
    vectorLogs();
    listLogs();
}

#endif
