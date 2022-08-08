#include "HHMLSys/HHMLSys_EventSaver.h"

//
// Save branches in new Tree
//

//IMPORTANT. Please make sure to add only necessary branches.

//--------------------------------------------------------------
void HHMLSys_EventSaver::SetOutTree(TTree* outTree, bool setNom) {

  //
  // Add new Branches
  //
  
  //Common
  outTree->Branch("Event"        , &ntup.eventNumber);
  outTree->Branch("RunNumber"    , &ntup.runNumber);
  outTree->Branch("RunYear"      , &ntup.RunYear);
  outTree->Branch("weight_pileup", &ntup.weight_pileup);
  outTree->Branch("mcChannelNumber", &ntup.mcChannelNumber);

  //MC weights of each channel
  outTree->Branch("scale"        , &m_scale); //Sum of weighted events
  outTree->Branch("weight_2l"    , &weight_2l);
  outTree->Branch("weight_3l"    , &weight_3l);
  outTree->Branch("weight_4l"    , &weight_4l);
  outTree->Branch("weight_4lbb"  , &weight_4lbb);
  outTree->Branch("weight_2l1tau", &weight_2l1tau);
  outTree->Branch("weight_1l2tau", &weight_1l2tau);
  outTree->Branch("weight_2l2tau", &weight_2l2tau);

  //CR's
  outTree->Branch("weight_1l2tauCRSS", &weight_1l2tauCRSS);
  outTree->Branch("weight_2l2tauCRSS", &weight_2l2tauCRSS);

  //Booleans of each singal regions
  outTree->Branch("is2Lep_SR"  , &is2Lep_SR);
  outTree->Branch("is2Lep_CR"  , &is2Lep_CR);
  outTree->Branch("is3Lep"     , &is3Lep);
  outTree->Branch("is4Lep"     , &is4Lep);
  outTree->Branch("is4Lepbb"   , &is4Lepbb);
  outTree->Branch("is2Lep1Tau" , &is2Lep1Tau);
  outTree->Branch("is1Lep2Tau" , &is1Lep2Tau);
  outTree->Branch("is2Lep2Tau" , &is2Lep2Tau);

  //CRs
  outTree->Branch("SR3Lep"     , &SR3Lep);
  outTree->Branch("CR3Lep"     , &CR3Lep);
  outTree->Branch("Sample3Lep" , &Sample3Lep);

  outTree->Branch("is1Lep2TauCRSS" , &is1Lep2TauCRSS);
  outTree->Branch("is2Lep2TauCRSS" , &is2Lep2TauCRSS);

  //BDT outputs of each channel
  outTree->Branch("BDTOutput_2l"       , &BDTOutput_2l);
  outTree->Branch("BDTOutput_2l_VV"    , &BDTOutput_2l_VV);
  outTree->Branch("BDTOutput_2l_tt"    , &BDTOutput_2l_tt);
  outTree->Branch("BDTOutput_2l_Vjets" , &BDTOutput_2l_Vjets);
  outTree->Branch("BDTOutput_3l"       , &BDTOutput_3l);
  outTree->Branch("BDTOutput_4lbb"     , &BDTOutput_4lbb);
  outTree->Branch("BDTOutput_2l1tau"   , &BDTOutput_2l1tau);
  outTree->Branch("BDTOutput_1l2tau"   , &BDTOutput_1l2tau);
  outTree->Branch("BDTOutput_2l2tau"   , &BDTOutput_2l2tau);

  outTree->Branch("lep_truthOrigin_0"       , &ntup.lep_truthOrigin_0);
  outTree->Branch("lep_truthParentOrigin_0" , &ntup.lep_truthParentOrigin_0);
  outTree->Branch("lep_truthParentPdgId_0"  , &ntup.lep_truthParentPdgId_0);
  outTree->Branch("lep_truthParentType_0"   , &ntup.lep_truthParentType_0);
  //outTree->Branch("lep_truthType_0", &ntup.lep_truthType_0);
  outTree->Branch("lep_isPrompt_0"          , &ntup.lep_isPrompt_0);
  outTree->Branch("lep_isQMisID_0"          , &ntup.lep_isQMisID_0);
  outTree->Branch("lep_Mtrktrk_atConvV_CO_0", &ntup.lep_Mtrktrk_atConvV_CO_0);
  outTree->Branch("lep_Mtrktrk_atPV_CO_0"   , &ntup.lep_Mtrktrk_atPV_CO_0);
  outTree->Branch("lep_RadiusCO_0"          , &ntup.lep_RadiusCO_0);
  outTree->Branch("lep_RadiusCO_0"          , &ntup.lep_RadiusCO_0);

  outTree->Branch("lep_truthOrigin_1"       , &ntup.lep_truthOrigin_1);
  outTree->Branch("lep_truthParentOrigin_1" , &ntup.lep_truthParentOrigin_1);
  outTree->Branch("lep_truthParentPdgId_1"  , &ntup.lep_truthParentPdgId_1);
  outTree->Branch("lep_truthParentType_1"   , &ntup.lep_truthParentType_1);
  //outTree->Branch("lep_truthType_0", &ntup.lep_truthType_0);
  outTree->Branch("lep_isPrompt_1"          , &ntup.lep_isPrompt_1);
  outTree->Branch("lep_isQMisID_1"          , &ntup.lep_isQMisID_1);
  outTree->Branch("lep_Mtrktrk_atConvV_CO_1", &ntup.lep_Mtrktrk_atConvV_CO_1);
  outTree->Branch("lep_Mtrktrk_atPV_CO_1"   , &ntup.lep_Mtrktrk_atPV_CO_1);
  outTree->Branch("lep_RadiusCO_1"          , &ntup.lep_RadiusCO_1);
  outTree->Branch("lep_RadiusCO_1"          , &ntup.lep_RadiusCO_1);




  //BDT input variables + some kinematic vars.
  outTree->Branch("MAll"           , &ntup.MAll);
  outTree->Branch("MetAll"         , &ntup.MetAll);
  outTree->Branch("Mlep0tau0"      , &ntup.Mlep0tau0);
  outTree->Branch("Mlep0tau1"      , &ntup.Mlep0tau1);
  outTree->Branch("Mlep1tau0"      , &ntup.Mlep1tau0);
  outTree->Branch("MLep0Jet"       , &ntup.MLep0Jet);
  outTree->Branch("MLep1Jet"       , &ntup.MLep1Jet);
  outTree->Branch("MLep0MET"       , &ntup.MLep0MET);
  outTree->Branch("MLep1MET"       , &ntup.MLep1MET);
  outTree->Branch("Mtau0tau1"      , &ntup.Mtau0tau1);
  outTree->Branch("Mlep0Lj"        , &ntup.Mlep0Lj);
  outTree->Branch("Mlep1Lj"        , &ntup.Mlep1Lj);
  outTree->Branch("Mlep0SLj"       , &ntup.Mlep0SLj);
  outTree->Branch("Mlep01LjSLj"    , &ntup.Mlep01LjSLj);
  outTree->Branch("Mlep0tau0tau1"  , &ntup.Mlep0tau0tau1);
  outTree->Branch("Mlep1tau0tau1"  , &ntup.Mlep1tau0tau1);
  outTree->Branch("Mlep0lep1"      , &ntup.Mlep0lep1);
  outTree->Branch("Mlep0lep2"      , &ntup.Mlep0lep2);
  outTree->Branch("Mlep1lep2"      , &ntup.Mlep1lep2);
  outTree->Branch("Mlep012"        , &ntup.Mlep012);
  outTree->Branch("Mlep2LjSLj"     , &ntup.Mlep2LjSLj);
  outTree->Branch("Mlep012LjSLj"   , &ntup.Mlep012LjSLj);
  outTree->Branch("DRlep0Lj"       , &ntup.DRlep0Lj);
  outTree->Branch("DRlep0SLj"      , &ntup.DRlep0SLj);
  outTree->Branch("minDR_LJ_0"     , &ntup.minDR_LJ_0);
  outTree->Branch("minDR_LJ_1"     , &ntup.minDR_LJ_1);
  outTree->Branch("DRtau0tau1lep0" , &ntup.DRtau0tau1lep0);
  outTree->Branch("DRtau0tau1lep1" , &ntup.DRtau0tau1lep1);
  outTree->Branch("DRlep1tau0"     , &ntup.DRlep1tau0);
  outTree->Branch("DRlep0lep1"     , &ntup.DRlep0lep1);
  outTree->Branch("DRl0Lj"         , &ntup.DRl0Lj);
  outTree->Branch("DRlep1Lj"       , &ntup.DRlep1Lj);
  outTree->Branch("DRl0l1"         , &ntup.DRl0l1);
  outTree->Branch("DRlep1lep2"     , &ntup.DRlep1lep2);
  outTree->Branch("DRlep2CloseJ"   , &ntup.DRlep2CloseJ);
  outTree->Branch("DR_min_LepJet"  , &ntup.DR_min_LepJet); 
  outTree->Branch("minDRlep0Jet"   , &ntup.minDRlep0Jet);
  outTree->Branch("minDRLep1Jet"   , &ntup.minDRLep1Jet);
  outTree->Branch("farDRlep0Jet"   , &ntup.farDRlep0Jet);
  outTree->Branch("minDRLepTau0"   , &ntup.minDRLepTau0);
  outTree->Branch("SumPttau0tau1"  , &ntup.SumPttau0tau1); 
  outTree->Branch("SumPtLep0Jet"   , &ntup.SumPtLep0Jet);
  outTree->Branch("MaxEtalep01"    , &ntup.MaxEtalep01);
  outTree->Branch("DEtalep01"      , &ntup.DEtalep01);
  outTree->Branch("AbsDEtalep01"   , &ntup.AbsDEtalep01);
  outTree->Branch("lep_flavor"     , &ntup.lep_flavor); 
  outTree->Branch("DPhilep0Lj"     , &ntup.DPhilep0Lj);
  outTree->Branch("RMS"            , &ntup.RMS); 
  outTree->Branch("FlavorCat"      , &ntup.FlavorCat);
  outTree->Branch("lep_flavor"     , &ntup.lep_flavor);
  outTree->Branch("MCloserLepTau0" , &ntup.MCloserLepTau0);
  outTree->Branch("MCloserJetlep0" , &ntup.MCloserJetlep0);
  outTree->Branch("RSumPtlep01tau0Jets", &ntup.RSumPtlep01tau0Jets);
  outTree->Branch("MLep12_4l"      , &ntup.MLep12_4l);
  outTree->Branch("MLep34_4l"      , &ntup.MLep34_4l);
  outTree->Branch("M4_4l"          , &ntup.M4_4l);
  outTree->Branch("MLjSLj_4l"      , &ntup.MLjSLj_4l);
  outTree->Branch("PtLjSLj_4l"     , &ntup.PtLjSLj_4l);
  outTree->Branch("DPhiJetMET"     , &ntup.DPhiJetMET);
  outTree->Branch("LBoost2L_ThetaLjTau0"    , &ntup.LBoost2L_ThetaLjTau0);
  outTree->Branch("LBoost2L_ThetaSLjTau0"   , &ntup.LBoost2L_ThetaSLjTau0);
  outTree->Branch("LBoostLep0Tau0_DRlep0SLj", &ntup.LBoostLep0Tau0_DRlep0SLj);
  outTree->Branch("LBoostLep1Tau0_DRlep1Lj" , &ntup.LBoostLep1Tau0_DRlep1Lj);
  
  //GN1 branches
  outTree->Branch("MET"           , &ntup.met_met);
  outTree->Branch("lep_ID_0"      , &ntup.lep_ID_0);
  outTree->Branch("lep_Pt_0"      , &ntup.lep_Pt_0);
  outTree->Branch("lep_E_0"       , &ntup.lep_E_0);
  outTree->Branch("lep_Eta_0"     , &ntup.lep_Eta_0);
  outTree->Branch("lep_EtaBE2_0"  , &ntup.lep_EtaBE2_0);
  outTree->Branch("lep_ID_1"      , &ntup.lep_ID_1);
  outTree->Branch("lep_Pt_1"      , &ntup.lep_Pt_1);
  outTree->Branch("lep_E_1"       , &ntup.lep_E_1);
  outTree->Branch("lep_Eta_1"     , &ntup.lep_Eta_1);
  outTree->Branch("lep_EtaBE2_1"  , &ntup.lep_EtaBE2_1);
  outTree->Branch("lep_ID_2"      , &ntup.lep_ID_2);
  outTree->Branch("lep_Pt_2"      , &ntup.lep_Pt_2);
  outTree->Branch("lep_E_2"       , &ntup.lep_E_2);
  outTree->Branch("lep_Eta_2"     , &ntup.lep_Eta_2);
  outTree->Branch("lep_EtaBE2_2"  , &ntup.lep_EtaBE2_2);
  outTree->Branch("lep_ID_3"      , &ntup.lep_ID_3);
  outTree->Branch("lep_Pt_3"      , &ntup.lep_Pt_3);
  outTree->Branch("lep_E_3"       , &ntup.lep_E_3);
  outTree->Branch("lep_Eta_3"     , &ntup.lep_Eta_3);
  outTree->Branch("tau_pt_0"      , &ntup.tau_pt_0);
  outTree->Branch("tau_charge_0"  , &ntup.tau_charge_0);
  outTree->Branch("tau_numTrack_0", &ntup.tau_numTrack_0);
  outTree->Branch("tau_pt_1"      , &ntup.tau_pt_1);
  outTree->Branch("tau_charge_1"  , &ntup.tau_charge_1);
  outTree->Branch("tau_numTrack_1", &ntup.tau_numTrack_1);
  outTree->Branch("onelep_type"   , &ntup.onelep_type);
  outTree->Branch("dilep_type"    , &ntup.dilep_type);
  outTree->Branch("trilep_type"   , &ntup.trilep_type);
  outTree->Branch("quadlep_type"  , &ntup.quadlep_type);
  outTree->Branch("total_leptons" , &ntup.total_leptons);
  outTree->Branch("total_charge"  , &ntup.total_charge);
  outTree->Branch("Mll01"         , &ntup.Mll01);
  outTree->Branch("Ptll01"        , &ntup.Ptll01);
  outTree->Branch("DRll01"        , &ntup.DRll01);
  outTree->Branch("nJets_OR"      , &ntup.nJets_OR);
  outTree->Branch("nJets_OR_DL1r_77" , &ntup.nJets_OR_DL1r_77);
  outTree->Branch("nTaus_OR_Pt25_RNN", &ntup.nTaus_OR_Pt25_RNN);
  outTree->Branch("HT"            , &ntup.HT);
  outTree->Branch("HT_lep"        , &ntup.HT_lep);
  outTree->Branch("HT_jets"       , &ntup.HT_jets);
  outTree->Branch("lead_jetPt"    , &ntup.lead_jetPt);
  outTree->Branch("lead_jetE"     , &ntup.lead_jetE);
  outTree->Branch("sublead_jetPt" , &ntup.sublead_jetPt);
  //outTree->Branch("" , &);
  
  //Systematic branches. REMOVE SOME UNNECESSARY BRANCHES LATER
  outTree->Branch("tauSFRNNMedium_TAU_SF_NOMINAL", &ntup.tauSFRNNMedium_TAU_SF_NOMINAL); 
  outTree->Branch("tauSFRNNLoose_TAU_SF_NOMINAL", &ntup.tauSFRNNLoose_TAU_SF_NOMINAL); 
  outTree->Branch("tauSFRNNMedium_EFF_ELEOLR_TOTAL_UP", &ntup.tauSFRNNMedium_EFF_ELEOLR_TOTAL_UP);
  outTree->Branch("tauSFRNNLoose_EFF_ELEOLR_TOTAL_UP", &ntup.tauSFRNNLoose_EFF_ELEOLR_TOTAL_UP); 
  outTree->Branch("tauSFRNNMedium_EFF_ELEOLR_TOTAL_DOWN", &ntup.tauSFRNNMedium_EFF_ELEOLR_TOTAL_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_ELEOLR_TOTAL_DOWN", &ntup.tauSFRNNLoose_EFF_ELEOLR_TOTAL_DOWN);
  outTree->Branch("tauSFRNNMedium_ELE_EFF_ELEOLR_STAT_UP", &ntup.tauSFRNNMedium_ELE_EFF_ELEOLR_STAT_UP);
  outTree->Branch("tauSFRNNLoose_ELE_EFF_ELEOLR_STAT_UP", &ntup.tauSFRNNLoose_ELE_EFF_ELEOLR_STAT_UP);
  outTree->Branch("tauSFRNNMedium_ELE_EFF_ELEOLR_STAT_DOWN", &ntup.tauSFRNNMedium_ELE_EFF_ELEOLR_STAT_DOWN);
  outTree->Branch("tauSFRNNLoose_ELE_EFF_ELEOLR_STAT_DOWN", &ntup.tauSFRNNLoose_ELE_EFF_ELEOLR_STAT_DOWN);
  outTree->Branch("tauSFRNNMedium_ELE_EFF_ELEOLR_SYST_UP", &ntup.tauSFRNNMedium_ELE_EFF_ELEOLR_SYST_UP);
  outTree->Branch("tauSFRNNLoose_ELE_EFF_ELEOLR_SYST_UP", &ntup.tauSFRNNLoose_ELE_EFF_ELEOLR_SYST_UP);
  outTree->Branch("tauSFRNNMedium_ELE_EFF_ELEOLR_SYST_DOWN", &ntup.tauSFRNNMedium_ELE_EFF_ELEOLR_SYST_DOWN);
  outTree->Branch("tauSFRNNLoose_ELE_EFF_ELEOLR_SYST_DOWN", &ntup.tauSFRNNLoose_ELE_EFF_ELEOLR_SYST_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2025_UP", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2025_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2025_UP", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2025_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2025_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2025_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2025_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2025_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2530_UP", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2530_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2530_UP", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2530_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2530_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT2530_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2530_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT2530_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT3040_UP", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT3040_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT3040_UP", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT3040_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT3040_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPT3040_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT3040_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPT3040_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPTGE40_UP", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPTGE40_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPTGE40_UP", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPTGE40_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPTGE40_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_1PRONGSTATSYSTPTGE40_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPTGE40_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_1PRONGSTATSYSTPTGE40_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2025_UP", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2025_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2025_UP", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2025_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2025_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2025_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2025_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2025_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2530_UP", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2530_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2530_UP", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2530_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2530_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT2530_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2530_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT2530_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT3040_UP", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT3040_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT3040_UP", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT3040_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT3040_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPT3040_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT3040_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPT3040_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPTGE40_UP", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPTGE40_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPTGE40_UP", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPTGE40_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPTGE40_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_3PRONGSTATSYSTPTGE40_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPTGE40_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_3PRONGSTATSYSTPTGE40_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_HIGHPT_UP", &ntup.tauSFRNNMedium_EFF_RNNID_HIGHPT_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_HIGHPT_UP", &ntup.tauSFRNNLoose_EFF_RNNID_HIGHPT_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_HIGHPT_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_HIGHPT_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_HIGHPT_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_HIGHPT_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_SYST_UP", &ntup.tauSFRNNMedium_EFF_RNNID_SYST_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_SYST_UP", &ntup.tauSFRNNLoose_EFF_RNNID_SYST_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RNNID_SYST_DOWN", &ntup.tauSFRNNMedium_EFF_RNNID_SYST_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RNNID_SYST_DOWN", &ntup.tauSFRNNLoose_EFF_RNNID_SYST_DOWN);
  outTree->Branch("tauSFRNNMedium_EFF_RECO_TOTAL_UP", &ntup.tauSFRNNMedium_EFF_RECO_TOTAL_UP);
  outTree->Branch("tauSFRNNLoose_EFF_RECO_TOTAL_UP", &ntup.tauSFRNNLoose_EFF_RECO_TOTAL_UP);
  outTree->Branch("tauSFRNNMedium_EFF_RECO_TOTAL_DOWN", &ntup.tauSFRNNMedium_EFF_RECO_TOTAL_DOWN);
  outTree->Branch("tauSFRNNLoose_EFF_RECO_TOTAL_DOWN", &ntup.tauSFRNNLoose_EFF_RECO_TOTAL_DOWN);
  if(setNom) {
    outTree->Branch("weight_pileup_UP", &ntup.weight_pileup_UP);
    outTree->Branch("weight_pileup_DOWN", &ntup.weight_pileup_DOWN);
    outTree->Branch("jvtSF_customOR__1up", &ntup.jvtSF_customOR__1up);
    outTree->Branch("jvtSF_customOR__1down", &ntup.jvtSF_customOR__1down);
    outTree->Branch("lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_STAT_UP_AT", &ntup.lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_STAT_UP_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_TightLH_FCLoose_STAT_UP_AT", &ntup.lepSF_SF_El_ChargeMisID_TightLH_FCLoose_STAT_UP_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_STAT_DOWN_AT", &ntup.lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_STAT_DOWN_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_TightLH_FCLoose_STAT_DOWN_AT", &ntup.lepSF_SF_El_ChargeMisID_TightLH_FCLoose_STAT_DOWN_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_SYST_UP_AT", &ntup.lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_SYST_UP_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_TightLH_FCLoose_SYST_UP_AT", &ntup.lepSF_SF_El_ChargeMisID_TightLH_FCLoose_SYST_UP_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_SYST_DOWN_AT", &ntup.lepSF_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_SYST_DOWN_AT);
    outTree->Branch("lepSF_SF_El_ChargeMisID_TightLH_FCLoose_SYST_DOWN_AT", &ntup.lepSF_SF_El_ChargeMisID_TightLH_FCLoose_SYST_DOWN_AT);
    outTree->Branch("lepSF_SF_El_Reco_UP_AT", &ntup.lepSF_SF_El_Reco_UP_AT);
    outTree->Branch("lepSF_SF_El_Reco_DOWN_AT", &ntup.lepSF_SF_El_Reco_DOWN_AT);
    outTree->Branch("lepSF_SF_El_ID_LooseAndBLayerLH_UP_AT", &ntup.lepSF_SF_El_ID_LooseAndBLayerLH_UP_AT);
    outTree->Branch("lepSF_SF_El_ID_TightLH_UP_AT", &ntup.lepSF_SF_El_ID_TightLH_UP_AT);
    outTree->Branch("lepSF_SF_El_ID_LooseAndBLayerLH_DOWN_AT", &ntup.lepSF_SF_El_ID_LooseAndBLayerLH_DOWN_AT);
    outTree->Branch("lepSF_SF_El_ID_TightLH_DOWN_AT", &ntup.lepSF_SF_El_ID_TightLH_DOWN_AT);
    outTree->Branch("lepSF_SF_El_Iso_FCLoose_UP_AT", &ntup.lepSF_SF_El_Iso_FCLoose_UP_AT);
    outTree->Branch("lepSF_SF_El_Iso_FCLoose_DOWN_AT", &ntup.lepSF_SF_El_Iso_FCLoose_DOWN_AT);
    outTree->Branch("lepSF_SF_El_PLVLoose_UP_AT", &ntup.lepSF_SF_El_PLVLoose_UP_AT);
    outTree->Branch("lepSF_SF_El_PLVLoose_DOWN_AT", &ntup.lepSF_SF_El_PLVLoose_DOWN_AT);
    outTree->Branch("lepSF_SF_El_PLVTight_UP_AT", &ntup.lepSF_SF_El_PLVTight_UP_AT);
    outTree->Branch("lepSF_SF_El_PLVTight_DOWN_AT", &ntup.lepSF_SF_El_PLVTight_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_TTVA_STAT_UP_AT", &ntup.lepSF_SF_Mu_TTVA_STAT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_TTVA_STAT_DOWN_AT", &ntup.lepSF_SF_Mu_TTVA_STAT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_TTVA_SYST_UP_AT", &ntup.lepSF_SF_Mu_TTVA_SYST_UP_AT);
    outTree->Branch("lepSF_SF_Mu_TTVA_SYST_DOWN_AT", &ntup.lepSF_SF_Mu_TTVA_SYST_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_STAT_UP_AT", &ntup.lepSF_SF_Mu_ID_Loose_STAT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_STAT_UP_AT", &ntup.lepSF_SF_Mu_ID_Medium_STAT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_STAT_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Loose_STAT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_STAT_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Medium_STAT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_SYST_UP_AT", &ntup.lepSF_SF_Mu_ID_Loose_SYST_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_SYST_UP_AT", &ntup.lepSF_SF_Mu_ID_Medium_SYST_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_SYST_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Loose_SYST_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_SYST_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Medium_SYST_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_STAT_LOWPT_UP_AT", &ntup.lepSF_SF_Mu_ID_Loose_STAT_LOWPT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_STAT_LOWPT_UP_AT", &ntup.lepSF_SF_Mu_ID_Medium_STAT_LOWPT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_STAT_LOWPT_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Loose_STAT_LOWPT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_STAT_LOWPT_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Medium_STAT_LOWPT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_SYST_LOWPT_UP_AT", &ntup.lepSF_SF_Mu_ID_Loose_SYST_LOWPT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_SYST_LOWPT_UP_AT", &ntup.lepSF_SF_Mu_ID_Medium_SYST_LOWPT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Loose_SYST_LOWPT_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Loose_SYST_LOWPT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_ID_Medium_SYST_LOWPT_DOWN_AT", &ntup.lepSF_SF_Mu_ID_Medium_SYST_LOWPT_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_Iso_FCLoose_SYST_UP_AT", &ntup.lepSF_SF_Mu_Iso_FCLoose_SYST_UP_AT);
    outTree->Branch("lepSF_SF_Mu_Iso_FCLoose_SYST_DOWN_AT", &ntup.lepSF_SF_Mu_Iso_FCLoose_SYST_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_Iso_FCLoose_STAT_UP_AT", &ntup.lepSF_SF_Mu_Iso_FCLoose_STAT_UP_AT);
    outTree->Branch("lepSF_SF_Mu_Iso_FCLoose_STAT_DOWN_ATSF_Mu_PLVLoose_UP_AT", &ntup.lepSF_SF_Mu_Iso_FCLoose_STAT_DOWN_ATSF_Mu_PLVLoose_UP_AT);
    outTree->Branch("lepSF_SF_Mu_PLVLoose_DOWN_AT", &ntup.lepSF_SF_Mu_PLVLoose_DOWN_AT);
    outTree->Branch("lepSF_SF_Mu_PLVTight_UP_AT", &ntup.lepSF_SF_Mu_PLVTight_UP_AT);
    outTree->Branch("lepSF_SF_Mu_PLVTight_DOWN_AT", &ntup.lepSF_SF_Mu_PLVTight_DOWN_AT);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_0__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_0__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_0__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_0__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_1__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_1__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_1__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_1__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_2__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_2__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_2__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_2__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_3__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_3__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_3__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_3__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_4__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_4__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_4__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_4__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_5__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_5__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_5__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_5__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_6__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_6__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_6__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_6__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_7__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_7__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_7__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_7__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_8__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_8__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_8__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_B_8__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_0__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_0__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_0__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_0__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_1__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_1__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_1__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_1__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_2__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_2__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_2__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_2__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_3__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_3__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_3__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_C_3__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_0__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_0__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_0__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_0__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_1__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_1__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_1__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_1__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_2__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_2__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_2__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_2__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_3__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_3__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_3__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_Eigen_Light_3__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_extrapolation__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_extrapolation__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_extrapolation__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_extrapolation__1up);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_extrapolation_from_charm__1down", &ntup.bTagSF_weight_DL1r_77_FT_EFF_extrapolation_from_charm__1down);
    outTree->Branch("bTagSF_weight_DL1r_77_FT_EFF_extrapolation_from_charm__1up", &ntup.bTagSF_weight_DL1r_77_FT_EFF_extrapolation_from_charm__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigStatUncertainty__1up", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigStatUncertainty__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigStatUncertainty__1down", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigStatUncertainty__1down);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigSystUncertainty__1up", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigSystUncertainty__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigSystUncertainty__1down", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT_MUON_EFF_TrigSystUncertainty__1down);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_DLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_DLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_DLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_DLT_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigStatUncertainty__1up", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigStatUncertainty__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigStatUncertainty__1down", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigStatUncertainty__1down);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigSystUncertainty__1up", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigSystUncertainty__1up);
    outTree->Branch("custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigSystUncertainty__1down", &ntup.custTrigSF_TightElMediumMuID_FCLooseIso_DLT_MUON_EFF_TrigSystUncertainty__1down);
  }
}
