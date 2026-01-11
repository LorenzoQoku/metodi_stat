#ifndef NULL_H  
#define NULL_H

#include <iostream>
using namespace std;

bool nessun_null(Double_t* x) {
    for (int i = 0; i < 5; i++) {
        if(x[i]==-999){
            return false;
        }
    }
    return true;
}


#endif