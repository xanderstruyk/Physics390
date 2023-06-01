#define N_SAMPLE_SIZES 7


void
plotCompareNaiveVSMeanVarianceErrors() {



  gStyle->SetOptStat(0);

  int trials=1000;
  char mystr[256]; // for histo name, file name, etc

  int sample_sizes[N_SAMPLE_SIZES]={ 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
  EColor sample_color[N_SAMPLE_SIZES]={ kWhite, EColor(kOrange+7), kYellow, kGreen, kBlue, kMagenta, kRed };

  TH1F *  harr_circ[N_SAMPLE_SIZES];  TTree * tarr_circ[N_SAMPLE_SIZES];
  TH1F *  harr_sph[N_SAMPLE_SIZES];  TTree * tarr_sph[N_SAMPLE_SIZES];
  TH1F *  harr_mv[N_SAMPLE_SIZES];  TTree * tarr_mv[N_SAMPLE_SIZES];

  for( int i=0; i<N_SAMPLE_SIZES; i++ ) {
    
    if( i == 0 ) { 
      sprintf(mystr, "h_circ_%d", sample_sizes[i]);
      harr_circ[i] = new TH1F(mystr,mystr,100,0,6);
      sprintf(mystr, "h_sph_%d", sample_sizes[i]);
      harr_sph[i] = new TH1F(mystr,mystr,100,0,6);
      sprintf(mystr, "h_mv_%d", sample_sizes[i]);
      harr_mv[i] = new TH1F(mystr,mystr,100,0,6);
    }
    else {
      sprintf(mystr, "h_circ_%d", sample_sizes[i]);
      harr_circ[i] = new TH1F(mystr,mystr,100,3.0,3.3);
      sprintf(mystr, "h_sph_%d", sample_sizes[i]);
      harr_sph[i] = new TH1F(mystr,mystr,100,3.0,3.3);
      sprintf(mystr, "h_mv_%d", sample_sizes[i]);
      harr_mv[i] = new TH1F(mystr,mystr,100,3.0,3.3);
    }
    
    //
    // circle
    //
    sprintf(mystr, "t_circ_%d", sample_sizes[i]);    
    tarr_circ[i] = new TTree(mystr,mystr);
    sprintf(mystr, "./data/pi_1D_Naive_ntrials_%d_samples_%d.dat", trials, sample_sizes[i]);    
    tarr_circ[i]->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I");
    
    sprintf(mystr, "pi>>h_circ_%d", sample_sizes[i]);
    tarr_circ[i]->Draw(mystr,"","goff");
    harr_circ[i]->SetLineColor(sample_color[i]);
    harr_circ[i]->SetLineWidth(2);
    
    //
    // sphere
    //
    sprintf(mystr, "t_sph_%d", sample_sizes[i]);    
    tarr_sph[i] = new TTree(mystr,mystr);
    sprintf(mystr, "./data/pi_2D_Naive_ntrials_%d_samples_%d.dat", trials, sample_sizes[i]);    
    tarr_sph[i]->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I");
    
    sprintf(mystr, "pi>>h_sph_%d", sample_sizes[i]);
    tarr_sph[i]->Draw(mystr,"","goff");
    harr_sph[i]->SetLineColor(sample_color[i]);
    harr_sph[i]->SetLineWidth(2);
  
    //
    // mean/variance
    //
    sprintf(mystr, "t_mv_%d", sample_sizes[i]);    
    tarr_mv[i] = new TTree(mystr,mystr);
    sprintf(mystr, "./data/pi_1D_MeanVariance_ntrials_%d_samples_%d.dat", trials, sample_sizes[i]);    
    tarr_mv[i]->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I");
    
    sprintf(mystr, "pi>>h_mv_%d", sample_sizes[i]);
    tarr_mv[i]->Draw(mystr,"","goff");
    harr_mv[i]->SetLineColor(sample_color[i]);
    harr_mv[i]->SetLineWidth(2);
  }
  
  
  
  vector<double> n_vals_circ, rms_vals_circ, sem_vals_circ;
  vector<double> n_vals_sph, rms_vals_sph, sem_vals_sph;
  vector<double> n_vals_mv, rms_vals_mv, sem_vals_mv;
  
  for( int i=0; i<N_SAMPLE_SIZES; i++ ) { 

    tarr_circ[i]->Draw("err>>htmp_circ","","goff");
    TH1F * htmp_circ = (TH1F*)(gDirectory->Get("htmp_circ"));
    double tmp_err_circ = htmp_circ->GetMean();
    htmp_circ->Delete();
    n_vals_circ.push_back(tarr_circ[i]->GetMinimum("trials"));
    rms_vals_circ.push_back(harr_circ[i]->GetRMS());
    sem_vals_circ.push_back(tmp_err_circ);

    tarr_sph[i]->Draw("err>>htmp_sph","","goff");
    TH1F * htmp_sph = (TH1F*)(gDirectory->Get("htmp_sph"));
    double tmp_err_sph = htmp_sph->GetMean();
    htmp_sph->Delete();
    n_vals_sph.push_back(tarr_sph[i]->GetMinimum("trials"));
    rms_vals_sph.push_back(harr_sph[i]->GetRMS());
    sem_vals_sph.push_back(tmp_err_sph);

    tarr_mv[i]->Draw("err>>htmp_mv","","goff");
    TH1F * htmp_mv = (TH1F*)(gDirectory->Get("htmp_mv"));
    double tmp_err_mv = htmp_mv->GetMean();
    htmp_mv->Delete();
    n_vals_mv.push_back(tarr_mv[i]->GetMinimum("trials"));
    rms_vals_mv.push_back(harr_mv[i]->GetRMS());
    sem_vals_mv.push_back(tmp_err_mv);
  }
  
  TGraph * g_rms_circ = new TGraph((Int_t) n_vals_circ.size(), (double*)&(n_vals_circ[0]), (double*)&(rms_vals_circ[0]));
  TGraph * g_sem_circ = new TGraph((Int_t) n_vals_circ.size(), (double*)&(n_vals_circ[0]), (double*)&(sem_vals_circ[0]));
  TGraph * g_rms_sph = new TGraph((Int_t) n_vals_sph.size(), (double*)&(n_vals_sph[0]), (double*)&(rms_vals_sph[0]));
  TGraph * g_sem_sph = new TGraph((Int_t) n_vals_sph.size(), (double*)&(n_vals_sph[0]), (double*)&(sem_vals_sph[0]));
  TGraph * g_rms_mv = new TGraph((Int_t) n_vals_mv.size(), (double*)&(n_vals_mv[0]), (double*)&(rms_vals_mv[0]));
  TGraph * g_sem_mv = new TGraph((Int_t) n_vals_mv.size(), (double*)&(n_vals_mv[0]), (double*)&(sem_vals_mv[0]));

  double minX_circ=  0.1*TMath::MinElement(g_rms_circ->GetN(),g_rms_circ->GetX());
  double minY_circ=  0.1*TMath::MinElement(g_rms_circ->GetN(),g_rms_circ->GetY());
  double maxX_circ = 10*TMath::MaxElement(g_rms_circ->GetN(),g_rms_circ->GetX());
  double maxY_circ = 10*TMath::MaxElement(g_rms_circ->GetN(),g_rms_circ->GetY());

  double minX_sph=  0.1*TMath::MinElement(g_rms_sph->GetN(),g_rms_sph->GetX());
  double minY_sph=  0.1*TMath::MinElement(g_rms_sph->GetN(),g_rms_sph->GetY());
  double maxX_sph = 10*TMath::MaxElement(g_rms_sph->GetN(),g_rms_sph->GetX());
  double maxY_sph = 10*TMath::MaxElement(g_rms_sph->GetN(),g_rms_sph->GetY());
  
  double minX_mv=  0.1*TMath::MinElement(g_rms_mv->GetN(),g_rms_mv->GetX());
  double minY_mv=  0.1*TMath::MinElement(g_rms_mv->GetN(),g_rms_mv->GetY());
  double maxX_mv = 10*TMath::MaxElement(g_rms_mv->GetN(),g_rms_mv->GetX());
  double maxY_mv = 10*TMath::MaxElement(g_rms_mv->GetN(),g_rms_mv->GetY());

  
  TCanvas * cc = new TCanvas("cc","cc",6-0,0,600,500);
  
  
  TH1F* fframe = (TH1F*)(cc->DrawFrame(TMath::Min(TMath::Min(minX_circ,minX_sph),minX_mv),
				       TMath::Min(TMath::Min(minY_circ,minY_sph),minY_mv),
				       TMath::Max(TMath::Max(maxX_circ,maxX_sph),maxX_mv),
				       TMath::Max(TMath::Max(maxY_circ,maxY_sph),maxY_mv)));


  TLegend * leg = new TLegend(0.7,0.45,0.9,0.9);
  leg->SetTextSize(0.035);
  
  //
  // Circle
  //  
  g_rms_circ->SetMarkerColor(kBlue);
  g_rms_circ->SetMarkerStyle(20);
  g_rms_circ->SetMarkerSize(1.2);
  leg->AddEntry(g_rms_circ,"#sigma^{2}_{means_2d}","p");

  g_sem_circ->SetLineColor(kRed);
  g_sem_circ->SetLineWidth(2);
  leg->AddEntry(g_sem_circ,"#sigma^{2}_{binomial}(p=#frac{#pi}{4})","l");

  //
  // Sphere
  //  
  g_rms_sph->SetMarkerColor(kViolet);
  g_rms_sph->SetMarkerStyle(20);
  g_rms_sph->SetMarkerSize(1.2);

  g_sem_sph->SetLineColor(kGreen+2);
  g_sem_sph->SetLineWidth(2);


  //
  // Mean/Variance
  //  
  g_rms_mv->SetMarkerColor(kCyan);
  g_rms_mv->SetMarkerStyle(20);
  g_rms_mv->SetMarkerSize(1.2);
  leg->AddEntry(g_rms_mv,"#sigma^{2}_{means_f}","p");

  g_sem_mv->SetLineColor(kBlack);
  g_sem_mv->SetLineWidth(2);
  leg->AddEntry(g_sem_mv,"#frac{#sigma^{2}_{f}}{#sqrt{N}}","l");

  cc->SetLogy();
  cc->SetLogx();
  g_sem_circ->Draw("l");
  g_rms_circ->Draw("p");
  g_sem_sph->Draw("l");
  g_rms_sph->Draw("p");
  g_sem_mv->Draw("l");
  g_rms_mv->Draw("p");
  leg->Draw("same");


}
