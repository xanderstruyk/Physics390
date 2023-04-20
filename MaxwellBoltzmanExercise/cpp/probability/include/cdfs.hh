#ifndef PRNG_CDFS
#define PRNG_CDFS

double cdf_exponential( double x, double* params );
double inv_cdf_exponential( double x, double* params );

double cdf_gaussian( double x, double* params );
double inv_cdf_gaussian( double x, double* params );

double cdf_maxwell_boltzmann( double x, double* params );
#endif
