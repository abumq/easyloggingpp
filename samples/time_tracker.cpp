/**
 * This file is part of EasyLogging++ samples
 * Demonstration of PERFORMANCE logging and time tracking
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

FUNC(int,sum,(int x,int y))
    RETURN(x+y)
END_FUNC(0)

int main(void) {
   int result = sum(1,2);
   LINFO << "Result is " << result;
   return 0;
}
