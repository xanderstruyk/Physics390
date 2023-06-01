

void
plotIntegralInstructionsTime(int ntrials, int nevts) {

  const float LINEWIDTH = 3;
  const int   nbins     = 100000;
  const float minX      = 100000000;
  const float maxX      = 250000000;

  gStyle->SetOptStat(1101);


  TTree *t_naive, *t_meanvar; 
  TH1F  *h_naive, *h_meanvar;  // instructions
  TPaveStats *s_naive, *s_meanvar; 

  char mystr[256]; // for histo name, file name, etc



  //
  // Naive
  //
  h_naive = new TH1F("hnaive","hnaive",nbins,minX,maxX);
  sprintf(mystr, "./data/stat_O0_pi_1D_Naive_ntrials_%d_samples_%d.dat", ntrials, nevts);    
  t_naive = new TTree("tnaive","tnaive");
  t_naive->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I:l4/C:deltaT/F:l5/C:instru/F");
  t_naive->Draw("instru>>hnaive","","goff");
  h_naive->SetLineColor(kRed);
  h_naive->SetLineWidth(LINEWIDTH);


  //
  // MeanVar
  //
  h_meanvar = new TH1F("hmeanvar","hmeanvar",nbins,minX,maxX);
  sprintf(mystr, "./data/stat_O0_pi_1D_MeanVariance_ntrials_%d_samples_%d.dat", ntrials, nevts);    
  t_meanvar = new TTree("tmeanvar","tmeanvar");
  t_meanvar->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I:l4/C:deltaT/F:l5/C:instru/F");
  t_meanvar->Draw("instru>>hmeanvar","","goff");
  h_meanvar->SetLineColor(kRed);
  h_meanvar->SetLineWidth(LINEWIDTH);


  //
  // draw
  //

  TCanvas * c = new TCanvas("c","c", 0, 0, 700, 600);
  TH1F* frame = (TH1F*)(c->DrawFrame(0.9*minX, 0.1, 1.1*maxX, 2*h_meanvar->GetMaximum()));
  frame->GetXaxis()->SetTitle("# instructions");
  h_naive->Draw("samesh");
  h_meanvar->Draw("samesh");
  c->SetLogy();
  c->Modified();
  c->Update();

  s_naive = (TPaveStats*)(h_naive->GetListOfFunctions()->FindObject("stats"));
  s_naive->SetTextColor(kRed);
  s_naive->SetY1NDC(0.85);
  s_naive->SetY2NDC(0.75);
  s_meanvar = (TPaveStats*)(h_meanvar->GetListOfFunctions()->FindObject("stats"));
  s_meanvar->SetTextColor(kRed);
  s_meanvar->SetY1NDC(0.75);
  s_meanvar->SetY2NDC(0.65);
  c->Modified();
  c->Update();


  TCanvas * cc = new TCanvas("cc","cc", 700, 0, 700, 600);
  t_naive->Draw("instru:deltaT", "", "Colz");

  TCanvas * ccc = new TCanvas("ccc","ccc", 1400, 0, 700, 600);
  t_meanvar->Draw("instru:deltaT", "", "Colz");

}
