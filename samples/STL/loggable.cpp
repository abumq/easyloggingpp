 //
 // This file is part of Easylogging++ samples
 // el::Loggable sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class MyClass : public el::Loggable {
public:
    MyClass(const char* name) : m_name(name) {}

    virtual void log(std::ostream& os) const {
        os << m_name;
    }


private:
    const char* m_name;
};

int main(void) {
    MyClass c("c"); 
    MyClass c2("c2"); 
    LOG(INFO) << "I am " << c << "; and I am " << c2;
    return 0;
}
