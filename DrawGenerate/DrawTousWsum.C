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

void DrawTousWsum(){
  double c_light=3e8;
  double charge_e=1.6e-19;
  double circum=237.53;
  double bunch_current=9.8e-3; 
  double num_bunch=93;
  double N_bunch = bunch_current*(circum/c_light)/charge_e;  
  double N_beam = num_bunch*N_bunch;

  ifstream file_Wsum(Form("../output/TousWsumtoS.txt"));
  double Vs[700],VN[700],Vlscat[700];
  double s,w,lscat,tau=0;
  int i=0;
  while(!file_Wsum.eof()){
    file_Wsum>>w>>s>>lscat;
    Vs[i]=s;
    VN[i]=w*c_light*N_bunch*lscat/circum;
    tau=tau+VN[i];
    i++;
  }
  cout<<"life time:"<<1/tau<<endl;
  int n_total=i;
  
}

