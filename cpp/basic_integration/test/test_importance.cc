//
// example V from Eric Anderson Stat 578C (Statistical Genetics) lecture notes ...
//

#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <math.h>
#include "probability.hh"

using namespace std;


int main (int argc, char ** argv) { 

  const int  Ntest  = 5000;
  const int  Nevt   = 1000;

  const double range_i = -50.;
  const double range_f = 50.;
  const double mean = 0.;
  const double sigma = 1.;
  double gaussian_params[] = {mean, sigma};

  double uniform_params[] = {range_i,range_f};
  double student_params[] = { 1 }; // 1 d.f.
  double student30_params[] = { 30 }; // 30 d.f

  srand(strtoul(argv[1],NULL,10));

  // save the MC events from the first trial
  FILE * fh_uniform   = fopen("./data/importance_example/uniform.dat","w");
  FILE * fh_student   = fopen("./data/importance_example/student.dat","w");
  FILE * fh_student30 = fopen("./data/importance_example/student30.dat","w");



  //
  // using pdf_gaussian here as the target function 
  //
  // sampling distributions are uniform, student, student-30
  //
  // the MC integral is the expected value of (target distribution)/(sampling distribution),
  // see (12) from text
  //

  for( int t=0; t<Ntest; t++ ) {   

    // uniform
    float sum_uniform=0.,ssum_uniform=0.;
    for( int e=0; e<Nevt; e++ ) {   
      float x = sample_pdf_rejection( &pdf_uniform, (double*)&uniform_params, range_i, range_f );
      float val = pdf_gaussian( x, (double*)&gaussian_params)/pdf_uniform(x, (double*)&uniform_params);
      if( t == 0 ) fprintf(fh_uniform,"%f\t%f\n", x, val);
      sum_uniform += val;
      ssum_uniform += val*val;
    }
    float mean_uniform = sum_uniform/Nevt;
    float sqerr_est_uniform = (1./(Nevt*(Nevt-1)))*( ssum_uniform - Nevt*mean_uniform*mean_uniform ); 


    // student t, 1 DF
    float sum_student=0.,ssum_student=0.;
    for( int e=0; e<Nevt; e++ ) {   
      float x = sample_pdf_rejection( &pdf_student, (double*)&student_params, range_i, range_f );
      float val = pdf_gaussian( x, (double*)&gaussian_params)/pdf_student(x, (double*)&student_params);
      if( t == 0 ) fprintf(fh_student,"%f\t%f\n", x, val);
      sum_student += val;
      ssum_student += val*val;
    }
    float mean_student = sum_student/Nevt;
    float sqerr_est_student = (1./(Nevt*(Nevt-1)))*( ssum_student - Nevt*mean_student*mean_student );

    // student with 30 DF
    float sum_student30=0.,ssum_student30=0.;
    for( int e=0; e<Nevt; e++ ) {   
      float x = sample_pdf_rejection( &pdf_student, (double*)&student30_params, range_i, range_f );
      float val = pdf_gaussian( x, (double*)&gaussian_params)/pdf_student(x, (double*)&student30_params);
      if( t == 0 ) fprintf(fh_student30,"%f\t%f\n", x, val);
      sum_student30 += val;
      ssum_student30 += val*val;
    }
    float mean_student30 = sum_student30/Nevt;
    float sqerr_est_student30 = (1./(Nevt*(Nevt-1)))*( ssum_student30 - Nevt*mean_student30*mean_student30 );

    /*
    // by definition ...
    float sum_gauss=0;
    for( int e=0; e<Nevt; e++ ) {   
    float x = sample_pdf_rejection( &pdf_gaussian, mean, sigma, range_i, range_f );
    sum_gauss += pdf_gaussian( x, mean, sigma)/pdf_gaussian(x, mean, sigma);
    }
    sum_gauss *= 1./Nevt;
    */  
    
    cout  << t << " "
	  << mean_uniform << " "
	  << mean_student << " "
	  << mean_student30 << " "
	  << sqrt(sqerr_est_uniform) << " "
	  << sqrt(sqerr_est_student) << " "
	  << sqrt(sqerr_est_student30)
	  <<  endl;

    if( t==0 ) { 
      fclose(fh_uniform);
      fclose(fh_student);
      fclose(fh_student30);
    }

    
  }


}



