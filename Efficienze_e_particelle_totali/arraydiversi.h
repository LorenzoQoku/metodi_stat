#ifndef AD_H  
#define AD_H

#include <iostream>
using namespace std;

//La funzione controlla se tutti i valori in un array di Double_t sono diversi tra loro
//Mi serve per contare gli eventi che fanno scintillare tutti gli scintillatori 

bool tuttiDiversiCArray(Double_t* x) {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (x[i] == x[j]) {
                return false;
            }
        }
    }
    return true;
}


#endif