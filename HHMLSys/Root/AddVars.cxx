#include "HHMLSys/HHMLSys_EventSaver.h"

using namespace std;

//
// Add new variables
//

//---------------------------------------------------------------------------------------
void HHMLSys_EventSaver::AddVars() {

  ntup.Mtau0tau1      = -999.;
  ntup.Mlep0tau0      = -999.;
  ntup.Mlep0tau1      = -999.;
  ntup.MLep0Jet       = -999.;
  ntup.Mlep1tau0tau1  = -999.;

  ntup.DRtau0tau1     = 99.;
  ntup.DRlep0Lj       = 99.;
  ntup.DRlep0SLj      = 99.;
  ntup.DRtau0tau1lep0 = 99.;
  ntup.DRtau0tau1lep1 = 99.;
  ntup.minDR_LJ_0     = 99.;
  ntup.minDR_LJ_1     = 99.;
  ntup.DR_min_LepJet  = 99.;

  ntup.SumPttau0tau1  = -999.;
  ntup.MaxEtalep01    = -999;
  ntup.DEtalep01      = -999;
  
  //Lepton flavor
  ntup.lep_flavor = -1;
  if(ntup.dilep_type) {
    if(isMuonPair())      ntup.lep_flavor = 1;
    else if(isElecPair()) ntup.lep_flavor = 4;
    else if(isOFPair()) {
      if(isMuElPair())      ntup.lep_flavor = 2;
      else if(isElMuPair()) ntup.lep_flavor = 3;
    }
    else ATH_MSG_FATAL("AddVars - lep0, lep1 neither elec nor muon pair");
  }

  TLorentzVector taus[2];
  TLorentzVector leps[2];
  TLorentzVector jets[2];
  TLorentzVector jet;
    
  //taus
  taus[0].SetPtEtaPhiE( ntup.tau_pt_0, ntup.tau_eta_0, ntup.tau_phi_0, ntup.tau_E_0 );
  taus[1].SetPtEtaPhiE( ntup.tau_pt_1, ntup.tau_eta_1, ntup.tau_phi_1, ntup.tau_E_1 );

  //leptons
  leps[0].SetPtEtaPhiE( ntup.lep_Pt_0, ntup.lep_Eta_0, ntup.lep_Phi_0, ntup.lep_E_0 );
  leps[1].SetPtEtaPhiE( ntup.lep_Pt_1, ntup.lep_Eta_1, ntup.lep_Phi_1, ntup.lep_E_1 );
  
  
  //DeltaR

  //Lead and subleading jets
  unsigned int nJets = ntup.nJets_OR;
  jets[0].SetPtEtaPhiE(ntup.lead_jetPt, ntup.lead_jetEta, ntup.lead_jetPhi, ntup.lead_jetE);
  ntup.DRlep0Lj = leps[0].DeltaR(jets[0]);

  if(nJets > 1) {
    jets[1].SetPtEtaPhiE(ntup.sublead_jetPt, ntup.sublead_jetEta, ntup.sublead_jetPhi, ntup.sublead_jetE);
    ntup.DRlep0SLj = leps[0].DeltaR(jets[1]);
  }

  ntup.DRtau0tau1     = taus[1].DeltaR(taus[0]);
  ntup.DRtau0tau1lep0 = (taus[0] + taus[1]).DeltaR(leps[0]);
  ntup.DRtau0tau1lep1 = (taus[0] + taus[1]).DeltaR(leps[1]);

  //Invariant mass
  ntup.Mlep0tau0 = (leps[0] + taus[0]).M();
  ntup.Mlep0tau1 = (leps[0] + taus[1]).M();
  ntup.Mtau0tau1 = (taus[0] + taus[1]).M();
  ntup.Mlep1tau0tau1 = (leps[1] + taus[0] + taus[1]).M();
  
  //Transverse mass of the W boson
  if( ntup.onelep_type > 0 ) {
    ntup.Mtw = sqrt(2 * ntup.lep_Pt_0 * ntup.met_met * (1 - cos(ntup.lep_Phi_0 - ntup.met_phi)));
  }
  else if(ntup.dilep_type > 0) {
    TLorentzVector met;
    met.SetPtEtaPhiM(ntup.met_met, 0, ntup.met_phi, 0);
    met.SetPz(0);
    met.SetE(met.Pt());
    ntup.Mtw = (leps[0]+leps[1]+met).Mt();
  }

  //Sum pT
  ntup.SumPttau0tau1 = (taus[0] + taus[1]).Pt();

  //Max & Delta eta lep0 & lep1
  ntup.MaxEtalep01 = std::fmax(std::fabs(ntup.lep_Eta_0), std::fabs(ntup.lep_Eta_1));
  ntup.DEtalep01   = (ntup.lep_Eta_0 - ntup.lep_Eta_1 );
  
  //Min. DeltaR between leptons, taus and closest jet
  Float_t DR_l0j = 99.;
  Float_t DR_l1j = 99.;

  int index_l0j(-1); //index for close jet
  for(unsigned int i = 0; i < ntup.jet_phi->size(); i++) {
    
    jet.SetPtEtaPhiE(ntup.jet_pt->at(i), ntup.jet_eta->at(i), ntup.jet_phi->at(i), ntup.jet_e->at(i));

    DR_l0j = leps[0].DeltaR(jet);
    DR_l1j = leps[1].DeltaR(jet);
    
    if(DR_l0j == 99 or DR_l1j == 99) cout << "AddVars - DeltaR between leptons is wrong!!" << endl;

    if(DR_l0j < ntup.minDR_LJ_0) {
      ntup.minDR_LJ_0 = DR_l0j;
      index_l0j = i;
    }
    if(DR_l1j < ntup.minDR_LJ_1) {
      ntup.minDR_LJ_1 = DR_l1j;
    }    
  }
  
  ntup.DR_min_LepJet = ntup.minDR_LJ_0;
  if(ntup.minDR_LJ_1 < ntup.DR_min_LepJet) ntup.DR_min_LepJet = ntup.minDR_LJ_1;
    
  //Closest jet and leading lepton
  jet = TLorentzVector();
  if(index_l0j != -1) {
    jet.SetPtEtaPhiE(ntup.jet_pt->at(index_l0j), ntup.jet_eta->at(index_l0j), ntup.jet_phi->at(index_l0j), ntup.jet_e->at(index_l0j));
    ntup.MLep0Jet = (leps[0] + jet).M();
  }
}
