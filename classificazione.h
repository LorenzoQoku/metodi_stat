#ifndef CLASS_H  
#define CLASS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TTree.h"
#include "letturafile.h"
#include <cmath>



using namespace std;

//La funzione prende in ingresso il nome del file dei dati e riempe un istogramma

void classifica(string a, TTree *t, TH1F *h) {

    Double_t x[2]={33,33};
    Double_t y;
    Double_t beta[2]={0,0};
   
    t->Branch("x", x, "x/d");
    t->Branch("y", &y, "y/d");
    t->Branch("beta", beta, "beta/d");

    ifstream file(a);
    double value=0;
    int i=0;
    //Variabile che serve da stop nel momento in cui incontro -999
    int j=0;
    //variabile che serve per eliminare le doppie hit
    int d=0;
    //Variabile che serve per contare a quale delle coppie siamo
    int c=0;
    int Nhit=0;
    int Npart=0;
    int l=0;
    int b=0;
    while(file >> value) {
        Double_t v=value;
        
        if(c==2){
            c=0;
        }
        
        if (l==0){
            i++;
            cout<<"i=" << i<< endl;    
        
            if(i==1){
                Nhit++;
                if (c==0){
                    x[0]=v;
                    cout<<"x0= "<<x[0]<<endl;
                    if (x[0]==-999){
                        l++;
                    }
                    
                }
                else if (c==1){
                    x[1]=v;
                    if(x[0]==x[1]){
                        d++;
                        if(x[0]==-999){
                            l++;
                        }
                    }
                    
                }
                
        
            }
            else if(i==2){
                Nhit++;
            }
            else if(i==3){
                Nhit++;
                if(Nhit==30){
                    Nhit=0;
                    Npart++;
                }
                i=0;
                
                if (c==0){
                    beta[0]=v;
                    c++;
                    
                }
                else if (c==1 && d==0){
                    beta[1]=v;
                    //se le x sono diverse allora riempio l'istogramma
                    Double_t m;
                    // m=sqrt(1-v*v)*1400;
                    h->Fill(beta[0]);
                    if (beta[1]!=-999){
                        h->Fill(beta[1]);
                        cout<<beta[0]<<" "<<beta[1]<<endl;
                        l++;
                    }
                    c++;
                               
                }
                else{
                    d=0;
                    c++;
                    
                }
                cout<<Nhit<<endl;
                    
            }
            else{
                    cout<<"Errore nel formato del file per i"<<endl;
                    break;
                }
            }
            
               
                            
        
        else{
            j++;
            b=Nhit+j;
            if(b==30){
                l=0;
                Npart++;
                j=0;
                i=0;
                c=0;
                b=0;
                d=0;
                Nhit=0;
                x[0]=33;
                x[1]=33;
                beta[0]=0;
                beta[1]=0;
            }
            else if(b>30){
                cout<<"Errore nel formato del file"<<endl;
                break;
            }
            
        }

}

cout<<"Numero totale di particelle: "<<Npart<<endl;  

    file.close();

    
}

#endif