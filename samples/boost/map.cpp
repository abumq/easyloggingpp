#include <boost/container/map.hpp>

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {
   boost::container::map<int, float> m;
   m[0] =  1.0f;
   m[5] =  3.3f;
   LOG(INFO) << m;
}
