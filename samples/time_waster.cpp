#include "../easylogging++.h"

SUB(timeWaster,(int x))
    for (int i = 0; i < x; i++) {
      sleep(1);
    }
END_SUB

int main(void) {
   timeWaster(100);
   return 0;
}
