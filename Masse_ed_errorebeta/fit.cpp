#include "analisi_beta.h"
#include "TCanvas.h"
#include "TFile.h"


void fit(){

    Int_t nbins=50000;
    Double_t min=0;
    Double_t max=1.1;

    string a="/home/lorenzo/documenti/metodi_stat/Efficienze_e_particelle_totali/data_Lorenzo_Qoku.txt";

    TH1F *h = new TH1F( "hname","htitle",nbins,min,max);
    h->GetXaxis()->SetTitle("X axis (units)");
    h->GetYaxis()->SetTitle("Entries");
    h->SetLineColor(kRed+2);
    h->SetLineWidth(2);
    h->SetFillColor(kRed-7);

    isto_beta(a,h);


    TCanvas *c = new TCanvas("cname","ctitle",-1000, 1000);
    c->cd()->SetGrid();
    h->Draw("");

}