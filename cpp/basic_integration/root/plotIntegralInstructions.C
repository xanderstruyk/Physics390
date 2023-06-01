

void
plotIntegralInstructions(int ntrials, int nevts) {

  const int   N_PLOTS   = 5;
  const float LINEWIDTH = 3;
  const int   nbins     = 10000;
  const float minX_naive   = 120000000;
  const float maxX_naive   = 250000000;
  const float minX_meanvar = 80000000;
  const float maxX_meanvar = 150000000;

  gStyle->SetOptStat(1101);

  char Olevel[N_PLOTS][256] = { "O0", "O1", "O2", "O3", "Ofast" };
  EColor Ocolors[N_PLOTS]   = { kBlack, kRed, kViolet, kBlue, EColor(kGreen+2) };

  TTree *t_naive[N_PLOTS], *t_meanvar[N_PLOTS]; 
  TH1F  *h_naive[N_PLOTS], *h_meanvar[N_PLOTS]; 
  TPaveStats *s_naive[N_PLOTS], *s_meanvar[N_PLOTS]; 

  char mystr[256]; // for histo name, file name, etc



  //
  // Naive
  //

  for( int i=0; i<N_PLOTS; i++ ) { 

    sprintf(mystr, "hnaive_%s", Olevel[i]);
    h_naive[i] = new TH1F(mystr,mystr,nbins,minX_naive,maxX_naive);

    sprintf(mystr, "./data/stat_%s_pi_1D_Naive_ntrials_%d_samples_%d.dat", Olevel[i], ntrials, nevts);    
    t_naive[i] = new TTree("t","t");
    t_naive[i]->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I:l4/C:deltaT/F:l5/C:instru/F");
    sprintf(mystr, "instru>>hnaive_%s", Olevel[i]);
    t_naive[i]->Draw(mystr,"","goff");

    h_naive[i]->SetLineColor(Ocolors[i]);
    h_naive[i]->SetLineWidth(LINEWIDTH);

  }





  //
  // MeanVar
  //

  for( int i=0; i<N_PLOTS; i++ ) { 

    sprintf(mystr, "hmeanvar_%s", Olevel[i]);
    h_meanvar[i] = new TH1F(mystr,mystr,nbins,minX_meanvar,maxX_meanvar);

    sprintf(mystr, "./data/stat_%s_pi_1D_MeanVariance_ntrials_%d_samples_%d.dat", Olevel[i], ntrials, nevts);    
    t_meanvar[i] = new TTree("t","t");
    t_meanvar[i]->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I:l4/C:deltaT/F:l5/C:instru/F");
    sprintf(mystr, "instru>>hmeanvar_%s", Olevel[i]);
    t_meanvar[i]->Draw(mystr,"","goff");

    h_meanvar[i]->SetLineColor(Ocolors[i]);
    h_meanvar[i]->SetLineWidth(LINEWIDTH);

  }



  //
  // draw
  //

  TCanvas * c = new TCanvas("c","c", 0, 0, 700, 600);
  TH1F* frame = (TH1F*)(c->DrawFrame(0.9*minX_naive, 0.1, 1.1*maxX_naive, 2*h_naive[N_PLOTS-1]->GetMaximum()));
  frame->GetXaxis()->SetTitle("# instructions");
  for( int i=0; i<N_PLOTS; i++ )
    h_naive[i]->Draw("samesh");
  c->SetLogy();
  c->Modified();
  c->Update();

  for( int i=0; i<N_PLOTS; i++ ) { 
    s_naive[i] = (TPaveStats*)(h_naive[i]->GetListOfFunctions()->FindObject("stats"));
    s_naive[i]->SetTextColor(Ocolors[i]);
    float y1 = 0.95-i*0.15;
    float y2 = 0.85-i*0.15;
    s_naive[i]->SetY1NDC(y1);
    s_naive[i]->SetY2NDC(y2);
  }
  c->Modified();
  c->Update();

  TCanvas * cc = new TCanvas("cc","cc", 700, 0, 700, 600);
  TH1F* fframe = (TH1F*)(cc->DrawFrame(0.9*minX_meanvar, 0.1, 1.1*maxX_meanvar, 2*h_naive[N_PLOTS-1]->GetMaximum()));
  fframe->GetXaxis()->SetTitle("# instructions");
  for( int i=0; i<N_PLOTS; i++ )
   h_meanvar[i]->Draw("samesh");
  cc->SetLogy();
  cc->Modified();
  cc->Update();

  for( int i=0; i<N_PLOTS; i++ ) { 
    s_meanvar[i] = (TPaveStats*)(h_meanvar[i]->GetListOfFunctions()->FindObject("stats"));
    s_meanvar[i]->SetTextColor(Ocolors[i]);
    float y1 = 0.95-i*0.15;
    float y2 = 0.85-i*0.15;
    s_meanvar[i]->SetY1NDC(y1);
    s_meanvar[i]->SetY2NDC(y2);
  }
  cc->Modified();
  cc->Update();

}
