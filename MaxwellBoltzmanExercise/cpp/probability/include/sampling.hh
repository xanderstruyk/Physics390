
#ifndef PRNG_SAMPLING
#define PRNG_SAMPLING



// tmp : global call counts
//extern unsigned count_reject, count_metro;

double sample_pdf_rejection( double (*function)(double,double*), 
			     double* params,
			     double range_i, double range_f ) ;

double sample_pdf_inversion( double (*function)(double,double*), 
			     double* params,
			     double range_i, double range_f ) ;

double sample_pdf_metropolis( double (*function)(double,double*), 
			      double* params,
			      double range_i, double range_f,
			      double x) ;

/*
pair<double,double> sample_2D_pdf( double (*function)(double,double,double*), 
				   double* params,
				   double range_i, double range_f );
*/

#endif
