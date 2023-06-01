#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>   // for pair
#include <numeric>   // accumulate
#include <algorithm> // for max
#include <cmath>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>

#include "pdfs.hh"
#include "vegas.hh"


using namespace std;




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int 
main (int argc, char** argv) 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
{

  //
  // run options
  //

  VegasOptions opt;
  parse_args(argc,argv,opt);

  srand(opt.seed);
  const unsigned      Ntrial = opt.trial;//strtoul(argv[2],NULL,10); //10000
  const unsigned       Niter = opt.iter;//strtoul(argv[3],NULL,10); //25
  const unsigned        Nevt = opt.evts; strtoul(argv[4],NULL,10); //1000
  const unsigned long     Ng = opt.bins;//20; // #bins
  const char *   output_path = opt.path;

  //
  // the double gaussian
  //

  const double range_i = -1*VEGAS_HIGH_RANGE;
  const double range_f = VEGAS_HIGH_RANGE;

  const double frac1 = 0.5;
  const double mean1x = -1.5;
  const double sigma1x = 0.3;
  const double mean2x = 1.5;
  const double sigma2x = 0.3;

  double uniform_y_params[] = { 0., 1. };
  double double_gaussian_params[]  = { 
    frac1, 
    mean1x, sigma1x,
    mean2x, sigma2x
  };




  //
  // dump output to files
  //

  VegasDump dump(1,Ntrial,Niter,Nevt,Ng,opt.path);
  if( opt.debug ) dump.start_run();


  //
  // sample loop
  //

  vector<VegasBin> x1vec;
  for( int trial=0; trial<Ntrial; trial++ ) 
    {   

      // setup initial uniform binning in x
      setup_map( x1vec, range_i, range_f, Ng);


      // update dump
      if( opt.debug ) dump.start_trial();


      // loop control
      bool do_importance_remap = opt.importance;

  


      //
      // loop over iterations : this is the integral
      //

      VegasResults results = vegas_integral_1D( trial, Nevt, Niter,  Ng, 
						do_importance_remap,
						x1vec,
						&pdf_double_gaussian, (double*)&double_gaussian_params,
						dump, opt.debug ); 

      
      //
      // save avg x bin occupany from last test from first trial
      //
      
      if( results.iterations.size() < Niter && opt.debug ) 
	dump.update_bin_avg();
      
      
      
      //
      // output first (uniform) and last (vegas converged) I estimate, variance, (stderr)^2
      //

      double Iavg_uniform     = results.iterations.front().mean;
      double Ivar_uniform     = results.iterations.front().var;
      double Ivarmean_uniform = results.iterations.front().var_mean;
      double Iavg_vegas       = results.iterations.back().mean;
      double Ivar_vegas       = results.iterations.back().var;
      double Ivarmean_vegas   = results.iterations.back().var_mean;

      unsigned ndof_vegas     = results.iterations.size();
      double chisq_vegas      = results.chisq;
      double chisq_ndof_vegas = results.chisq/(results.iterations.size()-1);
      double I_weighted       = results.wI;
      double I_err_weighted   = results.wIerr;


      cout << fixed 
	   << trial << " "
	   << Nevt << " "
	   << Iavg_uniform << " "
	   << Ivar_uniform << " "
	   << std::setprecision(10) 
	   << Ivarmean_uniform << " "
	   << std::setprecision(6) 
	   << Iavg_vegas << " "
	   << Ivar_vegas << " "
	   << std::setprecision(10) 
	   << Ivarmean_vegas << " "
	   << std::setprecision(6) 
	   << ndof_vegas << " "
	   << chisq_vegas << " "
	   << chisq_ndof_vegas << " "
	   << I_weighted << " "
	   << I_err_weighted << " "
	   << endl;

      
      if( opt.debug ) dump.end_trial(x1vec,results.converged);

    } // trial
  
  if( opt.debug ) dump.end_run();

  return 0;
  
}
 
