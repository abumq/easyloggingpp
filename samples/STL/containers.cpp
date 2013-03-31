
#include "easylogging++.h"
#include <sstream>
_INITIALIZE_EASYLOGGINGPP

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

void otherContainerLogs() {
    std::map<int, std::string> map_;
    map_.insert (std::pair<int, std::string>(1, "one"));
    map_.insert (std::pair<int, std::string>(2, "two"));
    LINFO << "Map: " << map_;

    std::queue<int> queue_;
    queue_.push(77);
    queue_.push(16);
    LINFO << queue_;

    std::bitset<10> bitset_ (std::string("10110"));
    LINFO << bitset_;

    int pqueueArr_[]= { 10, 60, 50, 20 };
    std::priority_queue< int, std::vector<int>, std::greater<int> > pqueue (pqueueArr_, pqueueArr_ + 4);
    LINFO << pqueue;

    std::deque<int> mydeque_ (3,100);
    mydeque_.at(1) = 200;

    std::stack<int> stack_ (mydeque_);
    LINFO << stack_;

    std::stack<std::string*> stackStr_;
    stackStr_.push (new std::string("test"));
    LINFO << stackStr_;
    delete stackStr_.top();
}

int main(void) {
    vectorLogs();
    listLogs();
    otherContainerLogs();
    return 0;
}
