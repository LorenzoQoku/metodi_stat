#include "mass.h"
#include "TCanvas.h"
#include"montec_var.h"


//La funzione esegue il fit dell'istogramma dei valori di beta calcolati

void graph(){

    Int_t nbins=30000;
    Double_t min=0;
    Double_t max=0.99999;
    Double_t t_cut=110;
    string a="massafine2.txt";
    Int_t nbins_LDA=nbins;
    Double_t max_LDA=1500*sqrt(1-min*min);
    Double_t min_LDA=1500*sqrt(1-max*max);
    Double_t space=(max_LDA-min_LDA)/nbins;
    cout<<"Lospazioè: "<< space<<endl;
//Definizione delle possibilli funzioni di fit

    //TF1* ftot_log=new TF1("ftot_log","[0]*(2/((x)*TMath::Sqrt(2*pi*[2]*[2])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/(x)),2))-TMath::Log(TMath::Power((1500/[1]),2))),2))/(2*[2]*[2]))",0,1400);
    TF1* ftot_log=new TF1("ftot_log","(2/((x)*TMath::Sqrt(2*pi*[1]*[1])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/(x)),2))-TMath::Log(TMath::Power((1500/[0]),2))),2))/(2*[1]*[1]))",0,1400);
    //TF1* ftot_log2=new TF1("ftot_log2","[3]*(2/((TMath::Exp(x))*TMath::Sqrt(2*pi*[5]*[5])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/(TMath::Exp(x))),2))-TMath::Log(TMath::Power((1500/[4]),2))),2))/(2*[5]*[5]))",0,400);
    //TF1* ftot_f=new TF1("ftot_f","(ftot_log+ftot_log)*([0]+[3])*TMath::Exp(-([0]+[3])/36436)/(TMath::Power(TMath::Gamma(36436),1/36436))",50,400);
    //TF1* ftot_f=new TF1("ftot_f","(ftot_log+ftot_log+[6]*([0]+[3])*TMath::Exp(-([0]+[3]))",2,100);
    //TF1* ftot_f=new TF1("ftot_f","(ftot_log+ftot_log+[6]*TMath::Power([7],[8]*(TMath::Exp(x))-[9]))",2,100);
    TF1* ftot_f=new TF1("ftot_f","([1]*ftot_log+(1-[1])*ftot_log)*([0])*TMath::Exp(-([0])/36436)/(TMath::Power(TMath::Gamma(36436),1/36436))",50,400);



//Istogrammma delle masse

    TH1F *h_LDA= new TH1F( "hLDA","hLDA",nbins_LDA,min_LDA,max_LDA);

    h_LDA->GetXaxis()->SetTitle("X axis (units)");
    h_LDA->GetYaxis()->SetTitle("Entries");
    h_LDA->SetLineColor(kRed+2);
    h_LDA->SetLineWidth(2);
    h_LDA->SetFillColor(kRed-7);
    h_LDA->SetAxisRange(20, 400, "X");
    h_LDA->SetAxisRange(0, 300, "Y");




//Usiamo la formula che connnette la beta con la massa

    make_histo_m(a,h_LDA);

//Settimao gli errori dei bin come poissoniani

    int r= h_LDA->GetNbinsX() + 1;
    for(int i=1; i<r; i++){
        h_LDA->SetBinError(i, sqrt(h_LDA->GetBinContent(i)));
    }

    /*Int_t bin_min = h_LDA->FindBin(0);
    Int_t bin_max = h_LDA->FindBin(t_cut);
    Double_t integral = h_LDA->Integral(bin_min, bin_max);
    if (integral > 0) {
        h_LDA->Scale(1.0/integral);
    }*/


//Fa il fit e riporta i parametri

    //ftot_f->SetParameters(30,91.3,0.055,13,80.5,0.06);
    ftot_f->SetParameters(35000,0.7,91.3,0.055,80.5,0.06);
    h_LDA->Fit(ftot_f,"L","",70,t_cut);

    cout<<"Fit parameters: "<<endl;
    for(int i=0;i<6;i++) cout<<"Parameter "<<i<<": "<<ftot_f->GetParameter(i)<<endl;
    cout<<"Chi2/NDF: "<<ftot_f->GetChisquare()/ftot_f->GetNDF()<<endl;



// Conto il numero di entries dopo il cut selezionato
    Int_t sum=0;
    Double_t start=70;
    Int_t i=h_LDA->FindBin(start);
    while(start<=t_cut){
        start=start+space;
        sum=sum + h_LDA->GetBinContent(i);
        i++;
    }
    cout<<"Il numero totale di entries tra il minimo e il cut è: "<<sum<<endl;
    cout<<"il numero di punti che abbiamo dal nostro fit è; "<<i<<endl;

    Int_t risposta=0;
    cout<<"Vuoi avere anche la varianza tramite un montecarlo? Digita 1 se vuoi farlo"<<endl;
    cin>>risposta;
    if(risposta == 1){
        Double_t var[6]={0,0,0,0,0,0};
        montevar(ftot_f->GetParameter(0),ftot_f->GetParameter(1),ftot_f->GetParameter(2),ftot_f->GetParameter(3),ftot_f->GetParameter(4),ftot_f->GetParameter(5),ftot_f,sum,nbins_LDA,min_LDA,max_LDA,t_cut,var);
        for(int p=0; p<6;p++) cout<<"La varianza per il parametro: "<< p<< "è: "<<var[p]<<endl;
    }

//Disegno l'istogramma

    TCanvas *c2 = new TCanvas("cname2","ctitle2",-1000, 1000);
    c2->cd()->SetGrid();
    h_LDA->Draw("ftot_f");

//Riporta nella legeda il chi quadro e i parametri

    gStyle->SetOptFit(1111);

}
