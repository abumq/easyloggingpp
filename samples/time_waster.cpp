#include "../easylogging++.h"

SUB(timeWaster,(int x,int y))
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
         //do nothing just waste time
      }
    }
END_SUB

int main(void) {
   timeWaster(10000000,100);
   return 0;
}
