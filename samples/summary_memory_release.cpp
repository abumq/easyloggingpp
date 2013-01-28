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

  INFO("This is start of logging...");
  INFO("Memory has already been allocated for logging");
  INFO("Now we are not using _END_EASYLOGGINGPP, yet memory will be released (it is defined in END_MAIN");
  INFO("But what if we exit here by conditional return?");
  if (true) {
    INFO("Note: MAIN_RETURN is different from RETURN because RETURN does not release memory to minimize delete calls");
    INFO("After following line all the memory is released!");
    RETURN_MAIN(0);
  }
  //If you log anything here afterwards,memory will be re allocated and will be deleted by END_MAIN
  // provided the above condition was not reached
END_MAIN
