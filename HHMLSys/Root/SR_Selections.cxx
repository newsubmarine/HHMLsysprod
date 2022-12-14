#include "HHMLSys/HHMLSys_EventSaver.h"

//
// HHML signal region selections
//

//2l channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR2lSelection() {

  weight_2l = 1.0;
  is2Lep_SR = false;

  BDTOutput_2l       = -99;
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
  //if( !METCut(10) ) return;
  //if( !ZVeto("2l") ) return;
  if( !JetCut(2) ) return;
  if( !BJetVeto()  ) return;
  if( !Mll01Cut(12)) return;
  is2Lep_SR = true;
 
  if(!m_isData) weight_2l = getMCweight("2l");

  //Get 2l BDT
  if(m_do_2lMVA) mva.EvaluateMVA_2l(ntup, BDTOutput_2l, BDTOutput_2l_VV, BDTOutput_2l_tt, BDTOutput_2l_Vjets);
}

//3l channel
//---------------------------------------------------------------------
void HHMLSys_EventSaver::SR3lSelection() {

  weight_3l = 1.0;

  is3Lep = false;

  BDTOutput_3l = -99;

//  if( !ntup.trilep_type ) return;
//  if( abs(ntup.total_charge) != 1 ) return;
//  if( !(ntup.GlobalTrigDecision > 0) ) return;
//  if( !LepTrigMatch("SLTorDLT_Loose") ) return;
//  if( !(ntup.nTaus_OR_Pt25_RNN == 0) ) return;
//  if( !Tight3LepCuts() ) return;
//  if( !TriLepPtCuts(10, 15, 15) ) return;
//  if( !JetCut(1) ) return;
//  if( !BJetVeto() ) return;
//  if( !ZVeto("3l") ) return;
//  if( !ntup.SFOFZVeto ) return;
//
//  is3Lep = true;
  SR3Lep = ntup.trilep_type &&
          abs(ntup.total_charge) == 1 &&
          (ntup.GlobalTrigDecision > 0) &&
          LepTrigMatch("SLTorDLT_Loose") &&
          (ntup.nTaus_OR_Pt25_RNN == 0) &&
          Tight3LepCuts() &&
          TriLepPtCuts(10, 15, 15) &&
          JetCut(1) &&
          BJetVeto() &&
          ZVeto("3l") &&
          ntup.SFOFZVeto && ntup.SFOFLowMassVeto;

  if(!m_isData) weight_3l = getMCweight("3l");

  CR3lSelection();
  Sample3lSelection();

  if (SR3Lep || CR3Lep >= 0) is3Lep = true;
  //Get 3l BDT
  if(m_do_3lMVA && is3Lep) BDTOutput_3l = mva.EvaluateMVA_3l(ntup);
}

void HHMLSys_EventSaver::CR3lSelection() {
    CR3Lep = -1;

    auto two_electron = abs(ntup.lep_ID_1) == 11 && abs(ntup.lep_ID_2) == 11;
    auto two_muon = abs(ntup.lep_ID_1) == 13 && abs(ntup.lep_ID_2) == 13;
    { // Internal/Material Conversion:

        // everything but author cut (ambiguity cut)
        auto preselection = ntup.trilep_type &&
                 abs(ntup.total_charge) == 1 &&
                 (ntup.GlobalTrigDecision > 0) &&
                 LepTrigMatch("SLTorDLT_Loose") &&
                 (ntup.nTaus_OR_Pt25_RNN == 0) &&
                 Tight3LepCuts() &&
                 TriLepPtCuts(10, 15, 15) &&
                 JetCut(0) &&
                 BJetVeto() &&
                 !ZVeto("3l");

        auto lep_Mtrktrk_atConvV_CO_1 = (ntup.lep_Mtrktrk_atConvV_CO_1 < 0.1 && ntup.lep_Mtrktrk_atConvV_CO_1 > 0);
        auto lep_Mtrktrk_atConvV_CO_2 = (ntup.lep_Mtrktrk_atConvV_CO_2 < 0.1 && ntup.lep_Mtrktrk_atConvV_CO_2 > 0);

        auto lep_IntConv_atPV_CO_1 = (ntup.lep_Mtrktrk_atPV_CO_1 < 0.1 && ntup.lep_Mtrktrk_atPV_CO_1 > 0);
        auto lep_IntConv_atPV_CO_2 = (ntup.lep_Mtrktrk_atPV_CO_2 < 0.1 && ntup.lep_Mtrktrk_atPV_CO_2 > 0);

        auto material_con_1 =
                (abs(ntup.lep_ID_1) == 11 && (ntup.lep_RadiusCO_1 > 20 && lep_Mtrktrk_atConvV_CO_1)) || abs(ntup.lep_ID_1) == 13;
        auto material_con_2 =
                (abs(ntup.lep_ID_2) == 11 && (ntup.lep_RadiusCO_2 > 20 && lep_Mtrktrk_atConvV_CO_2)) || abs(ntup.lep_ID_2) == 13;

        auto ele_1 = (abs(ntup.lep_ID_1) == 13) ||
                     (abs(ntup.lep_ID_1) == 11 &&
                      (!(lep_IntConv_atPV_CO_1 && !(ntup.lep_RadiusCO_1 > 20 && lep_Mtrktrk_atConvV_CO_1)) &&
                       !(ntup.lep_RadiusCO_1 > 20 && lep_Mtrktrk_atConvV_CO_1)));
        auto ele_2 = (abs(ntup.lep_ID_2) == 13) ||
                     (abs(ntup.lep_ID_2) == 11 &&
                      (!(lep_IntConv_atPV_CO_2 && !(ntup.lep_RadiusCO_2 > 20 && lep_Mtrktrk_atConvV_CO_2)) &&
                       !(ntup.lep_RadiusCO_2 > 20 && lep_Mtrktrk_atConvV_CO_2)));

//        auto internal_con_1 = abs(ntup.lep_ID_1) == 11 && (lep_IntConv_atPV_CO_1);
//        auto internal_con_2 = abs(ntup.lep_ID_2) == 11 && (lep_IntConv_atPV_CO_2);

        auto external_conversion = preselection && (material_con_1 && material_con_2) && !(ele_1 & ele_2);

//        auto internal_conversion = preselection && (internal_con_1 ^ internal_con_2) && !(material_con_1 || material_con_2);
        if (external_conversion) CR3Lep = 0;
    }

    { // Heavy Flavor
        bool l0 = ((abs(ntup.lep_ID_0) == 11) ? ntup.lep_isLooseLH_0 : ntup.lep_isLoose_0);
        bool l1 = ((abs(ntup.lep_ID_1) == 11) ? ntup.lep_isTightLH_1 : ntup.lep_isMedium_1);
        bool l2 = ((abs(ntup.lep_ID_2) == 11) ? ntup.lep_isTightLH_2 : ntup.lep_isMedium_2);

        bool AuthorCut = ( ((abs(ntup.lep_ID_0) == 11 and ntup.lep_ambiguityType_0 == 0) or abs(ntup.lep_ID_0) == 13) and ((abs(ntup.lep_ID_1) == 11 and ntup.lep_ambiguityType_1 == 0) or abs(ntup.lep_ID_1) == 13) and ((abs(ntup.lep_ID_2) == 11 and ntup.lep_ambiguityType_2 == 0) or abs(ntup.lep_ID_2) == 13) );
        bool ChargeIDBDT = ( ((abs(ntup.lep_ID_0) == 11) ? ntup.lep_chargeIDBDTLoose_0 : 1) and ((abs(ntup.lep_ID_1) == 11) ? ntup.lep_chargeIDBDTLoose_1 : 1) and ((abs(ntup.lep_ID_2) == 11) ? ntup.lep_chargeIDBDTLoose_2 : 1) );

        auto preselection = ntup.trilep_type &&
                           abs(ntup.total_charge) == 1 &&
                           (ntup.GlobalTrigDecision > 0) &&
                           LepTrigMatch("SLTorDLT_Loose") &&
                           (ntup.nTaus_OR_Pt25_RNN == 0) &&
                           AuthorCut && ChargeIDBDT && l0 && l1 && l2 &&
                           TriLepPtCuts(10, 15, 15) &&
                           JetCut(2) &&
                           ntup.nJets_OR_DL1r_77 >= 2 &&
                           ZVeto("3l") &&
                           ntup.SFOFZVeto && ntup.SFOFLowMassVeto;

        auto hf_e = preselection && two_electron;
        auto hf_m = preselection && two_muon;

        if (hf_e) CR3Lep = 1;
        if (hf_m) CR3Lep = 2;
    }

    { // WZ CR
        auto preselection = ntup.trilep_type &&
                            abs(ntup.total_charge) == 1 &&
                            (ntup.GlobalTrigDecision > 0) &&
                            LepTrigMatch("SLTorDLT_Loose") &&
                            (ntup.nTaus_OR_Pt25_RNN == 0) &&
                            Tight3LepCuts() &&
                            TriLepPtCuts(10, 15, 15) &&
                            JetCut(0) &&
                            BJetVeto() &&
                            ZVeto("3l") &&
                            !ntup.SFOFZVeto &&
                            ntup.SFOFLowMassVeto &&
                            ntup.met_met/1000. > 30;

        if (preselection) CR3Lep = 3;
    }
}

void HHMLSys_EventSaver::Sample3lSelection() {
    Sample3Lep = -2;

    auto brem_election_1 = (ntup.lep_truthParentPdgId_1 == (int) ntup.lep_ID_1 && ntup.lep_truthParentType_1 == 2);
    auto brem_election_2 = (ntup.lep_truthParentPdgId_2 == (int) ntup.lep_ID_2 && ntup.lep_truthParentType_2 == 2);
    auto prompt_e_1 = (abs((int) ntup.lep_ID_1) == 11 && ntup.lep_truthOrigin_1 == 5 && brem_election_1);
    auto prompt_e_2 = (abs((int) ntup.lep_ID_2) == 11 && ntup.lep_truthOrigin_2 == 5 && brem_election_2);
    auto prompt_m_1 = (abs((int) ntup.lep_ID_1) == 13 && ntup.lep_truthOrigin_1 == 0);
    auto prompt_m_2 = (abs((int) ntup.lep_ID_2) == 13 && ntup.lep_truthOrigin_2 == 0);

    auto prompt_1 = (ntup.lep_isPrompt_1 || prompt_m_1 || prompt_e_1);
    auto prompt_2 = (ntup.lep_isPrompt_2 || prompt_m_2 || prompt_e_2);

    {
        // prompt lepton:
        if(prompt_1 && prompt_2) Sample3Lep = -1;

        // Miss charge
        if(!(((int)ntup.lep_isQMisID_0 == 0) && ((int)ntup.lep_isQMisID_1 == 0) && ((int)ntup.lep_isQMisID_2 == 0))) Sample3Lep = 0;
        if (Sample3Lep == -1 || Sample3Lep == 0) return;
    }

    // Conversion
    auto conv = (ntup.lep_truthOrigin_1 == 5 && !brem_election_1) ||
                (ntup.lep_truthOrigin_2 == 5 && !brem_election_2);

    auto qed = (ntup.lep_truthParentType_1 == 21 && ntup.lep_truthParentOrigin_1 == 0) ||
               (ntup.lep_truthParentType_2 == 21 && ntup.lep_truthParentOrigin_2 == 0);

//    sample.external_conversion = conv && !qed;
//    sample.internal_conversion = conv && qed;
    if (conv && !qed) Sample3Lep = 1;
    if (conv && qed) Sample3Lep = 2;

    { // Heavy-Flavor Electron
        auto hf_1 = (ntup.lep_truthOrigin_1 >= 25 && ntup.lep_truthOrigin_1 <= 29)
                    || ntup.lep_truthOrigin_1 == 32
                    || ntup.lep_truthOrigin_1 == 33;
        auto hf_2 = (ntup.lep_truthOrigin_2 >= 25 && ntup.lep_truthOrigin_2 <= 29)
                    || ntup.lep_truthOrigin_2 == 32
                    || ntup.lep_truthOrigin_2 == 33;

        auto hf_e = ((hf_1 && abs(ntup.lep_ID_1) == 11) || (hf_2 && abs(ntup.lep_ID_2) == 11)) &&
                      ((!(prompt_e_1 || ntup.lep_isPrompt_1) && abs(ntup.lep_ID_1) == 11) ||
                       (!(prompt_e_2 || ntup.lep_isPrompt_2) && abs(ntup.lep_ID_2) == 11)) &&
                      !conv;
        auto hf_m = ((hf_1 && abs(ntup.lep_ID_1) == 13) || (hf_2 && abs(ntup.lep_ID_2) == 13)) &&
                      ((!(prompt_m_1 || ntup.lep_isPrompt_1) && abs(ntup.lep_ID_1) == 13) ||
                       (!(prompt_m_2 || ntup.lep_isPrompt_2) && abs(ntup.lep_ID_2) == 13)) &&
                      !conv;

        // LF
        auto lf_e = !((hf_1 && abs(ntup.lep_ID_1) == 11) || (hf_2 && abs(ntup.lep_ID_2) == 11)) &&
                      ((!(prompt_e_1 || ntup.lep_isPrompt_1) && abs(ntup.lep_ID_1) == 11) ||
                       (!(prompt_e_2 || ntup.lep_isPrompt_2) && abs(ntup.lep_ID_2) == 11)) &&
                      !conv;
        auto lf_m = !((hf_1 && abs(ntup.lep_ID_1) == 13) || (hf_2 && abs(ntup.lep_ID_2) == 13)) &&
                      ((!(prompt_m_1 || ntup.lep_isPrompt_1) && abs(ntup.lep_ID_1) == 13) ||
                       (!(prompt_m_2 || ntup.lep_isPrompt_2) && abs(ntup.lep_ID_2) == 13)) &&
                      !conv;

//        auto others = !conv && (!(prompt_e_1 || ntup.lep_isPrompt_1) && abs(ntup.lep_ID_1) == 11 ||
//                                  !(prompt_e_2 || ntup.lep_isPrompt_2) && abs(ntup.lep_ID_2) == 11);

        if (hf_e) Sample3Lep = 3;
        if (hf_m) Sample3Lep = 4;
        if (lf_e) Sample3Lep = 5;
        if (lf_m) Sample3Lep = 6;
//        if (others) Sample3Lep = 7;
    }

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

  if(!m_isData) weight_4l = getMCweight("4l");
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

  if(!m_isData) weight_4lbb = getMCweight("4lbb");

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
  if( !LepTrigMatch("SLTorDLT_Tight") ) return;
  if( !DiLepPtCuts(20, 20) ) return;
  if( !isSSPair() ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 1) ) return;
  if( !OneTauCuts("Med") ) return;
  if( !isTauOSToLep() ) return;
  if( !OneTauPtCut(25) ) return;
  //if( !ZVeto("2lep") ) return;
  if( !JetCut(2) ) return;
  if( !BJetVeto() ) return;

  is2Lep1Tau = true;

  if(!m_isData) weight_2l1tau = getMCweight("2l1tau");
  if(!m_isData && m_do_2l1tauFakeTauSF){
    tauSF_fakeTau_nom_2l1tau = sfcalc.ApplyFakeTauSF_2l1tau(ntup, "nom");
    tauSF_fakeTau_compostion_up_2l1tau = sfcalc.ApplyFakeTauSF_2l1tau(ntup, "composition_up");
    tauSF_fakeTau_compostion_dn_2l1tau = sfcalc.ApplyFakeTauSF_2l1tau(ntup, "composition_dn");
    tauSF_fakeTau_numerator_up_2l1tau = sfcalc.ApplyFakeTauSF_2l1tau(ntup, "numerator_up");
    tauSF_fakeTau_numerator_dn_2l1tau = sfcalc.ApplyFakeTauSF_2l1tau(ntup, "numerator_dn");
    //if (!(ntup.tau_truthType_0 > 0 && ntup.tau_truthType_0<=12)){
    //  std::cout<<"tau ntrk: "<<ntup.tau_numTrack_0<<std::endl;
    //  std::cout<<"tau pt: "<<ntup.tau_pt_0<<std::endl;
    //  std::cout<<"tau nom SF: "<<tauSF_fakeTau_nom_2l1tau<<std::endl;
    //}
  }

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

  if(!m_isData) weight_1l2tau = getMCweight("1l2tau");

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
  if( !JetCut(0) ) return;
  if( !BJetVeto() ) return;
  if( ntup.DRtau0tau1 > 2 ) return;

  is2Lep2Tau = true;

  if(!m_isData) weight_2l2tau = getMCweight("2l2tau");

  //Get 2l2tau BDT
  if(m_do_2l2tauMVA) BDTOutput_2l2tau = mva.EvaluateMVA_2l2tau(ntup);
}
