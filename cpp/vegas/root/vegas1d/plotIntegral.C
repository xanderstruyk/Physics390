#include <vector>
#include "TF1.h"

const int start_ndof=3;
const int end_ndof=22;

Double_t ChiSquareDistr(Double_t *x,Double_t *par)
{
  // Chisquare density distribution for nrFree degrees of freedom

  Double_t nrFree = par[0];
  Double_t amp = par[1];
  Double_t chi2 = x[0];

  if (chi2 > 0) {
    Double_t lambda = nrFree/2.;
    Double_t norm = TMath::Gamma(lambda)*TMath::Power(2.,lambda);
    return amp*TMath::Power(chi2,lambda-1)*TMath::Exp(-0.5*chi2)/norm;
  } else
    return 0.0;
}

Double_t ChiSquareSum(Double_t *x,Double_t *par)
{
  
  double val=0.;
  for( int i=start_ndof; i<end_ndof; i++ ) { 
    val += ChiSquareDistr(x,par+((i-start_ndof)*2));
  }
  return val;
}


void plotIntegral(Int_t Ntrials, Int_t Ntests, Int_t Nevts, const char* ipath, const char* opath) { 

  char fname[512];
  sprintf(fname, "%s/Itrials__Ntrials_%d_Niter_%d_Nevts_%d.dat",
	  ipath,Ntrials,Ntests,Nevts);  
  
  TTree * t = new TTree("t","t");
  t->ReadFile(fname, "trial/I:Nevts_new/F:Iavg_u/F:Ivar_u/F:Ivarmean_u/F:Iavg_v/F:Ivar_v/F:Ivarmean_v/F:ndof/I:chisq/F:chisq_ndof/F:wI/F:wIerr/F"); 
  t->Print();

  //char  cutstr[256] = "ndof<20";
  // for fixed iterations
  char  cutstr[256] = "fabs(chisq_ndof -1.)<0.5";
  
  TH1F * h_u_avg = new TH1F( "h_u_avg", "h_u_avg", 200, 0.8,1.2);
  TH1F * h_v_avg = new TH1F( "h_v_avg", "h_v_avg", 200, 0.8,1.2);
  
  TH1F * h_u_var = new TH1F( "h_u_var", "h_u_var", 200, 0.,4);
  TH1F * h_v_var = new TH1F( "h_v_var", "h_v_var", 200, 0.,4);
  
  TH1F * h_u_std = new TH1F( "h_u_std", "h_u_std", 500, 0.,.1);
  TH1F * h_v_std = new TH1F( "h_v_std", "h_v_std", 500, 0.,.1);
  
  TH1F * h_chisq = new TH1F( "h_chisq", "h_chisq", 100, 0, 40);

  // sampling distribution of the integrals
  t->Draw("Iavg_u>>h_u_avg",cutstr,"goff");
  t->Draw("Iavg_v>>h_v_avg",cutstr,"goff");
  // distribution of variance estimates from each sample
  t->Draw("Ivar_u>>h_u_var",cutstr,"goff");
  t->Draw("Ivar_v>>h_v_var",cutstr,"goff");
  // stderr estimate, the mean of this distribution
  // approximates the stderr on the mean of the sample distrib
  t->Draw("sqrt(Ivarmean_u)>>h_u_std", cutstr);
  t->Draw("sqrt(Ivarmean_v)>>h_v_std", cutstr);
  // chisq
  t->Draw("chisq>>h_chisq",cutstr,"goff");

  char pngstr[512];



  //
  // plot the integrals, ie: sample means 
  //

  TCanvas * c1 = new TCanvas("c1","c1",0,0,600,500);
  double max_avg = 1.1*max(h_u_avg->GetMaximum(),h_v_avg->GetMaximum());
  TH1F * f1 = (TH1F*)(c1->DrawFrame(0.8,0.1,1.2,max_avg));
  h_u_avg->SetLineColor(kRed);
  h_u_avg->SetLineWidth(2);
  h_v_avg->SetLineColor(kBlue);
  h_v_avg->SetLineWidth(2);

  h_u_avg->Draw("hsames");
  c1->Modified();c1->Update();
  TPaveStats * stats1u = (TPaveStats*)(c1->GetPrimitive("stats"));
  stats1u->SetName("stats1u");
  stats1u->SetY1NDC(0.9);
  stats1u->SetY2NDC(0.7);

  h_v_avg->Draw("hsames");
  c1->Modified();c1->Update();
  TPaveStats * stats1v = (TPaveStats*)(c1->GetPrimitive("stats"));
  stats1v->SetName("stats1v");
  stats1v->SetY1NDC(0.7);
  stats1v->SetY2NDC(0.5);  

  c1->SetLogy();
  sprintf(pngstr,"%s/Iavg_Ntrials_%d_Ntests_%d_Nevts_%d.png",
	  opath,Ntrials,Ntests,Nevts);
  c1->Print(pngstr);




  //
  // plot the estimated stderr, using sample variance as a estimate 
  // of the population variance.  The mean of this distribution 
  // should be consistent with the stderr of the plot above ...
  //

  TCanvas * c2 = new TCanvas("c2","c2",600,0,600,500);
  double max_std = 1.1*max(h_u_std->GetMaximum(),h_v_std->GetMaximum());
  TH1F * f2 = (TH1F*)(c2->DrawFrame(1e-4,0.1,0.05,max_std));
  h_u_std->SetLineColor(kRed);
  h_u_std->SetLineWidth(2);
  h_v_std->SetLineColor(kBlue);
  h_v_std->SetLineWidth(2);

  h_u_std->Draw("hsames");
  c2->Modified();c2->Update();
  TPaveStats * stats2u = (TPaveStats*)(c2->GetPrimitive("stats"));
  stats2u->SetName("stats2u");
  stats2u->SetY1NDC(0.9);
  stats2u->SetY2NDC(0.7);

  h_v_std->Draw("hsames");
  c2->Modified();c2->Update();
  TPaveStats * stats2v = (TPaveStats*)(c2->GetPrimitive("stats"));
  stats2v->SetName("stats2v");
  stats2v->SetY1NDC(0.7);
  stats2v->SetY2NDC(0.5);  

  sprintf(pngstr,"%s/Istderr_Ntrials_%d_Ntests_%d_Nevts_%d.png",
	  opath, Ntrials,Ntests,Nevts);
  //c2->SetLogx();
  c2->SetLogy();
  c2->Print(pngstr);




  //
  // plot the sample variance.  This should not change with incr Nevt
  //

  TCanvas * c2b = new TCanvas("c2b","c2b",1200,0,600,500);
  double max_var = 1.1*max(h_u_var->GetMaximum(),h_v_var->GetMaximum());
  TH1F * f2b = (TH1F*)(c2b->DrawFrame(0.,0.1,4,max_var));
  h_u_var->SetLineColor(kRed);
  h_u_var->SetLineWidth(2);
  h_v_var->SetLineColor(kBlue);
  h_v_var->SetLineWidth(2);

  h_u_var->Draw("hsames");
  c2b->Modified();c2b->Update();
  TPaveStats * stats2ub = (TPaveStats*)(c2b->GetPrimitive("stats"));
  stats2ub->SetName("stats2ub");
  stats2ub->SetY1NDC(0.9);
  stats2ub->SetY2NDC(0.7);

  h_v_var->Draw("hsames");
  c2b->Modified();c2b->Update();
  TPaveStats * stats2vb = (TPaveStats*)(c2b->GetPrimitive("stats"));
  stats2vb->SetName("stats2vb");
  stats2vb->SetY1NDC(0.7);
  stats2vb->SetY2NDC(0.5);  

  sprintf(pngstr,"%s/Ivar_Ntrials_%d_Ntests_%d_Nevts_%d.png",
	  opath,Ntrials,Ntests,Nevts);
  //c2b->SetLogx();
  c2b->SetLogy();
  c2b->Print(pngstr);



  //
  // plot the chisq
  //

  TCanvas * c3 = new TCanvas("c3","c3",1800,0,600,500);
  TH1F* f3 = (TH1F*)(c3->DrawFrame(0.,0.,40.,1)); 
  h_chisq->SetLineColor(kBlue);
  h_chisq->SetLineWidth(2);
  h_chisq->Draw();

  char cutstr2[256];
  vector<int> ndofvec;
  vector<double> entvec;
  for( int i=start_ndof; i<end_ndof; i++ ) {
    sprintf(cutstr2, "ndof==%d&&%s", i, cutstr );
    ndofvec.push_back(i-1);
    entvec.push_back((double)t->Draw("chisq",cutstr2,"goff"));
  }

  TF1 * fchisq = new TF1("fchisq",ChiSquareSum,0.01,40,36);
  double div = h_chisq->GetNbinsX()/h_chisq->GetXaxis()->GetXmax();

  for(int i=0; i<ndofvec.size(); i++ ) { 
    fchisq->SetParameter((i*2), ndofvec[i]);
    fchisq->SetParameter((i*2)+1,entvec[i]/div);
  }

  fchisq->SetLineColor(kViolet);
  fchisq->Draw("same");
  sprintf(pngstr,"%s/chisq_Ntrials_%d_Ntests_%d_Nevts_%d.png",
	  opath,Ntrials,Ntests,Nevts);
  c3->Print(pngstr);  




  // mean of sample means : clusters around pop mean
  // rms of sample means : goes as 1/sqrtN  
  // mean of sample rms  : this is an estimate of the pop RMS


  cout  << "enew: "  << Nevts << "\t"
	<< "meanU: " << h_u_avg->GetMean()  << "\t"
	<< "meanV: " << h_v_avg->GetMean()  << "\t"
	<< "rmsU: "  << h_u_avg->GetRMS()  << "\t"
	<< "rmsV: "  << h_v_avg->GetRMS()  << "\t"
	<< "varU: "  << h_u_var->GetMean()  << "\t"
	<< "varV: "  << h_v_var->GetMean()  << "\t"
	<< "serrU: " << h_u_std->GetMean()  << "\t"
	<< "serrV: " << h_v_std->GetMean()  << endl;

}

