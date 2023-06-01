
int plotWeightedStdErrSummary(const char* ipath, const char* opath) {


  TTree * t = new TTree("t","t");
  char fname[512];
  sprintf(fname, "%s/weighted_sample_stderr.dat", ipath);
  t->ReadFile(fname,"Nevts/I:wIavg/F:wIrms/F:wIerr/F");

  TCanvas * c = new TCanvas("c","c",0,0,600,500);
  TH1F* frame = (TH1F*)(c->DrawFrame(9000,1e-7,20*11000000,0.5));


  t->SetMarkerColor(kBlue);
  t->SetMarkerStyle(20);
  t->SetMarkerSize(1.2);
  //t->Draw("wIrms:Nevts*20","","same");
  // also draw to graph 
  int n1 = t->Draw("wIrms:Nevts*20","","goff");
  TGraph * g1 = new TGraph(n1,t->GetV2(),t->GetV1());
  g1->SetName("g1");
  g1->SetMarkerColor(kRed);
  g1->SetMarkerStyle(21);
  g1->SetMarkerSize(1.2);
    g1->Draw("p");

  t->SetLineColor(kBlue);
  t->SetLineWidth(2);
  //t->Draw("wIerr:Nevts*20","","lsame");


  TF1 *flinear_sm = new TF1("flinear_sm", "[0]*TMath::Power(x,[1])", 10000, 20*1000000);
  flinear_sm->SetParameter(0,0.6);
  flinear_sm->SetParameter(1,-0.5);
  flinear_sm->SetLineColor(kMagenta);
  g1->Fit("flinear_sm", "","", 20*10000, 20*1000000);

  

  c->SetLogy();
  c->SetLogx();
  sprintf(fname, "%s/weighted_stderr_scaling.png",opath);
  c->Print(fname);

  return 0;
}
