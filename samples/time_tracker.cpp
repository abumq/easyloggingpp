/*
 * This file is part of EasyLogging++ samples
 * Demonstration of PERFORMANCE logging and time tracking
 * @author mkhan3189
 */
#include "../easylogging++.h"

FUNC(int,sum,(int x,int y))
    RETURN(x+y)
END_FUNC

int main(void) {
   int result = sum(1,2);
   INFO("Result is " << result);
   return 0;
}
