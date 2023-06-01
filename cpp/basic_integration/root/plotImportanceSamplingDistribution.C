void plotImportanceSamplingDistribution() {

  const int nbins = 200;
  const float range_i = -50;
  const float range_f = 50;

  TTree * tu = new TTree("tu","tu");
  tu->ReadFile("./data/importance_example/uniform.dat", "x/F:val/F");
  TTree * ts = new TTree("ts","ts");
  ts->ReadFile("./data/importance_example/student.dat", "x/F:val/F");
  TTree * ts30 = new TTree("ts30","ts30");
  ts30->ReadFile("./data/importance_example/student30.dat", "x/F:val/F");

  
  TH1F * hu = new TH1F("hu","hu", nbins, range_i, range_f);
  TH1F * hs = new TH1F("hs","hs", nbins, range_i, range_f);
  TH1F * hs30 = new TH1F("hs30","hs30", nbins, range_i, range_f);
  tu->Draw("x>>hu","","goff");
  ts->Draw("x>>hs","","goff");
  ts30->Draw("x>>hs30","","goff");
  
  hu->SetLineColor(kBlack);
  hs->SetLineColor(kViolet);
  hs30->SetLineColor(kBlue);
  hu->SetLineWidth(2);
  hs->SetLineWidth(2);
  hs30->SetLineWidth(2);


  TCanvas * c = new TCanvas("c","c", 0, 0, 600, 500);
  // zoom in 
  TH1F* frame = (TH1F*)(c->DrawFrame(-10,0,10,1.2*hs30->GetMaximum()));

  hu->Draw("same");
  hs->Draw("same");
  hs30->Draw("same");

  TF1* f = new TF1("f","gaus",range_i,range_f);

  float amp = (1000./sqrt(2*TMath::Pi())) * (range_f-range_i)/nbins;

  f->SetParameter(0,amp);
  f->SetParameter(1,0.);
  f->SetParameter(2,1.);
  f->SetLineColor(kRed);
  f->SetLineWidth(2);
  f->Draw("same");

  c->Print("./png/importance_example/sampling_distribs.png");

}
