// Sample based on http://www.boost.org/doc/libs/1_51_0/libs/numeric/ublas/doc/vector.htm

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main () {
    using namespace boost::numeric::ublas;
    vector<double> v (3);
    for (unsigned i = 0; i < v.size (); ++ i)
        v (i) = i;
    LOG(INFO) << v;
}
