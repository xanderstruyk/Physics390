#ifndef VEGAS_UTIL
#define VEGAS_UTIL


#include <vector>
using namespace std;

typedef struct  { 
  double low_edge;
  double width;
} VegasBin;
 

typedef struct { 
  double mean, var, var_mean;
} VegasIterResults;

typedef struct  { 
public: 

  bool converged;
  unsigned Nev_total;
  double chisq;
  vector<VegasIterResults> iterations;
  double wI, wIerr; // weighted results
  //
  int niter;
} VegasResults;

/*
class VegasResults  { 
public: 

  bool converged;
  unsigned Nev_total;
  double chisq;
  vector<VegasIterResults> iterations;
  double wI, wIerr; // weighted results
  //
  int niter;

  VegasResults():niter(0) {};
  VegasResults(int Niter):niter(Niter) {iterations.resize(niter);};
  VegasResults(const VegasResults &obj) { 
    converged = obj.converged;
    Nev_total = obj.Nev_total;
    chisq = obj.chisq;
    wI = obj.wI;
    wIerr = obj.wIerr;

    iterations.resize(obj.niter);
    iterations = obj.iterations;
    
  }

  ~VegasResults() {iterations.clear();};
} ;
*/

#endif


