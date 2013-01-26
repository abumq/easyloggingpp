/*
 * This file is part of EasyLogging++ samples
 * Demonstration of PERFORMANCE logging
 * @author mkhan3189
 */
#include "../easylogging++.h"
#include <unistd.h>
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
