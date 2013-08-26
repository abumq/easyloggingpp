 //
 // This file is part of Easylogging++ samples
 // MAKE_LOGGABLE sample
 //
 // Feature since: v9.12
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class Integer {
public:
    Integer(int i) : m_underlyingInt(i) {}
    Integer& operator=(const Integer& integer) { m_underlyingInt = integer.m_underlyingInt; return *this; }
    virtual ~Integer(void) { m_underlyingInt = -1; }
    int getInt(void) const { return m_underlyingInt; }
private:
    int m_underlyingInt;
};

// Lets say Integer class is in some third party library

// We use MAKE_LOGGABLE(class, instance, outputStream) to make it loggable
inline MAKE_LOGGABLE(Integer, integer, os) {
    os << integer.getInt();
    return os;
}


int main(void) {
    
    Integer count = 5;
    LOG(INFO) << count;
    return 0;
}
