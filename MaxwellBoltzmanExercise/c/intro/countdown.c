#include <stdio.h>

main() {

  int i,j;

  setbuf(stdout, NULL);

  i=5;
  while( i>0 ) { 
    j=i;
    if( i == 3 ) { i--; continue; }
    while( j>0 ) {
      printf( "%d ... ", j);
      sleep(1);
      j--;
    }
    printf("liftoff!\n");
    i--;
  }
}
