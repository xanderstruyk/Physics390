#include <vector>
#include "vegas_constants.hh"

void plotBounds(Int_t Ntest, Int_t Nevt, const char* ipath, const char* opath) { 


  TTree * t = new TTree("t","t");
  char fname[512];
  sprintf(fname,"%s/xbounds__Niter_%d_Nevt_%d.dat", ipath,Ntest,Nevt);
  t->ReadFile(fname, "test/I:index/I:lbound1/F:width1/F");
  TCanvas * c = new TCanvas("c","c",0,0,600,500);

  //
  // the 1D double gaussian
  //

  TF1 * gsum = new TF1("gsum","gaus(0)+gaus(3)",-1*VEGAS_HIGH_RANGE,VEGAS_HIGH_RANGE);
  gsum->SetParameter(0,0.5);
  gsum->SetParameter(1,-1.5);
  gsum->SetParameter(2,0.3);
  gsum->SetParameter(3,0.5);
  gsum->SetParameter(4,1.5);
  gsum->SetParameter(5,0.3);
 
  for( int i=0; i<t->GetMaximum("test"); i++ ) {  
  
    (TH1F*)(c->DrawFrame(-VEGAS_HIGH_RANGE,0.,VEGAS_HIGH_RANGE,1.));

    char drawstr[256];
    sprintf(drawstr,"test==%d",i);

    int n1 = t->Draw("lbound1",drawstr,"goff");
    std::vector<TLine*> lvec1;
    for( int i=0; i<n1; i++ ) {
      double lbound = *(t->GetV1()+i);
      lvec1.push_back(new TLine(lbound,0.,lbound,1.));
      lvec1.back()->Draw("s");
    }


    TLine * e1line = new TLine(VEGAS_HIGH_RANGE,0.,VEGAS_HIGH_RANGE,1.);
    e1line->Draw("s");

    gsum->Draw("same");

    sprintf(drawstr,"%s/lbounds_Nevt_%d_test_%d.png",opath,Nevt,i);
    c->Print(drawstr);

  }

}

