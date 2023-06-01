
#include "vegas_dump.hh"

/*

  Definitions : 
  - Ntrial : number of independent runs of the vegas algorithm
  - Niter  : each run of the algo spans multiple iterations in order 
             to converge to the optimal map
  - Nevt   : the number of events in each iteration of each trial

*/



//------------------------------------------------------------------------------
//
// Constructor.  Initialize stuff and open the non-debug file
//
//------------------------------------------------------------------------------
VegasDump::VegasDump( int theDim, 
		      unsigned theNtrial, unsigned theNiter, 
		      unsigned theNevt, unsigned theNg, char * thePath ) : 
  dim(theDim),Ntrial(theNtrial),Niter(theNiter),Nevt(theNevt),Ng(theNg),path(thePath) 
//------------------------------------------------------------------------------
{ 
  trial=0, iter=0;
  n_converged_trials=0;
  
  if( dim == 1 ) { 
    dump_xocc_avg.insert(dump_xocc_avg.begin(),Ng, 0.);
  }
  else {
    dump_xocc_avg.insert(dump_xocc_avg.begin(),Ng*Ng, 0.);
  }

};


//------------------------------------------------------------------------------
//
//  Open all of the debug-specific files
//
//------------------------------------------------------------------------------
void 
VegasDump::start_run() 
//------------------------------------------------------------------------------
{ 
    char dumpstr[512]; 
    sprintf( dumpstr, "%s/xbounds__Niter_%d_Nevt_%d.dat", path, Niter, Nevt );
    fh_dump_xbounds = fopen(dumpstr,"w");
    sprintf( dumpstr, "%s/xhist__Niter_%d_Nevt_%d.dat", path, Niter, Nevt );
    fh_dump_xhist = fopen(dumpstr,"w");

    if( dim != 1 ) {
      sprintf( dumpstr, "%s/hypercube__Niter_%d_Nevt_%d.dat", path, Niter, Nevt );
      fh_dump_hypercube = fopen(dumpstr,"w");
    }

    sprintf( dumpstr, "%s/xbin_avg__Niter_%d_Nevt_%d.dat", path, Niter, Nevt );
    fh_dump_binavg = fopen(dumpstr,"w");
};



//------------------------------------------------------------------------------
//
//  Call at the beginning of each vegas trial.  Opens separate dump files for 
//  the first 10 trials, none after that
//
//------------------------------------------------------------------------------
void 
VegasDump::start_trial() 
//------------------------------------------------------------------------------
{ 
  // reset the iter 
  iter = 0;

  // reset the x occ vec
  if( trial == 0 ) dump_xocc.clear();

  // dump the events from trials 0-9
  char dumpstr[512]; 
  if( trial < 10 ) { 
    sprintf( dumpstr, "%s/Isample__Nevt_%d_trial_%d.dat", path, Nevt, trial );
    fh_dump_I = fopen(dumpstr,"w");
  }
};



//------------------------------------------------------------------------------
//
// Call at the start of each iteration.  This stores a zeroed vector of x bin
// occupanices (for each iter) on the first trial.  For each trial (<10), throw 
// away function values from the previous iteration, we ultimately just save 
// those from the last iteration ..
//
//------------------------------------------------------------------------------
void 
VegasDump::start_iter(unsigned x1size) 
//------------------------------------------------------------------------------
{ 
  if( trial == 0 ) dump_xocc.push_back(vector<int> (x1size,0));
  if( trial == 0 ) dump_avgval_vs_bin.push_back(vector<double> (x1size,0));
  if( trial == 0 ) dump_avgval2_vs_bin.push_back(vector<double> (x1size,0));
  if( trial < 10 ) dump_I_last_iter.clear();
};


//------------------------------------------------------------------------------
//
// Just updated internal iter count
//
//------------------------------------------------------------------------------
void 
VegasDump::end_iter() 
//------------------------------------------------------------------------------
{ 
  iter++;
};



//------------------------------------------------------------------------------
//
// Called for each new event within a trial/iteration.  Add the function value  
// to the I vector for the "last" iteration.  Increment the occpancy of the 
// appropriate bin of the current trial of the xocc vector
//
//------------------------------------------------------------------------------
void 
VegasDump::new_event(double x1, vector<VegasBin> x1vec, double val ) 
//------------------------------------------------------------------------------
{ 
  if( trial == 0 ) { 
    int bin = find_x_bin(x1,x1vec);
    dump_xocc[iter][bin] += 1;
    dump_avgval_vs_bin[iter][bin] += val; // take the avg in  
    dump_avgval2_vs_bin[iter][bin] += val*val; // 
  }
  if( trial < 10 ) dump_I_last_iter.push_back(val);
};



//------------------------------------------------------------------------------
//
// Called for each iteration but only operates on the first 10 trials.  For the 
// first trial, push back a vector of xbins for each iteration.  For all 10 
// trials, store the function values for the first iteration by copying to 
// dump_I_first_iter
//  
//
//------------------------------------------------------------------------------
void 
VegasDump::update_iter(vector<VegasBin> x1vec) 
//------------------------------------------------------------------------------
{ 
  if( trial == 0 ) { 
    dump_xbounds1.push_back(x1vec);
    cerr << "trial: 0 iteration: " << iter << endl;
  }
  if( trial < 10 && iter == 0 ) { 
    dump_I_first_iter = dump_I_last_iter;
  }
};



//------------------------------------------------------------------------------
//
// Called in main after a converged trial
//
//------------------------------------------------------------------------------
void 
VegasDump::update_bin_avg() 
//------------------------------------------------------------------------------
{ 
  n_converged_trials++;
  if( trial==0 ) { 
    for( int b=0; b<dump_xocc.back().size(); b++ ) { 
      dump_xocc_avg[b] += (double)dump_xocc[iter][b]/Ntrial;
    }
  }
};



//------------------------------------------------------------------------------
//
// Close the integral distributions for the first 10 trials
// For the first trial, save the final map and then print out the xbins from 
//  each of the iterations 
// Print the bin occupancies from the 
//------------------------------------------------------------------------------
void 
VegasDump::end_trial(vector<VegasBin> x1vec, bool converged) 
//------------------------------------------------------------------------------
{

  if( !(trial%1000) ) cerr << "completed trial  " << trial << endl;

  if( trial < 10 && converged) { 
    for( int i=0; i<dump_I_first_iter.size(); i++ )
      fprintf( fh_dump_I, "%f %f\n", dump_I_first_iter[i],dump_I_last_iter[i] );
    fclose(fh_dump_I);
  }
  
  if( trial == 0 ) { 

    dump_xbounds1.push_back(x1vec);
    
    // loop over iterations in the first trial
    for( int it=0; it<dump_xbounds1.size(); it++ ) {
      // loop over bin boundaries 
      for( int b=0; b<Ng; b++ ) {
	fprintf(fh_dump_xbounds, "%d %d %f %f\n",
		it, b, dump_xbounds1[it][b].low_edge, dump_xbounds1[it][b].width);
      }
    }
    fclose(fh_dump_xbounds);
    
    
    // loop over iterations in the first trial
    for( int it=0; it<dump_xocc.size(); it++ ) {
      // loop over xbins
      for( int b=0; b<dump_xocc[it].size(); b++ ) {

	double x1b = dump_xbounds1[it][b].low_edge;
	dump_avgval_vs_bin[it][b] /= dump_xocc[it][b];
	dump_avgval2_vs_bin[it][b] /= dump_xocc[it][b];
	fprintf(fh_dump_xhist, "%d %d %f %d %f %f\n",
	it, b, x1b, dump_xocc[it][b],dump_avgval_vs_bin[it][b], dump_avgval2_vs_bin[it][b]);
	
      }
    }
    fclose(fh_dump_xhist);
    //cerr << "closed trail 0 ..." << endl;
  }

  trial++; // update trial
};


//------------------------------------------------------------------------------
//
//
//
//------------------------------------------------------------------------------
void 
VegasDump::end_run() 
//------------------------------------------------------------------------------
{
  for( int b=0; b<dump_xocc_avg.size(); b++ ) { 
    double rescaled = dump_xocc_avg[b] * ((double)Ntrial/n_converged_trials);
    if( dim == 1 ) { 
      fprintf(fh_dump_binavg, "%d %f %f\n", 
	      b,
	      dump_xbounds1.back()[b].low_edge,
	      rescaled);
    } 
    /*
      else { 
      int x1bin = b%Ng;
      int x2bin = b/Ng;
      fprintf(fh_dump_binavg, "%d %f %f %f\n", 
      b,
      dump_xbounds1.back()[x1bin].low_edge,dump_xbounds2.back()[x2bin].low_edge,
      rescaled);
      }
    */
  }

};




