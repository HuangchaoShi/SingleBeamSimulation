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

void DrawBremWsum(){
  double c_light=3e8;
  double charge_e=1.6e-19;
  double circum=237.53;
  double bunch_current=9.8e-3; 
  double num_bunch=93;
  double N_bunch = bunch_current*(circum/c_light)/charge_e;  
  double N_beam = num_bunch*N_bunch;
  
  double P=1e-7;
  double kb=1.38e-23;
  double T=300;
  double N_gas=2*P/kb/T;

  ifstream file_Wsum(Form("../output/BremWsumtoS.txt"));
  double Vs[700],VN[700],Vlscat[700];
  double s,w,lscat,tau=0;
  int i=0;
  while(!file_Wsum.eof()){
    file_Wsum>>w>>s>>lscat;
    Vs[i]=s;
    VN[i]=w*c_light*N_gas*lscat/circum;
    tau=tau+VN[i];
    i++;
  }
  cout<<"life time:"<<1/tau/3600<<"hour"<<endl;
  int n_total=i;
  
}

