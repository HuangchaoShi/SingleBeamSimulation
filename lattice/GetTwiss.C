#include <iostream>
#include <fstream>
using namespace std;

void GetTwiss(){
  TFile *Twissfile = new TFile("Twiss.root","recreate");
  TString filename_BEPC = "ApertSet_BEPC.txt";
  TString filename_STCF = "ApertSet_STCF.txt";
  TString filename_STCFslice = "ApertSet_STCFslice.txt";

  // BEPC parameter  
  double ID_BEPC,s_BEPC,length_BEPC,betaX_BEPC,betaY_BEPC,AX_BEPC,AY_BEPC,EX_BEPC,EY_BEPC,EPX_BEPC,EPY_BEPC;
  int Nid_BEPC=0;
  TTree *newtree_BEPC = new TTree("BEPC","new one"); 
  TBranch *BrID_BEPC = newtree_BEPC->Branch("ID",&ID_BEPC,"ID/D");  
  TBranch *Brs_BEPC = newtree_BEPC->Branch("s",&s_BEPC,"s/D");
  TBranch *Brlength_BEPC = newtree_BEPC->Branch("length",&length_BEPC,"length/D");
  TBranch *BrbetaX_BEPC = newtree_BEPC->Branch("betaX",&betaX_BEPC,"betaX/D");
  TBranch *BrbetaY_BEPC = newtree_BEPC->Branch("betaY",&betaY_BEPC,"betaY/D");
  TBranch *BrAX_BEPC = newtree_BEPC->Branch("AX",&AX_BEPC,"AX/D");
  TBranch *BrAY_BEPC = newtree_BEPC->Branch("AY",&AY_BEPC,"AY/D");
  TBranch *BrEX_BEPC = newtree_BEPC->Branch("EX",&EX_BEPC,"EX/D");
  TBranch *BrEY_BEPC = newtree_BEPC->Branch("EY",&EY_BEPC,"EY/D");
  TBranch *BrEPX_BEPC = newtree_BEPC->Branch("EPX",&EPX_BEPC,"EPX/D");
  TBranch *BrEPY_BEPC = newtree_BEPC->Branch("EPY",&EPY_BEPC,"EPY/D");
  
  ifstream file_BEPC(filename_BEPC);
  while(!file_BEPC.eof()){
    file_BEPC>>ID_BEPC>>s_BEPC>>length_BEPC>>betaX_BEPC>>betaY_BEPC>>AX_BEPC>>AY_BEPC>>EX_BEPC>>EY_BEPC>>EPX_BEPC>>EPY_BEPC;
    newtree_BEPC->GetEntry(Nid_BEPC);
    newtree_BEPC->Fill();
    Nid_BEPC++;
  }
  newtree_BEPC->Write();
  delete newtree_BEPC;

  // STCF no slice
  double ID_STCF,s_STCF,length_STCF,betaX_STCF,betaY_STCF,AX_STCF,AY_STCF,EX_STCF,EY_STCF,EPX_STCF,EPY_STCF;
  int Nid_STCF=0;
  TTree *newtree_STCF = new TTree("STCF","new one");
  TBranch *BrID_STCF = newtree_STCF->Branch("ID",&ID_STCF,"ID/D");
  TBranch *Brs_STCF = newtree_STCF->Branch("s",&s_STCF,"s/D");
  TBranch *Brlength_STCF = newtree_STCF->Branch("length",&length_STCF,"length/D");
  TBranch *BrbetaX_STCF = newtree_STCF->Branch("betaX",&betaX_STCF,"betaX/D");
  TBranch *BrbetaY_STCF = newtree_STCF->Branch("betaY",&betaY_STCF,"betaY/D");
  TBranch *BrAX_STCF = newtree_STCF->Branch("AX",&AX_STCF,"AX/D");
  TBranch *BrAY_STCF = newtree_STCF->Branch("AY",&AY_STCF,"AY/D");
  TBranch *BrEX_STCF = newtree_STCF->Branch("EX",&EX_STCF,"EX/D");
  TBranch *BrEY_STCF = newtree_STCF->Branch("EY",&EY_STCF,"EY/D");
  TBranch *BrEPX_STCF = newtree_STCF->Branch("EPX",&EPX_STCF,"EPX/D");
  TBranch *BrEPY_STCF = newtree_STCF->Branch("EPY",&EPY_STCF,"EPY/D");
  
  ifstream file_STCF(filename_STCF);
  while(!file_STCF.eof()){
    file_STCF>>ID_STCF>>s_STCF>>length_STCF>>betaX_STCF>>betaY_STCF>>AX_STCF>>AY_STCF>>EX_STCF>>EY_STCF>>EPX_STCF>>EPY_STCF;
    newtree_STCF->GetEntry(Nid_STCF);
    newtree_STCF->Fill();
    Nid_STCF++;
  }
  newtree_STCF->Write();
  delete newtree_STCF;

  // STCF slice
  double ID_STCFslice,s_STCFslice,length_STCFslice,betaX_STCFslice,betaY_STCFslice,AX_STCFslice,AY_STCFslice,EX_STCFslice,EY_STCFslice,EPX_STCFslice,EPY_STCFslice;
  int Nid_STCFslice=0;
  TTree *newtree_STCFslice = new TTree("STCFslice","new one");
  TBranch *BrID_STCFslice = newtree_STCFslice->Branch("ID",&ID_STCFslice,"ID/D");
  TBranch *Brs_STCFslice = newtree_STCFslice->Branch("s",&s_STCFslice,"s/D");
  TBranch *Brlength_STCFslice = newtree_STCFslice->Branch("length",&length_STCFslice,"length/D");
  TBranch *BrbetaX_STCFslice = newtree_STCFslice->Branch("betaX",&betaX_STCFslice,"betaX/D");
  TBranch *BrbetaY_STCFslice = newtree_STCFslice->Branch("betaY",&betaY_STCFslice,"betaY/D");
  TBranch *BrAX_STCFslice = newtree_STCFslice->Branch("AX",&AX_STCFslice,"AX/D");
  TBranch *BrAY_STCFslice = newtree_STCFslice->Branch("AY",&AY_STCFslice,"AY/D");
  TBranch *BrEX_STCFslice = newtree_STCFslice->Branch("EX",&EX_STCFslice,"EX/D");
  TBranch *BrEY_STCFslice = newtree_STCFslice->Branch("EY",&EY_STCFslice,"EY/D");
  TBranch *BrEPX_STCFslice = newtree_STCFslice->Branch("EPX",&EPX_STCFslice,"EPX/D");
  TBranch *BrEPY_STCFslice = newtree_STCFslice->Branch("EPY",&EPY_STCFslice,"EPY/D") ;
  
  ifstream file_STCFslice(filename_STCFslice);
  while(!file_STCFslice.eof()){
    file_STCFslice>>ID_STCFslice>>s_STCFslice>>length_STCFslice>>betaX_STCFslice>>betaY_STCFslice>>AX_STCFslice>>AY_STCFslice>>EX_STCFslice>>EY_STCFslice>>EPX_STCFslice>>EPY_STCFslice;
    newtree_STCFslice->GetEntry(Nid_STCFslice);
    newtree_STCFslice->Fill();
    Nid_STCFslice++;
  }
  newtree_STCFslice->Write();
  delete newtree_STCFslice;

}
