#include <iostream>
#include <fstream>
#include "histo.h"
#include "mass.h"
#include "TestbinnedChi2.h"
#include "sum_no_doppieh.h"

using namespace std;
//Creo un file txt con tutte le masse
void file_masse(){

    string a="/home/lorenzo/documenti/metodi_stat/Efficienze_e_particelle_totali/data_Lorenzo_Qoku.txt";
    Double_t mass=0;
    Double_t beta[10]={0,0,0,0,0,0,0,0,0,0};
    Double_t x[10]={33,33,33,33,33,33,33,33,33,33};
    Double_t y[10]={33,33,33,33,33,33,33,33,33,33};
    Double_t k[10]={0,0,0,0,0,0,0,0,0,0};

    ifstream file(a);
    ofstream file_m;
    file_m.open("mass2.txt");
    double value=0;
    //variabile che tiene conto di quale tipo di dato stiamo leggendo
    int i=0;
    //variabile che tiene conto del evento che stiamo leggendo
    int c=0;
    int l=0;

    while(file >> value ) {
        Double_t v=value;
        if(i==3){
            i=0;
        }
        if(c==10){
            c=0;
            for(int r=0;r<10;r++){
                k[r]=0;
            }
        }
    

        if(i==0){
                if(c==0){
                    x[0]=v;
                    
                }
                else if(c==1){
                    x[1]=v;
                    
                }
                else if(c==2){
                    x[2]=v;
                    
                }
                else if(c==3){
                    x[3]=v;
                    
                }
                else if(c==4){
                    x[4]=v;
                    
                }
                else if(c==5){
                    x[5]=v;
                    
                }
                else if(c==6){ 
                    x[6]=v;
                    
                }
                else if(c==7){
                    x[7]=v;
                    
                }
                else if(c==8){
                    x[8]=v;
                    
                }
                else if(c==9){
                    x[9]=v;
                    for(int r=0; r<10;r++){
                        for(int j=0; j<10; j++){
                            if( j!=r ){
                                if(x[r]==x[j]) k[r]=1;
                            }
                        }
                    }
                }
            }
            if(i==1){
                if(c==0){
                    y[0]=v;
                    
                }
                else if(c==1){
                    y[1]=v;
                    
                }
                else if(c==2){
                    y[2]=v;
                    
                }
                else if(c==3){
                    y[3]=v;
                    
                }
                else if(c==4){
                    y[4]=v;
                    
                }
                else if(c==5){
                    y[5]=v;
                    
                }
                else if(c==6){ 
                    y[6]=v;
                    
                }
                else if(c==7){
                    y[7]=v;
                    
                }
                else if(c==8){
                    y[8]=v;
                    
                }
                else if(c==9){
                    y[9]=v;
                }
            }
        
        if(i==2){
            if (c==0){
                beta[0]=v;
                c++;
            }
            else if(c==1){
                beta[1]=v;
                c++;
            }
            else if(c==2){
                beta[2]=v;
                c++;
            }
            else if(c==3){
                beta[3]=v;
                c++;
            }
            else if(c==4){
                beta[4]=v;
                c++;
            }
            else if(c==5){
                beta[5]=v;
                c++;
            }
            else if(c==6){
                beta[6]=v;
                c++;
            }
            else if(c==7){
                beta[7]=v;
                c++;
            }
            else if(c==8){
                beta[8]=v;
                c++;
            }
            else if(c==9){
                beta[9]=v;
                c++;
                Double_t mean_beta=sum_noh(beta,k,x,y);
                mass = sqrt(1-mean_beta*mean_beta)*1500;
                //Double_t mass_log=log(mass);
                if(file_m.is_open()){
                    if(mass!=0){
                        file_m << mass;
                        file_m << " ";
                    }
                }
                else {
                    cout << "Unable to open file!"<<endl;
                }
            
            }
            
        } 
        i++;

    }
    file.close();
    file_m.close();

    
}
