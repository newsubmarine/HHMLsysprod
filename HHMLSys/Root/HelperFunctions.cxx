#include "HHMLSys/HHMLSys_EventSaver.h"

//
// Helper Functions
//

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Tight1LepCuts() {
  
  if( ntup.onelep_type == 0 ) return false;
  
  if( ( abs(ntup.lep_ID_0) == 13         and 
	ntup.lep_isMedium_0 > 0          and 
	ntup.lep_isolationFCLoose_0 > 0  and
	abs(ntup.lep_Eta_0) < 2.5        and
	abs(ntup.lep_Z0SinTheta_0) < 0.5 and 
	abs(ntup.lep_sigd0PV_0) < 3 )
      or
      ( abs(ntup.lep_ID_0) == 11         and 
	ntup.lep_isLooseLH_0 > 0         and
	ntup.lep_isolationFCLoose_0 > 0  and
	abs(ntup.lep_EtaBE2_0) < 2.5     and
	(abs(ntup.lep_EtaBE2_0) < 1.37   or 
	 abs(ntup.lep_EtaBE2_0) > 1.52)  and
	abs(ntup.lep_Z0SinTheta_0) < 0.5 and 
	abs(ntup.lep_sigd0PV_0) < 5 )
      ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Tight2LepCuts(const std::string& channel) {

  if( !ntup.dilep_type ) return false;
 
  if( channel == "2l" ) {
    //Cuts for 2lSS+0tau
    if( ((abs(ntup.lep_ID_0) == 13 and ntup.lep_isMedium_0 > 0  and ntup.lep_plvWP_Tight_0 > 0 and ntup.lep_isolationFCLoose_0 > 0 and abs(ntup.lep_Z0SinTheta_0) < 0.5 and abs(ntup.lep_sigd0PV_0) < 3 and abs(ntup.lep_Eta_0) < 2.5) or
         (abs(ntup.lep_ID_0) == 11 and ntup.lep_isTightLH_0 > 0 and ntup.lep_plvWP_Tight_0 > 0 and ntup.lep_isolationFCLoose_0 > 0 and abs(ntup.lep_Z0SinTheta_0) < 0.5 and abs(ntup.lep_sigd0PV_0) < 5 and abs(ntup.lep_Eta_0) < 2.5 and
	  (abs(ntup.lep_Eta_0) < 1.37 or abs(ntup.lep_Eta_0) > 1.52) and ntup.lep_chargeIDBDTResult_0 > -0.337671 and ntup.lep_ambiguityType_0 == 0))
	and
        ((abs(ntup.lep_ID_1) == 13 and ntup.lep_isMedium_1 > 0  and ntup.lep_plvWP_Tight_1 > 0 and ntup.lep_isolationFCLoose_1 > 0 and abs(ntup.lep_Z0SinTheta_1) < 0.5 and abs(ntup.lep_sigd0PV_1) < 3 and abs(ntup.lep_Eta_1) < 2.5) or
         (abs(ntup.lep_ID_1) == 11 and ntup.lep_isTightLH_1 > 0 and ntup.lep_plvWP_Tight_1 > 0 and ntup.lep_isolationFCLoose_1 > 0 and abs(ntup.lep_Z0SinTheta_1) < 0.5 and abs(ntup.lep_sigd0PV_1) < 5 and abs(ntup.lep_Eta_1) < 2.5 and
	  (abs(ntup.lep_Eta_1) < 1.37 or abs(ntup.lep_Eta_1) > 1.52) and ntup.lep_chargeIDBDTResult_1 > -0.337671 and ntup.lep_ambiguityType_1 == 0))
	) return true;
  }
  else if( channel == "2l1tau" ) { 
    //Cuts for 2lSS+1tau
    if( ((abs(ntup.lep_ID_0) == 13 and ntup.lep_isMedium_0 > 0  and ntup.lep_isolationFCLoose_0 > 0 and abs(ntup.lep_Z0SinTheta_0) < 0.5 and abs(ntup.lep_sigd0PV_0) < 3 and abs(ntup.lep_Eta_0) < 2.5) or
         (abs(ntup.lep_ID_0) == 11 and ntup.lep_isLooseLH_0 > 0 and ntup.lep_isolationFCLoose_0 > 0 and abs(ntup.lep_Z0SinTheta_0) < 0.5 and abs(ntup.lep_sigd0PV_0) < 5 and abs(ntup.lep_EtaBE2_0) < 2.5 and
	  (abs(ntup.lep_EtaBE2_0) < 1.37 or abs(ntup.lep_EtaBE2_0) > 1.52) and ntup.lep_chargeIDBDTLoose_0 > 0))
        and
        ((abs(ntup.lep_ID_1) == 13 and ntup.lep_isMedium_1 > 0  and ntup.lep_isolationFCLoose_1 > 0 and abs(ntup.lep_Z0SinTheta_1) < 0.5 and abs(ntup.lep_sigd0PV_1) < 3 and abs(ntup.lep_Eta_1) < 2.5) or
         (abs(ntup.lep_ID_1) == 11 and ntup.lep_isLooseLH_1 > 0 and ntup.lep_isolationFCLoose_1 > 0 and abs(ntup.lep_Z0SinTheta_1) < 0.5 and abs(ntup.lep_sigd0PV_1) < 5 and abs(ntup.lep_EtaBE2_1) < 2.5 and
	  (abs(ntup.lep_EtaBE2_1) < 1.37 or abs(ntup.lep_EtaBE2_1) > 1.52) and ntup.lep_chargeIDBDTLoose_1 > 0))
	) return true;
  }
  else if( channel == "2l2tau" ) {
    //Cuts for 2l+2tau
    if( ((abs(ntup.lep_ID_0) == 13 and ntup.lep_isMedium_0 > 0  and ntup.lep_isolationFCLoose_0 > 0 and abs(ntup.lep_Z0SinTheta_0) < 0.5 and abs(ntup.lep_sigd0PV_0) < 3 and abs(ntup.lep_Eta_0) < 2.5) or
	 (abs(ntup.lep_ID_0) == 11 and ntup.lep_isLooseLH_0 > 0 and ntup.lep_isolationFCLoose_0 > 0 and abs(ntup.lep_Z0SinTheta_0) < 0.5 and abs(ntup.lep_sigd0PV_0) < 5 and abs(ntup.lep_EtaBE2_0) < 2.5 and
	  (abs(ntup.lep_EtaBE2_0) < 1.37 or abs(ntup.lep_EtaBE2_0) > 1.52)))
	and
	((abs(ntup.lep_ID_1) == 13 and ntup.lep_isMedium_1 > 0  and ntup.lep_isolationFCLoose_1 > 0 and abs(ntup.lep_Z0SinTheta_1) < 0.5 and abs(ntup.lep_sigd0PV_1) < 3 and abs(ntup.lep_Eta_1) < 2.5) or
	 (abs(ntup.lep_ID_1) == 11 and ntup.lep_isLooseLH_1 > 0 and ntup.lep_isolationFCLoose_1 > 0 and abs(ntup.lep_Z0SinTheta_1) < 0.5 and abs(ntup.lep_sigd0PV_1) < 5 and abs(ntup.lep_EtaBE2_1) < 2.5 and
	  (abs(ntup.lep_EtaBE2_1) < 1.37 or abs(ntup.lep_EtaBE2_1) > 1.52)))
	) return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Tight3LepCuts() {

  //Cuts for 3l channel

  if( !ntup.trilep_type ) return false;
  
  bool l0 = ((abs(ntup.lep_ID_0) == 11) ? ntup.lep_isLooseLH_0 : ntup.lep_isLoose_0) and ntup.lep_plvWP_Loose_0;
  bool l1 = ((abs(ntup.lep_ID_1) == 11) ? ntup.lep_isTightLH_1 : ntup.lep_isTight_1) and ntup.lep_plvWP_Tight_1;
  bool l2 = ((abs(ntup.lep_ID_2) == 11) ? ntup.lep_isTightLH_2 : ntup.lep_isTight_2) and ntup.lep_plvWP_Tight_2;
  
  bool AuthorCut = ( ((abs(ntup.lep_ID_0) == 11 and ntup.lep_ambiguityType_0 == 0) or abs(ntup.lep_ID_0) == 13) and ((abs(ntup.lep_ID_1) == 11 and ntup.lep_ambiguityType_1 == 0) or abs(ntup.lep_ID_1) == 13) and ((abs(ntup.lep_ID_2) == 11 and ntup.lep_ambiguityType_2 == 0) or abs(ntup.lep_ID_2) == 13) );
  bool ChargeIDBDT = ( ((abs(ntup.lep_ID_0) == 11) ? ntup.lep_chargeIDBDTLoose_0 : 1) and ((abs(ntup.lep_ID_1) == 11) ? ntup.lep_chargeIDBDTLoose_1 : 1) and ((abs(ntup.lep_ID_2) == 11) ? ntup.lep_chargeIDBDTLoose_2 : 1) );
  
  if( l0 and l1 and l2 and AuthorCut and ChargeIDBDT ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Tight4LepCuts() {

  //Cuts for 4l channel
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Tight4LepbbCuts() {

  //Cuts for 4lbb channel
  if( ntup.lep_plvWP_Loose_2 > 0 and ntup.lep_plvWP_Loose_3 > 0 ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::OneLepTriggers() {
  
  if( (ntup.RunYear == 2015 and (ntup.HLT_mu20_iloose_L1MU15 or ntup.HLT_mu50 or ntup.HLT_e24_lhmedium_L1EM20VH or ntup.HLT_e60_lhmedium or ntup.HLT_e120_lhloose))
      or 
      ( (ntup.RunYear == 2016 or ntup.RunYear == 2017 or ntup.RunYear == 2018) and (ntup.HLT_mu26_ivarmedium or ntup.HLT_mu50 or ntup.HLT_e26_lhtight_nod0_ivarloose or ntup.HLT_e60_lhmedium_nod0 or ntup.HLT_e140_lhloose_nod0 ))) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::DiLepTriggers() {
  
  if( (ntup.RunYear == 2015 and (ntup.HLT_2e12_lhloose_L12EM10VH or ntup.HLT_mu18_mu8noL1 or ntup.HLT_e17_lhloose_mu14))
      or
      ( (ntup.RunYear == 2016 or ntup.RunYear == 2017 or ntup.RunYear == 2018) and (ntup.HLT_2e17_lhvloose_nod0 or ntup.HLT_mu22_mu8noL1 or ntup.HLT_e17_lhloose_nod0_mu14))) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::LepTrigMatch(const std::string& matching) {
  
  if( matching == "SLT" ) {
    if( ntup.custTrigMatch_LooseID_FCLooseIso_SLT > 0 ) return true;
  }
  else if(matching == "SLTorDLT_Loose") {
    if( ntup.custTrigMatch_LooseID_FCLooseIso_SLTorDLT > 0 ) return true;
  }
  else if( matching == "SLTorDLT_Tight" ) {
    if( ntup.custTrigMatch_TightElMediumMuID_FCLooseIso_SLTorDLT > 0 ) return true;
  }
  else {
    if( ntup.GlobalTrigMatch_AT_default_postOR > 0 ) return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::OneLepPtCut() {

  if( ntup.RunYear == 2015 and ((abs(ntup.lep_ID_0) == 13 and ntup.lep_Pt_0/GeV > 21) or (abs(ntup.lep_ID_0) == 11 and ntup.lep_Pt_0/GeV > 25)) ) return true;
  else if( ntup.lep_Pt_0/GeV > 27 ) return true;
  else return false;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::DiLepPtCuts(const float lep0Pt, const float lep1Pt) {

  if( ntup.lep_Pt_0/GeV > lep0Pt and ntup.lep_Pt_1/GeV > lep1Pt ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::TriLepPtCuts(const float lep0Pt, const float lep1Pt, const float lep2Pt) {

  if( ntup.lep_Pt_0/GeV >= lep0Pt and ntup.lep_Pt_1/GeV >= lep1Pt and ntup.lep_Pt_2/GeV >= lep2Pt ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::JetCut(int njet) {
  
  if( ntup.nJets_OR >= njet ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::BJetCut(int nbjet) {
  
  if( ntup.nJets_OR_DL1r_77 >= nbjet ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::BJetVeto() {
  
  if( ntup.nJets_OR_DL1r_77 == 0 ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::Lep0PtCut(const float lep0Pt) {

  if( ntup.lep_Pt_0/GeV > lep0Pt ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::Lep1PtCut(const float lep1Pt) {

  if( ntup.lep_Pt_1/GeV > lep1Pt ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::Lep2PtCut(const float lep2Pt) {

  if( ntup.lep_Pt_2/GeV > lep2Pt ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::Lep3PtCut(const float lep3Pt) {

  if( ntup.lep_Pt_3/GeV > lep3Pt ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLep0Elec() {
  
  if( abs(ntup.lep_ID_0) == 11 ) return true;
  
  return false;
}

//----------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLep0Muon() {
  
  if( abs(ntup.lep_ID_0) == 13 ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isMuonPair() {

  if(ntup.dilep_type == 1) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isOFPair() {

  if(ntup.dilep_type == 2) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isMuElPair() {
  
  if(ntup.dilep_type == 2) {
    if(abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 11) return true;
  }

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isElMuPair() {

  if(ntup.dilep_type == 2) {
    if(abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 13) return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isElecPair() {

  if(ntup.dilep_type == 3) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLep12ElPair() {

  if( abs(ntup.lep_ID_1) == 11 && abs(ntup.lep_ID_2) == 11) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLep12MuPair() {

  if( abs(ntup.lep_ID_1) == 13 && abs(ntup.lep_ID_2) == 13 ) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLep12ElMuPair() {

  if( abs(ntup.lep_ID_1) == 11 && abs(ntup.lep_ID_2) == 13) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLep12MuElPair() {

  if( abs(ntup.lep_ID_1) == 13 && abs(ntup.lep_ID_2) == 11 ) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------                                                                               
bool HHMLSys_EventSaver::isSSPair() {

  if(ntup.lep_ID_0 * ntup.lep_ID_1 > 0) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------                                                                               
bool HHMLSys_EventSaver::isOSPair() {

  if(ntup.lep_ID_0 * ntup.lep_ID_1 < 0) return true;

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::OneTauCuts(const std::string& selection) {

  if( selection == "Base" ) {
    
    if( ntup.tau_passJetIDRNNLoose_0 > 0 and
	ntup.tau_passEleBDT_0        > 0 and
	ntup.tau_passMuonOLR_0       > 0 ) return true;
  }
  else if( selection == "Med" ) {
    
    if( ntup.tau_passJetIDRNNMed_0 > 0 and
	ntup.tau_passEleBDT_0      > 0 and
	ntup.tau_passMuonOLR_0     > 0 ) return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::DiTauCuts(const std::string& selection) {

  if( selection == "Base" ) {
    
    if( ntup.tau_passJetIDRNNLoose_0 > 0 and
	ntup.tau_passEleBDT_0        > 0 and
	ntup.tau_passMuonOLR_0       > 0 and
	ntup.tau_passJetIDRNNLoose_1 > 0 and
	ntup.tau_passEleBDT_1        > 0 and
	ntup.tau_passMuonOLR_1       > 0 ) return true;
  }
  else if( selection == "Med" ) {
    
    if( ntup.tau_passJetIDRNNMed_0   > 0 and
	ntup.tau_passEleBDT_0        > 0 and
	ntup.tau_passMuonOLR_0       > 0 and
	ntup.tau_passJetIDRNNMed_1   > 0 and
	ntup.tau_passEleBDT_1        > 0 and
	ntup.tau_passMuonOLR_1       > 0 ) return true;
  }
  else if( selection == "MedTau0LTau1" ) {
    
    if( ntup.tau_passJetIDRNNMed_0   > 0 and
	ntup.tau_passEleBDT_0        > 0 and
	ntup.tau_passMuonOLR_0       > 0 and
	ntup.tau_passJetIDRNNLoose_1 > 0 and
	ntup.tau_passEleBDT_1        > 0 and
	ntup.tau_passMuonOLR_1       > 0 ) return true;
  }
  else if( selection == "LTau0MedTau1" ) {
    
    if( ntup.tau_passJetIDRNNLoose_0 > 0 and
	ntup.tau_passEleBDT_0        > 0 and
	ntup.tau_passMuonOLR_0       > 0 and
	ntup.tau_passJetIDRNNMed_1   > 0 and
	ntup.tau_passEleBDT_1        > 0 and
	ntup.tau_passMuonOLR_1       > 0 ) return true;
  }

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::OneTauPtCut(const float taupt) {

  if( ntup.tau_pt_0/GeV > taupt ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::DiTauPtCuts(const float tau0pt, const float tau1pt) {

  if( ntup.tau_pt_0/GeV > tau0pt  and
      ntup.tau_pt_1/GeV > tau1pt ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::OSTauPair() {
  
  if(ntup.tau_charge_0 * ntup.tau_charge_1 < 0) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::SSTauPair() {
  
  if(ntup.tau_charge_0 * ntup.tau_charge_1 > 0) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isTauOSToLep() {

  if(ntup.tau_charge_0 * ntup.lep_ID_0 > 0) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::ZVeto(const std::string& channel) {
 
  if(channel == "2l2tau")  {
    if( abs(ntup.Mll01 - 91.2e3) > 10e3 ) return true;
  }
  else if(channel == "2l") {
    if( ((ntup.dilep_type == 3 and abs(ntup.Mll01 - 91200) >= 10e3) or ntup.dilep_type == 2 or ntup.dilep_type == 1) ) return true;
  }
  else if(channel == "3l") {
    if( fabs(ntup.Mlll012/GeV - ZMass/GeV) >= 10 ) return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Mll01SFCut(const float mllcut) {
  
  if( (abs(ntup.lep_ID_0) != abs(ntup.lep_ID_1)) or ntup.Mll01/GeV > mllcut ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::METCut(const float met) {

  if( ntup.met_met/GeV > met ) return true;
  
  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::Mll01Cut(const float mll) {

  if( ntup.Mll01/GeV > mll ) return true;
  
  return false;
}
