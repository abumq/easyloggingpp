#ifndef LIB1_HH
#define LIB1_HH

#include "easylogging++.h"  // WE INCLUDE THIS IN HEADER FILE SO THAT USER CAN INITIALZE EASYLOGGING++ WITHOUT USING IT
                            // THIS IS INCLUDED IN HEADER TO MAKE SURE USERS NOT USING EASYLOGGING++ WILL HAVE ACCESS TO
                            // '_INITIALIZE_EASYLOGGINGPP' MACRO
#include "lib1_global.hh"

class LIB1SHARED_EXPORT Lib1
{
public:
    Lib1();
};

#endif // LIB1_HH
