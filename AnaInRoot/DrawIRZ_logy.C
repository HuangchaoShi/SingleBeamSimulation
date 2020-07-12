#include"/hepustc/home/shihc/workarea/headfile/bes3plotstyle.c"
#include <TCanvas.h>
#include "TTree.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
using namespace std;

void DrawIRZ_logy(){
  SetPrelimStyle();
  SetStyle();
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);

  TString filename = "rootfiles/all.root";
  TFile *fileTracking = new TFile(filename);
  TTree *Toustree = (TTree*) fileTracking->Get("Tous");
  TTree *Coultree = (TTree*) fileTracking->Get("Coul");
  TTree *Bremtree = (TTree*) fileTracking->Get("Brem");

  double xmin=-4,xmax=4,ymax=2e7;
  int nbin=100;
  TH1F *fIRZ_tous = new TH1F("fIRZ_tous","",nbin,xmin,xmax);
  TH1F *fIRZ_coul = new TH1F("fIRZ_coul","",nbin,xmin,xmax);
  TH1F *fIRZ_brem = new TH1F("fIRZ_brem","",nbin,xmin,xmax); 
  fIRZ_tous->SetLineColor(kRed);
  fIRZ_coul->SetLineColor(kGreen);
  fIRZ_brem->SetLineColor(kCyan);
  fIRZ_tous->SetXTitle("Z position /m");
  fIRZ_tous->SetYTitle("Lost number /s"); 
  fIRZ_tous->GetYaxis()->SetRangeUser(0,ymax);

  //---fill touschek----
  Int_t ntous=Toustree->GetEntries();
  Float_t dN_tous,dX_tous,Z0_tous,x_tous,px_tous,y_tous,py_tous,Z_tous,dE_tous,nturn_tous;
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
    fIRZ_tous->Fill(Z_tous);//,dN_tous);
  }

  //----fill coulomb-----
  Int_t ncoul=Toustree->GetEntries();
  Float_t dN_coul,dX_coul,Z0_coul,x_coul,px_coul,y_coul,py_coul,Z_coul,dE_coul,nturn_coul;
  Toustree->SetBranchAddress("dN",&dN_coul);
  Toustree->SetBranchAddress("dX",&dX_coul);
  Toustree->SetBranchAddress("Z0",&Z0_coul);
  Toustree->SetBranchAddress("x",&x_coul);
  Toustree->SetBranchAddress("px",&px_coul);
  Toustree->SetBranchAddress("y",&y_coul);
  Toustree->SetBranchAddress("py",&py_coul);
  Toustree->SetBranchAddress("Z",&Z_coul);
  Toustree->SetBranchAddress("dE",&dE_coul);
  Toustree->SetBranchAddress("nturn",&nturn_coul);
  for(Int_t icoul=0;icoul<ncoul;icoul++){
    Toustree->GetEntry(icoul);
    fIRZ_coul->Fill(Z_coul,dN_coul);
  }
 
  //---fill bremsstrahlung----
  Int_t nbrem=Toustree->GetEntries();
  Float_t dN_brem,dX_brem,Z0_brem,x_brem,px_brem,y_brem,py_brem,Z_brem,dE_brem,nturn_brem;
  Toustree->SetBranchAddress("dN",&dN_brem);
  Toustree->SetBranchAddress("dX",&dX_brem);
  Toustree->SetBranchAddress("Z0",&Z0_brem);
  Toustree->SetBranchAddress("x",&x_brem);
  Toustree->SetBranchAddress("px",&px_brem);
  Toustree->SetBranchAddress("y",&y_brem);
  Toustree->SetBranchAddress("py",&py_brem);
  Toustree->SetBranchAddress("Z",&Z_brem);
  Toustree->SetBranchAddress("dE",&dE_brem);
  Toustree->SetBranchAddress("nturn",&nturn_brem);

  for(Int_t ibrem=0;ibrem<nbrem;ibrem++){
    Toustree->GetEntry(ibrem);
    fIRZ_brem->Fill(Z_brem,dN_brem);
  }
   
  TCanvas *c1 = new TCanvas("c1");

  int DrawLogY=1;
  if(DrawLogY==1){
    double step=(xmax-xmin)/nbin;
    for(double m=xmin+step/2;m<xmax;m=m+step){
      fIRZ_tous->Fill(m,1);
      fIRZ_coul->Fill(m,1);
      fIRZ_brem->Fill(m,1);
    }
    fIRZ_tous->GetYaxis()->SetRangeUser(1,ymax);
    gPad->SetLogy();
  }

  TLegend *leg =new TLegend(0.2,0.65,0.55,0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(fIRZ_tous,"Touschek","l");
  leg->AddEntry(fIRZ_coul,"Coulomb","l");
  leg->AddEntry(fIRZ_brem,"Bremsstrahlung","l");

  fIRZ_tous->Draw(""); 
  fIRZ_coul->Draw("same");
  fIRZ_brem->Draw("same");
  leg->Draw();

  c1->Print("Drawings/Zloss_logy.eps");
}
