#ifndef DOPPIAH_H  
#define DOPPIAH_H
#include <iostream>
using namespace std;

bool doppia(Double_t* x, Double_t* k) {
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (x[i] == x[j] && x[i]!=-999) {
                k[i]=1;
                return true;
            }
        }
    }
    return false;
}
#endif