#ifndef HISTO_H  
#define HISTO_H

#include <iostream>
using namespace std;

#include "analisi_beta_oned.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"




//La funzione esegue il fit dell'istogramma dei valori di beta calcolati

void histo(string a0,TH1F *h){

    


    h->GetXaxis()->SetTitle("X axis (units)");
    h->GetYaxis()->SetTitle("Entries");
    h->SetLineColor(kRed+2);
    h->SetLineWidth(2);
    h->SetFillColor(kRed-7);

    


    isto_beta_o(a0,h);
    int r= h->GetNbinsX() + 1;

    for(int i=1; i<r; i++){
        h->SetBinError(i, sqrt(h->GetBinContent(i)));
    }

    /*ftot_p->SetParameters(63,0.998,0.0001,30,0.9986,0.00008,120,0.8317,0.12);
	h->Fit(ftot_p,"L","",0.99,1);
    cout<<"Fit parameters: "<<endl;
    for(int i=0;i<8;i++){
        cout<<"Parameter "<<i<<": "<<ftot_p->GetParameter(i)<<endl;
    }
   cout<<"Chi2/NDF: "<<ftot_p->GetChisquare()/ftot_p->GetNDF()<<endl;*/





}

#endif