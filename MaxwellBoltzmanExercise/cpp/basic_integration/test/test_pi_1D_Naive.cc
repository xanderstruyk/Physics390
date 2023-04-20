#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_Naive.hh"
#include "circle_functions.hh"



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
  double params[] = { 1. }; // circle of radius 1.0
  srand(seed);

  double area;
  if( verbose ) area=integrate_1D_Naive(&circular_arc_2D, (double*)&params, 0., 1., ntrials, &points);
  else          area=integrate_1D_Naive(&circular_arc_2D, (double*)&params, 0., 1., ntrials );


  // with estimated error
  //fprintf( stderr, "Area: %lf\t4xArea: %lf\terror: %lf\tNtrials: %lu\n", 
  //area, 4*area, 4*binomial_error(ntrials, area*ntrials), ntrials);

  // with true error
  fprintf( stderr, "Area: %lf\t4xArea: %lf\terror: %lf\tNtrials: %lu\n", 
	   area, 4*area, 4*binomial_error(ntrials, (M_PI/4)*ntrials), ntrials);

}
