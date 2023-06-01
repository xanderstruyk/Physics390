#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "pdfs.hh"

// -----------------------------------------------------------------------------
// uniform PDF over a range
// -----------------------------------------------------------------------------
double 
pdf_uniform( double x, double* params ) 
// -----------------------------------------------------------------------------
{
  double ri = params[0];
  double rf = params[1];
  return 1./(rf-ri);
}



// -----------------------------------------------------------------------------
// exponential PDF
// -----------------------------------------------------------------------------
double 
pdf_exponential( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double lambda = params[0];
  return lambda*exp(-lambda*x);
}




// -----------------------------------------------------------------------------
// gaussian PDF
// -----------------------------------------------------------------------------
double 
pdf_gaussian( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double mu = params[0];
  double sigma = params[1];
  double arg_exp = -(x-mu)*(x-mu)/(2*sigma*sigma);
  double arg_amp = 1./(sigma*sqrt(2*M_PI));
  return arg_amp*exp(arg_exp);
}



// -----------------------------------------------------------------------------
// 1D double gaussian PDF
// -----------------------------------------------------------------------------
double 
pdf_double_gaussian( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double frac1 = params[0];
  double frac2 = 1. - frac1;
  double val = frac1*pdf_gaussian( x, params+1 )  + frac2*pdf_gaussian( x, params+3 ); 
  return val;
}



// -----------------------------------------------------------------------------
// student t PDF
// -----------------------------------------------------------------------------
double 
pdf_student( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double df = params[0];
  double numer = tgamma((df+1)/2);
  double denom = sqrt(df*M_PI)*tgamma(df/2);
  double term2 = 1. + x*x/df;
  double power = -((df+1)/2);
  double val = (numer/denom)*pow(term2,power);
  return val;
}


// -----------------------------------------------------------------------------
// gamma
// -----------------------------------------------------------------------------
double 
pdf_gamma( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double alpha = params[0];
  double beta  = params[1];
  double val = pow(x,alpha-1)*exp(-beta*x)*pow(beta,alpha)/tgamma(alpha);
  return val;
}



// -----------------------------------------------------------------------------
// maxwell-boltzman
// -----------------------------------------------------------------------------
double
pdf_maxwell_boltzmann( double x, double* params)
// -----------------------------------------------------------------------------
{
  if(x<0) {
    return 0;
  }
  double a = params[0];
  double val = sqrt(2./M_PI)*(x*x*exp(-x*x/(2.*a*a)))/(a*a*a);
  return val;
}
