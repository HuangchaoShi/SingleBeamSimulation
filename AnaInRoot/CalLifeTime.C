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
    //if(dN>1e5) cout<<dN<<";"<<dX<<";"<<Z<<";"<<nturn<<endl;
    Ntotal+=dN; 
  } 
  return Ntotal;
}

void CalLifeTime(){
  double beam_current=0.91,circum=237.53,c_light=3e8,charge_e=1.6e-19;
  double N_beam=beam_current*(circum/c_light)/charge_e;
  cout<<"Total beam particles:"<<N_beam<<endl;
 
  TString file_tous="../output/TousTracking.txt";
  double Ntotal_tous=ReadNtotal(file_tous);
  double tau_tous=N_beam/Ntotal_tous/3600;
  cout<<"Touschek life time:"<<tau_tous<<" hours"<<endl;
 
  TString file_brem="../output/BremTracking.txt";
  double Ntotal_brem=ReadNtotal(file_brem);
  double tau_brem=N_beam/Ntotal_brem/3600;
  cout<<"Bremsstrahlung life time:"<<tau_brem<<" hours"<<endl;

  TString file_coul="../output/CoulTracking.txt";
  double Ntotal_coul=ReadNtotal(file_coul);
  double tau_coul=N_beam/Ntotal_coul/3600;
  cout<<"Coulomb life time:"<<tau_coul<<" hours"<<endl; 

}
