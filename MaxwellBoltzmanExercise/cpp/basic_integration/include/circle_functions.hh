#ifndef CIRCLE_FUNCTIONS
#define CIRCLE_FUNCTIONS

#include <math.h>

//------------------------------------------------------------------------------
//
// The area under which is pi/4
//
//------------------------------------------------------------------------------
double 
circular_arc_2D( double x, double* params) 
//------------------------------------------------------------------------------
{
  double R = params[0];
  return sqrt( R*R - x*x);
};

//------------------------------------------------------------------------------
//
// specifically for determining Pi from the above via mean/variance
// see https://math.stackexchange.com/questions/19119/approximating-pi-using-monte-carlo-integratio
// f = sqrt(1-x^2)
// Var[<f>] = Int_{0}^{1} f^2 - ( Int_{0}^{1} f )^2
//          = (x - x^3/3)|0,1 - pi/4
//          = (2/3) - pi/4 
//
//------------------------------------------------------------------------------
double 
variance( unsigned long N )
//------------------------------------------------------------------------------
{
  double var = (2./3) - (M_PI/4)*(M_PI/4);
  return sqrt( var/N );
};


#endif
