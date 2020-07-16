#include"/hepustc/home/shihc/workarea/headfile/bes3plotstyle.c"
#include <TCanvas.h>
#include "TTree.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
using namespace std;

void DrawIRXY(){
  SetPrelimStyle();
  SetStyle();
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);

  TString filename = "rootfiles/all.root";
  TFile *fileTracking = new TFile(filename);
  TTree *Toustree = (TTree*) fileTracking->Get("Tous");
  TTree *Coultree = (TTree*) fileTracking->Get("Coul");
  TTree *Bremtree = (TTree*) fileTracking->Get("Brem");
  
  double length=0.2;
  double xmin=-length,xmax=length,ymin=-length,ymax=length;
  int nbinx=40,nbiny=40;
  TH2F *fIRXY_tous = new TH2F("fIRXY_tous","",nbinx,xmin,xmax,nbiny,ymin,ymax);
  TH2F *fIRXY_coul = new TH2F("fIRXY_coul","",nbinx,xmin,xmax,nbiny,ymin,ymax);
  TH2F *fIRXY_brem = new TH2F("fIRXY_brem","",nbinx,xmin,xmax,nbiny,ymin,ymax); 
  fIRXY_tous->SetXTitle("X position /m");
  fIRXY_tous->SetYTitle("Y position /m"); 

  //---fill touschek----
  Int_t ntous=Toustree->GetEntries();
  Double_t dN_tous,dX_tous,Z0_tous,x_tous,px_tous,y_tous,py_tous,Z_tous,dE_tous,nturn_tous;
  Toustree->SetBranchAddress("dN",&dN_tous);
  Toustree->SetBranchAddress("dX",&dX_tous);
  Toustree->SetBranchAddress("Z0",&Z0_tous);
  Toustree->SetBranchAddress("x",&x_tous);
  Toustree->SetBranchAddress("px",&px_tous);
  Toustree->SetBranchAddress("y",&y_tous);
  Toustree->SetBranchAddress("py",&py_tous);
  Toustree->SetBranchAddress("Z",&Z_tous);
  Toustree->SetBranchAddress("dE",&dE_tous);
  Toustree->SetBranchAddress("nturn",&nturn_tous);
  for(Int_t itous=0;itous<ntous;itous++){
    Toustree->GetEntry(itous);   
    fIRXY_tous->Fill(x_tous,y_tous,dN_tous);
  }

  //----fill coulomb-----
  Int_t ncoul=Coultree->GetEntries();
  Double_t dN_coul,dX_coul,Z0_coul,x_coul,px_coul,y_coul,py_coul,Z_coul,dE_coul,nturn_coul;
  Coultree->SetBranchAddress("dN",&dN_coul);
  Coultree->SetBranchAddress("dX",&dX_coul);
  Coultree->SetBranchAddress("Z0",&Z0_coul);
  Coultree->SetBranchAddress("x",&x_coul);
  Coultree->SetBranchAddress("px",&px_coul);
  Coultree->SetBranchAddress("y",&y_coul);
  Coultree->SetBranchAddress("py",&py_coul);
  Coultree->SetBranchAddress("Z",&Z_coul);
  Coultree->SetBranchAddress("dE",&dE_coul);
  Coultree->SetBranchAddress("nturn",&nturn_coul);
  for(Int_t icoul=0;icoul<ncoul;icoul++){
    Coultree->GetEntry(icoul);
    if(fabs(Z_coul)>0.9) continue;
    fIRXY_coul->Fill(x_coul,y_coul,dN_coul);
  }
 
  //---fill bremsstrahlung----
  Int_t nbrem=Bremtree->GetEntries();
  Double_t dN_brem,dX_brem,Z0_brem,x_brem,px_brem,y_brem,py_brem,Z_brem,dE_brem,nturn_brem;
  Bremtree->SetBranchAddress("dN",&dN_brem);
  Bremtree->SetBranchAddress("dX",&dX_brem);
  Bremtree->SetBranchAddress("Z0",&Z0_brem);
  Bremtree->SetBranchAddress("x",&x_brem);
  Bremtree->SetBranchAddress("px",&px_brem);
  Bremtree->SetBranchAddress("y",&y_brem);
  Bremtree->SetBranchAddress("py",&py_brem);
  Bremtree->SetBranchAddress("Z",&Z_brem);
  Bremtree->SetBranchAddress("dE",&dE_brem);
  Bremtree->SetBranchAddress("nturn",&nturn_brem);

  for(Int_t ibrem=0;ibrem<nbrem;ibrem++){
    Bremtree->GetEntry(ibrem);
    if(fabs(Z_brem)>0.9) continue;
    fIRXY_brem->Fill(x_brem,y_brem,dN_brem);
  }
   
  TCanvas *c1 = new TCanvas("c1");
  c1->Divide(2,2);

  c1->cd(1);
  fIRXY_tous->Draw("colz"); 
  c1->cd(2);
  fIRXY_coul->Draw("colz");
  c1->cd(3);
  fIRXY_brem->Draw("colz");

  c1->Print("Drawings/XY.eps");
}
