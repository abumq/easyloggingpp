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
END_FUNC

int main(void) {
   int result = sum(1,2);
   INFO("Result is " << result);
   _END_EASYLOGGINGPP // Release memory from INFO(..)
   return 0;
}
