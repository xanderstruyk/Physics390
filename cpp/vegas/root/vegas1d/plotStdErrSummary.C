
int plotStdErrSummary(const char* ipath, const char* opath) {

  // 'stddev' is the SD of the sample means
  // 'meanvar' is the avg var of the samples 
  //   the SEM = sqrt(meanvar/Nevts)

  TTree * t = new TTree("t","t");
  char fname[512];
  sprintf(fname, "%s/sample_stderr.dat", ipath);
  t->ReadFile(fname,"Nevts/I:Nevts_new/F:avgU/F:avgV/F:rmsU/F:rmsV/F:varU/F:varV/F:stderrU/F:stderrV/F");

  TCanvas * c = new TCanvas("c","c",0,0,600,500);
  //TH1F* frame = (TH1F*)(c->DrawFrame(0,1e-4,1.5*t->GetMaximum("Nevts"),0.5));
  TH1F* frame = (TH1F*)(c->DrawFrame(0,1e-4,1100000,0.5));

  t->SetMarkerColor(kBlue);
  t->SetMarkerStyle(20);
  t->SetMarkerSize(1.2);
  t->Draw("rmsU:Nevts_new","","same");

  t->SetLineColor(kBlue);
  t->SetLineWidth(2);
  t->Draw("stderrU:Nevts_new","","lsame");
  
  t->SetMarkerColor(kRed);
  t->SetMarkerStyle(20);
  t->SetMarkerSize(1.2);
  t->Draw("rmsV:Nevts_new","","same");

  t->SetLineColor(kRed);
  t->SetLineWidth(2);
  t->Draw("stderrV:Nevts_new","","lsame");



  t->SetLineColor(kViolet);
  t->SetLineWidth(2);
  t->Draw("(rmsU/sqrt(2)):Nevts_new","","lsame");


  c->SetLogy();
  sprintf(fname, "%s/stderr_scaling.png",opath);
  c->Print(fname);

  return 0;
}
