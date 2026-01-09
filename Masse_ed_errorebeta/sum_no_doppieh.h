#ifndef SUMNOH_H  
#define SUMNOH_H

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