#include <stdio.h>

int foo = 1;

main() { 
  int foo = 22;
  printf( "foo: %d\n", foo );
  { 
    int foo = 333;
    printf( "foo: %d\n", foo );
    {
      int foo = 444;
      printf( "foo: %d\n", foo );
    }
    printf( "foo: %d\n", foo );
  }
  printf( "foo: %d\n", foo );
}
