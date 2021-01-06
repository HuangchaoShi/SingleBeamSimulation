#include <iostream>
#include <fstream>
using namespace std;
const double IRlength=2.875;

double ReadNtotal(TString filename){
  ifstream file1(filename);
  double dN,dX,Z0,x,px,y,py,Z,dE,nturn;
  double Ntotal=0;
  while(!file1.eof()){
    file1>>dN>>dX>>Z0>>x>>px>>y>>py>>Z>>dE>>nturn;
    if(nturn==1001) continue;
    if(dN>2e6) cout<<"filename:"<<filename<<":  "<<dN<<";"<<dX<<";"<<Z0<<";"<<Z<<";"<<nturn<<endl;
    
    Ntotal+=dN; 
  } 
  return Ntotal;
}

double ReadNIR(TString filename,int Zmin,int Zmax){
  ifstream file1(filename);
  double dN,dX,Z0,x,px,y,py,Z,dE,nturn;
  double NIR=0;
  while(!file1.eof()){
    file1>>dN>>dX>>Z0>>x>>px>>y>>py>>Z>>dE>>nturn;
    if(nturn==1001) continue;
    //if(dN>1e8) cout<<dN<<";"<<dX<<";"<<Z0<<";"<<Z<<";"<<nturn<<endl;
    if(fabs(Z)>IRlength) continue;
    NIR+=dN;
  }
  return NIR;
}

double ReadEvtIR(TString filename,int Zmin,int Zmax){
  ifstream file1(filename);
  double dN,dX,Z0,x,px,y,py,Z,dE,nturn;
  double EvtIR=0;
  while(!file1.eof()){
    file1>>dN>>dX>>Z0>>x>>px>>y>>py>>Z>>dE>>nturn;
    if(nturn==1001) continue;
    //if(Z>4||Z<-4) continue;
    if(fabs(Z)>IRlength) continue;
    //if(dN<0.01) continue;
    EvtIR++;
    }
    return EvtIR;
}

void CalLifeTime(){
  double beam_current=0.91,circum=237.53,c_light=3e8,charge_e=1.6e-19;
  double N_beam=beam_current*(circum/c_light)/charge_e;
  cout<<"Total beam particles:"<<N_beam<<endl;

  double tau_tous=0,tau_coul=0,tau_brem=0;
  double NIRtotal_tous=0,NIRtotal_coul=0,NIRtotal_brem=0;
  double EvtIRtotal_tous=0,EvtIRtotal_coul=0,EvtIRtotal_brem=0;

  int ID_start=100,ID_end=200,nfile=ID_end-ID_start;
  for(int i=ID_start;i<ID_end;i++){ 
   cout<<"cal file"<<i<<endl;
   TString file_tous=Form("../runTracking/output/TousTracking_%d.txt",i);
    double Ntotal_tous=ReadNtotal(file_tous);
    tau_tous+=N_beam/Ntotal_tous/3600/nfile;
    double NIR_tous=ReadNIR(file_tous,-4,4); 
    NIRtotal_tous+=NIR_tous/nfile;
    double EvtIR_tous=ReadEvtIR(file_tous,-4,4);
    EvtIRtotal_tous+=EvtIR_tous;

    TString file_brem=Form("../runTracking/output/BremTracking_%d.txt",i);
    double Ntotal_brem=ReadNtotal(file_brem);
    tau_brem+=N_beam/Ntotal_brem/3600/nfile;
    double NIR_brem=ReadNIR(file_brem,-4,4);
    NIRtotal_brem+=NIR_brem/nfile;
    double EvtIR_brem=ReadEvtIR(file_brem,-4,4);
    EvtIRtotal_brem+=EvtIR_brem;
 
    TString file_coul=Form("../runTracking/output/CoulTracking_%d.txt",i);
    double Ntotal_coul=ReadNtotal(file_coul);
    tau_coul+=N_beam/Ntotal_coul/3600/nfile;
    double NIR_coul=ReadNIR(file_coul,-4,4);
    NIRtotal_coul+=NIR_coul/nfile;
    double EvtIR_coul=ReadEvtIR(file_coul,-4,4);
    EvtIRtotal_coul+=EvtIR_coul;
  }

  cout<<"Touschek life time: "<<tau_tous<<" hours"<<endl;
  cout<<"Bremsstrahlung life time: "<<tau_brem<<" hours"<<endl;
  cout<<"Coulomb life time: "<<tau_coul<<" hours"<<endl;

  cout<<"Touschek Loss rate: "<<NIRtotal_tous/1e6<<"MHz"<<endl;
  cout<<"Bremsstrahlung Loss rate: "<<NIRtotal_brem/1e6<<"MHz"<<endl;
  cout<<"Coulomb Loss rate: "<<NIRtotal_coul/1e6<<"MHz"<<endl;

//  cout<<"Touschek evt rate: "<<EvtIRtotal_tous<<endl;
//  cout<<"Bremsstrahlung evt rate: "<<EvtIRtotal_brem<<endl;
//  cout<<"Coulomb evt rate: "<<EvtIRtotal_coul<<endl;   

  exit();
}
