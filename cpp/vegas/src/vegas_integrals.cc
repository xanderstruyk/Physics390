#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

#include "vegas_integrals.hh"
#include "vegas_importance.hh"
#include "vegas_constants.hh"
#include "probability.hh"


/*

  Definitions : 
  - trial  : the identifier of this specific of the vegas algorithm
  - Niter  : each run of the algo spans multiple iterations in order 
             to converge to the optimal map
  - Nevt   : the number of events in each iteration of each trial

*/


// -----------------------------------------------------------------------------
VegasResults
vegas_integral_1D(unsigned trial, unsigned Nevt, unsigned Niter, unsigned Ng,
		  bool do_importance_remap,
		  vector<VegasBin> &x1vec,
		  double (*integrand)( double, double*), double* integrand_params,
		  VegasDump &dump, bool debug  ) 
// -----------------------------------------------------------------------------
{

  vector<int> n1vec(Ng);
  vector<double> d1vec(Ng);

  bool map_done;
  if( do_importance_remap ) map_done=false; else map_done=true; 

  VegasResults results; 
#ifdef FIXED_ITERATIONS
  results.iterations.resize(Niter);
#endif

  for( int it=0; it<Niter; it++ ) 
    {   
	  
      if( debug ) dump.start_iter(x1vec.size());
      
      // for importance sampling ...
      n1vec.assign(Ng,0);
      d1vec.assign(Ng,0.);
      
      double sum=0.,ssum=0.;      
      for( int e=0; e<Nevt; e++ ) 
	{   
	  double uniform_y1_params[] = {0.,1.};
	  double y1 = sample_pdf_rejection( &pdf_uniform, (double*)&uniform_y1_params,0.,1. );
	  while( y1 == 1. ) y1=sample_pdf_rejection( &pdf_uniform, (double*)&uniform_y1_params,0.,1. );
	  double x1 = xform__x_from_y( y1, x1vec, Ng );
	  
	  double f = (*integrand)( x1,integrand_params );
	  double val = Jy(y1,x1vec,Ng)*f;

	  sum += val;
	  ssum += (val*val);
	  
	  // accumulate per bin
	  int iy1 = floor(y1*Ng);
	  n1vec[iy1] += 1.;
	  d1vec[iy1] += (val*val);

	  if( debug ) dump.new_event( x1, x1vec, val );	  
	}


      //
      // push the x bounds from this iteration
      // before updating
      //
      
      if( debug ) dump.update_iter(x1vec); 
      
      
      //
      // save the results
      //
      
      double I_mean = sum/Nevt;
      // this the variance within the sample, ie: it estimates the population var
      double I_var = (1./Nevt)*( ssum - Nevt*I_mean*I_mean );
      // this is an estimate of the (std err)^2 on the mean, taking the recorded variance as 
      // an estimate of the population estimate ... over sqrt(N)
      double I_var_mean = I_var/(Nevt-1);
      
#ifdef FIXED_ITERATIONS      
      results.iterations[it] = VegasIterResults {I_mean,I_var,I_var_mean};
#else 
      results.iterations.push_back(VegasIterResults {I_mean,I_var,I_var_mean});
#endif

      //
      // running weighted avg ... 
      //

      double Iavg_n =0., Iavg_d=0.;
      for( int i=0; i<results.iterations.size(); i++ ) {
	// want *sample* var here, not pop est, so div by N-1 ...
	Iavg_n += results.iterations[i].mean/results.iterations[i].var_mean;
	Iavg_d += 1./results.iterations[i].var_mean;
      }
      double Iavg = Iavg_n/Iavg_d;
      double Ierr = sqrt(1./Iavg_d);
      results.wI = Iavg;
      results.wIerr = Ierr;


      //	  
      // chisq
      //

      results.chisq = 0.;
      for( int i=0; i<results.iterations.size(); i++ ) {
	// want *sample* var here, not pop est, do div by N-1 ...
	double diff = results.iterations[i].mean - Iavg;
	results.chisq +=  (diff*diff)/results.iterations[i].var_mean;
      }

      

      //
      // test for convergence, loop control
      //
#ifndef FIXED_ITERATIONS      
      if( results.iterations.size() > 1 ) { 
	double err_last    = sqrt(results.iterations[results.iterations.size()-1].var_mean);
	double err_last_m1 = sqrt(results.iterations[results.iterations.size()-2].var_mean);
	if( fabs(err_last-err_last_m1)/err_last < VEGAS_CONVERGENCE_THRESHOLD ) {
	  if ( !map_done ) { 
	    map_done = true;
	    if( trial ==  0 && debug ) cerr << "map done " << results.iterations.size() << endl;
	  }
	}
      }
#else
      // like GSL version of vegas
      //if( results.iterations.size() > Niter-1 ) {
	if( it == Niter-1 ) {
	map_done = true;
      }
#endif

      //
      // done with map
      //

      if( map_done ) { 
	results.converged = true;
	break;
      }


      //
      // update map
      //

      if( !map_done ) { 
	normalize_d(d1vec,n1vec);
	smooth(d1vec);
	compress(d1vec,1.5);
	update_map(x1vec,d1vec,Ng);
      }

      if( debug ) dump.end_iter(); 

    } // iter

    return results;

}
