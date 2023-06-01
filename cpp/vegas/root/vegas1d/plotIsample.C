#include <vector>
#include "TF1.h"


//
// plots contributions to the integral from each event for the first 
// and last iterations of a given trial.  
//
// The first iteration corresponds to uniform binning in x, so most 
// events will be away from the gaussian peaks and their contributions
// are small, giving a peak in the I distribution near zero.  The integral 
// value (ie: the sum of all contributions) is driven by the events in 
// the tails of the I distribution, which are near the peaks of the gaussians
//
// The last iteration corresponds to converged importance remapping.  Now 
// more events are located near the gaussian peaks, giving a peak in the 
// I distribution at higher values 
//


void plotIsample(Int_t Nevt, Int_t trial, const char* ipath, const char* opath) { 

  char fname[512];
  sprintf(fname, "%s/Isample__Nevt_%d_trial_%d.dat", ipath, Nevt,trial);
  
  TTree * t = new TTree("t","t");
  t->ReadFile(fname, "Ifirst/F:Ilast/F");

  TH1F * h_first = new TH1F( "h_first", "h_first", 250, 0,5);
  TH1F * h_last  = new TH1F( "h_last", "h_last", 250, 0,5);


  t->Draw("Ifirst>>h_first","","goff");
  t->Draw("Ilast>>h_last","","goff");


  TCanvas * c1 = new TCanvas("c1","c1",0,0,600,500);
  double max_I = 1.1*max(h_first->GetMaximum(),h_last->GetMaximum());
  TH1F * f1 = (TH1F*)(c1->DrawFrame(-0.1,0.1,5,max_I));
  h_first->SetLineColor(kRed);
  h_first->SetLineWidth(2);
  h_last->SetLineColor(kBlue);
  h_last->SetLineWidth(2);

  h_first->Draw("hsames");
  c1->Modified();c1->Update();
  TPaveStats * stats1u = (TPaveStats*)(c1->GetPrimitive("stats"));
  stats1u->SetName("stats1u");
  stats1u->SetY1NDC(0.9);
  stats1u->SetY2NDC(0.7);

  h_last->Draw("hsames");
  c1->Modified();c1->Update();
  TPaveStats * stats1v = (TPaveStats*)(c1->GetPrimitive("stats"));
  stats1v->SetName("stats1v");
  stats1v->SetY1NDC(0.7);
  stats1v->SetY2NDC(0.5);  

  char pngstr[512];
  sprintf(pngstr,"%s/Isample_Nevts_%d_trial_%d.png", opath,Nevt,trial);
  c1->SetLogy();
  c1->Print(pngstr);


}

