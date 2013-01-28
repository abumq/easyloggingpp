/**
 * This file is part of EasyLogging++ samples
 * Demonstration of conditional logging
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(void) {

  INFO_IF(1 == 1, "1 is equal to 1");

  INFO_IF(1 > 2, "1 is greater than 2");

  DEBUG_IF(1 == 2, "1 is equal to 2");

  PERFORMANCE_IF((1 == 2) && (3 == 4), "Wow, 1 == 2 and 3 == 4");
  PERFORMANCE_IF((1 == 1) && (3 < 4), "Wow, 1 == 1 and 3 < 4");
  _END_EASYLOGGINGPP
  return 0;
}
