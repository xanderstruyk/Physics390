#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_MeanVariance.hh"
#include "circle_functions.hh"


int 
main(int argc, char** argv ) 
{ 
  
  unsigned seed = strtoul(argv[1],NULL,10);
  unsigned long ntrials = strtoul(argv[2],NULL,10);

  double params[] = { 1. }; // circle of radius 1.0
  srand(seed);

  double area = integrate_1D_MeanVariance(&circular_arc_2D, (double*)&params, 0., 1., ntrials );

  fprintf( stderr, "Area: %lf\t4xArea: %lf\terror: %lf\tNtrials: %lu\n", 
	   area, 4*area, 4*variance(ntrials), ntrials);
}
