#ifndef CLASS_H  
#define CLASS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TTree.h"
#include "letturafile.h"



using namespace std;

//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma

void classifica(string a, TTree *t, TH1F *h) {

    Double_t x;
    Double_t y;
    Double_t beta;
   
    t->Branch("x", &x, "x/d");
    t->Branch("y", &y, "y/d");
    t->Branch("beta", &beta, "beta/d");

    ifstream file(a);
    double value=0;
    int i=0;
    while(file >> value ) {
        Double_t v=value;
        if (v != -999){G

            if(i>=3){
                i=0;
                
             }
             else{

            if(i==0){
                //riempo x
            }else {
            if(i==1){
                //riempo y
            } 
            else{

            if(i==2){
                h->Fill(v);
            }
        }
        }
        }
        i++;
    }

    file.close();

    }
}

#endif