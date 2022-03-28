#include "HHMLSys/HHMLSys_EventSaver.h"

using namespace std;

//
// CR cuts to get lepton fakes for SR using FF.
//

//2lSS + 0tau channel
//SR like CR where FF to be applied . 1 Tight and 1 Anti-Tight lepton, NJet >= 4
//--------------------------------------------------------------------------------
void HHMLSys_EventSaver::CR_2LepSS_FFCuts() {

  ntup.CR_2lSS_eeFF_EventWeight = -99;
  ntup.CR_2lSS_mmFF_EventWeight = -99;
  ntup.CR_2lSS_ofFF_EventWeight = -99;

  CR_2lSS_eeFF_Prompt  = false;
  CR_2lSS_eeFF_QMisID  = false;
  CR_2lSS_eeFF_Fake    = false;

  CR_2lSS_mmFF_Prompt  = false;
  CR_2lSS_mmFF_Fake    = false;

  CR_2lSS_ofFF_Prompt  = false;
  CR_2lSS_ofFF_QMisID  = false;
  CR_2lSS_ofFF_Fake    = false;

  if( !ntup.passEventCleaning ) return;
  if( !(SLTrigCuts() || DLTrigCuts()) ) return;
  if( !ntup.dilep_type ) return;
  if( !Lep2TrigMatch() ) return;
  if( !isSSPair() ) return;
  if( !(ntup.nTaus_OR_Pt25 == 0) ) return;
  if( !Jet_OR_T_Cut(4) ) return; //Jet >= 4
  if( !BJet_OR_T_Cut(1) )  return;

  if( AntiTight2LepCuts("ee") ) {

    Int_t bin_num(-99);
    Float_t ee_FF_weight(1), ee_FF_weightUp(1), ee_FF_weightDn(1);

    if(isLTPair01())      m_apply2lSSFF->ApplyFFWeight(ee_FF_weight, ee_FF_weightUp, ee_FF_weightDn, bin_num, ntup.lep_Pt_0/GeV, LepEnum::Electron);
    else if(isTLPair01()) m_apply2lSSFF->ApplyFFWeight(ee_FF_weight, ee_FF_weightUp, ee_FF_weightDn, bin_num, ntup.lep_Pt_1/GeV, LepEnum::Electron);
    else                ATH_MSG_WARNING("CR_2LepSSCuts - ee - Lep0 or Lep1 is not anti-Tight??");

    ATH_MSG_VERBOSE("ee ff is " << ee_FF_weight);
    
    ntup.CR_2lSS_eeFF_EventWeight = ee_FF_weight;
    
    if(!m_isData) {
      if( !isQMisIdEvent() ) CR_2lSS_eeFF_Prompt = true;
      if(  isQMisIdEvent() ) CR_2lSS_eeFF_QMisID = true;
    }
    else {
      CR_2lSS_eeFF_Fake = true;
    }
  }
  
  if( AntiTight2LepCuts("mm") ) {
    
    Int_t bin_num(-99);
    Float_t mm_FF_weight(1), mm_FF_weightUp(1), mm_FF_weightDn(1);

    if(isLTPair01())      m_apply2lSSFF->ApplyFFWeight(mm_FF_weight, mm_FF_weightUp, mm_FF_weightDn, bin_num, ntup.lep_Pt_0/GeV, LepEnum::Muon);
    else if(isTLPair01()) m_apply2lSSFF->ApplyFFWeight(mm_FF_weight, mm_FF_weightUp, mm_FF_weightDn, bin_num, ntup.lep_Pt_1/GeV, LepEnum::Muon);
    else                ATH_MSG_WARNING("CR_2LepSSCuts - mm - Lep0 or Lep1 is not anti-Tight??");
    
    ATH_MSG_VERBOSE("mm ff is " << mm_FF_weight);

    ntup.CR_2lSS_mmFF_EventWeight = mm_FF_weight;

    if(!m_isData) CR_2lSS_mmFF_Prompt = true;
    else          CR_2lSS_mmFF_Fake   = true;
  }

  if( AntiTight2LepCuts("elNotmu") ) {
   
    Int_t bin_num(-99);
    Float_t mu_FF_weight(1), mu_FF_weightUp(1), mu_FF_weightDn(1);

    if(isLTPair01())      m_apply2lSSFF->ApplyFFWeight(mu_FF_weight, mu_FF_weightUp, mu_FF_weightDn, bin_num, ntup.lep_Pt_0/GeV, LepEnum::Muon);
    else if(isTLPair01()) m_apply2lSSFF->ApplyFFWeight(mu_FF_weight, mu_FF_weightUp, mu_FF_weightDn, bin_num, ntup.lep_Pt_1/GeV, LepEnum::Muon);
    else                ATH_MSG_WARNING("CR_2LepSSCuts - elNotmu - Lep0 or Lep1 is not anti-Tight??");
    
    ATH_MSG_VERBOSE("mu ff is " << mu_FF_weight);

    ntup.CR_2lSS_ofFF_EventWeight = mu_FF_weight;
    
    if(!m_isData) {
      if( !isQMisIdEvent() ) CR_2lSS_ofFF_Prompt = true;
      if(  isQMisIdEvent() ) CR_2lSS_ofFF_QMisID = true;
    }
    else {
      CR_2lSS_ofFF_Fake = true;
    }
  }

  if( AntiTight2LepCuts("muNotel") ) {
  
    Int_t bin_num(-99);
    Float_t el_FF_weight(1), el_FF_weightUp(1), el_FF_weightDn(1);

    if(isLTPair01())      m_apply2lSSFF->ApplyFFWeight(el_FF_weight, el_FF_weightUp, el_FF_weightDn, bin_num, ntup.lep_Pt_0/GeV, LepEnum::Electron);
    else if(isTLPair01()) m_apply2lSSFF->ApplyFFWeight(el_FF_weight, el_FF_weightUp, el_FF_weightDn, bin_num, ntup.lep_Pt_1/GeV, LepEnum::Electron);
    else                ATH_MSG_WARNING("CR_2LepSSCuts - muNotel - Lep0 or Lep1 is not anti-Tight??");
    
    ATH_MSG_VERBOSE("el ff is " << el_FF_weight);

    ntup.CR_2lSS_ofFF_EventWeight = el_FF_weight;

    if(!m_isData) {
      if( !isQMisIdEvent() ) CR_2lSS_ofFF_Prompt = true;
      if(  isQMisIdEvent() ) CR_2lSS_ofFF_QMisID = true;
    }
    else {
      CR_2lSS_ofFF_Fake = true;
    }
  }
}
