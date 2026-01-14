
#include "histo.h"
#include "mass.h"



//La funzione esegue il fit dell'istogramma dei valori di beta calcolati

void graph(){

    Int_t nbins=7000;
    Double_t min=0.3;
    Double_t max=0.999;
    string a="/home/lorenzo/documenti/metodi_stat/Efficienze_e_particelle_totali/data_Lorenzo_Qoku.txt";

    TH1F *h = new TH1F( "hname","htitle",nbins,min,max);
    TF1* ftot_log=new TF1("ftot_log","[0]*(2/(x*TMath::Sq(2*pi*[2]*[2])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/x),2))-TMath::Log(TMath::Power((1500/[1]),2))),2))/(2*[2]*[2]))",50,400);
    TF1* ftot_log2=new TF1("ftot_log2","[3]*(2/(x*TMath::Sq(2*pi*[5]*[5])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/x),2))-TMath::Log(TMath::Power((1500/[4]),2))),2))/(2*[5]*[5]))",50,400);
    TF1* ftot_f=new TF1("ftot_f","ftot_log+ftot_log2+gaus(6)",50,400);
    TF1* ftot=new TF1("ftot","gaus(0)+gaus(3)+gaus(6)",0.8,1);
    //TF1* fpois=new TF1("pois","[0]*TMath::Power(([1]),(x))*(TMath::Exp(-[1]))/TMath::Gamma(x+1)",0.5,1);
   // TF1* ftot_p=new TF1("ftot_p","gaus(0)+gaus(3)+pois(5)",0.5,1);
    TF1* ftot_LDA=new TF1("ftot_LDA","gaus(0)+gaus(3)+gaus(6)",70,300);
    //vera funzione di fit, capisci come implementare il logartmo su root
    


    histo(a,h,ftot);




    Int_t nbins_LDA=nbins;
    Double_t min_LDA=1500*sqrt(1-min*min);
    Double_t max_LDA=1500*sqrt(1-max*max);

    TH1F *h_LDA= new TH1F( "hLDA","hLDA",nbins_LDA,min_LDA,max_LDA);

    h_LDA->GetXaxis()->SetTitle("X axis (units)");
    h_LDA->GetYaxis()->SetTitle("Entries");
    h_LDA->SetLineColor(kRed+2);
    h_LDA->SetLineWidth(2);
    h_LDA->SetFillColor(kRed-7);
    h_LDA->SetAxisRange(0, 1400, "X");
    h_LDA->SetAxisRange(0, 300, "Y");

    do_LDA(a,ftot,h_LDA);

    int r= h_LDA->GetNbinsX() + 1;

    for(int i=1; i<r; i++){
        h_LDA->SetBinError(i, sqrt(h_LDA->GetBinContent(i)));
    }

    ftot_LDA->SetParameters(114,85.19,2.3,53,75.14,2,11,824,215);
    ftot_f->SetParameters(1,80.3,0.05,1.6,91,0.05,9,876,230);
	h_LDA->Fit(ftot_f,"L","",70,150);
    cout<<"Fit parameters: "<<endl;
    for(int i=0;i<9;i++){
        cout<<"Parameter "<<i<<": "<<ftot_f->GetParameter(i)<<endl;
    }
   cout<<"Chi2/NDF: "<<ftot_f->GetChisquare()/ftot_f->GetNDF()<<endl;

    

    TCanvas *c = new TCanvas("cname","ctitle",-1000, 1000);
    c->cd()->SetGrid();
    h->Draw("ftot_p");
   TCanvas *c1 = new TCanvas("cname1","ctitle1",-1000, 1000);
    c1->cd()->SetGrid();
    h_LDA->Draw("");
    gStyle->SetOptFit(1111);

}