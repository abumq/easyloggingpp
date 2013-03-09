/*
 * A very basic usage of EasyLogging++
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h" // Include header

_INITIALIZE_EASYLOGGINGPP     // Initialize - Needed only once in your application

int main(int argc, char** argv) {
  LINFO << "This is first log!"; // Write
}
