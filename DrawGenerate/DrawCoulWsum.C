//#include"/Users/shihuangchao/Downloads/root_files/headfile/bes3plotstyle.c"
#include <TCanvas.h>
#include <TH2.h>
#include "TTree.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
using namespace TMath;
typedef std::vector<double> Vdouble;

void DrawCoulWsum(){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);

  double c_light=3e8;
  double charge_e=1.6e-19;
  //double circum=237.53;
  //double bunch_current=9.8e-3; 
  //double num_bunch=93;
  double bunch_current=1e-2;
  double circum=740.18;
  double num_bunch=200;
  double N_bunch = bunch_current*(circum/c_light)/charge_e;  
  double N_beam = num_bunch*N_bunch;

  ifstream file_Wsum(Form("../output/CoulWsumtoS.txt"));
  Double_t Vs[2000],VN[2000],Vlscat[2000],;
  double s,w,lscat,tau=0;
  int i=0;
  while(!file_Wsum.eof()){
    file_Wsum>>w>>s>>lscat;
    Vs[i]=s;
    VN[i]=w*c_light*N_bunch*lscat/circum;
    tau=tau+VN[i];
    VN[i]=VN[i]/lscat*N_beam;
    i++;
  }
  cout<<"life time:"<<1/(tau*3600)<<" hour"<<endl;

  int n_total=i;
  int nbin = 100;
  double xmin = 300, xmax = 450, ymax=1e6;
  //TH1F* h1 = new TH1F("h1","",nbin,xmin,xmax);
  //h1->SetFillColor(kRed);
  TGraph* h1 = new TGraph(n_total,Vs,VN);
  h1->GetXaxis()->SetTitle("position / m");
  h1->GetYaxis()->SetTitle("Loss rate / Hz");
  h1->GetXaxis()->SetRangeUser(xmin,xmax);
  //h1->GetYaxis->SetRangeUser(0,ymax);
  //for(i=0;i<n_total;i++){
  //  h1->Fill(Vs[i],VN[i]);
  //}

  TCanvas *c1 = new TCanvas();
  h1->Draw("A*");
  c1->Print("CoulNumDis.eps"); 
}

