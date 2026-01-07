#include "classificazione.h"
#include "letturafile.h"
#include "TCanvas.h"
#include "TFile.h"





//La funzione disegna un istogramma riempito di alcuni dati

void disegno(){


    Int_t nbins=100000;
    Double_t min=0;
    Double_t max=1;

    string a="data_Lorenzo_Qoku.txt";


    TTree *t = new TTree("dati","ttitle");
    TH1F *h = new TH1F( "hname","htitle",nbins,min,max);
    h->GetXaxis()->SetTitle("X axis (units)");
    h->GetYaxis()->SetTitle("Entries");
    h->SetLineColor(kRed+2);
    h->SetLineWidth(2);
    h->SetFillColor(kRed-7);

    classifica(a,t,h);
    //leggi_e_riempi(a, h);


    TCanvas *c = new TCanvas("cname","ctitle",-1000, 1000);
    c->cd()->SetGrid();
    h->Draw("");
    
    

}