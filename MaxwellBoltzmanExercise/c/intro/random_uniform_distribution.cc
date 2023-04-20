#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv ) {

  if ( argc != 3  ) {
    fprintf(stderr, "Error: arguments <seed> <max iterations>\n");
    return -1;
  }

  // set the seed
  unsigned myseed = strtoul(argv[1],NULL,10);
  srand(myseed);

  // set the max iteration
  unsigned max_iteration = strtoul(argv[2],NULL,10);

  for( int i=0; i<max_iteration; i++ )  {
    double rval = ((double)rand())/RAND_MAX;
    printf("i: %d\trval: %lf\n", i, rval );
  }

}
