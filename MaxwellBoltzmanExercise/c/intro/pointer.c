#include <stdio.h>

main() {
  int foo = 22;
  int *bar = &foo;

  printf( "foo: %u\n", foo); 
  printf( "bar: %u\n", bar); 
  printf( "*bar: %u\n", *bar); 
  
  printf("------- changing foo through bar ---------\n");

  *bar = 333;
  printf( "foo: %u\n", foo); 
}
