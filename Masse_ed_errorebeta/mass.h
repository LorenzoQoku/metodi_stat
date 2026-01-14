#ifndef MASS_H  
#define MASS_H

#include <iostream>
#include "histo.h"

using namespace std;

void do_LDA(string a, TF1 *ftot, TH1F *h_LDA){

        using namespace std;

//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma con i valori di beta calcolati


    Double_t beta[10]={0,0,0,0,0,0,0,0,0,0};
    Double_t x[10]={33,33,33,33,33,33,33,33,33,33};
    Double_t k[10]={0,0,0,0,0,0,0,0,0,0};

    ifstream file(a);
    double value=0;
    //variabile che tiene conto di quale tipo di dato stiamo leggendo
    int i=0;
    //variabile che tiene conto del evento che stiamo leggendo
    int c=0;
    int l=0;

    Double_t mu_0=ftot->GetParameter(1);
    Double_t mu_1=ftot->GetParameter(4);
    Double_t var_0=ftot->GetParameter(2);
    Double_t var_1=ftot->GetParameter(5);
    Double_t alpha=1/(var_0+var_1)*(mu_0-mu_1);

    while(file >> value ) {
        Double_t v=value;
        if(i==3){
            i=0;
        }
        if(c==10){
            c=0;
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
                Double_t mass = sqrt(1-mean_beta*mean_beta)*1500;
                h_LDA->Fill(mass);
            
            }
            
        } 
        i++;

    }
    file.close();

    
}




#endif