
int plotDoubleGaussianSample(int index, unsigned Nsamples, unsigned Nevts) {

  char fname[512];
  sprintf(fname,"./data/double_gaussian_sampling/sample_%d_Nsamples_%d_Nevts_%d.dat",
	  index,Nsamples,Nevts);
  
  TTree * t = new TTree("t","t");
  t->ReadFile(fname,"index/I:x/F");

  TCanvas * c = new TCanvas("c","c",0,0,600,500);
  TH1F * h = new TH1F("h","h",100,-5,5);
  t->Draw("x>>h","","goff");

  c->DrawFrame(-5,0.1,5,1.1*h->GetMaximum());
  h->SetLineColor(kBlue);
  h->SetLineWidth(2);
  h->Draw("sames");
  //  TH1F * h = new TH1F("h","h",100,-5,5);


  char pngname[512];
  sprintf(pngname,"./png/double_gaussian_sampling/sample_%d_Nsamples_%d_Nevts_%d.png",
	  index,Nsamples,Nevts);
  c->Print(pngname);

  return 0;
}
