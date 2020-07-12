#include "TTree.h"
#include <iostream>
#include <fstream>
using namespace std;

void Gene(int i,int nfile){
  TFile *newfile = new TFile(Form("rootfiles/Tracking_%d.root",i),"recreate");

  //-----touschek-------
  float dN_tous,dX_tous,Z0_tous,x_tous,px_tous,y_tous,py_tous,Z_tous,dE_tous,nturn_tous;
  int Nid_tous=0;
  TTree *newtree_tous = new TTree("Tous","new one");
  TBranch *BrdN_tous = newtree_tous->Branch("dN",&dN_tous,"dN/F");
  TBranch *BrdX_tous = newtree_tous->Branch("dX",&dX_tous,"dX/F");
  TBranch *BrZ0_tous = newtree_tous->Branch("Z0",&Z0_tous,"Z0/F");
  TBranch *Brx_tous = newtree_tous->Branch("x",&x_tous,"x/F"); 
  TBranch *Brpx_tous = newtree_tous->Branch("px",&px_tous,"px/F");
  TBranch *Bry_tous = newtree_tous->Branch("y",&y_tous,"y/F");
  TBranch *Brpy_tous = newtree_tous->Branch("py",&py_tous,"py/F");
  TBranch *BrZ_tous = newtree_tous->Branch("Z",&Z_tous,"Z/F");
  TBranch *BrdE_tous = newtree_tous->Branch("dE",&dE_tous,"dE/F");
  TBranch *Brnturn_tous = newtree_tous->Branch("nturn",&nturn_tous,"nturn/F");
  
  TString filename_tous=Form("../runTracking/output/TousTracking_%d.txt",i);
  ifstream file_tous(filename_tous);
  while(!file_tous.eof()){
    file_tous>>dN_tous>>dX_tous>>Z0_tous>>x_tous>>px_tous>>y_tous>>py_tous>>Z_tous>>dE_tous>>nturn_tous;
    if(nturn_tous==1001||Z_tous<-4||Z_tous>4) continue;
    dN_tous=dN_tous/nfile;
    newtree_tous->GetEntry(Nid_tous);
    newtree_tous->Fill();
    Nid_tous+=1;
  }
  cout<<"Write Touschek"<<endl;
  newtree_tous->Write();
  delete newtree_tous;

  //-----Bremsstrahlung------
  double dN_brem,dX_brem,Z0_brem,x_brem,px_brem,y_brem,py_brem,Z_brem,dE_brem,nturn_brem;
  int Nid_brem=0;
  TTree *newtree_brem = new TTree("Brem","new one");
  TBranch *BrdN_brem = newtree_brem->Branch("dN",&dN_brem,"dN/F");
  TBranch *BrdX_brem = newtree_brem->Branch("dX",&dX_brem,"dX/F");
  TBranch *BrZ0_brem = newtree_brem->Branch("Z0",&Z0_brem,"Z0/F");
  TBranch *Brx_brem = newtree_brem->Branch("x",&x_brem,"x/F");
  TBranch *Brpx_brem = newtree_brem->Branch("px",&px_brem,"px/F");
  TBranch *Bry_brem = newtree_brem->Branch("y",&y_brem,"y/F");
  TBranch *Brpy_brem = newtree_brem->Branch("py",&py_brem,"py/F");
  TBranch *BrZ_brem = newtree_brem->Branch("Z",&Z_brem,"Z/F");
  TBranch *BrdE_brem = newtree_brem->Branch("dE",&dE_brem,"dE/F");
  TBranch *Brnturn_brem = newtree_brem->Branch("nturn",&nturn_brem,"nturn/F");

  TString filename_brem=Form("../runTracking/output/BremTracking_%d.txt",i);
  ifstream file_brem(filename_brem);
  while(!file_brem.eof()){
    file_brem>>dN_brem>>dX_brem>>Z0_brem>>x_brem>>px_brem>>y_brem>>py_brem>>Z_brem>>dE_brem>>nturn_brem;
    if(dX_brem<=0||dX_brem>0.98)  continue;
    if(nturn_brem==1001||Z_brem<-4||Z_brem>4) continue;
    dN_brem=dN_brem/nfile;
    newtree_brem->GetEntry(Nid_brem);
    newtree_brem->Fill();
    Nid_brem+=1;
  }
  cout<<"Write Bremsstrahlung"<<endl;
  newtree_brem->Write();
  delete newtree_brem;

  //-----Coulomb------
  float dN_coul,dX_coul,Z0_coul,x_coul,px_coul,y_coul,py_coul,Z_coul,dE_coul,nturn_coul;
  int Nid_coul=0;
  TTree *newtree_coul = new TTree("Coul","new one");
  TBranch *BrdN_coul = newtree_coul->Branch("dN",&dN_coul,"dN/F");
  TBranch *BrdX_coul = newtree_coul->Branch("dX",&dX_coul,"dX/F");
  TBranch *BrZ0_coul = newtree_coul->Branch("Z0",&Z0_coul,"Z0/F");
  TBranch *Brx_coul = newtree_coul->Branch("x",&x_coul,"x/F");
  TBranch *Brpx_coul = newtree_coul->Branch("px",&px_coul,"px/F");
  TBranch *Bry_coul = newtree_coul->Branch("y",&y_coul,"y/F");
  TBranch *Brpy_coul = newtree_coul->Branch("py",&py_coul,"py/F");
  TBranch *BrZ_coul = newtree_coul->Branch("Z",&Z_coul,"Z/F");
  TBranch *BrdE_coul = newtree_coul->Branch("dE",&dE_coul,"dE/F");
  TBranch *Brnturn_coul = newtree_coul->Branch("nturn",&nturn_coul,"nturn/F");

  TString filename_coul=Form("../runTracking/output/CoulTracking_%d.txt",i);
  ifstream file_coul(filename_coul);
  while(!file_coul.eof()){
    file_coul>>dN_coul>>dX_coul>>Z0_coul>>x_coul>>px_coul>>y_coul>>py_coul>>Z_coul>>dE_coul>>nturn_coul;
    if(nturn_coul==1001||Z_coul<-4||Z_coul>4) continue;
    dN_coul=dN_coul/nfile;
    newtree_coul->GetEntry(Nid_coul);
    newtree_coul->Fill();
    Nid_coul+=1;
  }
  cout<<"Write Coulomb"<<endl;
  newtree_coul->Write();
  delete newtree_coul;  

  newfile->Write();
  delete newfile;
} 

void GeneIRRoot(){
  int ID_start=100,ID_end=200,nfile=ID_end-ID_start;
  for(int i=ID_start;i<ID_end;i++){
    cout<<"make "<<i<<" root file"<<endl;
    Gene(i,nfile);
  }
}
