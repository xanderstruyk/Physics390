#ifndef VEGAS_INTEGRALS
#define VEGAS_INTEGRALS

#include "vegas_util.hh"
#include "vegas_dump.hh"

VegasResults  vegas_integral_1D(unsigned trial, unsigned Nevt, unsigned Niter, unsigned Ng,
				bool do_importance_remap,
				vector<VegasBin> &x1vec,
				double (*integrand)( double, double*), double* integrand_params,
				VegasDump &dump, bool debug=false ); 

#endif
