#ifndef BETA_H  
#define BETA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TTree.h"
#include <cmath>
#include "sum_no_doppieh.h"


using namespace std;

//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma con i valori di beta calcolati

void isto_beta_o(string a, TH1F *h, TH2F *h2) {

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
    Double_t summ[2]={0,0};
    Double_t vett[2000];
    int l=0;

    while(file >> value ) {
        Double_t v=value;
        if(i==3){
            i=0;
        }
        if(c==10){
            c=0;
        }
        if(b==2){
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
                h->Fill(mean_beta);
                summ[b]=mean_beta;
                b++;
                if(b==2){
                   // h2->Fill(summ[0],summ[1]);
                }
                vett[l]=mean_beta;
            }
            
        } 
        i++;
        l++;

    }
    file.close();

    for (int p=0; p<200; p++){
        for (int k=0; k<200; k++){
            if(p!=k ){
                h2->Fill(vett[p],vett[k]);
                
            }
        
        }
    }
}


#endif