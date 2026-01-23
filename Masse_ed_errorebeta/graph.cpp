
#include "histo.h"
#include "mass.h"
#include "TestbinnedChi2.h"



//La funzione esegue il fit dell'istogramma dei valori di beta calcolati

void graph(){

    Int_t nbins=3000;
    Double_t min=0.6;
    Double_t max=0.99999;
    Double_t t_cut=4.6;
    string a0="/home/lorenzo/documenti/metodi_stat/Efficienze_e_particelle_totali/data_Lorenzo_Qoku.txt";
    string a="mass2.txt";

    TH1F *h = new TH1F( "hname","htitle",nbins,min,max);
    TF1* ftot_log=new TF1("ftot_log","[0]*(2/((TMath::Exp(x))*TMath::Sqrt(2*pi*[2]*[2])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/(TMath::Exp(x))),2))-TMath::Log(TMath::Power((1500/[1]),2))),2))/(2*[2]*[2]))",0,400);
    TF1* ftot_log2=new TF1("ftot_log2","[3]*(2/((TMath::Exp(x))*TMath::Sqrt(2*pi*[5]*[5])))*TMath::Exp(-(TMath::Power((TMath::Log(TMath::Power((1500/(TMath::Exp(x))),2))-TMath::Log(TMath::Power((1500/[4]),2))),2))/(2*[5]*[5]))",0,400);
    TF1* ftot_f=new TF1("ftot_f","ftot_log+ftot_log",50,400);
    //TF1* ftot_f=new TF1("ftot_f","(ftot_log+ftot_log+[6]*TMath::Power([7],[8]*(TMath::Exp(x))))*([0]+[3]+[6])*TMath::Exp(-([0]+[3]+[6])/48551)",2,100);
    //TF1* ftot_f=new TF1("ftot_f","(ftot_log+ftot_log+[6]*TMath::Power([7],[8]*(TMath::Exp(x))-[9]))",2,100);
    
    
 //Istogramma delle beta   

   // histo(a0,h);



//Istogrammma delle masse

    Int_t nbins_LDA=nbins;
    Double_t max_LDA=log(1500*sqrt(1-min*min));
    Double_t min_LDA=log(1500*sqrt(1-max*max));

    TH1F *h_LDA= new TH1F( "hLDA","hLDA",nbins_LDA,min_LDA,max_LDA);

    h_LDA->GetXaxis()->SetTitle("X axis (units)");
    h_LDA->GetYaxis()->SetTitle("Entries");
    h_LDA->SetLineColor(kRed+2);
    h_LDA->SetLineWidth(2);
    h_LDA->SetFillColor(kRed-7);
    h_LDA->SetAxisRange(4, max_LDA, "X");
    h_LDA->SetAxisRange(0, 500, "Y");

//Usiamo la formula che connnette la beta con la massa
    do_LDA(a,h_LDA);

//Settimao gli errori dei bin come poissoniani
    int r= h_LDA->GetNbinsX() + 1;
    for(int i=1; i<r; i++){
        h_LDA->SetBinError(i, sqrt(h_LDA->GetBinContent(i)));
    }


    ftot_f->SetParameters(700,91.3,0.055,300,80.5,0.06,1.5,2.7,0.004,1);
    h_LDA->Fit(ftot_f,"LI","",4.3,t_cut);

    cout<<"Fit parameters: "<<endl;
    for(int i=0;i<9;i++) cout<<"Parameter "<<i<<": "<<ftot_f->GetParameter(i)<<endl;
    cout<<"Chi2/NDF: "<<ftot_f->GetChisquare()/ftot_f->GetNDF()<<endl;


       /* ROOT::Fit::DataOptions opt;
    opt.fIntegral = true;
    ROOT::Fit::DataRange range(max_LDA,min_LDA);
    ROOT::Fit::BinData data(opt,range);
    ROOT::Fit::FillData(data, h_LDA);
    //ROOT::Math::WrappedMultiTF1 fitFunction(ftot_f );
   // ROOT::Fit::PoissonLikelihoodFCN(data);*/

    Double_t space=(max_LDA-min_LDA)/nbins;
    Double_t start=min_LDA;
    Double_t sum=0;
    Int_t i=0;

    while(start<=t_cut){
        start=start+space;
        sum=sum + h_LDA->GetBinContent(i);
        i++;
    }
    cout<<"Il numero totale di entries tra il minimo e il cut è: "<<sum<<endl;


    TCanvas *c2 = new TCanvas("cname2","ctitle2",-1000, 1000);
    c2->cd()->SetGrid();
    h_LDA->Draw("ftot_f");
    gStyle->SetOptFit(1111);

    //Double_t chi=binnedchi(nbins, min_LDA,max_LDA, h_LDA, ftot_f, f_gaus);

}
