#ifndef EFF_H  
#define EFF_H

#include "conteggio.h"

void efficienza(Double_t n, Double_t N, Double_t &eff, Double_t &e_eff){

    if (n!=0){
        eff=N/n;
        e_eff=sqrt(eff*(1-eff)/n);
    }
    else{
        cout << "Impossibile calcolare l'efficienza: numero di particelle n è uguale a zero." << endl;
    }

}


#endif