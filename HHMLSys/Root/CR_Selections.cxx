#include "HHMLSys/HHMLSys_EventSaver.h"

//
// HHML signal region selections
//

//2l channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::CR2lSelection() {

  weight_2l = 1.0;

  is2Lep_CR = false;
  
  if(is2Lep_SR) return;

  //BDTOutput_2l       = -99;
  //BDTOutput_2l_VV    = -99;
  //BDTOutput_2l_tt    = -99;
  //BDTOutput_2l_Vjets = -99;

  // Commom selection 

  if( !ntup.dilep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight2LepCuts("2l") ) return;
  if( !LepTrigMatch("SLTorDLT_Tight") ) return;
  if( !DiLepPtCuts(20, 20) ) return;
  if( !isSSPair() ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 0) ) return;
  

  if( !JetCut(2) ) return; // At least 2 jets
  if( BJetVeto() ) return; // At least 1 bjets 
  
  is2Lep_CR = true;

  // Currently keep the events and do TF at config level

  //bool XXX_TTBAR_PROMPT = ((ntup.lep_isPrompt_0||((abs(ntup.lep_ID_0)==13&&ntup.lep_truthOrigin_0==0)||(abs(ntup.lep_ID_0)==11&&ntup.lep_truthOrigin_0==5&& (ntup.lep_truthParentPdgId_0==ntup.lep_ID_0) &&ntup.lep_truthParentType_0==2)))&&(ntup.lep_isPrompt_1||((abs(ntup.lep_ID_1)==13&&ntup.lep_truthOrigin_1==0)||(abs(ntup.lep_ID_1)==11&&ntup.lep_truthOrigin_1==5&&(ntup.lep_truthParentPdgId_1==ntup.lep_ID_1)&&ntup.lep_truthParentType_1==2)))); 

  //bool XXX_TTBAR_CONV = (((ntup.lep_truthOrigin_0==5&&!(ntup.lep_truthParentPdgId_0==ntup.lep_ID_0&&ntup.lep_truthParentType_0==2))||(ntup.lep_truthOrigin_1==   5&&!(ntup.lep_truthParentPdgId_1==ntup.lep_ID_1&&ntup.lep_truthParentType_1==2)))));

  //bool XXX_TTBAR_NONQMISID = (ntup.lep_isQMisID_0==0&&ntup.lep_isQMisID_1==0);

  //bool XXX_TTBAR_QED = ((ntup.lep_truthParentType_0==21&&ntup.lep_truthParentOrigin_0==0)||(ntup.lep_truthParentType_1==21&&ntup.lep_truthParentOrigin_1==0));
  if(!m_isData) weight_2l = getMCweight("2l");

  //Get 2l BDT
  if(m_do_2lMVA) mva.EvaluateMVA_2l(ntup, BDTOutput_2l, BDTOutput_2l_VV, BDTOutput_2l_tt, BDTOutput_2l_Vjets);
}

// 2l1tau fake tau scale factor CR
void HHMLSys_EventSaver::CRFakeTauSFSelection() {

  weight_2lLL1tau = 1.0;

  isCRFakeTauSF = false;

  if( !ntup.dilep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight2LepCuts("2l1tau") ) return;
  if( !LepTrigMatch("SLTorDLT_Tight") ) return;
  if( !DiLepPtCuts(20, 20) ) return;
  if( !isOSPair() ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 1) ) return;
  if( !OneTauCuts("Med") ) return;
//  if( !isTauOSToLep() ) return;
  if( !OneTauPtCut(25) ) return;
  //if( !ZVeto("2lep") ) return;
  if( !JetCut(2) ) return;
//  if( !BJetVeto() ) return;
  if( !Mll01SFCut(12) ) return;

  isCRFakeTauSF = true;

  if(!m_isData) weight_2lLL1tau = getMCweight("2l1tau");
}
