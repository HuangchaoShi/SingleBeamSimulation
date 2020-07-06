#include"/Users/shihuangchao/Downloads/root_files/headfile/bes3plotstyle.c"
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

void DrawCoulW(){
  double c_light=3e8;
  double charge_e=1.6e-19;
  double bunch_current=9.8e-3; 
  double circum=237.53;
  double num_bunch=93;
  double N_bunch = bunch_current*(circum/c_light)/charge_e;  
  double N_beam = num_bunch*N_bunch;
  double n_scat = 662;

  double P=1e-7;
  double kb=1.38e-23;
  double T=300;
  double N_gas=2*P/kb/T;
  double thetamin=0.0011;

  ifstream file_W(Form("../output/CoulWtoTheta.txt"));
  Vdouble VN,Vtheta;
  double w,theta,tau=0;
  int i=0;
  while(!file_W.eof()){
    file_W>>w>>theta;
    if(theta==0) continue;
    Vtheta.push_back(theta);
    VN.push_back(w*c_light*N_gas);
//cout<<VN[i]<<endl;
    tau=tau+VN[i];
    i++;
  }
  cout<<"life time:"<<1*n_scat/tau/3600<<"hour"<<endl;
  int n_total=i;
  
}

