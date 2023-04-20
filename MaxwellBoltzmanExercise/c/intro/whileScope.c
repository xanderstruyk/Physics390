#include <stdio.h>

int foo = 1000;
int bar = 0;

main() { 
  int foo = 3;
  for( ; foo > 0; foo-- ) { 
    int bar = -999 + foo;
    printf( "foo: %d\tbar: %d\n", foo, bar );
  }
}
