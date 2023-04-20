#include <stdio.h>

int main( int argc, char** argv) { 
  int i=0;

  printf( "argc: %d\n", argc );
  printf("--------------\n");
  for( ; i<argc; i++ ) { 
    printf( "argc[%d]: %s\n", i, argv[i]);
  }
}
