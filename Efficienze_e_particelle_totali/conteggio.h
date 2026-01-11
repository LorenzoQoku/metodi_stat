#ifndef CONT_H  
#define CONT_H


#include "arraydiversi.h"
#include <fstream>
#include <string>
#include <sstream>
#include "TTree.h"
#include <cmath>
#include "diversi_da_X.h"
#include "diversi_da_null.h"
#include "almeno_div_e_nonull.h"



using namespace std;

//è una funzione che permette di contare il numero di particelle totali N, il numero di eventi che coinvolgono tutti gli scintillatori N_tot e il numero di eventi che coinvolgono tutti gli scintillatori tranne uno n_i

void classifica(string a, Double_t &N, Double_t X,Double_t &N_tot, Double_t &n_i){

    Double_t x[10]={33,33,33,33,33,33,33,33,33,33};
    

    ifstream file(a);
    double value=0;
    int i=0;
    //Variabile che serve per contare a quale delle coppie siamo
    int c=0;
 
    while(file >> value) {
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
                    c++;
                }
                else if(c==1){
                    x[1]=v;
                    c++;
                }
                else if(c==2){
                    x[2]=v;
                    c++;
                }
                else if(c==3){
                    x[3]=v;
                    c++;
                }
                else if(c==4){
                    x[4]=v;
                    c++;
                }
                else if(c==5){
                    x[5]=v;
                    c++;
                }
                else if(c==6){ 
                    x[6]=v;
                    c++;
                }
                else if(c==7){
                    x[7]=v;
                    c++;
                }
                else if(c==8){
                    x[8]=v;
                    c++;
                }
                else if(c==9){
                    x[9]=v;
                    c++;
                    bool diversi=tuttiDiversiCArray(x);
                    bool diversi_da_X=nessun_X_e_null(x,X);
                    bool diversi_da_null=nessun_null(x);
                    bool almeno=almeno_uno(x);
                    if(diversi==true && diversi_da_null==true){ //Hittano tutti gli scintillatori
                        N_tot++;
                    }
                    if((diversi==true && diversi_da_X==true) || (diversi==true && diversi_da_null==true && diversi_da_X==false) ){ //Hittano tutti gli scintillatori tranne quello scelto
                        n_i++;
                    }
                    if(almeno==true){
                        N++;
                    }
                }
            }
            i++;
    }

file.close();

}


#endif