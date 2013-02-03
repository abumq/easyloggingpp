/**
 * This file is part of EasyLogging++ samples
 * Demonstration of PERFORMANCE logging
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../../easylogging++-full.h"
#include <unistd.h>

_INITIALIZE_EASYLOGGINGPP

SUB(timeWaster,(int x))
    for (int i = 0; i < x; i++) {
      sleep(1);
    }
END_SUB

int main(void) {
   INFO("I will now waste 5 seconds");
   timeWaster(5);
   _END_EASYLOGGINGPP
   return 0;
}
