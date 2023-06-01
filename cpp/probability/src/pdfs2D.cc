#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "pdfs2D.hh"

// -----------------------------------------------------------------------------
double 
pdf_2D_gaussian( double x, double y, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double mux = params[0];
  double muy = params[1];
  double sigmax = params[2];
  double sigmay = params[3];
  double rho = params[4];

  double norm_term = 1./(2*M_PI*sigmax*sigmay*sqrt(1.-(rho*rho)));

  double xdiff = (x-mux)/sigmax;
  double ydiff = (y-muy)/sigmay;
  double exp_arg  = (-1./(2*(1.-(rho*rho))))*(xdiff*xdiff - 2*rho*xdiff*ydiff + ydiff*ydiff);
  return norm_term*exp(exp_arg);
}



// -----------------------------------------------------------------------------
// gaussian PDF
// -----------------------------------------------------------------------------
double 
pdf_double_2D_gaussian( double x, double y, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double frac1 = params[0];
  double frac2 = 1. - frac1;
  double ret = frac1*pdf_2D_gaussian( x, y, params+1 )  + frac2*pdf_2D_gaussian( x, y, params+6 );
  return ret; 
}

// -----------------------------------------------------------------------------
// uniform PDF over a range
// -----------------------------------------------------------------------------
double 
pdf_2D_uniform( double x, double y, double* params ) 
// -----------------------------------------------------------------------------
{
  double ri = params[0];
  double rf = params[1];
  return (1./(rf-ri))*(1./(rf-ri));
}

