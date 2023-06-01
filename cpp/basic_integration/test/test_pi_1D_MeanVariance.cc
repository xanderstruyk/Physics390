#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_MeanVariance.hh"
#include "circle_functions.hh"

#ifdef PERF_TIME
#include <sys/time.h>
struct timeval t_start, t_stop;
#endif

int 
main(int argc, char** argv ) 
{ 
  
  unsigned seed = strtoul(argv[1],NULL,10);
  unsigned long ntrials = strtoul(argv[2],NULL,10);

  double params[] = { 1. }; // circle of radius 1.0
  double range_i = 0.;
  double range_f = 1.;
  srand(seed);

#ifdef PERF_TIME
  gettimeofday(&t_start,NULL);
#endif

  MeanVarianceResults results = 
    integrate_1D_MeanVariance(&circular_arc_2D, (double*)&params, range_i, range_f, ntrials);

#ifdef PERF_TIME
  gettimeofday(&t_stop,NULL);
  unsigned delta_t = 1e6*(t_stop.tv_sec - t_start.tv_sec) + (t_stop.tv_usec - t_start.tv_usec);
  fprintf( stderr, "Integral: %lf\t4xIntegral: %lf\terror: %lf\tNtrials: %lu\tusec: %lu\n", 
	   results.integral, 4*results.integral, 4*results.error, ntrials, delta_t);
#else
  fprintf( stderr, "Integral: %lf\t4xIntegral: %lf\terror: %lf\tNtrials: %lu\n", 
  results.integral, 4*results.integral, 4*results.error, ntrials);
#endif

}
