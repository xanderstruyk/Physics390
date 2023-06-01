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
  
  double range_i = 0.;
  double range_f = 20.;
  double lambda  = 0.5;  //stddev
  double params[] = {lambda};

  double x,z;
  for( int i=0; i<250000; i++ ) { 
    x = sample_pdf_rejection( &pdf_exponential, (double*)&params, range_i, range_f);
    z = cdf_exponential(x,params);
    printf( "i: %d val: %lf cdf(val): %lf\n", i, x, z);
  }

  fprintf(stderr, "count_reject: %d\n", count_reject);


}
