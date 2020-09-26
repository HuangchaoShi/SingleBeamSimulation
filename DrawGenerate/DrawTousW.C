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

void DrawTousW(){
  double c_light=3e8;
  double charge_e=1.6e-19;
  //double bunch_current=9.8e-3; 
  //double circum=237.53;
  //double num_bunch=93;
  double bunch_current=1e-2;
  double circum=740.18;
  double num_bunch=200;
  double N_bunch = bunch_current*(circum/c_light)/charge_e;  
  double N_beam = num_bunch*N_bunch;
  //double dEmin = 6.8e-3; 
  double n_scat = 662;
cout<<"particle number in a bunch:"<<N_bunch<<endl;

  ifstream file_W(Form("../output/TousWtodE.txt"));
  Vdouble VN,VdE;
  double w,dE,tau=0;
  int i=0;
  while(!file_W.eof()){
    file_W>>w>>dE;
  //  if(dE<dEmin) continue;
    VdE.push_back(dE);
    VN.push_back(w*c_light*N_bunch*2);
//cout<<VN[i]<<endl;
    tau=tau+VN[i];
    i++;
  }
  cout<<"life time:"<<1*n_scat/tau/3600<<"hour"<<endl;

  int n_total = i;
  int nbin = 100;
  double xmin = -0.1, xmax = 0.1, ymax=1e6;
  TH1F* h1 = new TH1F("h1","",nbin,xmin,xmax);
  h1->SetFillColor(kRed);
  h1->SetXTitle("dE");
  h1->SetYTitle("Loss rate / Hz");
  //h1->GetYaxis->SetRangeUser(0,ymax);
  for(i=0;i<n_total;i++){
    h1->Fill(VdE[i],VN[i]);
  }
  h1->Draw(); 
}

