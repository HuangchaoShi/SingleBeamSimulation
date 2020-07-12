#include <iostream>
#include <fstream>
using namespace std;

double ReadNtotal(TString filename){
  ifstream file1(filename);
  double dN,dX,Z0,x,px,y,py,Z,dE,nturn;
  double Ntotal=0;
  while(!file1.eof()){
    file1>>dN>>dX>>Z0>>x>>px>>y>>py>>Z>>dE>>nturn;
    if(nturn==1001) continue;
    //if(dN>0) cout<<dN<<";"<<dX<<";"<<Z0<<";"<<Z<<";"<<nturn<<endl;
    Ntotal+=dN; 
  } 
  return Ntotal;
}

void CalLifeTime(){
  double beam_current=0.91,circum=237.53,c_light=3e8,charge_e=1.6e-19;
  double N_beam=beam_current*(circum/c_light)/charge_e;
  cout<<"Total beam particles:"<<N_beam<<endl;

  double tau_tous=0,tau_coul=0,tau_brem=0;
  int ID_start=100,ID_end=199,nfile=ID_end-ID_start+1;
  for(int i=ID_start;i<ID_end;i++){ 
   cout<<"cal file"<<i<<endl;
   TString file_tous=Form("../runTracking/output/TousTracking_%d.txt",i);
    double Ntotal_tous=ReadNtotal(file_tous);
    tau_tous+=N_beam/Ntotal_tous/3600/nfile;
  
    TString file_brem=Form("../runTracking/output/BremTracking_%d.txt",i);
    double Ntotal_brem=ReadNtotal(file_brem);
    tau_brem+=N_beam/Ntotal_brem/3600/nfile;
 
    TString file_coul=Form("../runTracking/output/CoulTracking_%d.txt",i);
    double Ntotal_coul=ReadNtotal(file_coul);
    tau_coul+=N_beam/Ntotal_coul/3600/nfile;

  }

  cout<<"Touschek life time:"<<tau_tous<<" hours"<<endl;
  cout<<"Bremsstrahlung life time:"<<tau_brem<<" hours"<<endl;
  cout<<"Coulomb life time:"<<tau_coul<<" hours"<<endl;
}
