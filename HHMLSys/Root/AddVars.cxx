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
float HHMLSys_EventSaver::getRMS(const std::vector<float>& values) {

  float sum_squares = 0;
  unsigned int entries = values.size();
  
  for(unsigned int i=0; i < entries; i++) {
    sum_squares += (values.at(i)) * (values.at(i));
  }
  return sqrt(sum_squares / (float(entries)));
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
  ntup.DRlep1tau0     = 99.;
  ntup.minDR_LJ_0     = 99.;
  ntup.minDR_LJ_1     = 99.;
  ntup.SumPttau0tau1  = -999.;
  ntup.MaxEtalep01    = -999;
  ntup.DEtalep01      = -999;

  //2lSS+1tau
  ntup.DRlep0lep1               = 99.;
  ntup.DRl0Lj                   = 99.;
  ntup.Mlep0Lj                  = -999.;
  ntup.Mlep1Lj                  = -999.;
  ntup.Mlep0SLj                 = -999.; //
  ntup.Mlep01LjSLj              = -999.;
  ntup.MCloserLepTau0           = -999.;
  ntup.MCloserJetlep0           = -999.; //
  ntup.minDRlep0Jet             = 20.;
  ntup.minDRLep1Jet             = -99.; //
  ntup.LBoost2L_ThetaLjTau0     = 20.;//
  ntup.LBoost2L_ThetaSLjTau0    = 20.;//
  ntup.LBoostLep0Tau0_DRlep0SLj = 20.;//
  ntup.LBoostLep1Tau0_DRlep1Lj  = 20.;//

  ntup.DPhilep0Lj   = -99.;
  ntup.farDRlep0Jet = -20.;
  ntup.minDRLepTau0 = 99.;
  ntup.DRlep1Lj     = 99.;
  ntup.RSumPtlep01tau0Jets = -999.;

  //2l
  ntup.MAll     = -999.;
  ntup.MetAll   = -999.;
  ntup.MLep1Jet = -999.;
  ntup.MLep0MET = -999.;
  ntup.MLep1MET = -999.;
  ntup.RMS      = 99.;
  ntup.DR_min_LepJet = 99.;

  //3l
  ntup.FlavorCat    = -2;
  ntup.Mlep0lep1    = -999.;
  ntup.Mlep0lep2    = -999.;
  ntup.Mlep1lep2    = -999.;
  ntup.Mlep012      = -999.;
  ntup.Mlep2LjSLj   = -999.;
  ntup.Mlep012LjSLj = -999.;
  ntup.DRl0l1       = 99.;
  ntup.DRlep1lep2   = 99.;
  ntup.DRlep2CloseJ = 99.;
  ntup.SFOFZVeto = false;

  //4l
  ntup.DR4leps    = 99.;
  ntup.Pt20_4leps = 0;
  ntup.Pt15_4leps = 0;
  ntup.Pt10_4leps = 0;
  ntup.MLep12_4l  = -999.;
  ntup.MLep34_4l  = -999.;
  ntup.M4_4l      = -999.;
  ntup.MLjSLj_4l  = -999.;
  ntup.PtLjSLj_4l = -999.;
  ntup.DPhiJetMET = -99.;
  fill_n(ntup.lepID, sizeof(ntup.lepID), 0);
  ntup.ID_leps4.clear();
  ntup.TLV_4l = TLorentzVector();
  ntup.TLV_4l_lep2 = TLorentzVector();

  //TLV's
  TLorentzVector taus[2];
  TLorentzVector leps[2];
  TLorentzVector jets[2];
  TLorentzVector jet;
  TLorentzVector totalSumjet;
  TLorentzVector MET;

  TLorentzVector TLV_Jets[2];
  TLorentzVector TLV_Leps[3];
  TLorentzVector TLV_tau;

  //2l1tau TLV's for boost
  TLorentzVector TLV_closerJetLep0;
  TLorentzVector TLV_Lep_boost[2];
  TLorentzVector TLV_tau0_boost;
  TLorentzVector TLV_Ljet_boost[2];
  TLorentzVector TLV_SLjet_boost[2];
  TLorentzVector TLV_invMlep0lep1, TLV_invMlep0tau0, TLV_invMlep1tau0;

  //
  //Lepton flavor
  //
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

  if(ntup.trilep_type) {
    float lep_ID[3] = {0};

    lep_ID[0] = ntup.lep_ID_0;
    lep_ID[1] = ntup.lep_ID_1;
    lep_ID[2] = ntup.lep_ID_2;

    int nElectron = 0, nMuon = 0;
    for(auto id: lep_ID) {
      if(abs(id) == 11) nElectron++;
      if(abs(id) == 13) nMuon++;
    }
    if (nElectron == 3) ntup.FlavorCat = 1; // eee
    if (nElectron == 2 and abs(lep_ID[0]) == 11 and abs(lep_ID[1]) == 11) ntup.FlavorCat = 2; // eem
    if (nElectron == 2 and abs(lep_ID[0]) == 11 and abs(lep_ID[1]) == 13) ntup.FlavorCat = 3; // eme
    if (nElectron == 1 and abs(lep_ID[0]) == 11) ntup.FlavorCat = 4; // emm
    if (nElectron == 2 and abs(lep_ID[0]) == 13) ntup.FlavorCat = 5; // mee
    if (nElectron == 1 and abs(lep_ID[0]) == 13 and abs(lep_ID[1]) == 11) ntup.FlavorCat = 6; // mem
    if (nElectron == 1 and abs(lep_ID[0]) == 13 and abs(lep_ID[1]) == 13) ntup.FlavorCat = 7; // mme
    if (nElectron == 0) ntup.FlavorCat = 8; // mmm

    Float_t ZMass_l01 = fabs(ntup.Mll01/GeV - ZMass/GeV);
    Float_t ZMass_l02 = fabs(ntup.Mll02/GeV - ZMass/GeV);
    
    if( ntup.FlavorCat == 2 or ntup.FlavorCat == 7 ) ntup.SFOFZVeto = (ZMass_l01 >= 10);
    if( ntup.FlavorCat == 3 or ntup.FlavorCat == 6 ) ntup.SFOFZVeto = (ZMass_l02 >= 10);
    if( ntup.FlavorCat == 1 or ntup.FlavorCat == 8 ) ntup.SFOFZVeto = ((ZMass_l01 >= 10) and (ZMass_l02 >= 10));
  }

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
  TLV_Leps[2].SetPtEtaPhiE( ntup.lep_Pt_2/1000., ntup.lep_Eta_2, ntup.lep_Phi_2, ntup.lep_E_2/1000. );

  //
  //Init. boost TLV's and compute boost angle vars. for 2l1tau channel
  //
  TLV_Lep_boost[0].SetPtEtaPhiE( ntup.lep_Pt_0/1000., ntup.lep_Eta_0, ntup.lep_Phi_0, ntup.lep_E_0/1000. );
  TLV_Lep_boost[1].SetPtEtaPhiE( ntup.lep_Pt_1/1000., ntup.lep_Eta_1, ntup.lep_Phi_1, ntup.lep_E_1/1000. );

  TLV_tau0_boost.SetPtEtaPhiE( ntup.tau_pt_0/1000., ntup.tau_eta_0, ntup.tau_phi_0, ntup.tau_E_0/1000. );
  
  TLV_Ljet_boost[0].SetPtEtaPhiE( ntup.lead_jetPt/1000., ntup.lead_jetEta, ntup.lead_jetPhi, ntup.lead_jetE/1000. );
  TLV_Ljet_boost[1].SetPtEtaPhiE( ntup.lead_jetPt/1000., ntup.lead_jetEta, ntup.lead_jetPhi, ntup.lead_jetE/1000. );

  TLV_SLjet_boost[0].SetPtEtaPhiE( ntup.sublead_jetPt/1000., ntup.sublead_jetEta, ntup.sublead_jetPhi, ntup.sublead_jetE/1000. );
  TLV_SLjet_boost[1].SetPtEtaPhiE( ntup.sublead_jetPt/1000., ntup.sublead_jetEta, ntup.sublead_jetPhi, ntup.sublead_jetE/1000. );

  TLV_invMlep0lep1 = (TLV_Lep_boost[0] + TLV_Lep_boost[1]);
  TLV_invMlep0tau0 = (TLV_Lep_boost[0] + TLV_tau0_boost);
  TLV_invMlep1tau0 = (TLV_Lep_boost[1] + TLV_tau0_boost);

  TLV_tau0_boost.Boost(-TLV_invMlep0lep1.BoostVector());
  
  TLV_Ljet_boost[0].Boost(-TLV_invMlep0lep1.BoostVector());
  TLV_SLjet_boost[0].Boost(-TLV_invMlep0lep1.BoostVector());

  TLV_Lep_boost[0].Boost(-TLV_invMlep0tau0.BoostVector());
  TLV_SLjet_boost[1].Boost(-TLV_invMlep0tau0.BoostVector());

  TLV_Lep_boost[1].Boost(-TLV_invMlep1tau0.BoostVector());
  TLV_Ljet_boost[1].Boost(-TLV_invMlep1tau0.BoostVector());

  ntup.LBoost2L_ThetaLjTau0  = TLV_tau0_boost.Angle(TLV_Ljet_boost[0].Vect());
  ntup.LBoost2L_ThetaSLjTau0 = TLV_tau0_boost.Angle(TLV_SLjet_boost[0].Vect());

  ntup.LBoostLep0Tau0_DRlep0SLj = DeltaR( (TLV_Lep_boost[0].Eta() - TLV_SLjet_boost[1].Eta()), DeltaPhi(TLV_Lep_boost[0].Phi(), TLV_SLjet_boost[1].Phi()) );
  ntup.LBoostLep1Tau0_DRlep1Lj  = DeltaR( (TLV_Lep_boost[1].Eta() - TLV_Ljet_boost[1].Eta()) , DeltaPhi(TLV_Lep_boost[1].Phi(), TLV_Ljet_boost[1].Phi()) );

  //
  //
  // Missing Energy
  //
  MET.SetPtEtaPhiM(ntup.met_met, 0, ntup.met_phi, 0);

  //
  //Eta info.
  //

  //Max & Delta eta lep0 & lep1
  ntup.MaxEtalep01 = fmax(fabs(ntup.lep_Eta_0), fabs(ntup.lep_Eta_1));
  
  Float_t DEtalep0Lj = (ntup.lep_Eta_0 - ntup.lead_jetEta);
  Float_t DEtalep1Lj = (ntup.lep_Eta_1 - ntup.lead_jetEta);
  
  Float_t DEtalep0tau0 = (ntup.lep_Eta_0 - ntup.tau_eta_0);
  Float_t DEtalep1tau0 = (ntup.lep_Eta_1 - ntup.tau_eta_0);

  ntup.AbsDEtalep01 = abs(ntup.lep_Eta_0 - ntup.lep_Eta_1); //2l
  ntup.DEtalep01 = ntup.lep_Eta_0 - ntup.lep_Eta_1; //2l

  //
  //DeltaPhi
  //
  vector<float> phi_leptons;
  vector<float> phi_jets;
  vector<float> phi_all;

  Float_t DPhilep0lep1 = DeltaPhi(ntup.lep_Phi_0, ntup.lep_Phi_1);
  Float_t DPhilep1Lj   = DeltaPhi(ntup.lep_Phi_1, ntup.lead_jetPhi);

  ntup.DPhilep0Lj = DeltaPhi(ntup.lep_Phi_0, ntup.lead_jetPhi); //2ltau

  Float_t DPhilep0tau0 = DeltaPhi(ntup.lep_Phi_0, ntup.tau_phi_0);
  Float_t DPhilep1tau0 = DeltaPhi(ntup.lep_Phi_1, ntup.tau_phi_0);

  if(ntup.dilep_type) {
    for(unsigned int i = 0; i < 2; i++) {
      phi_leptons.push_back(leps[i].Phi());
      phi_all.push_back(leps[i].Phi());
    }
    phi_leptons.push_back(ntup.met_phi);
    phi_all.push_back(ntup.met_phi);
  }

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

  ntup.DRtau0tau1     = taus[1].DeltaR(taus[0]); //2taus
  ntup.DRlep1tau0     = leps[1].DeltaR(taus[0]); //2taus
  ntup.DRtau0tau1lep0 = (taus[0] + taus[1]).DeltaR(leps[0]); //2taus
  ntup.DRtau0tau1lep1 = (taus[0] + taus[1]).DeltaR(leps[1]); //2taus

  ntup.DRl0Lj     = DeltaR(DEtalep0Lj    , ntup.DPhilep0Lj); //2l1tau
  ntup.DRlep1Lj   = DeltaR(DEtalep1Lj    , DPhilep1Lj); //2l1tau
  ntup.DRlep0lep1 = DeltaR(ntup.DEtalep01, DPhilep0lep1); //2l1tau
  
  Float_t DRlep0tau0 = DeltaR(DEtalep0tau0, DPhilep0tau0);
  Float_t DRlep1tau0 = DeltaR(DEtalep1tau0, DPhilep1tau0);

  ntup.DRl0l1       = TLV_Leps[0].DeltaR(TLV_Leps[1]); //3l
  ntup.DRlep1lep2   = TLV_Leps[1].DeltaR(TLV_Leps[2]); //3l
  ntup.DRlep2CloseJ = (TLV_Leps[2].DeltaR(TLV_Jets[0]) <= TLV_Leps[2].DeltaR(TLV_Jets[1])) ? TLV_Leps[2].DeltaR(TLV_Jets[0]) : TLV_Leps[2].DeltaR(TLV_Jets[1]); //3l

  //
  //Invariant mass
  //
  ntup.Mlep0tau0 = (leps[0] + taus[0]).M();
  ntup.Mlep0tau1 = (leps[0] + taus[1]).M();
  ntup.Mtau0tau1 = (taus[0] + taus[1]).M();
  ntup.Mlep1tau0tau1 = (leps[1] + taus[0] + taus[1]).M();
  
  ntup.Mlep0Lj  = (TLV_Leps[0] + TLV_Jets[0]).M(); //2l1tau
  ntup.Mlep1Lj  = (TLV_Leps[1] + TLV_Jets[0]).M(); //2l1tau
  ntup.Mlep0SLj = (TLV_Leps[0] + TLV_Jets[1]).M(); //2l1tau

  Float_t Mlep0tau0 = (TLV_Leps[0] + TLV_tau).M();
  Float_t Mlep1tau0 = (TLV_Leps[1] + TLV_tau).M();

  ntup.Mlep01LjSLj = (TLV_Leps[1] + TLV_Jets[0] + TLV_Jets[1]).M(); //2l1tau

  ntup.Mlep0lep1    = (TLV_Leps[0] + TLV_Leps[1]).M(); //3l
  ntup.Mlep0lep2    = (TLV_Leps[0] + TLV_Leps[2]).M(); //3l
  ntup.Mlep1lep2    = (TLV_Leps[1] + TLV_Leps[2]).M(); //3l
  ntup.Mlep012      = (TLV_Leps[0] + TLV_Leps[1] + TLV_Leps[2]).M(); //3l
  ntup.Mlep2LjSLj   = (TLV_Leps[2] + TLV_Jets[0] + TLV_Jets[1]).M(); //3l
  ntup.Mlep012LjSLj = min( double(ntup.Mlep0lep1 + ntup.Mlep2LjSLj), (ntup.Mlep0lep2 + (TLV_Leps[1] + TLV_Jets[0] + TLV_Jets[1]).M()) ); //3l

  ntup.MLep0MET = (leps[0] + MET).M(); //2l
  ntup.MLep1MET = (leps[1] + MET).M(); //2l

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
  Float_t DEtalep0Jet = -99., DEtalep1Jet = -99.;
  Float_t DPhilep0Jet = -99., DPhilep1Jet = -99.;
  Float_t DR_lep0Jet  = 99., DR_lep1Jet  = 99.;
  Float_t SumJetPt    = 0;

  int index_l0j(-1), index_l1j(-1); //index for close jet
  jet = TLorentzVector();

  for(unsigned int i = 0; i < ntup.jet_phi->size(); i++) {

    SumJetPt += ntup.jet_pt->at(i);

    jet.SetPtEtaPhiE(ntup.jet_pt->at(i), ntup.jet_eta->at(i), ntup.jet_phi->at(i), ntup.jet_e->at(i));

    totalSumjet += jet;

    phi_jets.push_back(ntup.jet_phi->at(i));
    phi_all.push_back(ntup.jet_phi->at(i));

    DR_l0j = leps[0].DeltaR(jet);
    DR_l1j = leps[1].DeltaR(jet);
    
    if(DR_l0j == 99 or DR_l1j == 99) cout << "AddVars - DeltaR between leptons is wrong!!" << endl;

    if(DR_l0j < ntup.minDR_LJ_0) {
      ntup.minDR_LJ_0 = DR_l0j;
      index_l0j = i;
    }
    if(DR_l1j < ntup.minDR_LJ_1) {
      ntup.minDR_LJ_1 = DR_l1j;
      index_l1j = i;
    }
    
    //2ltau
    if(ntup.jet_isbtagged_DL1r_77->at(i) == 0) {
      DEtalep0Jet = abs(ntup.lep_Eta_0 - ntup.jet_eta->at(i));
      DEtalep1Jet = abs(ntup.lep_Eta_1 - ntup.jet_eta->at(i));

      DPhilep0Jet = DeltaPhi(ntup.lep_Phi_0, ntup.jet_phi->at(i));
      DPhilep1Jet = DeltaPhi(ntup.lep_Phi_1, ntup.jet_phi->at(i));
      
      DR_lep0Jet = DeltaR(DEtalep0Jet, DPhilep0Jet);
      DR_lep1Jet = DeltaR(DEtalep1Jet, DPhilep1Jet);
      
      if( DR_lep0Jet < ntup.minDRlep0Jet ) {
	ntup.minDRlep0Jet = DR_lep0Jet;
	TLV_closerJetLep0 = TLorentzVector();
	TLV_closerJetLep0.SetPtEtaPhiE(ntup.jet_pt->at(i)/1000., ntup.jet_eta->at(i), ntup.jet_phi->at(i), ntup.jet_e->at(i)/1000.);
      }
      if( DR_lep0Jet > ntup.farDRlep0Jet ) {
	ntup.farDRlep0Jet = DR_lep0Jet;
      }
      if( DR_lep1Jet > ntup.minDRLep1Jet ) {
	ntup.minDRLep1Jet = DR_lep1Jet;
      }
    }
  }
  
  ntup.DR_min_LepJet = ntup.minDR_LJ_0;
  if(ntup.minDR_LJ_1 < ntup.DR_min_LepJet) ntup.DR_min_LepJet = ntup.minDR_LJ_1;

  ntup.MCloserJetlep0 = (TLV_Leps[0] + TLV_closerJetLep0).M();

  //Invariant mass var. for 2l 
  ntup.MAll = (leps[0] + leps[1] + totalSumjet + MET).M(); //2l
  ntup.MetAll = (leps[0] + leps[1] + totalSumjet + MET).Mt(); //2l
 
  //Phi info. for 2l
  ntup.RMS = getRMS(phi_jets) * getRMS(phi_leptons) / (getRMS(phi_all));

  //
  //Closest jet and leading/sun-leading lepton
  //
  jet = TLorentzVector();
  if(index_l0j != -1) {
    jet.SetPtEtaPhiE(ntup.jet_pt->at(index_l0j), ntup.jet_eta->at(index_l0j), ntup.jet_phi->at(index_l0j), ntup.jet_e->at(index_l0j));
    ntup.MLep0Jet = (leps[0] + jet).M(); //2l //1l+2tau
  }
  jet = TLorentzVector();
  if(index_l1j != -1) {
    jet.SetPtEtaPhiE(ntup.jet_pt->at(index_l1j), ntup.jet_eta->at(index_l1j), ntup.jet_phi->at(index_l1j), ntup.jet_e->at(index_l1j));
    ntup.MLep1Jet = (leps[1] + jet).M(); //2l
  }

  //
  //Closest lepton and tau
  //
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

  //
  //4l channel stuff
  //

  vector<TLorentzVector> leps4;
  TLorentzVector TLV_4Leps[4];

  if( ntup.quadlep_type ) {

    TLV_4Leps[0].SetPtEtaPhiE( ntup.lep_Pt_0, ntup.lep_Eta_0, ntup.lep_Phi_0, 0 );
    TLV_4Leps[1].SetPtEtaPhiE( ntup.lep_Pt_1, ntup.lep_Eta_1, ntup.lep_Phi_1, 0 );
    TLV_4Leps[2].SetPtEtaPhiE( ntup.lep_Pt_2, ntup.lep_Eta_2, ntup.lep_Phi_2, 0 );
    TLV_4Leps[3].SetPtEtaPhiE( ntup.lep_Pt_3, ntup.lep_Eta_3, ntup.lep_Phi_3, 0 );
  
    for(int l = 0; l < 4; l++) {
      leps4.push_back(TLV_4Leps[l]);
      if(l == 0) ntup.ID_leps4.push_back(ntup.lep_ID_0);
      if(l == 1) ntup.ID_leps4.push_back(ntup.lep_ID_1);
      if(l == 2) ntup.ID_leps4.push_back(ntup.lep_ID_2);
      if(l == 3) ntup.ID_leps4.push_back(ntup.lep_ID_3);
    }
    //DR info.
    for(int j = 1; j < int(leps4.size()); j++) {
      for(int k = 0; k < j; k++) {
        if(ntup.DR4leps < 0.1) break;
        ntup.DR4leps = sqrt( (leps4[j].Eta() - leps4[k].Eta()) * (leps4[j].Eta() - leps4[k].Eta()) + (leps4[j].Phi() - leps4[k].Phi()) * (leps4[j].Phi() - leps4[k].Phi()) ); //4l
      }
    }
    //Pt info. 
    for(int l = 0; l < int(leps4.size()); l++) {
      if( leps4[l].Pt()/GeV > 20 ) ntup.Pt20_4leps++;
      if( leps4[l].Pt()/GeV > 15 ) ntup.Pt15_4leps++;
      if( leps4[l].Pt()/GeV > 10 ) ntup.Pt10_4leps++;
    }
    //lepton pair selection
    Float_t delta_m = 999999;

    ntup.TLV_4l_lep2.SetPtEtaPhiM(0,0,0,ZMass);

    for(int j = 1; j < int(leps4.size()) and ntup.TLV_4l_lep2.M() > 4000; j++) {
      for(int k = 0; k < j && ntup.TLV_4l_lep2.M() > 4000; k++) {

        if(ntup.ID_leps4[j] == -ntup.ID_leps4[k] and ntup.ID_leps4[j] != 0 ) {
          
          ntup.TLV_4l_lep2 = leps4[j] + leps4[k];
        
          if(delta_m > fabs(ZMass - ntup.TLV_4l_lep2.M())) {
            ntup.MLep12_4l = ntup.TLV_4l_lep2.M();
            ntup.lepID[0] = j;
            ntup.lepID[1] = k;                     
            delta_m = fabs(ZMass - ntup.TLV_4l_lep2.M());
          }
        }
      }
    }
    ntup.MLep34_4l = (leps4[ntup.lepID[2]] + leps4[ntup.lepID[3]]).M();
    ntup.TLV_4l = leps4[ntup.lepID[0]] + leps4[ntup.lepID[1]] + leps4[ntup.lepID[2]] + leps4[ntup.lepID[3]];
    ntup.M4_4l  = ntup.TLV_4l.M()/GeV;
    ntup.MLjSLj_4l  = (jets[0] + jets[1]).M()/GeV;
    ntup.PtLjSLj_4l = (jets[0] + jets[1]).Pt()/GeV;
    ntup.DPhiJetMET = ntup.met_phi - ntup.lead_jetPhi;
  }
}
