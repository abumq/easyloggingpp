#include "lib1.hh"
#include "easylogging++.h"

//  ** DO NOT USE _INITIALIZE_EASYLOGGINGPP IN LIBRARIES / APIs
//  ** COMMENT THEM OUT WHEN YOU HAVE FINISHED TESTING **

Lib1::Lib1()
{
    LINFO << "Lib1 initialized";
}
