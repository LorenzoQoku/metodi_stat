#include "analisi_beta_oned.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"


//La funzione esegue il fit dell'istogramma dei valori di beta calcolati

void graph(){

    Int_t nbins=15000;
    Int_t nbins3=60;
    Double_t min=0;
    Double_t max=1;

    string a="/home/lorenzo/documenti/metodi_stat/Efficienze_e_particelle_totali/data_Lorenzo_Qoku.txt";

    TH1F *h = new TH1F( "hname","htitle",nbins,min,max);
    TH2F *h2 = new TH2F( "h2name","h2title",nbins3,min,max,nbins3,min,max);
    h->GetXaxis()->SetTitle("X axis (units)");
    h->GetYaxis()->SetTitle("Entries");
    h->SetLineColor(kRed+2);
    h->SetLineWidth(2);
    h->SetFillColor(kRed-7);

    h2->GetXaxis()->SetTitle("X axis (units)");
    h2->GetYaxis()->SetTitle("Entries");
    h2->SetLineColor(kRed+2);
    h2->SetLineWidth(2);
    h2->SetFillColor(kRed-7);
    
    TF2* f=new TF2("f","([0])*exp((x-[1])^2/[2])*exp((y-[3])^2/[4])",0.4,1,0.4,1);
    isto_beta_o(a,h,h2);

    /*for(int i=1; i< nbins*nbins*+1; i++){
        h2->SetBinError(i, sqrt(h2->GetBinContent(i)));
    }

    f->SetParameters(4000,0.998,0.005,0.998,0.005);
	h2->Fit(f,"0","",0,1);
    cout<<"Fit parameters: "<<endl;
    for(int i=0;i<5;i++){
        cout<<"Parameter "<<i<<": "<<f->GetParameter(i)<<endl;
    }
    cout<<"Chi2/NDF: "<<f->GetChisquare()/f->GetNDF()<<endl;

    TCanvas *c = new TCanvas("cname","ctitle",-1000, 1000);
    c->cd()->SetGrid();
    h->Draw("");*/
    TCanvas *c2 = new TCanvas("c2name","c2title",-1000, 1000);
    c2->cd()->SetGrid();
    h2->Draw("lego");

}