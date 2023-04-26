#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "circle_functions.hh"
#include "integration_Naive.hh"
#include "pdfs.hh"


int 
main(int argc, char** argv ) 
{ 

  unsigned seed = strtoul(argv[1],NULL,10);
  unsigned long ntrials = strtoul(argv[2],NULL,10);
  unsigned verbose=0;
  if( argc > 3 ) { 
    verbose = 1;
  }

  Points2D points;
  double params[] = { 1. }; // a=1.0
  srand(seed);

  double area;
  if( verbose ) area=integrate_1D_Naive(&pdf_maxwell_boltzmann, (double*)&params, 0., 5., ntrials, &points);
  else          area=integrate_1D_Naive(&pdf_maxwell_boltzmann, (double*)&params, 0., 5., ntrials );


  // with estimated error
  //fprintf( stderr, "Area: %lf\t4xArea: %lf\terror: %lf\tNtrials: %lu\n", 
  //area, 4*area, 4*binomial_error(ntrials, area*ntrials), ntrials);

  // with true error
  fprintf( stderr, "Area: %lf\t4xArea: %lf\terror: %lf\tNtrials: %lu\n", 
	   area, area, binomial_error(ntrials, ntrials/25.), ntrials);

}
