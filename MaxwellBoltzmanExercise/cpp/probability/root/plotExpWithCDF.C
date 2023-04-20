void
plotExpWithCDF() {

  // read in the data
  TTree * t = new TTree("t","t");
  t->ReadFile("data/exponential_rejection_with_cdf.dat","l0/C:index/I:l1/C:val/D:l2/C:cdfval/D");

  // make a histogram and fill the histo with it
  TH1F * h = new TH1F("h","h", 100, 0., 20);
  t->Draw("val>>h", "", "goff");

  // now draw it
  TCanvas * c = new TCanvas("c","c",0,0,700,500);
  TH1F* frame = (TH1F*)(c->DrawFrame(0.,0.,20.,1.1*h->GetMaximum()));
  h->Draw("sames");


  // make a histogram and fill the histo with it
  TH1F * hcdf = new TH1F("hcdf","hcdf", 100, 0, 1);
  t->Draw("cdfval>>hcdf", "", "goff");

  // now draw it
  TCanvas * cc = new TCanvas("cc","cc",700,0,700,500);
  TH1F* fframe = (TH1F*)(cc->DrawFrame(0.,0.,1.,1.1*hcdf->GetMaximum()));
  hcdf->Draw("sames");

}
