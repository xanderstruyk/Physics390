#include <stdio.h>
#include "fooStruct.h"

main () {
  int i;
  MyFooStruct foo[] = { {2012,3.14159}, {2013, 2.91}};

  for(i=0; i<sizeof(foo)/sizeof(MyFooStruct); i++ ) {
  printf( "foo[%d].bar: %d\tfoo[%d].foobar: %f\n", 
	  i, foo[i].bar, i, foo[i].foobar );
  }
}
