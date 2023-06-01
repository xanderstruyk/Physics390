#ifndef VEGAS_IMPORTANCE
#define VEGAS_IMPORTANCE

#include <vector>
#include "vegas_util.hh"

using namespace std;

void setup_map( vector<VegasBin> &xvec, double range_i, double range_f, unsigned Ng);

int find_x_bin( double x, vector<VegasBin> &xvec );

double xform__x_from_y( double y, vector<VegasBin> &xvec, int Ng );

double Jy( double y, vector<VegasBin> &xvec, int Ng );

void normalize_d( vector<double> &dvec, vector<int> &nvec );

void smooth( vector<double> &dvec );

void compress( vector<double> &dvec, double alpha );

void update_map( vector<VegasBin> &xvec, vector<double> &dvec, int Ng );


#endif


