#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv ) {

  if ( argc > 1 ) {
    unsigned myseed = strtoul(argv[1],NULL,10);
    srand(myseed);
  }

  for( int i=0; i<5; i++ )  {
    double rval = ((double)rand())/RAND_MAX;
    printf("i: %d\trval: %lf\n", i, rval );
  }
}
