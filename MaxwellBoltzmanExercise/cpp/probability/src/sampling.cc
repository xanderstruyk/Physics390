#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "probability.hh"


// -----------------------------------------------------------------------------
// sample from a PDF function.  Function should be normalized
// -----------------------------------------------------------------------------
double 
sample_pdf_rejection( double (*function)(double,double*), 
		      double* params,
		      double range_i, double range_f ) 
// -----------------------------------------------------------------------------
{
  double x,y;
  while( 1 ) {  
    x = range_i + rand()*((range_f-range_i)/RAND_MAX);
    y = (double)rand()/RAND_MAX; // [0,1]
    // count_reject++;
    if( y <= (*function)(x,params) ) break; 
  }
  return x;
}


// -----------------------------------------------------------------------------
// obtain a sample from a PDF by inverting the CDF
// -----------------------------------------------------------------------------
double 
sample_pdf_inversion( double (*invCDF)(double,double*), 
		      double* params,
		      double range_i, double range_f ) 
// -----------------------------------------------------------------------------
{
  double u = (double)rand()/RAND_MAX;
  return invCDF(u,params);
}


// -----------------------------------------------------------------------------
// sample from a PDF function.  Function should be normalized
// -----------------------------------------------------------------------------
double 
sample_pdf_metropolis( double (*function)(double,double*), 
		       double* params,
		       double range_i, double range_f,
		       double x) 
// -----------------------------------------------------------------------------
{

  // gaussian proposal density
  double g_params[] = {x,1.}; 
  //double x_prime = sample_pdf_rejection(&pdf_gaussian,(double*)&g_params,range_i,range_f);
  double x_prime = sample_pdf_inversion(&inv_cdf_gaussian,(double*)&g_params,range_i,range_f);

  // acceptance ratio
  double alpha = (*function)(x_prime,params)/(*function)(x,params);
  double y = (double)rand()/RAND_MAX; // [0,1]
  //count_metro++;

  if ( y <= alpha )
    return x_prime;
  return x;
}



/*
// -----------------------------------------------------------------------------
// sample from a 2D PDF function.  Function should be normalized
// -----------------------------------------------------------------------------
pair<double,double>
sample_2D_pdf( double (*function)(double,double,double*), 
	       double* params,
	       double range_i, double range_f ) 
// -----------------------------------------------------------------------------
{
  double x,y,z;
  while( 1 ) {  
    x = range_i + rand()*((range_f-range_i)/RAND_MAX);
    y = range_i + rand()*((range_f-range_i)/RAND_MAX);
    z = (double)rand()/RAND_MAX; // [0,1]
    if( z <= (*function)(x,y,params) ) break; 
  }
  return pair<double,double>(x,y);
}
*/
