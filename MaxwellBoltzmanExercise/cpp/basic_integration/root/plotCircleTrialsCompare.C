
void
plotCircleTrialsCompare(int nsamples) {


  gStyle->SetOptStat(0);

  int trials=1000;
  char mystr[256]; // for histo name, file name, etc



  //
  // Naive
  //
  sprintf(mystr, "h%d_naive", nsamples);
  TH1F * h_naive = new TH1F(mystr,mystr,100,3.0,3.3);
  sprintf(mystr, "t%d_naive", nsamples);    
  TTree * t_naive = new TTree(mystr,mystr);
  sprintf(mystr, "./data/pi_1D_Naive_ntrials_%d_samples_%d.dat", trials, nsamples);    
  t_naive->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I");
  sprintf(mystr, "pi>>h%d_naive", nsamples);
  t_naive->Draw(mystr,"","goff");
  h_naive->Print();

  //
  // Mean/Variance
  //
  sprintf(mystr, "h%d_meanvar", nsamples);
  TH1F * h_meanvar = new TH1F(mystr,mystr,100,3.0,3.3);  
  sprintf(mystr, "t%d_meanvar", nsamples);    
  TTree * t_meanvar = new TTree(mystr,mystr);
  sprintf(mystr, "./data/pi_1D_MeanVariance_ntrials_%d_samples_%d.dat", trials, nsamples);    
  t_meanvar->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I");
  sprintf(mystr, "pi>>h%d_meanvar", nsamples);
  t_meanvar->Draw(mystr,"","goff");
  h_meanvar->Print();


  TCanvas * c = new TCanvas("c","c", 0, 0, 700, 600);
  TH1F* frame = (TH1F*)(c->DrawFrame(3.,0.1,3.3,1.1*TMath::Max(h_naive->GetMaximum(),h_meanvar->GetMaximum())));
  TLegend * l = new TLegend(0.65,0.7, 0.95,0.95);

  cout << "samples: " << nsamples << "\t"
       << "trials: " << h_naive->GetEntries()  << "\t"
       << "mean_naive: " << h_naive->GetMean() << "\t"
       << "rms_naive: " << h_naive->GetRMS() << "\t" 
       << "mean_meanvar: " << h_meanvar->GetMean() << "\t"
       << "rms_meanvar: " << h_meanvar->GetRMS() << "\t" 
       << endl;

  h_naive->SetLineWidth(2);
  h_naive->SetLineColor(kRed);
  h_naive->Draw("hsame");

  h_meanvar->SetLineWidth(2);
  h_meanvar->SetLineColor(kBlue);
  h_meanvar->Draw("hsame");

  c->Modified();
  //frame->SetFillColor(kBlack);
  //  l->Draw("same");
  c->SetLogy();
  c->Update();
  c->Modified();

}
