#include <stdio.h>
#include "fooStruct.h"

main () {
  MyFooStruct foo;
  foo.bar = 2013;
  foo.foobar = 3.14159;
  printf( "foo.bar: %d\n", foo.bar );
  printf( "foo.foobar: %f\n", foo.foobar );
}
