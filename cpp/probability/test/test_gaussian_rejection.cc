#include <stdio.h>
#include <stdlib.h>
#include "probability.hh"

unsigned count_reject=0, count_metro=0;

int main(int argc, char** argv) {

  if( argc != 2 ) {
    fprintf(stderr,"Error : need a single argument (random seed)\n");
    return -1;
  }

  srand(strtoul(argv[1],NULL,10));
  
  double range_i = -5.;
  double range_f =  5.;
  double mu      = 0.25; //mean
  double sigma   = 1.5;  //stddev
  double params[2] = {mu, sigma};

  double x;
  for( int i=0; i<250000; i++ ) { 
    x = sample_pdf_rejection( &pdf_gaussian, (double*)&params, range_i, range_f);
    printf( "i: %d val: %lf\n", i, x);
  }

  fprintf(stderr, "count_reject: %d\n", count_reject);


}
