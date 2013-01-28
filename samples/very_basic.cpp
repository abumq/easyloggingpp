/*
 * A very basic usage of EasyLogging++
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h" // Include header

_INITIALIZE_EASYLOGGINGPP     // Initialize

int main(int argc, char** argv) {
  INFO("This is first log!"); // Write
  _END_EASYLOGGINGPP          // Release all memory
}
