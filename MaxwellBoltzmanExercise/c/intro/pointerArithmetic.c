#include <stdio.h>
#define ARRAY_SIZE 4
int foo[ARRAY_SIZE] = {1, 22, 333, 444};

main() {
  int *bar = foo;
  while( bar != foo+ARRAY_SIZE ) { 
    printf("*bar: %d\n", *bar);
    bar++;
  }
}
