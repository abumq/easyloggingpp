#ifndef LIB2_HH
#define LIB2_HH

#include "lib2_global.hh"

#include "easylogging++.h"  // WE INCLUDE THIS IN HEADER FILE SO THAT USER CAN INITIALZE EASYLOGGING++ WITHOUT USING IT
                            // THIS IS INCLUDED IN HEADER TO MAKE SURE USERS NOT USING EASYLOGGING++ WILL HAVE ACCESS TO
                            // '_INITIALIZE_EASYLOGGINGPP' MACRO

class LIB2SHARED_EXPORT Lib2
{
public:
    Lib2();
};

#endif // LIB2_HH
