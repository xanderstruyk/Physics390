#include <vector>
#include "TF1.h"

const int start_ndof=3;
const int end_ndof=22;


void plotWeightedIntegral(Int_t Ntrials, Int_t Ntests, Int_t Nevts, const char* ipath, const char* opath) { 

  char fname[512];
  sprintf(fname, "%s/Itrials__Ntrials_%d_Niter_%d_Nevts_%d.dat",
	  ipath,Ntrials,Ntests,Nevts);  
  
  TTree * t = new TTree("t","t");
  t->ReadFile(fname, "trial/I:Nevts_new/F:Iavg_u/F:Ivar_u/F:Ivarmean_u/F:Iavg_v/F:Ivar_v/F:Ivarmean_v/F:ndof/I:chisq/F:chisq_ndof/F:wI/F:wIerr/F"); 

  //char  cutstr[256] = "ndof<20";
  char  cutstr[256] = "TMath::Abs(chisq_ndof-1.)<.5";

  TH1F * h_vw_avg = new TH1F( "h_vw_avg", "h_vw_avg", 200, 0.99,1.01);
  TH1F * h_vw_err = new TH1F( "h_vw_err", "h_vw_err", 200, 0.,0.003);
  
  // sampling distribution of the integrals
  t->Draw("wI>>h_vw_avg",cutstr,"goff");

  // stderr estimate, the mean of this distribution
  // approximates the stderr on the mean of the sample distrib
  t->Draw("wIerr>>h_vw_err", cutstr,"goff");


  char pngstr[512];



  //
  // plot the weigted integrals
  //

  TCanvas * c1 = new TCanvas("c1","c1",0,0,600,500);
  double max_avg = 1.1*h_vw_avg->GetMaximum();
  cerr << "max_avg: " << max_avg << endl;
  TH1F * f1 = (TH1F*)(c1->DrawFrame(0.99,0.1,1.01,max_avg));
  h_vw_avg->SetLineColor(kRed);
  h_vw_avg->SetLineWidth(2);
  h_vw_avg->Draw("hsames");

  c1->SetLogy();
  sprintf(pngstr,"%s/wIavg_Ntrials_%d_Ntests_%d_Nevts_%d.png",
	  opath,Ntrials,Ntests,Nevts);
  c1->Print(pngstr);




  //
  // plot the weighted error
  //

  TCanvas * c2 = new TCanvas("c2","c2",600,0,600,500);
  double max_std = 1.1*h_vw_err->GetMaximum();
  TH1F * f2 = (TH1F*)(c2->DrawFrame(0,1,0.003,max_std));
  h_vw_err->SetLineColor(kRed);
  h_vw_err->SetLineWidth(2);
  h_vw_err->Draw("hsames");


  sprintf(pngstr,"%s/wIerr_Ntrials_%d_Ntests_%d_Nevts_%d.png",
	  opath, Ntrials,Ntests,Nevts);
  //c2->SetLogx();
  //c2->SetLogy();
  c2->Print(pngstr);

  cout << endl;
  cout << Nevts << " "
       << h_vw_avg->GetMean() << " "
       << h_vw_avg->GetRMS() << " "
       << h_vw_err->GetMean() << " "
       << endl;
}

