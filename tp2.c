#include <stdio.h>

int main() {
  #ifdef Darwin
    printf("Mac");
  #else
     printf("Linux");
  #endif
}
