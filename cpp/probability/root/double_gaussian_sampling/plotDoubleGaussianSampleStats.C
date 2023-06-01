
int plotDoubleGaussianSampleStats(unsigned Nsamples, unsigned Nevts) {

  char fname[512];
  sprintf(fname,"./data/double_gaussian_sampling/sample_stats_Nsamples_%d_Nevts_%d.dat",
	  Nsamples,Nevts);
  
  TTree * t = new TTree("t","t");
  t->ReadFile(fname,"index/I:mean/F:var/F");

  TCanvas * c = new TCanvas("c","c",0,0,1800,500);
  c->Divide(3,1);
  t->SetLineColor(kBlue);
  t->SetLineWidth(2);

  // CLT : this becomes gaussian of width sigma/sqrt(N) at large N
  // gamma mean is alpha/beta = 1/0.5 = 2;
  TPad * p = (TPad*)c->cd(1);
  t->Draw("mean>>hmean");
  TH1F * hmean = (TH1F*)(gROOT->FindObjectAny("hmean"));
  p->DrawFrame(-2,0,0,1.1*hmean->GetMaximum());
  hmean->Draw("sames");
  hmean->Fit("gaus");

  // the sample variance, which is an estimate of the population variance, 
  // is independent of N 
  c->cd(2);
  t->Draw("var>>hvar");
  TH1F * hvar = (TH1F*)(gROOT->FindObjectAny("hvar"));

  // taking the sample variance as an estimate of the population, determine
  // the stderr on the sample means.  The mean here should match the rms from 
  // the first plot ...
  c->cd(3);
  char drawstr[256];
  sprintf(drawstr,"sqrt(var/%d)>>hstd",Nevts);
  t->Draw(drawstr);
  TH1F * hstd = (TH1F*)(gROOT->FindObjectAny("hstd"));

  cout << "mean of means : " << hmean->GetMean()  << endl;
  cout << "rms of means, mean of vars  : " << hmean->GetRMS()  << " , " << hvar->GetMean() << endl;
  cout << "mean of sqrt(var/N) : " << hstd->GetMean()  << endl;

  char pngname[512];
  sprintf(pngname,"./png/double_gaussian_sampling/sample_stats_Nsamples_%d_Nevts_%d.png",
	  Nsamples,Nevts);
  c->Print(pngname);

  return 0;
}
