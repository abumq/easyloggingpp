#include "easylogging++.h"
#include <array>

_INITIALIZE_EASYLOGGINGPP

int main (void) {

  std::array<int, 5> arr;
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 4;
  arr[4] = 5;

  LOG(INFO) << arr;

  return 0;
}
