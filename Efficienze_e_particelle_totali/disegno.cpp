#include "conteggio.h"
#include "TCanvas.h"
#include "TFile.h"
#include "efficienza.h"






//La funzione sfrutta le altre per calcolare l'efficienza dei singoli scintillatori e il numero totale di particelles

void disegno(){

    Double_t N=0;
    Double_t x=0;
    Double_t N_tot=0;
    Double_t n_i=0;
    Double_t eff=0;
    Double_t e_eff=0;

    string a="data_Lorenzo_Qoku.txt";

    TH1F *h = new TH1F( "hname","htitle",nbins,min,max);
    h->GetXaxis()->SetTitle("X axis (units)");
    h->GetYaxis()->SetTitle("Entries");
    h->SetLineColor(kRed+2);
    h->SetLineWidth(2);
    h->SetFillColor(kRed-7);

    cout << "Di quale scintillatore vuoi conoscere l'efficienza? \n Scrivi " << 0 << "se vuoi conoscere l'efficienza del primo scintillatore \n " << 250 << " per il secondo, ecc."<<endl;
    cin >> x;

    classifica(a,N,x,N_tot,n_i);

    cout<<"Numero totale di particelle: "<<N<<endl;
    cout<<"Numero di eventi che coinvolgono tutti gli scintillatori è:"<<N_tot<<endl;
    cout<<"Numero di eventi che coinvolgono tutti gli scintillatori tranne lo scintillatore scelto è:"<<n_i<<endl;

    efficienza(n_i,N_tot,eff,e_eff);

    cout<<"Efficienza: "<<eff<<endl;
    cout<<"Errore sull'efficienza: "<<e_eff<<endl;


}