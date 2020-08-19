#include "TTree.h"
#include <iostream>
#include <fstream>
using namespace std;

void Gene(int i,int nfile){
  TFile *newfile = new TFile(Form("rootfiles/Tracking_%d.root",i),"recreate");

  //-----touschek-------
  double dN_tous,dX_tous,Z0_tous,x_tous,px_tous,y_tous,py_tous,Z_tous,dE_tous,nturn_tous;
  int Nid_tous=0;
  TTree *newtree_tous = new TTree("Tous","new one");
  TBranch *BrdN_tous = newtree_tous->Branch("dN",&dN_tous,"dN/D");
  TBranch *BrdX_tous = newtree_tous->Branch("dX",&dX_tous,"dX/D");
  TBranch *BrZ0_tous = newtree_tous->Branch("Z0",&Z0_tous,"Z0/D");
  TBranch *Brx_tous = newtree_tous->Branch("x",&x_tous,"x/D"); 
  TBranch *Brpx_tous = newtree_tous->Branch("px",&px_tous,"px/D");
  TBranch *Bry_tous = newtree_tous->Branch("y",&y_tous,"y/D");
  TBranch *Brpy_tous = newtree_tous->Branch("py",&py_tous,"py/D");
  TBranch *BrZ_tous = newtree_tous->Branch("Z",&Z_tous,"Z/D");
  TBranch *BrdE_tous = newtree_tous->Branch("dE",&dE_tous,"dE/D");
  TBranch *Brnturn_tous = newtree_tous->Branch("nturn",&nturn_tous,"nturn/D");
  
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
  TBranch *BrdN_brem = newtree_brem->Branch("dN",&dN_brem,"dN/D");
  TBranch *BrdX_brem = newtree_brem->Branch("dX",&dX_brem,"dX/D");
  TBranch *BrZ0_brem = newtree_brem->Branch("Z0",&Z0_brem,"Z0/D");
  TBranch *Brx_brem = newtree_brem->Branch("x",&x_brem,"x/D");
  TBranch *Brpx_brem = newtree_brem->Branch("px",&px_brem,"px/D");
  TBranch *Bry_brem = newtree_brem->Branch("y",&y_brem,"y/D");
  TBranch *Brpy_brem = newtree_brem->Branch("py",&py_brem,"py/D");
  TBranch *BrZ_brem = newtree_brem->Branch("Z",&Z_brem,"Z/D");
  TBranch *BrdE_brem = newtree_brem->Branch("dE",&dE_brem,"dE/D");
  TBranch *Brnturn_brem = newtree_brem->Branch("nturn",&nturn_brem,"nturn/D");

  TString filename_brem=Form("../runTracking/output/BremTracking_%d.txt",i);
  ifstream file_brem(filename_brem);
  while(!file_brem.eof()){
    file_brem>>dN_brem>>dX_brem>>Z0_brem>>x_brem>>px_brem>>y_brem>>py_brem>>Z_brem>>dE_brem>>nturn_brem;
    if(dE_brem<=-1||dE_brem>1||px_brem>1)  continue;
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
  double dN_coul,dX_coul,Z0_coul,x_coul,px_coul,y_coul,py_coul,Z_coul,dE_coul,nturn_coul;
  int Nid_coul=0;
  TTree *newtree_coul = new TTree("Coul","new one");
  TBranch *BrdN_coul = newtree_coul->Branch("dN",&dN_coul,"dN/D");
  TBranch *BrdX_coul = newtree_coul->Branch("dX",&dX_coul,"dX/D");
  TBranch *BrZ0_coul = newtree_coul->Branch("Z0",&Z0_coul,"Z0/D");
  TBranch *Brx_coul = newtree_coul->Branch("x",&x_coul,"x/D");
  TBranch *Brpx_coul = newtree_coul->Branch("px",&px_coul,"px/D");
  TBranch *Bry_coul = newtree_coul->Branch("y",&y_coul,"y/D");
  TBranch *Brpy_coul = newtree_coul->Branch("py",&py_coul,"py/D");
  TBranch *BrZ_coul = newtree_coul->Branch("Z",&Z_coul,"Z/D");
  TBranch *BrdE_coul = newtree_coul->Branch("dE",&dE_coul,"dE/D");
  TBranch *Brnturn_coul = newtree_coul->Branch("nturn",&nturn_coul,"nturn/D");

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
