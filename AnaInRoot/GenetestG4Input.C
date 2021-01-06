#include "TTree.h"
#include <iostream>
#include <fstream>
#include "ApertSet.C"
using namespace std;
using namespace TMath;

void GenetestG4Input(){
  double E0=1890,me=0.511; // MeV
  double p0=sqrt(E0*E0-me*me);
  double theta=0.011;
  double cost=cos(theta);
  double sint=sin(theta); 

  TFile *fileTracking = new TFile("rootfiles/all.root");
  TTree *toustree = (TTree*) fileTracking->Get("Tous");
  TTree *coultree = (TTree*) fileTracking->Get("Coul");
  TTree *bremtree = (TTree*) fileTracking->Get("Brem");

  bool bGeneElec = false;
  if(bGeneElec){
  TFile *newfile = new TFile("G4Input/testSamples/test0Elec.root","recreate");
  }
  else{
  TFile *newfile = new TFile("G4Input/testSamples/test0Posi.root","recreate");
  }
  TTree *newtree_tous = new TTree("tous","new one");
  TTree *newtree_coul = new TTree("coul","new one");
  TTree *newtree_brem = new TTree("brem","new one");

  //------touschek-----
  double dN_tous,x_tous,px_tous,y_tous,py_tous,z_tous,pz_tous; 
  double dN_tousnew,x_tousnew,px_tousnew,y_tousnew,py_tousnew,z_tousnew,pz_tousnew,E_tousnew;

  TBranch *BrdN_tous = newtree_tous->Branch("dN",&dN_tousnew,"dN/D");
  TBranch *Brx_tous = newtree_tous->Branch("x",&x_tousnew,"x/D");
  TBranch *Brpx_tous = newtree_tous->Branch("px",&px_tousnew,"px/D");
  TBranch *Bry_tous = newtree_tous->Branch("y",&y_tousnew,"y/D");
  TBranch *Brpy_tous = newtree_tous->Branch("py",&py_tousnew,"py/D");
  TBranch *Brz_tous = newtree_tous->Branch("z",&z_tousnew,"z/D");
  TBranch *Brpz_tous = newtree_tous->Branch("pz",&pz_tousnew,"pz/D");
  TBranch *BrE_tous = newtree_tous->Branch("E",&E_tousnew,"E/D");
  toustree->SetBranchAddress("dN",&dN_tous);
  toustree->SetBranchAddress("x",&x_tous);
  toustree->SetBranchAddress("px",&px_tous);
  toustree->SetBranchAddress("y",&y_tous);
  toustree->SetBranchAddress("py",&py_tous);
  toustree->SetBranchAddress("Z",&z_tous);
  toustree->SetBranchAddress("dE",&pz_tous);
  Int_t ntous=toustree->GetEntries();
  for(Int_t itous=0;itous<ntous;itous++){
    toustree->GetEntry(itous);
    dN_tousnew=dN_tous;
    
    //old transfer from acc coordinate to detector coordinate
    double px_cm=px_tous*p0;
    double py_cm=py_tous*p0;
    double pz_cm=(1+pz_tous)*p0;
    px_tousnew = px_cm*cost+pz_cm*sint;
    py_tousnew = py_cm;
    pz_tousnew = -px_cm*sint+pz_cm*cost;
    E_tousnew=sqrt(px_tousnew*px_tousnew+py_tousnew*py_tousnew+pz_tousnew*pz_tousnew+me*me);
/*
    if(x_tous>0.0315) x_tousnew=0.0315;
    else if(x_tous<-0.0315) x_tousnew=-0.0315;
    else x_tousnew = x_tous;

    if(y_tous>0.0315) y_tousnew=0.0315;
    else if(y_tous<-0.0315) y_tousnew=-0.0315;
    else y_tousnew = y_tous;
*/
    if(z_tous>2.8) z_tous=2.8;
    else if(z_tous<-2.8) z_tous=-2.8;

    px_tousnew = p0*sint;
    py_tousnew = 0;
    pz_tousnew = p0*cost;
    E_tousnew = E0;
    x_tousnew = z_tous*sint;
    y_tousnew = 0;
    z_tousnew = z_tous*cost;    

    //electron
    if(bGeneElec){
      pz_tousnew=-pz_tousnew;
      z_tousnew=-z_tousnew;
    }
  
    newtree_tous->GetEntry(itous);
    newtree_tous->Fill();
  }
  cout<<"write touschek"<<endl;

  //-----coulomb-------
  double dN_coul,x_coul,px_coul,y_coul,py_coul,z_coul,pz_coul;
  double dN_coulnew,x_coulnew,px_coulnew,y_coulnew,py_coulnew,z_coulnew,pz_coulnew,E_coulnew;

//  TTree *newtree_coul = new TTree("coul","new one");
  TBranch *BrdN_coul = newtree_coul->Branch("dN",&dN_coulnew,"dN/D");
  TBranch *Brx_coul = newtree_coul->Branch("x",&x_coulnew,"x/D");
  TBranch *Brpx_coul = newtree_coul->Branch("px",&px_coulnew,"px/D");
  TBranch *Bry_coul = newtree_coul->Branch("y",&y_coulnew,"y/D");
  TBranch *Brpy_coul = newtree_coul->Branch("py",&py_coulnew,"py/D");
  TBranch *Brz_coul = newtree_coul->Branch("z",&z_coulnew,"z/D");
  TBranch *Brpz_coul = newtree_coul->Branch("pz",&pz_coulnew,"pz/D");
  TBranch *BrE_coul = newtree_coul->Branch("E",&E_coulnew,"E/D");
  coultree->SetBranchAddress("dN",&dN_coul);
  coultree->SetBranchAddress("x",&x_coul);
  coultree->SetBranchAddress("px",&px_coul);
  coultree->SetBranchAddress("y",&y_coul);
  coultree->SetBranchAddress("py",&py_coul);
  coultree->SetBranchAddress("Z",&z_coul);
  coultree->SetBranchAddress("dE",&pz_coul);
  Int_t ncoul=coultree->GetEntries();
  for(Int_t icoul=0;icoul<ncoul;icoul++){
    coultree->GetEntry(icoul);
    dN_coulnew=dN_coul;
    double px_cm=px_coul*p0;
    double py_cm=py_coul*p0;
    double pz_cm=(1+pz_coul)*p0;
    px_coulnew = px_cm*cost+pz_cm*sint;
    py_coulnew = py_cm;
    pz_coulnew = -px_cm*sint+pz_cm*cost;
    E_coulnew=sqrt(px_coulnew*px_coulnew+py_coulnew*py_coulnew+pz_coulnew*pz_coulnew+me*me);
/*
    if(x_coul>0.0315) x_coulnew=0.0315;
    else if(x_coul<-0.0315) x_coulnew=-0.0315;
    else x_coulnew = x_coul;

    if(y_coul>0.0315) y_coulnew=0.0315;
    else if(y_coul<-0.0315) y_coulnew=-0.0315;
    else y_coulnew = y_coul;
*/
    if(z_coul>2.8) z_coul=2.8;
    else if(z_coul<-2.8) z_coul=-2.8;

    px_coulnew = p0*sint;
    py_coulnew = 0;
    pz_coulnew = p0*cost;
    E_coulnew = E0;
    x_coulnew = z_coul*sint;
    y_coulnew = 0;
    z_coulnew = z_coul*cost;


    if(bGeneElec){
      pz_coulnew=-pz_coulnew;
      z_coulnew=-z_coulnew;
    }
    
    newtree_coul->GetEntry(icoul);
    newtree_coul->Fill();
  }
  cout<<"write coulomb"<<endl;
  

  //----bremsstrahlung------
  double dN_brem,x_brem,px_brem,y_brem,py_brem,z_brem,pz_brem;
  double dN_bremnew,x_bremnew,px_bremnew,y_bremnew,py_bremnew,z_bremnew,pz_bremnew,E_bremnew;

//  TTree *newtree_brem = new TTree("brem","new one");
  TBranch *BrdN_brem = newtree_brem->Branch("dN",&dN_bremnew,"dN/D");
  TBranch *Brx_brem = newtree_brem->Branch("x",&x_bremnew,"x/D");
  TBranch *Brpx_brem = newtree_brem->Branch("px",&px_bremnew,"px/D");
  TBranch *Bry_brem = newtree_brem->Branch("y",&y_bremnew,"y/D");
  TBranch *Brpy_brem = newtree_brem->Branch("py",&py_bremnew,"py/D");
  TBranch *Brz_brem = newtree_brem->Branch("z",&z_bremnew,"z/D");
  TBranch *Brpz_brem = newtree_brem->Branch("pz",&pz_bremnew,"pz/D");
  TBranch *BrE_brem = newtree_brem->Branch("E",&E_bremnew,"E/D");
  bremtree->SetBranchAddress("dN",&dN_brem);
  bremtree->SetBranchAddress("x",&x_brem);
  bremtree->SetBranchAddress("px",&px_brem);
  bremtree->SetBranchAddress("y",&y_brem);
  bremtree->SetBranchAddress("py",&py_brem);
  bremtree->SetBranchAddress("Z",&z_brem);
  bremtree->SetBranchAddress("dE",&pz_brem);
  Int_t nbrem=bremtree->GetEntries();
  for(Int_t ibrem=0;ibrem<nbrem;ibrem++){
    bremtree->GetEntry(ibrem);
    dN_bremnew=dN_brem;
    double px_cm=px_brem*p0;
    double py_cm=py_brem*p0;
    double pz_cm=(1+pz_brem)*p0;
    px_bremnew = px_cm*cost+pz_cm*sint;
    py_bremnew = py_cm;
    pz_bremnew = -px_cm*sint+pz_cm*cost;
    E_bremnew=sqrt(px_bremnew*px_bremnew+py_bremnew*py_bremnew+pz_bremnew*pz_bremnew+me*me);
/*
    if(x_brem>0.0315) x_bremnew=0.0315;
    else if(x_brem<-0.0315) x_bremnew=-0.0315;
    else x_bremnew = x_brem;

    if(y_brem>0.0315) y_bremnew=0.0315;
    else if(y_brem<-0.0315) y_bremnew=-0.0315;
    else y_bremnew = y_brem;
*/
    if(z_brem>2.8) z_brem=2.8;
    else if(z_brem<-2.8) z_brem=-2.8;
   
    px_bremnew = p0*sint;
    py_bremnew = 0;
    pz_bremnew = p0*cost;
    E_bremnew = E0;
    x_bremnew = z_brem*sint;
    y_bremnew = 0;
    z_bremnew = z_brem*cost;

    if(bGeneElec){
      pz_bremnew=-pz_bremnew;
      z_bremnew=-z_bremnew;
    }

    newtree_brem->GetEntry(ibrem);
    newtree_brem->Fill();
  }
  cout<<"write bremsstrahlung"<<endl;

  newfile->Write();
  delete newfile;
}
