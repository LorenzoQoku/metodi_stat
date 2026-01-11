#ifndef ADENN_H  
#define ADENN_H

#include <iostream>
using namespace std;

//La funzione individua se è presente almeno un valore diverso dagli altri e diverso da -999
//forse questa è inutile , basta vedere le entries dell'istogramma della beta


int n=0;

bool almeno_uno(Double_t* x) {
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            while(x[i]!=x[j] && x[i]!=-999){
                n++;
                if(n>=1){
                    return true;
                }
            }

        }
    }
    return false;
}


#endif