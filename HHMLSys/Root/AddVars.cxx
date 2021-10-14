#include "HHMLSys/HHMLSys_EventSaver.h"

using namespace std;
const Double_t PI = TMath::Pi();

//
// Add new variables
//

//---------------------------------------------------------------------------------------
float HHMLSys_EventSaver::DeltaPhi(float Phi1, float Phi2) {
  
  float Dphi = Phi1 - Phi2;

  if( Dphi > PI )  Dphi = Dphi - (2 * PI);
  if( Dphi < -PI ) Dphi = Dphi + (2 * PI);

  return Dphi;
}

//---------------------------------------------------------------------------------------
float HHMLSys_EventSaver::DeltaR(float DEta, float DPhi){
    
  float DR = sqrt( pow(DEta, 2) + pow(DPhi, 2) );

  return DR;
}

//---------------------------------------------------------------------------------------
void HHMLSys_EventSaver::AddVars() {

  //1l+2tau & 2l+2tau
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

  //2lSS+1tau
  ntup.DRlep0lep1   = 99.;
  ntup.DRl0Lj       = 99.;
  ntup.DRlep1Lj     = 99.;
  ntup.DPhilep0Lj   = -99.;
  ntup.Mlep0Lj      = -999.;
  ntup.Mlep1Lj      = -999.;
  ntup.Mlep2LjSLj   = -999.;
  ntup.minDRlep0Jet = 20.;
  ntup.farDRlep0Jet = -20.;
  ntup.minDRLepTau0 = 99.;
  ntup.MCloserLepTau0 = -999.;
  ntup.RSumPtlep01tau0Jets = -999.;

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

  TLorentzVector TLV_Jets[2];
  TLorentzVector TLV_Leps[2];
  TLorentzVector TLV_tau;
    
  //
  //taus
  //
  taus[0].SetPtEtaPhiE( ntup.tau_pt_0, ntup.tau_eta_0, ntup.tau_phi_0, ntup.tau_E_0 );
  taus[1].SetPtEtaPhiE( ntup.tau_pt_1, ntup.tau_eta_1, ntup.tau_phi_1, ntup.tau_E_1 );

  TLV_tau.SetPtEtaPhiE( ntup.tau_pt_0/1000., ntup.tau_eta_0, ntup.tau_phi_0, ntup.tau_E_0/1000. );

  //
  //leptons
  //
  leps[0].SetPtEtaPhiE( ntup.lep_Pt_0, ntup.lep_Eta_0, ntup.lep_Phi_0, ntup.lep_E_0 );
  leps[1].SetPtEtaPhiE( ntup.lep_Pt_1, ntup.lep_Eta_1, ntup.lep_Phi_1, ntup.lep_E_1 );
  
  TLV_Leps[0].SetPtEtaPhiE( ntup.lep_Pt_0/1000., ntup.lep_Eta_0, ntup.lep_Phi_0, ntup.lep_E_0/1000. );
  TLV_Leps[1].SetPtEtaPhiE( ntup.lep_Pt_1/1000., ntup.lep_Eta_1, ntup.lep_Phi_1, ntup.lep_E_1/1000. );
  
  //
  //Eta info.
  //

  //Max & Delta eta lep0 & lep1
  ntup.MaxEtalep01 = std::fmax(std::fabs(ntup.lep_Eta_0), std::fabs(ntup.lep_Eta_1));
  ntup.DEtalep01   = (ntup.lep_Eta_0 - ntup.lep_Eta_1);
  
  Float_t DEtalep0Lj = (ntup.lep_Eta_0 - ntup.lead_jetEta);
  Float_t DEtalep1Lj = (ntup.lep_Eta_1 - ntup.lead_jetEta);
  
  Float_t DEtalep0tau0 = (ntup.lep_Eta_0 - ntup.tau_eta_0);
  Float_t DEtalep1tau0 = (ntup.lep_Eta_1 - ntup.tau_eta_0);

  //
  //DeltaPhi
  //
  
  Float_t DPhilep0lep1 = DeltaPhi(ntup.lep_Phi_0, ntup.lep_Phi_1);
  Float_t DPhilep1Lj   = DeltaPhi(ntup.lep_Phi_1, ntup.lead_jetPhi);

  ntup.DPhilep0Lj = DeltaPhi(ntup.lep_Phi_0, ntup.lead_jetPhi); //2ltau

  Float_t DPhilep0tau0 = DeltaPhi(ntup.lep_Phi_0, ntup.tau_phi_0);
  Float_t DPhilep1tau0 = DeltaPhi(ntup.lep_Phi_1, ntup.tau_phi_0);

  //
  //DeltaR
  //

  //Lead and subleading jets
  unsigned int nJets = ntup.nJets_OR;

  jets[0].SetPtEtaPhiE(ntup.lead_jetPt, ntup.lead_jetEta, ntup.lead_jetPhi, ntup.lead_jetE);
  TLV_Jets[0].SetPtEtaPhiE(ntup.lead_jetPt/1000., ntup.lead_jetEta, ntup.lead_jetPhi, ntup.lead_jetE/1000.);

  ntup.DRlep0Lj = leps[0].DeltaR(jets[0]);

  if(nJets > 1) {
    jets[1].SetPtEtaPhiE(ntup.sublead_jetPt, ntup.sublead_jetEta, ntup.sublead_jetPhi, ntup.sublead_jetE);
    TLV_Jets[1].SetPtEtaPhiE(ntup.sublead_jetPt/1000., ntup.sublead_jetEta, ntup.sublead_jetPhi, ntup.sublead_jetE/1000.);
    ntup.DRlep0SLj = leps[0].DeltaR(jets[1]);
  }

  ntup.DRtau0tau1     = taus[1].DeltaR(taus[0]);
  ntup.DRtau0tau1lep0 = (taus[0] + taus[1]).DeltaR(leps[0]);
  ntup.DRtau0tau1lep1 = (taus[0] + taus[1]).DeltaR(leps[1]);

  ntup.DRl0Lj     = DeltaR(DEtalep0Lj    , ntup.DPhilep0Lj); //2ltau
  ntup.DRlep1Lj   = DeltaR(DEtalep1Lj    , DPhilep1Lj); //2ltau
  ntup.DRlep0lep1 = DeltaR(ntup.DEtalep01, DPhilep0lep1); //2ltau
  
  Float_t DRlep0tau0 = DeltaR(DEtalep0tau0, DPhilep0tau0);
  Float_t DRlep1tau0 = DeltaR(DEtalep1tau0, DPhilep1tau0);

  //
  //Invariant mass
  //
  ntup.Mlep0tau0 = (leps[0] + taus[0]).M();
  ntup.Mlep0tau1 = (leps[0] + taus[1]).M();
  ntup.Mtau0tau1 = (taus[0] + taus[1]).M();
  ntup.Mlep1tau0tau1 = (leps[1] + taus[0] + taus[1]).M();
  
  ntup.Mlep0Lj = (TLV_Leps[0] + TLV_Jets[0]).M(); //2ltau
  ntup.Mlep1Lj = (TLV_Leps[1] + TLV_Jets[0]).M(); //2ltau

  Float_t Mlep0tau0 = (TLV_Leps[0] + TLV_tau).M();
  Float_t Mlep1tau0 = (TLV_Leps[1] + TLV_tau).M();

  ntup.Mlep2LjSLj = (TLV_Leps[1] + TLV_Jets[0] + TLV_Jets[1]).M(); //2ltau

  //
  //Transverse mass of the W boson
  //
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
  
  //
  //Min. DeltaR between leptons, taus and closest jet
  //
  Float_t DR_l0j      = 99.;
  Float_t DR_l1j      = 99.;
  Float_t DEtalep0Jet = -99.;
  Float_t DPhilep0Jet = -99.;
  Float_t DR_lep0Jet  = 99.;
  Float_t SumJetPt    = 0;

  int index_l0j(-1); //index for close jet
  jet = TLorentzVector();


  for(unsigned int i = 0; i < ntup.jet_phi->size(); i++) {

    SumJetPt += ntup.jet_pt->at(i);

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

    if(ntup.jet_isbtagged_DL1r_77->at(i) == 0) {
      DEtalep0Jet = abs(ntup.lep_Eta_0 - ntup.jet_eta->at(i));
      DPhilep0Jet = DeltaPhi(ntup.lep_Phi_0, ntup.jet_phi->at(i));

      DR_lep0Jet = DeltaR(DEtalep0Jet, DPhilep0Jet);

      if( DR_lep0Jet < ntup.minDRlep0Jet ) {
	ntup.minDRlep0Jet = DR_lep0Jet; //2ltau
      }
      if( DR_lep0Jet > ntup.farDRlep0Jet ) {
	ntup.farDRlep0Jet = DR_lep0Jet; //2l1tau
      }
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

  //Closest lepton and tau

  if(DRlep0tau0 < DRlep1tau0) {
    ntup.minDRLepTau0 = DRlep0tau0;
    ntup.MCloserLepTau0 = Mlep0tau0;
  }
  else{
    ntup.minDRLepTau0 = DRlep1tau0; //2ltau
    ntup.MCloserLepTau0 = Mlep1tau0; //2ltau
  }

  //
  //Sum pT
  //
  ntup.SumPttau0tau1 = (taus[0] + taus[1]).Pt();
  ntup.RSumPtlep01tau0Jets = (ntup.lep_Pt_0 + ntup.lep_Pt_1 + ntup.tau_pt_0) / SumJetPt; //2ltau
}
