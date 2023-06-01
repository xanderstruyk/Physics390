#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <boost/math/special_functions/erf.hpp>
#include "cdfs.hh"


// -----------------------------------------------------------------------------
// exponential CDF
// -----------------------------------------------------------------------------
double 
cdf_exponential( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double lambda = params[0];
  return 1. - exp(-lambda*x);
}


// -----------------------------------------------------------------------------
// exponential inverse CDF
// -----------------------------------------------------------------------------
double 
inv_cdf_exponential( double y, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double lambda = params[0];
  return -log(1-y)/lambda;
}


// -----------------------------------------------------------------------------
// gaussian CDF
// -----------------------------------------------------------------------------
double 
cdf_gaussian( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double mu = params[0];
  double sigma = params[1];
  double arg_erf = (x-mu)/(sqrt(2)*sigma);
  return 0.5*( 1. + erf(arg_erf));
}

// -----------------------------------------------------------------------------
// gaussian inverse CDF
// -----------------------------------------------------------------------------
double 
inv_cdf_gaussian( double y, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double mu = params[0];
  double sigma = params[1];
  double arg_erf_inv = 2*y-1.;
  return sigma*sqrt(2)*boost::math::erf_inv(arg_erf_inv) + mu;
}

// -----------------------------------------------------------------------------
// maxwell-boltzman CDF
// -----------------------------------------------------------------------------
double
cdf_maxwell_boltzmann( double y, double* params)
// -----------------------------------------------------------------------------
{
  double a = params[0];
  double val = erf(y/(sqrt(2.)*a))-sqrt(2./M_PI)*y*exp(-y*y/(2.*a*a))/a;
  return val;
}

