#ifndef MEANB_H  
#define MEANB_H

#include <iostream>
#include "TF1.h"
#include "TTree.h"
using namespace std;

//La funzione somma i valori di beta escludendo quelli con doppia hit e quelli diversi da -999 per ogni evento
//Prima di farlo però la funzione fa anche un analisi preliminare che permette di scartare i dati di errore

Double_t sum_noh(Double_t* beta, int* k,Double_t* x, Double_t* y){


    //Definisco gli array che mi serve di avere

    Double_t erry[10]={0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};
    Double_t ex[10]={0,0,0,0,0,0,0,0,0,0};
    Double_t X1[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t Y1[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t B1[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t X2[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t Y2[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    Double_t B2[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
    int c=0;
    int i=0;
    int j=0;


//Definisco un tree che mi serve per fare il fit e capire se ci sono dei dati che escono dalla
//traiettoria. La loro presenza indica ch equella hit non è veramente una hit della particella ma una hit di rumore
    TTree *t1=new TTree("t1","t1");
    t1->Branch("X1",X1,"X1[10]/D");
    t1->Branch("Y1",Y1,"Y1[10]/D");
    t1->Branch("B1",B1,"B1[10]/D");
    t1->Branch("erry", erry, "erry[10]/D");
    t1->Branch("ex", ex, "ex[10]/D");

    /*TTree *t2=new TTree("t2","t2");
    t2->Branch("X2",X2,"X2[5]");
    t2->Branch("Y2",Y2,"Y2[5]");
    t2->Branch("B2",B2,"B2[5]");
    t2->Branch("err_y", err_y, "err_y");*/
    TF1 *f = new TF1("f", "[0]+[1]*x",0,1001);


//Riempo il tree con i valori che nnon hanno doppie hit negli scintillatori e che sono diversi da -999
    for (i = 0; i < 10; i++) {
        if (k[i]==0) {
            X1[i]=x[i];
            Y1[i]=y[i];
            B1[i]=beta[i];
            c++;
        }
    }
    t1->Fill();
    if(c>2) {
        t1->UnbinnedFit("f","Y1:erry:X1:ex","", "QE");
    }


//Faccio una selezioen di dati che permette di ottenere un fit lineare buono

    Double_t chi=f->GetChisquare()/f->GetNDF();
    if(c>2 && chi>2){


       while (chi>2){
            TTree *t2=new TTree("t2","t2");
            t2->Branch("X1",X1,"X1[10]/D");
            t2->Branch("Y1",Y1,"Y1[10]/D");
            t2->Branch("B1",B1,"B1[10]/D");
            t2->Branch("erry", erry, "erry[10]/D");
            t2->Branch("ex", ex, "ex[10]/D");
            Double_t y_stim[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
            Double_t diff[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};

            for(i=0;i<10;i++){
                Y2[i]=Y1[i];
                X2[i]=X1[i];
                B2[i]=B1[i];
            }
            for(i=0;i<10;i++){
                Y1[i]=-999;
                X1[i]=-999;
                B1[i]=-999;
            }

            if(isnan(f->GetParameter(0)) || isnan(f->GetParameter(1))){
                cout << "è questo figlio di puttana" << endl;
                return 1;
            }

            for(i=0; i<10; i++){
                if(X2[i]!=-999){
                    y_stim[i]= f->GetParameter(0) + (f->GetParameter(1))*X2[i];
                }
            }
            for(i=0; i<10; i++){
                if(y_stim[i]!=-999){
                    diff[i]=sqrt(pow(Y2[i]-y_stim[i],2))/0.01;
                }
            }
            Double_t max_d=diff[0];
            for(i=0; i<10; i++){
                if(diff[i]>max_d){
                    max_d=diff[i];
                }
            }
    
            for(i=0; i<10; i++){
                if(diff[i]!=max_d){
                    Y1[i]=Y2[i];
                    X1[i]=X2[i];
                    B1[i]=B2[i];
                }
                else{
                    j=i;
                    Y1[j]=-999;
                    X1[j]=-999;
                    B1[j]=-999;
                    break;
                }
            }
            for(i=j+1; i<10;i++){
                Y1[i]=Y2[i];
                X1[i]=X2[i];
                B1[i]=B2[i];
            }

            c=c-1;

           if(c==2){
                for(int i=0; i<10; i++){
                    Y2[i]=Y1[i];
                    X2[i]=X1[i];
                    B2[i]=B1[i];
                }
                break;
            }
            else{
                t2->Fill();
                t2->UnbinnedFit("f","Y1:erry:X1:ex","", "QE");
                chi=f->GetChisquare()/f->GetNDF();
            }
            delete t2;

        }
        for(i=0;i<10;i++){
            Y2[i]=Y1[i];
            X2[i]=X1[i];
            B2[i]=B1[i];
        }
    }
    else{
        for( i=0; i<10; i++){
            Y2[i]=Y1[i];
            X2[i]=X1[i];
            B2[i]=B1[i];
        }
    }


//Sommo i dati selezionati
    Double_t tot = 0;
    Double_t n = 0;
    Double_t sum = 0;
    if(c>0){
    for (i = 0; i < 10; i++) {
        if (B2[i]!=-999) {
            tot = tot + B2[i];
            n++;
        }
    }
        sum = tot/n;
        if(isnan(sum)){
        for(i=0;i<10;i++){
            cout<<B2[i]<<" ,";
        }
        cout <<endl;
        for(i=0;i<10;i++){
            
            cout<<beta[i] <<" ,";
        }
        cout <<endl;
        for(i=0;i<10;i++){
            
            cout<<x[i] <<" ,";
        }
        cout <<endl;
        for(i=0;i<10;i++){
            
            cout<<y[i] <<" ,";
        }
        cout <<endl;
        for(i=0;i<10;i++){
            
            cout<<k[i] <<" ,";
        }
        cout <<endl;

        cout<<c<<endl;
    }
    

}
else{
    sum=-999;
    
}
delete t1;
return sum;



    
}

#endif