#ifndef SUMNOH_H  
#define SUMNOH_H

#include <iostream>
#include "TF1.h"
#include "TTree.h"
#include "histo.h"
using namespace std;

//La funzione somma i valori di beta escludendo quelli con doppia hit e quelli diversi da -999 per ogni evento
//Prima di farlo però la funzione fa anche un analisi preliminare che permette di scartare i dati di errore

Double_t sum_noh(Double_t* beta, Double_t* k,Double_t* x, Double_t* y){


    //Definisco gli array che mi serve di avere

    Double_t erry[10]={0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};
    Double_t ex[10]={0,0,0,0,0,0,0,0,0,0};
    Double_t X1[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t Y1[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t B1[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t X2[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t Y2[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t B2[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    int c=0;


//Definisco un tree che mi serve per fare il fit e capire se ci sono dei dati che escono dalla
//traiettoria. La loro presenza indica ch equella hit non è veramente una hit della particella ma una hit di rumore
    TTree *t1=new TTree("t1","t1");
    t1->Branch("X1",X1,"X1[10]");
    t1->Branch("Y1",Y1,"Y1[10]");
    t1->Branch("B1",B1,"B1[10]");
    t1->Branch("erry", erry, "erry[10]");
    t1->Branch("ex", ex, "ex[10]");

    /*TTree *t2=new TTree("t2","t2");
    t2->Branch("X2",X2,"X2[5]");
    t2->Branch("Y2",Y2,"Y2[5]");
    t2->Branch("B2",B2,"B2[5]");
    t2->Branch("err_y", err_y, "err_y");*/
    TF1 *f = new TF1("f", "[0]+[1]*x",0,1001);


//Riempo il tree con i valori che nnon hanno doppie hit negli scintillatori e che sono diversi da -999
    for (int i = 0; i < 10; i++) {
        if (k[i] != 1 && beta[i] != -999) {
            X1[i]=x[i];
            Y1[i]=y[i];
            B1[i]=beta[i];
            c++;
        }
    }
    t1->Fill();
    if(c>1) t1->UnbinnedFit("f","Y1:erry:X1:ex","", "QE");


//Seleziono solo i dati che stanno entro due deviazioni standard
if(c>1){
    Double_t chi=f->GetChisquare()/f->GetNDF();
    Double_t y_stim[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    if(chi >=2 && c>2){
        for(int i=0; i<10; i++){
            if(X1[i]!=-999) y_stim[i]= f->GetParameter(0) + (f->GetParameter(1))*X1[i];
        }
        Double_t diff[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
        for(int i=0; i<10; i++){
            if(y_stim[i]!=-999){
                diff[i]=sqrt(pow(y[i]-y_stim[i],2))/0.01;
            }
        }
        Double_t max_d=diff[0];
        for(int i=0; i<10; i++){
            if(diff[i]>max_d && diff[i]!=-999){
                max_d=diff[i];
            }
        }
        for(int i=0; i<10; i++){
            if(diff[i]!=max_d){
                Y2[i]=Y1[i];
                X2[i]=X1[i];
                B2[i]=B1[i];
            }
        }
    }
    else{
        for(int i=0; i<10; i++){
            Y2[i]=Y1[i];
            X2[i]=X1[i];
            B2[i]=B1[i];
        }
    }
}
else{
    B2[1]=B1[1];
}


//Sommo i dati selezionati
    Double_t tot = 0;
    int n = 0;
    for (int i = 0; i < 10; i++) {
        if (B2[i] != -999) {
            tot += B2[i];
            n++;
        }
    }
    
    
    if(n!=0){
        Double_t sum = tot / n;
        return sum;
    }
    else{
        return 1;
    }
    
}

#endif