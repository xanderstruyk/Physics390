
int plotDoubleGaussianSampleStdErr() {

  // 'stddev' is the SD of the sample means
  // 'meanvar' is the avg var of the samples 
  //   the SEM = sqrt(meanvar/Nevts)

  TTree * t = new TTree("t","t");
  t->ReadFile("./data/double_gaussian_sampling/sample_stats_std.dat","Nevts/I:stddev/F:meanvar/F");

  TLegend * leg = new TLegend(0.7,0.6,0.9,0.9);
  leg->SetTextSize(0.05);

  TCanvas * c = new TCanvas("c","c",0,0,600,500);
  TH1F* frame = (TH1F*)(c->DrawFrame(0,0.1*t->GetMinimum("stddev"),1.5*t->GetMaximum("Nevts"),1.5*t->GetMaximum("stddev")));
  t->SetMarkerColor(kBlue);
  t->SetMarkerStyle(20);
  t->SetMarkerSize(1.2);
  leg->AddEntry(t,"#sigma_{means}","p");
  
  t->Draw("stddev:Nevts","","same");
  t->SetLineColor(kRed);
  t->SetLineWidth(2);
  t->Draw("sqrt(meanvar/Nevts):Nevts","","lsame");
  leg->AddEntry(t,"#frac{#sigma_{sample}}{#sqrt{N}}","l");

  c->SetLogy();
  c->SetLogx();
  leg->Draw("same");
  c->Print("png/double_gaussian_sampling/sample_stats_stderr.png");

  return 0;
}
