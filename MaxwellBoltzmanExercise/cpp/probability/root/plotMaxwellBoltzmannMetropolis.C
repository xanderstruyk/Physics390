void
plotMaxwellBoltzmannMetropolis() {

  //read in the data
  TTree * t1 = new TTree("t","t");
  t1->ReadFile("data/maxwell_boltzmann_metropolis_1.dat","l0/C:index/I:l1/C:val/D");

  TTree * t2 = new TTree("t","t");
  t2->ReadFile("data/maxwell_boltzmann_metropolis_2.dat","l0/C:index/I:l1/C:val/D");

  TTree * t5 = new TTree("t","t");
  t5->ReadFile("data/maxwell_boltzmann_metropolis_5.dat","l0/C:index/I:l1/C:val/D");
  
  // make a histogram and fill the histo with it
  TH1F * h1 = new TH1F("h","h",100,0,20);
  t1->Draw("val>>h", "", "goff");

  TH1F * h2 = new TH1F("h","h",100,0,20);
  t2->Draw("val>>h", "", "goff");
  
  TH1F * h5 = new TH1F("h","h",100,0,20);
  t5->Draw("val>>h", "", "goff");
  
  //now draw it
  TCanvas *c = new TCanvas("c","c",0,0,700,500);
  TH1F* frame1 = (TH1F*)(c->DrawFrame(0.,0.,20.,1.1*h1->GetMaximum()));
  TH1F* frame2 = (TH1F*)(c->DrawFrame(0.,0.,20.,1.1*h1->GetMaximum()));
  TH1F* frame5 = (TH1F*)(c->DrawFrame(0.,0.,20.,1.1*h1->GetMaximum()));
  h1->Draw("sames");
  h2->Draw("sames");
  h5->Draw("sames");
}

