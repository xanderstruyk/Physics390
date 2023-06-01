
//
// hard coded paths ...
//
char fname[512];

int plotCombinedStdErrSummary() {

  //
  // homemade crude (red) / plain (blue)
  //

  TTree * t_plain = new TTree("t","t");
  sprintf(fname,"./data/plain_integration/stats_plain.dat");
  t_plain->ReadFile(fname, "nevts/F:I_mean_hm/F:I_rms_hm/F:I_stderr_hm/F:I_mean_sm/F:I_rms_sm/F:I_stderr_sm/F");

  t_plain->SetBranchStatus("*",0);
  t_plain->SetBranchStatus("nevts",1);
  t_plain->SetBranchStatus("I_rms_hm",1);
  t_plain->SetBranchStatus("I_stderr_hm",1);
  TTree * t_plain_hm = t_plain->CloneTree();
  t_plain_hm->Draw("nevts:I_rms_hm:I_stderr_hm","","goff");

  t_plain->SetBranchStatus("*",0);
  t_plain->SetBranchStatus("nevts",1);
  t_plain->SetBranchStatus("I_rms_sm",1);
  t_plain->SetBranchStatus("I_stderr_sm",1);
  TTree * t_plain_sm = t_plain->CloneTree();
  t_plain_sm->Draw("nevts:I_rms_sm:I_stderr_sm","","goff");

  TGraph * g_plain_rms_hm    = new TGraph( t_plain_hm->GetEntries(), t_plain_hm->GetV1(), t_plain_hm->GetV2());
  g_plain_rms_hm->Print();
  TGraph * g_plain_stderr_hm = new TGraph( t_plain_hm->GetEntries(), t_plain_hm->GetV1(), t_plain_hm->GetV3());
  TGraph * g_plain_rms_sm    = new TGraph( t_plain_sm->GetEntries(), t_plain_sm->GetV1(), t_plain_sm->GetV2());
  TGraph * g_plain_stderr_sm = new TGraph( t_plain_sm->GetEntries(), t_plain_sm->GetV1(), t_plain_sm->GetV3());


  g_plain_rms_hm->SetMarkerStyle(20);
  g_plain_rms_hm->SetMarkerSize(1.2);
  g_plain_rms_hm->SetMarkerColor(kRed);
  g_plain_stderr_hm->SetLineColor(kRed);
  g_plain_stderr_hm->SetLineWidth(2);

  g_plain_rms_sm->SetMarkerStyle(20);
  g_plain_rms_sm->SetMarkerSize(1.2);
  g_plain_rms_sm->SetMarkerColor(kBlue);
  g_plain_stderr_sm->SetLineColor(kBlue);
  g_plain_stderr_sm->SetLineWidth(2);


  //
  // gsl plain (magenta)
  //

  TTree * t_gsl = new TTree("t_gsl","t_gsl");
  sprintf(fname, "./data/gsl_1d/gsl_sample_stderr.dat");
  t_gsl->ReadFile(fname,"Nevts/F:I_mean/F:I_rms/F:S_mean/F");

  t_gsl->SetBranchStatus("*",0);
  t_gsl->SetBranchStatus("Nevts",1);
  t_gsl->SetBranchStatus("I_rms",1);
  TTree * t_gsl_rms = t_gsl->CloneTree();
  t_gsl_rms->Draw("Nevts:I_rms","","goff");
  TGraph * g_rms_gsl = new TGraph(t_gsl_rms->GetEntries(),t_gsl_rms->GetV1(),t_gsl_rms->GetV2());


  t_gsl->SetBranchStatus("*",0);
  t_gsl->SetBranchStatus("Nevts",1);
  t_gsl->SetBranchStatus("S_mean",1);
  TTree * t_gsl_smean = t_gsl->CloneTree();
  t_gsl_smean->Draw("Nevts:S_mean","","goff");
  TGraph * g_smean_gsl = new TGraph(t_gsl_smean->GetEntries(),t_gsl_smean->GetV1(),t_gsl_smean->GetV2());

  g_rms_gsl->SetMarkerColor(kMagenta);
  g_rms_gsl->SetMarkerStyle(25);
  g_rms_gsl->SetMarkerSize(1.5);

  g_smean_gsl->SetLineColor(kViolet);
  g_smean_gsl->SetLineWidth(2);

  
  //
  // homemade un-weighted vegas ( plain: yellow open diamond, adaptive: filled cyan circle, adaptive shifted : cyan cross )
  //

  TTree * t_unweighted = new TTree("t","t");
  sprintf(fname, "./data/vegas_1d_ng_50/sample_stderr.dat");
  t_unweighted->ReadFile(fname,"Nevts/I:Nevts_new/F:avgU/F:avgV/F:rmsU/F:rmsV/F:varU/F:varV/F:stderrU/F:stderrV/F");

  t_unweighted->SetBranchStatus("*",0);
  t_unweighted->SetBranchStatus("Nevts",1);
  t_unweighted->SetBranchStatus("rmsU",1);
  TTree * t_first_rms = t_unweighted->CloneTree();
  t_first_rms->Draw("Nevts:rmsU","","goff");
  TGraph * g_first_rms = new TGraph(t_first_rms->GetEntries(),t_first_rms->GetV1(),t_first_rms->GetV2());

  t_unweighted->SetBranchStatus("*",0);
  t_unweighted->SetBranchStatus("Nevts",1);
  t_unweighted->SetBranchStatus("rmsV",1);
  TTree * t_last_rms = t_unweighted->CloneTree();
  t_last_rms->Draw("(Nevts):rmsV","","goff");
  TGraph * g_last_rms = new TGraph(t_last_rms->GetEntries(),t_last_rms->GetV1(),t_last_rms->GetV2());
  TTree * t_last_rms_shifted = t_unweighted->CloneTree();
  t_last_rms_shifted->Draw("(Nevts*20):rmsV","","goff");
  TGraph * g_last_rms_shifted = new TGraph(t_last_rms_shifted->GetEntries(),t_last_rms_shifted->GetV1(),t_last_rms_shifted->GetV2());


  g_first_rms->SetMarkerColor(kYellow);
  g_first_rms->SetMarkerStyle(27);
  g_first_rms->SetMarkerSize(2.5);
  g_last_rms->SetMarkerColor(kCyan);
  g_last_rms->SetMarkerStyle(20);
  g_last_rms->SetMarkerSize(1.2);
  g_last_rms_shifted->SetMarkerColor(kCyan);
  g_last_rms_shifted->SetMarkerStyle(2);
  g_last_rms_shifted->SetMarkerSize(1.2);
  


  //
  // homemade weighted vegas ( green+2 )
  //

  TTree * t_weighted = new TTree("t_weighted","t_weighted");
  sprintf(fname, "./data/vegas_1d_ng_50/weighted_sample_stderr.dat");
  t_weighted->ReadFile(fname,"Nevts/I:wIavg/F:wIrms/F:wIerr/F");
  t_weighted->SetBranchStatus("*",0);
  t_weighted->SetBranchStatus("Nevts",1);
  t_weighted->SetBranchStatus("wIrms",1);
  TTree * t_weighted_rms = t_weighted->CloneTree();
  t_weighted_rms->Draw("(Nevts*20):wIrms","","goff");
  TGraph * g_weighted_rms = new TGraph(t_weighted_rms->GetEntries(),t_weighted_rms->GetV1(),t_weighted_rms->GetV2());
  g_weighted_rms->SetMarkerColor(kGreen+2);
  g_weighted_rms->SetMarkerStyle(20);
  g_weighted_rms->SetMarkerSize(1.2);
  g_weighted_rms->SetLineColor(kGreen+2);
  g_weighted_rms->SetLineWidth(2);

  

  
  //
  // gsl vegas (orange-3)
  //

  TTree * t_vegas_gsl = new TTree("t","t");
  sprintf(fname, "data/vegas_gsl_1d/sample_stderr.dat");
  t_vegas_gsl->ReadFile(fname,"Nevts/I:wIavg/F:wIrms/F:wIerr/F");
  t_vegas_gsl->SetBranchStatus("*",0);
  t_vegas_gsl->SetBranchStatus("Nevts",1);
  t_vegas_gsl->SetBranchStatus("wIrms",1);
  TTree * t_vegas_gsl_rms = t_vegas_gsl->CloneTree();
  t_vegas_gsl_rms->Draw("(Nevts*20):wIrms","","goff");
  TGraph * g_vegas_gsl_rms = new TGraph(t_vegas_gsl_rms->GetEntries(),t_vegas_gsl_rms->GetV1(),t_vegas_gsl_rms->GetV2());
  g_vegas_gsl_rms->SetMarkerColor(kOrange-3);
  g_vegas_gsl_rms->SetMarkerStyle(25);
  g_vegas_gsl_rms->SetMarkerSize(1.7);











  TCanvas * c = new TCanvas("c","c",0,0,1200,500);
  c->SetFillColor(kBlack);
  TH1F* frame = (TH1F*)(c->DrawFrame(9000,5e-5,20*1100000,0.05));
  frame->GetXaxis()->SetTitle("N_{evt}");
  frame->GetXaxis()->SetAxisColor(kWhite);
  frame->GetXaxis()->SetLabelColor(kWhite);
  frame->GetXaxis()->SetTitleColor(kWhite);
  frame->GetYaxis()->SetTitle("Std. Err");
  frame->GetYaxis()->SetAxisColor(kWhite);
  frame->GetYaxis()->SetLabelColor(kWhite);
  frame->GetYaxis()->SetTitleColor(kWhite);



  //
  // first draw the homemade crude/plain, and gsl plain
  //

  g_plain_rms_hm->Draw("p");
  //g_plain_stderr_hm->Draw("l");
  g_plain_rms_sm->Draw("p");
  //  g_plain_stderr_sm->Draw("l");
  g_rms_gsl->Draw("p");


  //
  // fit the homemade crude and plain
  //

  TF1 *flinear_hm = new TF1("flinear_hm", "[0]*TMath::Power(x,[1])", 10000, 20*1000000);
  flinear_hm->SetParameter(0,0.02);
  flinear_hm->SetParameter(1,-0.5);
  flinear_hm->SetLineColor(kRed);
  g_plain_rms_hm->Fit("flinear_hm", "","", 10000, 20*1000000);

  TF1 *flinear_sm = new TF1("flinear_sm", "[0]*TMath::Power(x,[1])", 10000, 20*1000000);
  flinear_sm->SetParameter(0,0.02);
  flinear_sm->SetParameter(1,-0.5);
  flinear_sm->SetLineColor(kBlue);
  g_rms_gsl->Fit("flinear_sm", "","", 10000, 20*1000000);


  //
  // now draw first iteration from homemade vegas, should lie 
  // on top of the plain abovie
  //


  g_first_rms->Draw("p");
  g_plain_rms_sm->Draw("p"); // redraw homemade plain so that points are on top


  //
  // draw the last iteration from the homemade vegas 
  //
  g_last_rms->Draw("p");
  g_last_rms_shifted->Draw("p");


  //
  // draw and fit the weighted homemade vegas
  //

  TF1 *flinear_wv = new TF1("flinear_wv", "[0]*TMath::Power(x,[1])", 10000, 20*1000000);
  flinear_wv->SetParameter(0,1.);
  flinear_wv->SetParameter(1,-0.5);
  flinear_wv->SetLineColor(kGreen+2);

  g_weighted_rms->Draw("p");
  g_weighted_rms->Fit("flinear_wv", "","", 10000, 20*1000000);


  //
  // draw the weighted gsl vegas
  //


  g_vegas_gsl_rms->Draw("p");


  c->SetLogy();
  c->SetLogx();
  //c->SetGridx();
  //c->SetGridy();
  //sprintf(fname, "%s/stderr_scaling.png",opath);
  //  c->Print(fname);


  TLegend * l1 = new TLegend(0.5,0.75,0.7,0.98);
  l1->SetFillColor(kBlack);
  l1->SetTextSizePixels(20);
  l1->SetTextColor(kWhite);
  l1->AddEntry( g_plain_rms_hm, "Hit or Miss", "p");
  l1->AddEntry( g_plain_rms_sm, "Sample Means", "p");
  l1->AddEntry( g_rms_gsl, "Sample Means GSL", "p");
  l1->Draw("same");

  TLegend * l2 = new TLegend(0.7,0.65,0.98,0.98);
  l2->SetFillColor(kBlack);
  l2->SetTextSizePixels(20);
  l2->SetTextColor(kWhite);
  l2->AddEntry( g_first_rms, "Vegas first iteration", "p");
  l2->AddEntry( g_last_rms, "Vegas last iteration", "p");
  l2->AddEntry( g_last_rms_shifted, "Vegas last itr., shifted", "p");
  l2->AddEntry( g_weighted_rms, "Vegas weighted", "p");
  l2->AddEntry( g_vegas_gsl_rms, "Vegas GSL weighted", "p");
  l2->Draw("same");

  return 0;
}
