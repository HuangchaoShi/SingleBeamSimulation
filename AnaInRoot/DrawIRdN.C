#include"/hepustc/home/shihc/workarea/headfile/bes3plotstyle.c"
#include <TCanvas.h>
#include "TTree.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
using namespace std;

void DrawIRdN(){
  SetPrelimStyle();
  SetStyle();
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);

  TString filename = "rootfiles/all.root";
  TFile *fileTracking = new TFile(filename);
  TTree *Toustree = (TTree*) fileTracking->Get("Tous");
  TTree *Coultree = (TTree*) fileTracking->Get("Coul");
  TTree *Bremtree = (TTree*) fileTracking->Get("Brem");

  double xmin=-8,xmax=5,ymax=6e4;
  int nbin=100;
  TH1F *fIRdN_tous = new TH1F("fIRdN_tous","",nbin,xmin,xmax);
  TH1F *fIRdN_coul = new TH1F("fIRdN_coul","",nbin,xmin,xmax);
  TH1F *fIRdN_brem = new TH1F("fIRdN_brem","",nbin,xmin,xmax); 
  fIRdN_tous->SetMarkerColor(kRed);
  fIRdN_coul->SetMarkerColor(kGreen);
  fIRdN_brem->SetMarkerColor(kBlue);
  fIRdN_tous->SetMarkerStyle(5);
  fIRdN_coul->SetMarkerStyle(26);
  fIRdN_brem->SetMarkerStyle(4);
  fIRdN_tous->SetMarkerSize(1.5);
  fIRdN_coul->SetMarkerSize(1.5);
  fIRdN_brem->SetMarkerSize(1.5);
  fIRdN_tous->SetXTitle("log10(dN)");
  fIRdN_tous->SetYTitle("Evt rate / Hz"); 
  fIRdN_tous->GetYaxis()->SetRangeUser(0,ymax);

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
    fIRdN_tous->Fill(log10(dN_tous));
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
    fIRdN_coul->Fill(log10(dN_coul));
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
    fIRdN_brem->Fill(log10(dN_brem));
  }

  TCanvas *c1 = new TCanvas("c1");
 // gPad->SetLogx();  

  TLegend *leg =new TLegend(0.2,0.7,0.5,0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(fIRdN_tous,"Touschek","p");
  leg->AddEntry(fIRdN_coul,"Coulomb","p");
  leg->AddEntry(fIRdN_brem,"Bremsstrahlung","p");
  
  fIRdN_tous->Draw("E");
  fIRdN_coul->Draw("Esame");
  fIRdN_brem->Draw("Esame");
  leg->Draw();

  c1->Print("Drawings/IRdN.eps");
}
