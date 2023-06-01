void plotImportanceIntegral() {

  const int nbins = 100;
  const float range_avg_i = 0.8;
  const float range_avg_f = 1.2;
  const float range_err_i = 0.0;
  const float range_err_f = 0.3;

  char text[256];

  TTree * t = new TTree("t","t");
  t->ReadFile("./data/importance_example/integrals.dat", "trial/I:avgU/F:avgS/F:avgS30/F:stdU/F:stdS/F:stdS30/F");


  //
  // plot the integrals
  //
  
  TH1F * h_avg_u = new TH1F("h_avg_u","h_avg_u", nbins, range_avg_i, range_avg_f);
  TH1F * h_avg_s = new TH1F("h_avg_s","h_avg_s", nbins, range_avg_i, range_avg_f);
  TH1F * h_avg_s30 = new TH1F("h_avg_s30","h_avg_s30", nbins, range_avg_i, range_avg_f);
  t->Draw("avgU>>h_avg_u","","goff");
  t->Draw("avgS>>h_avg_s","","goff");
  t->Draw("avgS30>>h_avg_s30","","goff");
  
  h_avg_u->SetLineColor(kBlack);
  h_avg_s->SetLineColor(kViolet);
  h_avg_s30->SetLineColor(kBlue);
  h_avg_u->SetLineWidth(2);
  h_avg_s->SetLineWidth(2);
  h_avg_s30->SetLineWidth(2);
  
  
  TCanvas * c = new TCanvas("c","c", 0, 0, 600, 500);
  // zoom in 
  TH1F* frame = (TH1F*)(c->DrawFrame(range_avg_i,1.,range_avg_f,10*h_avg_s30->GetMaximum()));
  frame->GetXaxis()->SetTitle("Integral");
  frame->GetYaxis()->SetTitle("Trials");
  h_avg_u->Draw("same");
  h_avg_s->Draw("same");
  h_avg_s30->Draw("same");
  
  c->SetLogy();

  TPaveText * leg = new TPaveText(0.6,0.6,0.89,0.89,"NDC");

  sprintf(text,"#mu_{U} = %f, #sigma_{U} = %f", h_avg_u->GetMean(), h_avg_u->GetRMS());
  leg->AddText(text);
  sprintf(text,"#mu_{S} = %f, #sigma_{S} = %f", h_avg_s->GetMean(), h_avg_s->GetRMS());
  leg->AddText(text);
  sprintf(text,"#mu_{S30} = %f, #sigma_{S30} = %f", h_avg_s30->GetMean(), h_avg_s30->GetRMS());
  leg->AddText(text);
  leg->SetFillColor(0);
  leg->Draw("same");

  c->Print("./png/importance_example/integrals.png");
  


  //
  // plot the estimated stderr of the sampling means
  //

  
  TH1F * h_stderr_u = new TH1F("h_stderr_u","h_stderr_u", nbins, range_err_i, range_err_f);
  TH1F * h_stderr_s = new TH1F("h_stderr_s","h_stderr_s", nbins, range_err_i, range_err_f);
  TH1F * h_stderr_s30 = new TH1F("h_stderr_s30","h_stderr_s30", nbins, range_err_i, range_err_f);
  t->Draw("stdU>>h_stderr_u","","goff");
  t->Draw("stdS>>h_stderr_s","","goff");
  t->Draw("stdS30>>h_stderr_s30","","goff");
  
  h_stderr_u->SetLineColor(kBlack);
  h_stderr_s->SetLineColor(kViolet);
  h_stderr_s30->SetLineColor(kBlue);
  h_stderr_u->SetLineWidth(2);
  h_stderr_s->SetLineWidth(2);
  h_stderr_s30->SetLineWidth(2);
  


  TCanvas * cc = new TCanvas("cc","cc", 600, 0, 600, 500);
  // zoom in 
  TH1F* frame2 = (TH1F*)(cc->DrawFrame(range_err_i,1.,range_err_f,1.2*h_stderr_s30->GetMaximum()));
  frame2->GetXaxis()->SetTitle("[StdErr]");
  frame2->GetYaxis()->SetTitle("Trials");
  h_stderr_u->Draw("same");
  h_stderr_s->Draw("same");
  h_stderr_s30->Draw("same");
  
  cc->SetLogy();

  TPaveText * leg2 = new TPaveText(0.7,0.7,0.89,0.89,"NDC");

  sprintf(text,"#mu_{U} = %f", h_stderr_u->GetMean());
  leg2->AddText(text);
  sprintf(text,"#mu_{S} = %f", h_stderr_s->GetMean());
  leg2->AddText(text);
  sprintf(text,"#mu_{S30} = %f", h_stderr_s30->GetMean());
  leg2->AddText(text);
  leg2->SetFillColor(0);
  leg2->Draw("same");


}
