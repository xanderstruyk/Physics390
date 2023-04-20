#define N_SAMPLE_SIZES 7


void
plotCircleTrialsMeanVariance() {

 
  gStyle->SetOptStat(0);

  int trials=1000;
  char mystr[256]; // for histo name, file name, etc

  int sample_sizes[N_SAMPLE_SIZES]={ 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
  EColor sample_color[N_SAMPLE_SIZES]={ kWhite, EColor(kOrange+7), kYellow, kGreen, kBlue, kMagenta, kRed };

  TH1F *  harr[N_SAMPLE_SIZES];  TTree * tarr[N_SAMPLE_SIZES]; TPaveStats * sarr[N_SAMPLE_SIZES];
  for( int i=0; i<N_SAMPLE_SIZES; i++ ) {

    sprintf(mystr, "h%d", sample_sizes[i]);
    if( i == 0 )
      harr[i] = new TH1F(mystr,mystr,100,0,6);
    else 
      harr[i] = new TH1F(mystr,mystr,100,3.0,3.3);

    sprintf(mystr, "t%d", sample_sizes[i]);    
    tarr[i] = new TTree(mystr,mystr);
    sprintf(mystr, "./data/pi_1D_MeanVariance_ntrials_%d_samples_%d.dat", trials, sample_sizes[i]);    
    tarr[i]->ReadFile(mystr, "l0/C:area/F:l1/C:pi/F:l2/C:err/F:l3/C:trials/I");

    sprintf(mystr, "pi>>h%d", sample_sizes[i]);
    tarr[i]->Draw(mystr,"","goff");
    //harr[i]->SetFillColor(kBlack);
    harr[i]->SetLineColor(sample_color[i]);
    harr[i]->SetLineWidth(2);
  }

  TCanvas * c = new TCanvas("c","c", 0, 0, 700, 600);
  c->SetFillColor(kBlack);
  TH1F* frame = (TH1F*)(c->DrawFrame(3.,0.1,3.3,1.1*harr[N_SAMPLE_SIZES-1]->GetMaximum()));
  frame->SetName("myframe");
  frame->SetFillColor(kBlack);
  frame->GetXaxis()->SetTitle("#hat{#pi}");
  frame->GetXaxis()->SetAxisColor(kWhite);
  frame->GetXaxis()->SetLabelColor(kWhite);
  frame->GetXaxis()->SetTitleColor(kWhite);
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->SetAxisColor(kWhite);
  frame->GetYaxis()->SetLabelColor(kWhite);
  frame->GetYaxis()->SetTitleColor(kWhite);

  TLegend * l = new TLegend(0.65,0.7, 0.95,0.95);
  l->SetFillColor(kBlack);
  l->SetTextColor(kWhite);

  for( int i=0; i<N_SAMPLE_SIZES; i++ ) { 

    cout << "samples: " << sample_sizes[i] << "\t"
	 << "mean: " << harr[i]->GetMean() << "\t"
	 << "rms: " << harr[i]->GetRMS() << "\t" 
	 << "err: " << tarr[i]->GetMinimum("err") << "\t"
	 << "trials: " << harr[i]->GetEntries()  << "\t"
	 << endl;

    if( i>0 ) harr[i]->Draw("hsame");

    sprintf(mystr, "n=%d, #sigma=%f", sample_sizes[i], harr[i]->GetRMS());
    l->AddEntry(harr[i],mystr,"l");

    //sarr[i] = (TPaveStats*)(harr[i]->GetListOfFunctions()->FindObject("stats"));
    //sarr[i]->SetFillColor(kBlack);
    //sarr[i]->SetTextColor(sample_color[i]);
  }

  c->Modified();
  frame->SetFillColor(kBlack);
  l->Draw("same");
  c->SetLogy();
  c->Update();
  c->Modified();

}
