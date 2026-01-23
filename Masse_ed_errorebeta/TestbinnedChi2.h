#ifndef BINCHI_H  
#define BINCHI_H

#include "histo.h"
#include "mass.h"

Double_t binnedchi(Int_t nbins, Double_t min_LDA, Double_t max_LDA, TH1F *h_LDA, TF1 *ftot_f, TF1 *f_gaus){

    Double_t nu=0;
    Double_t mu=0;
    Double_t p[9]={};


    for (int j=0; j<8; j++){
         p[j]=ftot_f->GetParameter(j);
    }

    Double_t space=(min_LDA-max_LDA)/nbins;
    Double_t start=max_LDA;
    Double_t stop=max_LDA;
    Double_t sum=0;
    Double_t mean=0;
    Double_t gdl=0;

    cout <<nbins <<endl;
    for (int i=0; i<nbins; i++){
        start=start+space;
        //cout<<start<<endl;
        stop=start-space;
            //[0]*(2/(x*TMath::Sq(2*pi*[2]*[2])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/x),2))-TMath::Log(TMath::Power((1500/[1]),2))),2))/(2*[2]*[2]))
        mu=p[0]*(2/(stop*sqrt(2*M_PI*p[2]*p[2])))*(exp(-(pow((log(pow((1500/stop),2))-log(pow((1500/p[1]),2))),2))/(2*p[2]*p[2])))+p[3]*(2/(stop*sqrt(2*M_PI*p[5]*p[5])))*(exp(-(pow((log(pow((1500/stop),2))-log(pow((1500/p[4]),2))),2))/(2*p[5]*p[5])))+p[6]*(exp(-0.5*pow(((stop-p[7])),2)));
        nu=p[0]*(2/(start*sqrt(2*M_PI*p[2]*p[2])))*exp(-(pow((log(pow((1500/start),2))-log(pow((1500/p[1]),2))),2))/(2*p[2]*p[2]))+p[3]+(2/(start*sqrt(2*M_PI*p[5]*p[5])))*exp(-(pow((log(pow((1500/start),2))-log(pow((1500/p[4]),2))),2))/(2*p[5]*p[5]))+p[6]*exp(-0.5*pow(((start-p[7])),2));
        mean=(mu+nu)/2;
        if(stop<=1300 && stop>=80){
            sum= sum + pow((mu-h_LDA->GetBinContent(i+1)),2)/mu;
            gdl++;
        }
        //sum= sum + pow((mean-h_LDA->GetBinContent(i)),2)/mean;
    

    }

    Double_t chi2=sum/(gdl-9);

    cout<< "Il valore del chi2 binned è: " << sum << endl;
    cout<< "Il valore del chi2 ridotto è: " << chi2 << endl;

    /*TCanvas *c3 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
    c3->SetFillColor(0);
    c3->SetGrid();
    c3->GetFrame()->SetFillColor(21);
    c3->GetFrame()->SetBorderSize(12);
    t->Draw("betas:ind");*/
    return chi2;

}


#endif