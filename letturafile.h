
#ifndef LETTURA_H  // Include guard
#define LETTURA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TH1F.h"



using namespace std;

//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma

void leggi_e_riempi(string a, TH1F *h) {

    ifstream file(a);
    double value=0;
    while(file >> value ) {
        Double_t v=value;
        h->Fill(v);
    }
    file.close();

}

#endif