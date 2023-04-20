#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility> // for pair
#include <numeric> // accumulate
#include <cmath>
#include <stdlib.h>
#include <assert.h>

#include "probability.hh"

using namespace std;



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int 
main (int argc, char** argv) 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
{

  const double range_i = -5.;
  const double range_f = 5.;
  const double mean1 = -2.;
  const double sigma1 = 0.5;
  const double mean2 = 1.;
  const double sigma2 = 1.;
  const double frac1 = 0.6;
  double double_gaussian_params[]  = { frac1, mean1, sigma1, mean2, sigma2 };


  /*

    the population mean is the weighted mean : 0.6(-2.) + (0.4)(1.) = -.8
    the poulation var is the weighted var 
      (see https://stats.stackexchange.com/questions/447626/mean-and-variance-of-a-mixture-distribution, comment 11)
    = 0.6*(0.5)^2 + 0.4 + (0.6*0.4*9)
    = 2.71
    ->  giving a stddev of 1.646

  */


  srand(strtoul(argv[1],NULL,10));
  unsigned Nsamples = (strtoul(argv[2],NULL,10)); // 1000
  unsigned Nevts    = (strtoul(argv[3],NULL,10)); // 100,1000,5000

  vector<pair<double,double> > sample_stats;
  for( int sample=0; sample<Nsamples; sample++ ) 
    {   

      FILE * fh_sample;
      if( sample < 10 ) { 
	char str_sample[512];
	sprintf(str_sample, "./data/double_gaussian_sampling/sample_%d_Nsamples_%d_Nevts_%d.dat",sample, Nsamples, Nevts);
	fh_sample = fopen(str_sample, "w");
      }

      double sum=0., ssum=0.;
      for( int evt=0; evt<Nevts; evt++ ) 
	{   
	  
	  double x = sample_pdf_rejection( &pdf_double_gaussian, (double*)&double_gaussian_params,range_i,range_f );
	  sum += x;
	  ssum += (x*x);
	  if( sample < 10 ) fprintf( fh_sample, "%d\t%f\n",evt,x);
	}
      if( sample < 10 ) fclose(fh_sample);

      double sample_mean = sum/Nevts;
      // the variance within the sample, not the standard error
      double sample_var = (1./Nevts)*( ssum - Nevts*sample_mean*sample_mean );
      sample_stats.push_back(pair<double,double>(sample_mean,sample_var));
    }
  
  char str_sample_stats[512];
  sprintf(str_sample_stats, "./data/double_gaussian_sampling/sample_stats_Nsamples_%d_Nevts_%d.dat",Nsamples,Nevts);
  FILE * fh_sample_stats = fopen(str_sample_stats, "w");
  for( int i=0; i<Nsamples; i++ ) 
    fprintf(fh_sample_stats, "%d\t%f\t%f\n", i, sample_stats[i].first,sample_stats[i].second);
  fclose(fh_sample_stats);


}
 
