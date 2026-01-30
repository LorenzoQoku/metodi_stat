#ifndef MCVAR_H  
#define MCVAR_H

#include "mass.h"

void montevar(Double_t N,Double_t alpha,Double_t mu1,Double_t sigma1,Double_t mu2,Double_t sigma2,TF1 *ftot_f,Int_t entries, Int_t bins, Double_t min, Double_t max,Double_t t_cut,Double_t* var){

    int i=0;
    Double_t nu[5000];
    Double_t w[5000];
    Double_t sig1[5000];
    Double_t sig2[5000];
    Double_t m1[5000];
    Double_t m2[5000];
    int num=5000;
    Double_t mean[6]={0,0,0,0,0,0};
    while(i<num){
        TF1* fpup=new TF1("fpup","ftot_f",0,1400);
        ftot_f->FixParameter(0,N);
        ftot_f->FixParameter(1,alpha);
        ftot_f->FixParameter(2,mu1);
        ftot_f->FixParameter(3,sigma1);        
        ftot_f->FixParameter(4,mu2);
        ftot_f->FixParameter(5,sigma2);
        TH1F *h=new TH1F("hist","hist",bins,min,max);
        h->FillRandom("ftot_f", entries);
        int r= h->GetNbinsX() + 1;
        for(int i=1; i<r; i++){
            h->SetBinError(i, sqrt(h->GetBinContent(i)));
        }
        ftot_f->SetParameters(35000,0.7,91.3,0.055,80.5,0.06);
        h->Fit(fpup,"LQ","",70,t_cut);
        nu[i]=fpup->GetParameter(0);
        w[i]=fpup->GetParameter(1);
        sig1[i]=fpup->GetParameter(3);
        sig2[i]=fpup->GetParameter(5);
        m1[i]=fpup->GetParameter(2);
        m2[i]=fpup->GetParameter(4);
        if(isnan(m1[i])||isnan(m2[i])){
                cout<<"Non fitta molto bene"<<endl;
                break;
        }
        i++;
        delete h;
        delete fpup;
    }

    for(int j=0;j<num;j++){
        mean[0]=mean[0]+nu[j];
        mean[1]=mean[1]+w[j];
        mean[2]=mean[2]+m1[j];
        mean[3]=mean[3]+sig1[j];
        mean[4]=mean[4]+m2[j];
        mean[5]=mean[5]+sig2[j];
    }

    mean[0]=mean[0]/(num);
    mean[1]=mean[1]/(num);
    mean[2]=mean[2]/(num);
    mean[3]=mean[3]/(num);
    mean[4]=mean[4]/(num);
    mean[5]=mean[5]/(num);

    for(int k=0;k<num;k++){
        var[0]=var[0] + pow(mean[0]-nu[k],2);
        var[1]=var[1] + pow(mean[1]-w[k],2);
        var[2]=var[2] + pow(mean[2]-m1[k],2);
        var[3]=var[3] + pow(mean[3]-sig1[k],2);
        var[4]=var[4] + pow(mean[4]-m2[k],2);
        var[5]=var[5] + pow(mean[5]-sig2[k],2);
    }
    var[0]=var[0]/(num-1);
    var[1]=var[1]/(num-1);
    var[2]=var[2]/(num-1);
    var[3]=var[3]/(num-1);
    var[4]=var[4]/(num-1);
    var[5]=var[5]/(num-1);

}



#endif