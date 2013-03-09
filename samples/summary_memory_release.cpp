/**
 * This sample demonstrate the summary usage of _END_EASYLOGGINGPP
 * on when is best to use this macro
 * see https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#summary-on-when-to-release-memory
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

MAIN(int argc, char** argv)

  LINFO << "This is start of logging...";
  LINFO << "Memory has already been allocated for logging";
  LINFO << "Now we are not using _END_EASYLOGGINGPP, yet memory will be released (it is defined in END_MAIN";
  LINFO << "But what if we exit here by conditional return?";
  if (true) {
    LINFO << "Note: MAIN_RETURN is different from RETURN because RETURN does not release memory to minimize delete calls";
    LINFO << "After following line all the memory is released!";
    RETURN_MAIN(0);
  }
END_MAIN(0)
