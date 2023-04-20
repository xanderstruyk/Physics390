#ifndef INTEGRATION_MEANVARIANCE
#define INTEGRATION_MEANVARIANCE

double integrate_1D_MeanVariance( double (*function)(double, double*), 
				  double* params, 
				  double range_i, double range_f, 
				  unsigned long ntrials );


#endif

