void
plotUniform() {

  // read in the data
  TTree * t = new TTree("t","t");
  t->ReadFile("uniform.dat","l0/C:index/I:l1/C:val/D");

  // make a histogram and fill the histo with it
  TH1F * h = new TH1F("h","h", 100, -5, 5);
  t->Draw("val>>h", "", "goff");

  // now draw it
  TCanvas * c = new TCanvas("c","c",0,0,700,500);
  TH1F* frame = (TH1F*)(c->DrawFrame(-5.,0.,5.,1.1*h->GetMaximum()));
  h->Draw("sames");

}
