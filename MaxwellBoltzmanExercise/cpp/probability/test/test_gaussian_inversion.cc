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
  
  double params[2] = {0.25, 0.5};
  double range_i = -5;
  double range_f = 5;

  double x,y,x_from_inv;
  for( int i=0; i<500000; i++ ) { 
    x = sample_pdf_rejection( &pdf_gaussian, (double*)&params, range_i, range_f);
    y = cdf_gaussian(x, (double*)&params);
    x_from_inv = sample_pdf_inversion( &inv_cdf_gaussian, (double*)&params, range_i, range_f);
    printf( "%d %lf %lf %lf\n", i, x, y, x_from_inv);
  }


}
