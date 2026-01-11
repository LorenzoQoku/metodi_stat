#ifndef NOXENULL_H  
#define NOXENULL_H

#include <iostream>
using namespace std;



bool nessun_X_e_null(Double_t* x, Double_t X) {
    int n=0;
    //cout<<"Valore di X scelto:"<<X<<endl;
    for (int i = 0; i < 4; i++) {
        if(x[i]!=X && x[i]!=-999){
            n++;
        }
    }
    if(n==4){
        return true;
    }
    else
    {
        return false;
    }
    
}





#endif