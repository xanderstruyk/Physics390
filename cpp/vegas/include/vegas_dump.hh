#ifndef VEGAS_DUMP
#define VEGAS_DUMP

#include <stdio.h>
#include <iostream>
#include <vector>

#include "vegas_importance.hh"
//#include "vegas_stratify.hh"

using namespace std;

class VegasDump { 
public : 

  // --
  //
  // data members
  //
  //--


  // a 2d vector containing bin info for each iteration of
  // the first trial, ie: xbins[iter][bin]
  vector<vector<VegasBin> > dump_xbounds1; //, dump_xbounds2;

  // a 2d vector containing HC info for each iteration of
  // the first trial, ie: hc[iter][bin]
  //vector<vector<VegasHypercube> > dump_hvec;

  // a 2d vector containing bin occupancies for each iteration of
  // the algo, ie: xocc[iter][bin] .  This is updated for each 
  // event in each iteration of the first trial
  vector<vector<int> > dump_xocc; 

  // save the function values from the first and last itrs
  // for the first 10 trials, ie: f[iter]
  vector<double> dump_I_first_iter, dump_I_last_iter; 

  // of the first 
  vector<vector<double> > dump_avgval_vs_bin, dump_avgval2_vs_bin;

  // avg bin occ for last iter of all converged trials
  // ie: avg_occ[bin]
  vector<double> dump_xocc_avg;  


  // input parameters for the algorithm
  int dim;  
  unsigned Ntrial, Niter, Nevt, Ng;

  // directory in which to dump printouts 
  char * path;


  // keep track of the current trial/iteration, convergence
  unsigned trial, iter, n_converged_trials;


  //
  // output file handles
  //

  FILE *fh_dump_xbounds;   // the x bin edges/widths
  FILE *fh_dump_hypercube; // HC info for stratification
  FILE *fh_dump_xhist;     
  FILE *fh_dump_binavg;
  FILE *fh_dump_I;



  // constructor
  VegasDump( int theDim, 
	     unsigned theNtrial, unsigned theNiter, 
	     unsigned theNevt, unsigned theNg, 
	     char * thePath );

  // generic
  void start_run();
  void start_trial(); 
  void update_bin_avg();
  void end_iter();
  void end_run();


  // 1D 
  void start_iter(unsigned x1size) ;
  void new_event(double x1, vector<VegasBin> x1vec, double val ) ;
  void update_iter(vector<VegasBin> x1vec);
  void end_trial(vector<VegasBin> x1vec, bool converged);

  /*
  // 2D
  void start_iter(int trial, unsigned x1size, unsigned x2size) ;
  void new_event(double x1, vector<VegasBin> x1vec, double x2, vector<VegasBin> x2vec, double val ) ;
  void update_iter(int trial, int iter, vector<VegasBin> x1vec, vector<VegasBin>  x2vec);
  //void update_iter(int trial, int iter, vector<VegasBin> x1vec, vector<VegasBin>  x2vec, vector<VegasHypercube> hvec);
  void end_trial(int trial, vector<VegasBin> x1vec, vector<VegasBin> x2vec, bool converged);
  //void end_trial(int trial, vector<VegasBin> x1vec, vector<VegasBin> x2vec, vector<VegasHypercube> hvec, bool converged);
  */
};

#endif
