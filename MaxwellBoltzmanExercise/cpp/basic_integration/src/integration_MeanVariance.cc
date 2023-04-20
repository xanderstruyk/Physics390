#include <stdlib.h>
#include <stdio.h>
#include "integration_MeanVariance.hh"


//------------------------------------------------------------------------------
//
// Integrate by taking the average function value within a sample of many trials
//
//------------------------------------------------------------------------------
double
integrate_1D_MeanVariance( double (*function)(double, double*), 
			   double* params, 
			   double range_i, double range_f, 
			   unsigned long ntrials ) 
//------------------------------------------------------------------------------
{

  double result=0;

  for( int i=0; i<ntrials; i++ ) {
    double x = (range_f-range_i)*rand()/RAND_MAX;
    double y = function(x,params);
    result += y/ntrials;
  } // trials

  return result;
}


