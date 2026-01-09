#ifndef SUMNOH_H  
#define SUMNOH_H

#include <iostream>
using namespace std;

//La funzione somma i valori di beta escludendo quelli con doppia hit e quelli diversi da -999 per ogni evento

Double_t sum_noh(Double_t* beta, Double_t* k) {
    Double_t tot = 0;
    int n = 0;
    for (int i = 0; i < 10; i++) {
        if (k[i] != 1 && beta[i] != -999) {
            tot += beta[i];
            n++;
        }
    }
    Double_t sum = tot / n;
    return sum;
}

#endif