#include "HHMLSys/HHMLSys_EventSaver.h"

//
// HHML signal region selections
//

//2l channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR2lSelection() {

  weight_2l = 1.0;

  is2Lep = false;

  BDTOutput_2l_1     = -99;
  BDTOutput_2l_2     = -99;
  BDTOutput_2l_VV    = -99;
  BDTOutput_2l_tt    = -99;
  BDTOutput_2l_Vjets = -99;

  if( !ntup.dilep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight2LepCuts("2l") ) return;
  if( !LepTrigMatch("SLTorDLT_Tight") ) return;
  if( !DiLepPtCuts(20, 20) ) return;
  if( !isSSPair() ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 0) ) return;
  if( !METCut(10) ) return;
  if( !Mll01Cut(12) ) return;
  if( !ZVeto("2l") ) return;
  if( !JetCut(2) ) return;
  if( !BJetVeto() ) return;
  
  is2Lep = true;

  weight_2l = getMCweight("2l");

  //Get 2l BDT
  if(m_do_2lMVA) mva.EvaluateMVA_2l(ntup, BDTOutput_2l_1, BDTOutput_2l_2, BDTOutput_2l_VV, BDTOutput_2l_tt, BDTOutput_2l_Vjets);
}

//3l channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR3lSelection() {

  weight_3l = 1.0;

  is3Lep = false;

  BDTOutput_3l = -99;

  if( !ntup.trilep_type ) return;
  if( abs(ntup.total_charge) != 1 ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !LepTrigMatch("SLTorDLT_Loose") ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 0) ) return;
  if( !Tight3LepCuts() ) return;
  if( !TriLepPtCuts(10, 15, 15) ) return;
  if( !JetCut(1) ) return;
  if( !BJetVeto() ) return;
  if( !ZVeto("3l") ) return;
  if( !ntup.SFOFZVeto ) return;
  
  is3Lep = true;

  weight_3l = getMCweight("3l");

  //Get 3l BDT
  if(m_do_3lMVA) BDTOutput_3l = mva.EvaluateMVA_3l(ntup);
}

//4l channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR4lSelection() {

  weight_4l = 1.0;

  is4Lep = false;

  if( !ntup.quadlep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !JetCut(1) ) return;
  if( !BJetVeto() ) return;
  
  is4Lep = true;

  weight_4l = getMCweight("4l");
}

//4lbb channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR4lbbSelection() {

  weight_4lbb = 1.0;

  is4Lepbb = false;

  BDTOutput_4lbb = -99;

  if( !ntup.quadlep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !(ntup.lep_isTrigMatch_0 or ntup.lep_isTrigMatch_1 or ntup.lep_isTrigMatch_2 or ntup.lep_isTrigMatch_3 or ntup.lep_isTrigMatchDLT_0 or ntup.lep_isTrigMatchDLT_1 or ntup.lep_isTrigMatchDLT_2 or ntup.lep_isTrigMatchDLT_3) ) return;
  if( !Tight4LepbbCuts() ) return;
  if( ntup.DR4leps < 0.1 ) return;
  if( ntup.TLV_4l_lep2.M()/GeV < 4 ) return;
  if( ntup.lepID[0] == ntup.lepID[1] ) return;
  if( (ntup.lepID[1] == 3 - ntup.lepID[0]) ) {
    ntup.lepID[2] = std::abs(2 - ntup.lepID[0]);
    ntup.lepID[3] = 3 - ntup.lepID[2];
  }
  else {
    ntup.lepID[2] = 3 - ntup.lepID[0];
    ntup.lepID[3] = 3 - ntup.lepID[1];
  }
  if( (ntup.ID_leps4[ntup.lepID[2]] != -ntup.ID_leps4[ntup.lepID[3]]) ) return;
  if( !JetCut(2) ) return;
  if( !BJetCut(1) ) return;
  if( ntup.TLV_4l.M()/GeV < 115 or ntup.TLV_4l.M()/GeV > 135 ) return;
  
  is4Lepbb = true;

  weight_4lbb = getMCweight("4lbb");

  //Get 4lbb BDT
  if(m_do_4lbbMVA) BDTOutput_4lbb = mva.EvaluateMVA_4lbb(ntup);
}

//2l+1tau channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR2l1TauSelection() {

  weight_2l1tau = 1.0;

  is2Lep1Tau = false;

  BDTOutput_2l1tau = -99;

  if( !ntup.dilep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight2LepCuts("2l1tau") ) return;
  if( !LepTrigMatch("SLTorDLT_Loose") ) return;
  if( !DiLepPtCuts(20, 20) ) return;
  if( !isSSPair() ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 1) ) return;
  if( !OneTauCuts("Med") ) return;
  if( !isTauOSToLep() ) return;
  if( !OneTauPtCut(30) ) return;
  //if( !ZVeto("2lep") ) return; 
  if( !JetCut(2) ) return;
  if( !BJetVeto() ) return;
  
  is2Lep1Tau = true;

  weight_2l1tau = getMCweight("2l1tau");

  //Get 2l+1tau BDT
  if(m_do_2l1tauMVA) BDTOutput_2l1tau = mva.EvaluateMVA_2l1tau(ntup);
}

//1l+2tau channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR1l2TauSelection() {
  
  weight_1l2tau = 1.0;
  
  is1Lep2Tau = false;

  BDTOutput_1l2tau = -99;

  if( ntup.onelep_type == 0 ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight1LepCuts() ) return;
  if( !LepTrigMatch("SLT") ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 2) ) return; 
  if( !DiTauCuts("Med") ) return;
  if( !OSTauPair() ) return;  
  if( !JetCut(2) ) return;
  if( !BJetVeto() ) return;
  if( ntup.DRtau0tau1 > 2 ) return;
  
  is1Lep2Tau = true;

  weight_1l2tau = getMCweight("1l2tau");

  //Get 1l+2tau BDT
  if(m_do_1l2tauMVA) BDTOutput_1l2tau = mva.EvaluateMVA_1l2tau(ntup);
}

//2l+2tau channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR2l2TauSelection() {

  weight_2l2tau = 1.0;

  is2Lep2Tau = false;

  BDTOutput_2l2tau = -99;

  if( !ntup.dilep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight2LepCuts("2l2tau") ) return;
  if( !isOSPair() ) return;
  if( !LepTrigMatch("SLTorDLT_Loose") ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 2) ) return;
  if( !DiTauCuts(("Med")) ) return;
  if( !OSTauPair() ) return;
  if( !ZVeto("2l2tau") ) return;
  if( !JetCut(1) ) return;
  if( !BJetVeto() ) return;
  if( ntup.DRtau0tau1 > 2 ) return;

  is2Lep2Tau = true;

  weight_2l2tau = getMCweight("2l2tau");
  
  //Get 2l2tau BDT
  if(m_do_2l2tauMVA) BDTOutput_2l2tau = mva.EvaluateMVA_2l2tau(ntup);
}
