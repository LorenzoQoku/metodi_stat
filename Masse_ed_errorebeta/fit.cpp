#include "analisi_beta_threed.h"
#include "TF3.h"
#include "TFile.h"
#include "TCanvas.h"
#include <cmath>


void fit(){

    TF3* f=new TF3("f","([0]/([2]*[4]*[6]))*exp((x-[1])^2/[2])*exp((y-[3])^2/[4])*exp((z-[5])^2/[6])",0.2,1,0.2,1,0.2,1);

    Int_t nbins=25;
    Double_t min=0;
    Double_t max=1.1;

    string a="/home/lorenzo/documenti/metodi_stat/Efficienze_e_particelle_totali/data_Lorenzo_Qoku.txt";

    TH3F *h3 = new TH3F( "h3name","h3title",nbins,min,max,nbins,min,max,nbins,min,max);
    /*h->GetXaxis()->SetTitle("X axis (units)");
    h->GetYaxis()->SetTitle("Entries");
    h->SetLineColor(kRed+2);
    h->SetLineWidth(2);
    h->SetFillColor(kRed-7);*/

    isto_beta_t(a,h3);

    for(int i=1; i< nbins*nbins*nbins+1; i++){
        h3->SetBinError(i, sqrt(h3->GetBinContent(i)));
    }


    f->SetParameters(2000,0.5,0.1,0.998,0.005,0.998,0.005);
	h3->Fit(f,"0","",0.2,1);
    cout<<"Fit parameters: "<<endl;
    for(int i=0;i<7;i++){
        cout<<"Parameter "<<i<<": "<<f->GetParameter(i)<<endl;
    }
    cout<<"Chi2/NDF: "<<f->GetChisquare()/f->GetNDF()<<endl;
    //TCanvas *c = new TCanvas("cname","ctitle",-1000, 1000);
    //c->cd()->SetGrid();
    //h->Draw("");

    


}