#include <stdio.h>

main() {

  int i,j;

  /*
  char a[4] = {'a','b','c', '\0'};
  char b[3] = "abc";
  printf( "a: %s :: b: %s\n", a, b);
  */
		      
  for( i=5; i>0; i-- ) {
    if( i == 3 ) { continue; }
    for( j=i; j>0; j-- ) {
      printf( "%d ... ", j);
    }
    printf("liftoff!\n");
  }
}
