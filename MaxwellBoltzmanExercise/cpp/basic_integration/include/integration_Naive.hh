#ifndef INTEGRATION_NAIVE
#define INTEGRATION_NAIVE

typedef struct { 
  double x;
  double y;
} Points2D;

unsigned naive_trial_1D( double (*function)(double, double*), 
			 double* params, 
			 double range_i, double range_f,  
			 Points2D* opt_points = NULL );

double integrate_1D_Naive( double (*function)(double, double*), 
			   double* params, 
			   double range_i, double range_f, 
			   unsigned long ntrials, 
			   Points2D* opt_points = NULL );

double binomial_error( unsigned long N, unsigned long k );


#endif
