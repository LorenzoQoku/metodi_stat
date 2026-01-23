#ifndef MASS_H  
#define MASS_H

#include <iostream>
#include "TTree.h"
#include "histo.h"
#include <cmath>

using namespace std;

void do_LDA(string a, TH1F *h_LDA){


//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma con i valori di beta calcolati

    Double_t mass=0;
    Double_t beta[10]={0,0,0,0,0,0,0,0,0,0};
    Double_t x[10]={33,33,33,33,33,33,33,33,33,33};
    Double_t y[10]={33,33,33,33,33,33,33,33,33,33};
    Double_t k[10]={0,0,0,0,0,0,0,0,0,0};

    ifstream file(a);
    double value=0;
    //variabile che tiene conto di quale tipo di dato stiamo leggendo
    int i=0;
    //variabile che tiene conto del evento che stiamo leggendo
    int c=0;
    int l=0;

    while(file >> value ) {
        Double_t v=value;
        mass=log(v);
        h_LDA->Fill(mass);
    }
    file.close();

    
}




#endif