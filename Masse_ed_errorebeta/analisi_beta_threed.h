#ifndef BETAD_H  
#define BETAD_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TTree.h"
#include <cmath>
#include "sum_no_doppieh.h"
#include "TH3F.h"


using namespace std;

//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma con i valori di beta calcolati

void isto_beta_t(string a, TH3F *h3) {

    Double_t beta[10]={0,0,0,0,0,0,0,0,0,0};
    Double_t x[10]={33,33,33,33,33,33,33,33,33,33};
    Double_t k[10]={0,0,0,0,0,0,0,0,0,0};

    ifstream file(a);
    double value=0;
    //variabile che tiene conto di quale tipo di dato stiamo leggendo
    int i=0;
    //variabile che tiene conto del evento che stiamo leggendo
    int c=0;

    int b=0;
    int l=0;
    Double_t sum[3]={0,0,0};
    Double_t vett[48551];

    while(file >> value ) {
        Double_t v=value;
        if(i==3){
            i=0;
        }
        if(c==10){
            c=0;
        }
        if(b==3){
            b=0;
        }

        if(i==0){
                if(c==0){
                    x[0]=v;
                    
                }
                else if(c==1){
                    x[1]=v;
                    
                }
                else if(c==2){
                    x[2]=v;
                    
                }
                else if(c==3){
                    x[3]=v;
                    
                }
                else if(c==4){
                    x[4]=v;
                    
                }
                else if(c==5){
                    x[5]=v;
                    
                }
                else if(c==6){ 
                    x[6]=v;
                    
                }
                else if(c==7){
                    x[7]=v;
                    
                }
                else if(c==8){
                    x[8]=v;
                    
                }
                else if(c==9){
                    x[9]=v;
                }
            }
        
        if(i==2){
            if (c==0){
                beta[0]=v;
                c++;
            }
            else if(c==1){
                beta[1]=v;
                c++;
            }
            else if(c==2){
                beta[2]=v;
                c++;
            }
            else if(c==3){
                beta[3]=v;
                c++;
            }
            else if(c==4){
                beta[4]=v;
                c++;
            }
            else if(c==5){
                beta[5]=v;
                c++;
            }
            else if(c==6){
                beta[6]=v;
                c++;
            }
            else if(c==7){
                beta[7]=v;
                c++;
            }
            else if(c==8){
                beta[8]=v;
                c++;
            }
            else if(c==9){
                beta[9]=v;
                c++;
                Double_t mean_beta=sum_noh(beta,k);
                sum[b]=mean_beta;
                b++;
                if(b==3){
                   // h3->Fill(sum[0],sum[1],sum[2]);
                }
                vett[l]=mean_beta;
            }
            
        } 
        i++;
        l++;

    }
    file.close();

    for (int j=0; j<48551; j++){
        for (int k=0; k<48551; k++){
            for (int p=0; p<48551; p++){
                if(j!=k && j!=p && k!==p)
                h->Fill(vett[j],vett[k],vett[p]);
            }
        
        }
    }
}


#endif