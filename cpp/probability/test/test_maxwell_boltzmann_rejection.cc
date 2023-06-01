#include <stdio.h>
#include <stdlib.h>
#include "probability.hh"

int main(int argc, char** argv) {

  if(argc != 3) {
    fprintf(stderr, "Error : need a single argument (random seet) and a val for a\n");
    return -1;
  }

  char* eptr;

  srand(strtoul(argv[1],NULL,10));
  const double a = strtod(argv[2], &eptr);
  const double range_i = 0;
  const double range_f = 20;
  double params[1] = {a};

  double x;
  for( int i=0; i<250000; i++) {
    x = sample_pdf_rejection( &pdf_maxwell_boltzmann, (double*)&params, range_i, range_f);
    printf( "i: %d val: %lf\n",i,x);
  }
  return 0;
}
