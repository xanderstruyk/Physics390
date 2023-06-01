void
plotVolumeNaive() {

  gStyle->SetOptStat(0);

  TTree * t = new TTree("t","t");
  t->ReadFile("./data/sphere.dat", "l0/C:inside/I:l1/C:x/F:l2/C:y/F:l3/C:z/F");

  TCanvas * c = new TCanvas("c","c", 0, 0, 700, 600);

  t->SetMarkerStyle(20);
  t->SetMarkerSize(0.7);
	     
  t->SetMarkerColor(kRed);
  t->Draw("x:y:z", "inside==0");
  t->SetMarkerColor(kBlue);
  t->Draw("x:y:z", "inside==1", "same");

}
