#include "HHMLSys/HHMLSys_MVA.h"

using namespace std;

//-----------------------------------------------------------------------------------
HHMLSys_MVA::HHMLSys_MVA(const std::string& name) :
  asg::AsgMessaging(name)
{
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::CheckXMLFile(const string& xmlFile) {

  StatusCode sc = StatusCode::SUCCESS;

  if(xmlFile == "") {
    ATH_MSG_FATAL("No weight xml file to read!");
    return StatusCode::FAILURE;
  }

  if(xmlFile != "" and xmlFile.find(".xml") != std::string::npos) {
    ATH_MSG_INFO("Reading weight xml file " << xmlFile);
  }
  else {
    ATH_MSG_FATAL("Unable to read weight xml file!!");
    return StatusCode::FAILURE;
  }

  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::CheckXMLFiles(const string& xmlEvenFile, const string& xmlOddFile) {

  StatusCode sc = StatusCode::SUCCESS;

  if(xmlEvenFile == "" or xmlOddFile == "") {
    ATH_MSG_FATAL("No even or odd weight xml file to read!");
    return StatusCode::FAILURE;
  }

  if(xmlEvenFile != "" and xmlEvenFile.find(".xml") != std::string::npos) {
    ATH_MSG_INFO("Reading even weight xml file ");
  }
  else {
    ATH_MSG_FATAL("Unable to read even weight xml file!!");
    return StatusCode::FAILURE;
  }

  if(xmlOddFile != "" and xmlOddFile.find(".xml") != std::string::npos) {
    ATH_MSG_INFO("Reading odd weight xml file ");
  }
  else {
    ATH_MSG_FATAL("Unable to read odd weight xml file!!");
    return StatusCode::FAILURE;
  }

  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_1l2tau(const string& xmlEvenFile, const string& xmlOddFile) {

  StatusCode sc = StatusCode::SUCCESS;

  sc = CheckXMLFiles(xmlEvenFile, xmlOddFile);

  if(sc.isFailure()) return StatusCode::FAILURE;

  TMVA::Tools::Instance();

  reader_1l2tau = new TMVA::Reader( "!Color:!Silent" );

  reader_1l2tau->AddVariable("Mtau0tau1"     , &BDTG_Mtau0tau1);
  reader_1l2tau->AddVariable("DRlep0Lj"      , &BDTG_DRlep0Lj);
  reader_1l2tau->AddVariable("DRlep0SLj"     , &BDTG_DRlep0SLj);
  reader_1l2tau->AddVariable("DRtau0tau1lep0", &BDTG_DRtau0tau1lep0);
  reader_1l2tau->AddVariable("SumPttau0tau1" , &BDTG_SumPttau0tau1);
  reader_1l2tau->AddVariable("Mlep0tau0tau1" , &BDTG_Mlep0tau0tau1);
  reader_1l2tau->AddVariable("MLep0Jet"      , &BDTG_MLep0Jet);
  reader_1l2tau->AddVariable("SumPtLep0Jet"  , &BDTG_SumPtLep0Jet);
  reader_1l2tau->AddVariable("MET"           , &BDTG_MET);
  reader_1l2tau->AddVariable("lead_jetPt"    , &BDTG_lead_jetPt);

  reader_1l2tau->BookMVA("BDTG method even", xmlEvenFile);
  reader_1l2tau->BookMVA("BDTG method odd" , xmlOddFile);

  return sc;
}

//---------------------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_2l2tau(const string& xmlEvenFile, const string& xmlOddFile) {

  StatusCode sc = StatusCode::SUCCESS;

  sc = CheckXMLFiles(xmlEvenFile, xmlOddFile);

  if(sc.isFailure()) return StatusCode::FAILURE;

  TMVA::Tools::Instance();

  reader_2l2tau = new TMVA::Reader( "!Color:!Silent" );

  reader_2l2tau->AddVariable("Mll01"         , &BDTG_Mll01);
  reader_2l2tau->AddVariable("lep_flavor"    , &BDTG_lep_flavor);
  reader_2l2tau->AddVariable("Mtau0tau1"     , &BDTG_Mtau0tau1);
  reader_2l2tau->AddVariable("Mlep1tau0"     , &BDTG_Mlep1tau0);
  reader_2l2tau->AddVariable("DRll01"        , &BDTG_DRll01);
  reader_2l2tau->AddVariable("DRlep1tau0"    , &BDTG_DRlep1tau0);
  reader_2l2tau->AddVariable("DRtau0tau1lep0", &BDTG_DRtau0tau1lep0);
  reader_2l2tau->AddVariable("SumPttau0tau1" , &BDTG_SumPttau0tau1);

  reader_2l2tau->BookMVA("BDTG method even", xmlEvenFile);
  reader_2l2tau->BookMVA("BDTG method odd" , xmlOddFile);

  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_2l1tau(const string& xmlFile) {

  StatusCode sc = StatusCode::SUCCESS;

  sc = CheckXMLFile(xmlFile);

  if(sc.isFailure()) return StatusCode::FAILURE;

  TMVA::Tools::Instance();

  reader_2l1tau = new TMVA::Reader( "!Color:!Silent" );

  reader_2l1tau->AddVariable("p_DR_l1_l2"              , &BDTG_DRlep0lep1); //
  reader_2l1tau->AddVariable("p_DR_l1_j1"              , &BDTG_DRl0Lj); //
  reader_2l1tau->AddVariable("p_invMass_l1_j1"         , &BDTG_Mlep0Lj); //
  reader_2l1tau->AddVariable("p_invMass_l1_j2"         , &BDTG_Mlep0SLj);
  reader_2l1tau->AddVariable("p_invMass_l2_j1"         , &BDTG_Mlep1Lj); //
  reader_2l1tau->AddVariable("p_invMCloserLepToTau"    , &BDTG_MCloserLepTau0);  //
  reader_2l1tau->AddVariable("p_drCloserJetToLeadLep"  , &BDTG_minDRlep0Jet); //
  reader_2l1tau->AddVariable("p_invMCloserJetToLeadLep", &BDTG_MCloserJetlep0);
  reader_2l1tau->AddVariable("p_drCloserJetToLep2"     , &BDTG_minDRLep1Jet); //
  reader_2l1tau->AddVariable("p_invMl2j1j2"            , &BDTG_Mlep01LjSLj);  //
  reader_2l1tau->AddVariable("p_LBoost2L_AngleTauJ1"   , &BDTG_LBoost2L_ThetaLjTau0);
  reader_2l1tau->AddVariable("p_LBoost2L_AngleTauJ2"   , &BDTG_LBoost2L_ThetaSLjTau0);
  reader_2l1tau->AddVariable("p_LBoostL1Tau_DRL1J2"    , &BDTG_LBoostLep0Tau0_DRlep0SLj);
  reader_2l1tau->AddVariable("p_LBoostL2Tau_DRL2J1"    , &BDTG_LBoostLep1Tau0_DRlep1Lj);

  reader_2l1tau->AddSpectator("eventNumber", &BDTG_EventNo);

  reader_2l1tau->BookMVA("BDTG", xmlFile);

  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_2l(const string& xmlFile, const string& xmlFile_VV, const string& xmlFile_tt, const string& xmlFile_Vjets) {

  StatusCode sc = StatusCode::SUCCESS;

  sc = (CheckXMLFile(xmlFile) and CheckXMLFile(xmlFile_VV) and CheckXMLFile(xmlFile_tt) and CheckXMLFile(xmlFile_Vjets));

  if(sc.isFailure()) return StatusCode::FAILURE;

  TMVA::Tools::Instance();

  reader_2l       = new TMVA::Reader( "!Color:!Silent" );
  reader_2l_VV    = new TMVA::Reader( "!Color:!Silent" );
  reader_2l_tt    = new TMVA::Reader( "!Color:!Silent" );
  reader_2l_Vjets = new TMVA::Reader( "!Color:!Silent" );
  
  reader_2l->AddVariable("BDTG_Diboson" , &BDTG_VV);
  reader_2l->AddVariable("BDTG_ttbar"   , &BDTG_tt);
  reader_2l->AddVariable("BDTG_Zjets"   , &BDTG_Vjets);
  //reader_2l->AddSpectator("Event_No", &BDTG_EventNo);

  //VV
  reader_2l_VV->AddVariable("dilep_type"              , &BDTG_dilep_type);
  reader_2l_VV->AddVariable("lep_Eta_0"               , &BDTG_lep_Eta_0);
  reader_2l_VV->AddVariable("lep_Eta_1"               , &BDTG_lep_Eta_1);
  reader_2l_VV->AddVariable("Mll01"                   , &BDTG_Mll01);
  reader_2l_VV->AddVariable("met_met"                 , &BDTG_MET);
  reader_2l_VV->AddVariable("minDeltaR_LJ_0"          , &BDTG_minDR_LJ_0);
  reader_2l_VV->AddVariable("minDeltaR_LJ_1"          , &BDTG_minDR_LJ_1);
  reader_2l_VV->AddVariable("Mlj_0"                   , &BDTG_MLep0Jet);
  reader_2l_VV->AddVariable("Mlj_1"                   , &BDTG_MLep1Jet);  
  reader_2l_VV->AddVariable("m_all"                   , &BDTG_MAll);
  reader_2l_VV->AddVariable("nJets_OR"                , &BDTG_nJets);
  reader_2l_VV->AddVariable("max_eta"                , &BDTG_MaxEtalep01);
  reader_2l_VV->AddVariable("DRll01"                  , &BDTG_DRll01);
  reader_2l_VV->AddVariable("HT"                      , &BDTG_HT);
  reader_2l_VV->AddVariable("HT_lep"                  , &BDTG_HT_lep);
  reader_2l_VV->AddVariable("DeltaR_min_lep_jet"      , &BDTG_DR_min_LepJet);
  reader_2l_VV->AddVariable("Mt_0"                    , &BDTG_MLep0MET);
  reader_2l_VV->AddVariable("Mt_1"                    , &BDTG_MLep1MET);
  reader_2l_VV->AddSpectator("Event_No", &BDTG_EventNo); 


  //ttbar
  reader_2l_tt->AddVariable("dilep_type"              , &BDTG_dilep_type);
  reader_2l_tt->AddVariable("lep_Eta_0"               , &BDTG_lep_Eta_0);
  reader_2l_tt->AddVariable("lep_Eta_1"               , &BDTG_lep_Eta_1);
  reader_2l_tt->AddVariable("Mll01"                   , &BDTG_Mll01);
  reader_2l_tt->AddVariable("minDeltaR_LJ_0"          , &BDTG_minDR_LJ_0);
  reader_2l_tt->AddVariable("minDeltaR_LJ_1"          , &BDTG_minDR_LJ_1);
  reader_2l_tt->AddVariable("Mlj_0"                   , &BDTG_MLep0Jet);
  reader_2l_tt->AddVariable("Mlj_1"                   , &BDTG_MLep1Jet);
  reader_2l_tt->AddVariable("max_eta"                 , &BDTG_MaxEtalep01);
  reader_2l_tt->AddVariable("DRll01"                  , &BDTG_DRll01);
  reader_2l_tt->AddVariable("HT"                      , &BDTG_HT);
  reader_2l_tt->AddVariable("DeltaR_min_lep_jet"   , &BDTG_DR_min_LepJet);
  reader_2l_tt->AddSpectator("Event_No", &BDTG_EventNo); 

  //V+jets
  reader_2l_Vjets->AddVariable("dilep_type"           , &BDTG_dilep_type);
  reader_2l_Vjets->AddVariable("Mll01"                , &BDTG_Mll01);
  reader_2l_Vjets->AddVariable("met_met"              , &BDTG_MET);
  reader_2l_Vjets->AddVariable("Ptll01"               , &BDTG_Ptll01);
  reader_2l_Vjets->AddVariable("mindR_l2j"            , &BDTG_minDR_LJ_1);
  reader_2l_Vjets->AddVariable("mindR_l1j"            , &BDTG_minDR_LJ_0);
  reader_2l_Vjets->AddVariable("nJets_OR"             , &BDTG_nJets);
  reader_2l_Vjets->AddVariable("max_eta"              , &BDTG_MaxEtalep01);
  reader_2l_Vjets->AddVariable("DeltaR_min_lep_jet"   , &BDTG_DR_min_LepJet);
  reader_2l_Vjets->AddSpectator("Event_No", &BDTG_EventNo); 

  reader_2l->BookMVA("BDTG_All", xmlFile);

  reader_2l_VV   ->BookMVA("BDTG_Diboson"   , xmlFile_VV); 
  reader_2l_tt   ->BookMVA("BDTG_ttbar"     , xmlFile_tt);
  reader_2l_Vjets->BookMVA("BDTG_Zjets"     , xmlFile_Vjets); 
 
  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_3l(const string& xmlFile) {

  StatusCode sc = StatusCode::SUCCESS;

  if(xmlFile == "") {
    ATH_MSG_FATAL("No weight xml file to read!");
    return StatusCode::FAILURE;
  }

  if(xmlFile != "" and xmlFile.find(".xml") != std::string::npos) {
    ATH_MSG_INFO("Reading weight xml file ");
  }
  else {
    ATH_MSG_FATAL("Unable to read weight xml file!!");
    return StatusCode::FAILURE;
  }

  if(sc.isFailure()) return StatusCode::FAILURE;

  TMVA::Tools::Instance();

  reader_3l = new TMVA::Reader( "!Color:!Silent" );

  reader_3l->AddVariable("FlavorCategory", &BDTG_FlavorCat);     
  reader_3l->AddVariable("nJets"    , &BDTG_nJets);                 
  reader_3l->AddVariable("dR_l1l2"  , &BDTG_DRl0l1);             
  reader_3l->AddVariable("dR_l2l3"  , &BDTG_DRlep1lep2);            
  reader_3l->AddVariable("dR_l3j"   , &BDTG_DRlep2CloseJ);          
  reader_3l->AddVariable("m_l1l2"   , &BDTG_Mlep0lep1);             
  reader_3l->AddVariable("m_l2l3"   , &BDTG_Mlep1lep2);             
  reader_3l->AddVariable("m_l1l3"   , &BDTG_Mlep0lep2);             
//  reader_3l->AddVariable("m_l3jj"   , &BDTG_Mlep2LjSLj);
  reader_3l->AddVariable("m_llljj"  , &BDTG_Mlep012LjSLj);          
  reader_3l->AddVariable("m_lll"    , &BDTG_Mlep012);               
  reader_3l->AddVariable("MET_ET"   , &BDTG_MET);                   
//  reader_3l->AddVariable("leadJetPt", &BDTG_leadJetPt);
//  reader_3l->AddVariable("leadJetE" , &BDTG_leadJetE);
//  reader_3l->AddVariable("lep_Pt_0" , &BDTG_lep_Pt_0);
//  reader_3l->AddVariable("lep_Pt_1" , &BDTG_lep_Pt_1);
//  reader_3l->AddVariable("lep_Pt_2" , &BDTG_lep_Pt_2);
//  reader_3l->AddVariable("lep_E_0"  , &BDTG_lep_E_0);
//  reader_3l->AddVariable("lep_E_1"  , &BDTG_lep_E_1);
//  reader_3l->AddVariable("lep_E_2"  , &BDTG_lep_E_2);
  reader_3l->AddVariable("HT"       , &BDTG_HT);
//  reader_3l->AddVariable("HT_lep"   , &BDTG_HT_lep);
  reader_3l->AddVariable("best_Z_Mll"  , &BDTG_best_Z_Mll);         
                                                                 
  reader_3l->AddSpectator("EvtNum", &BDTG_EventNo);              

  reader_3l->BookMVA("BDT_hh3l", xmlFile);

  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_4lbb(const string& xmlFile) {

  StatusCode sc = StatusCode::SUCCESS;

  if(xmlFile == "") {
    ATH_MSG_FATAL("No weight xml file to read!");
    return StatusCode::FAILURE;
  }

  if(xmlFile != "" and xmlFile.find(".xml") != std::string::npos) {
    ATH_MSG_INFO("Reading weight xml file ");
  }
  else {
    ATH_MSG_FATAL("Unable to read weight xml file!!");
    return StatusCode::FAILURE;
  }

  if(sc.isFailure()) return StatusCode::FAILURE;

  TMVA::Tools::Instance();

  reader_4lbb = new TMVA::Reader( "!Color:!Silent" );

  reader_4lbb->AddVariable("lep_Pt_0" , &BDTG_lep_Pt_0);
  reader_4lbb->AddVariable("lep_Pt_1" , &BDTG_lep_Pt_1);
  reader_4lbb->AddVariable("lep_Pt_2" , &BDTG_lep_Pt_2);
  reader_4lbb->AddVariable("lep_Pt_3" , &BDTG_lep_Pt_3);
  reader_4lbb->AddVariable("jet_Pt_0" , &BDTG_leadJetPt);
  reader_4lbb->AddVariable("jet_Pt_1" , &BDTG_sublead_JetPt);
  reader_4lbb->AddVariable("lep_topoEtcone20_0/lep_Pt_0", &BDTG_EtCone20Pt_0);
  reader_4lbb->AddVariable("lep_topoEtcone20_1/lep_Pt_1", &BDTG_EtCone20Pt_1);
  reader_4lbb->AddVariable("lep_topoEtcone20_2/lep_Pt_2", &BDTG_EtCone20Pt_2);
  reader_4lbb->AddVariable("lep_topoEtcone20_3/lep_Pt_3", &BDTG_EtCone20Pt_3);
  reader_4lbb->AddVariable("m_12"  , &BDTG_MLep12_4l);
  reader_4lbb->AddVariable("m_34"  , &BDTG_MLep34_4l);
  reader_4lbb->AddVariable("m_4l"  , &BDTG_M4_4l);
  reader_4lbb->AddVariable("m_jj"  , &BDTG_MLjSLj_4l);
  reader_4lbb->AddVariable("p_jj"  , &BDTG_PtLjSLj_4l);
  reader_4lbb->AddVariable("met_phi - jet_Phi_0"  , &BDTG_DPhiJetMET);
  reader_4lbb->AddVariable("njets" , &BDTG_nJets);
  reader_4lbb->AddVariable("nbjets", &BDTG_nJets_OR_DL1r_77);

  reader_4lbb->BookMVA("BDT_hh4lbb", xmlFile);

  return sc;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_1l2tau(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_Mtau0tau1      = ntup.Mtau0tau1;
  BDTG_DRlep0Lj       = ntup.DRlep0Lj;
  BDTG_DRlep0SLj      = ntup.DRlep0SLj;
  BDTG_DRtau0tau1lep0 = ntup.DRtau0tau1lep0;
  BDTG_SumPttau0tau1  = ntup.SumPttau0tau1;
  BDTG_Mlep0tau0tau1  = ntup.Mlep0tau0tau1;
  BDTG_MLep0Jet       = ntup.MLep0Jet;
  BDTG_SumPtLep0Jet   = ntup.SumPtLep0Jet;
  BDTG_MET            = ntup.met_met;
  BDTG_lead_jetPt     = ntup.lead_jetPt;

  if( ntup.eventNumber%2 == 1 ) {
    BDTG_weight = reader_1l2tau->EvaluateMVA("BDTG method even");
  }
  else if( ntup.eventNumber%2 == 0 ) {
    BDTG_weight = reader_1l2tau->EvaluateMVA("BDTG method odd");
  }

  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_2l2tau(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_Mll01          = ntup.Mll01;
  BDTG_lep_flavor     = float(ntup.lep_flavor);
  BDTG_Mtau0tau1      = ntup.Mtau0tau1;
  BDTG_Mlep1tau0      = ntup.Mlep1tau0;
  BDTG_DRll01         = ntup.DRll01;
  BDTG_DRlep1tau0     = ntup.DRlep1tau0;
  BDTG_DRtau0tau1lep0 = ntup.DRtau0tau1lep0;
  BDTG_SumPttau0tau1  = ntup.SumPttau0tau1;
  
if( ntup.eventNumber%2 == 1 ) {
    BDTG_weight = reader_2l2tau->EvaluateMVA("BDTG method even");
  }
  else if( ntup.eventNumber%2 == 0 ) {
    BDTG_weight = reader_2l2tau->EvaluateMVA("BDTG method odd");
  }
  
  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_2l1tau(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_EventNo        = ntup.eventNumber;
  BDTG_DRlep0lep1     = ntup.DRlep0lep1;
  BDTG_DRl0Lj         = ntup.DRl0Lj;
  BDTG_Mlep0Lj        = ntup.Mlep0Lj;
  BDTG_Mlep0SLj       = ntup.Mlep0SLj;
  BDTG_Mlep1Lj        = ntup.Mlep1Lj;
  BDTG_MCloserLepTau0 = ntup.MCloserLepTau0;
  BDTG_minDRlep0Jet   = ntup.minDRlep0Jet;
  BDTG_MCloserJetlep0 = ntup.MCloserJetlep0;
  BDTG_minDRLep1Jet   = ntup.minDRLep1Jet;
  BDTG_Mlep01LjSLj    = ntup.Mlep01LjSLj;
  BDTG_LBoost2L_ThetaLjTau0     = ntup.LBoost2L_ThetaLjTau0;
  BDTG_LBoost2L_ThetaSLjTau0    = ntup.LBoost2L_ThetaSLjTau0;
  BDTG_LBoostLep0Tau0_DRlep0SLj = ntup.LBoostLep0Tau0_DRlep0SLj;
  BDTG_LBoostLep1Tau0_DRlep1Lj  = ntup.LBoostLep1Tau0_DRlep1Lj;

  BDTG_weight = reader_2l1tau->EvaluateMVA("BDTG");

  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
void HHMLSys_MVA::EvaluateMVA_2l(const HHMLSys_Ntuple& ntup, float& BDTG_weight_2l, float& BDTG_weight_2l_VV, float& BDTG_weight_2l_tt, float& BDTG_weight_2l_Vjets )
{
  BDTG_EventNo          = ntup.eventNumber;
  BDTG_lep_Eta_0        = ntup.lep_Eta_0;
  BDTG_lep_Eta_1        = ntup.lep_Eta_1;
  BDTG_Mll01            = ntup.Mll01;
  BDTG_DRll01           = ntup.DRll01;
  BDTG_Ptll01           = ntup.Ptll01;
  BDTG_HT_lep           = ntup.HT_lep;
  BDTG_DR_min_LepJet    = ntup.DR_min_LepJet;
  BDTG_HT               = ntup.HT;
  BDTG_dilep_type       = float(ntup.dilep_type);
  BDTG_MET              = ntup.met_met;
  BDTG_nJets            = float(ntup.nJets_OR);
  BDTG_total_charge     = float(ntup.total_charge);
  BDTG_DEtalep01        = float(ntup.DEtalep01);
  BDTG_AbsDEtalep01     = ntup.AbsDEtalep01;
  BDTG_MLep0Jet         = ntup.MLep0Jet;
  BDTG_MLep1Jet         = ntup.MLep1Jet;
  BDTG_MLep0MET         = ntup.MLep0MET;
  BDTG_MLep1MET         = ntup.MLep1MET;
  BDTG_MAll             = ntup.MAll;
  BDTG_MetAll           = ntup.MetAll;
  BDTG_minDR_LJ_0       = ntup.minDR_LJ_0;
  BDTG_minDR_LJ_1       = ntup.minDR_LJ_1;
  BDTG_MaxEtalep01      = ntup.MaxEtalep01;
  BDTG_RMS              = ntup.RMS;
  
  BDTG_weight_2l_VV    = reader_2l_VV->EvaluateMVA("BDTG_Diboson");
  BDTG_weight_2l_tt    = reader_2l_tt->EvaluateMVA("BDTG_ttbar");
  BDTG_weight_2l_Vjets = reader_2l_Vjets->EvaluateMVA("BDTG_Zjets");

  BDTG_tt    = BDTG_weight_2l_tt;
  BDTG_VV    = BDTG_weight_2l_VV;
  BDTG_Vjets = BDTG_weight_2l_Vjets;

  BDTG_weight_2l = reader_2l->EvaluateMVA("BDTG_All");
/* 
cout << " BDTG_tt " << BDTG_tt << endl; 
cout << " BDTG_VV " << BDTG_VV << endl; 
cout << " BDTG_Vjets " << BDTG_Vjets << endl;
cout << " BDTG_2l " << BDTG_weight_2l << endl; 
*/
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_3l(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_EventNo      = static_cast<float>(ntup.eventNumber);
  BDTG_FlavorCat    = float(ntup.FlavorCat);
  BDTG_nJets        = float(ntup.nJets_OR);
  BDTG_Mlep0lep1    = ntup.Mlep0lep1;
  BDTG_Mlep0lep2    = ntup.Mlep0lep2;
  BDTG_Mlep1lep2    = ntup.Mlep1lep2;
  BDTG_Mlep012      = ntup.Mlep012;
  BDTG_Mlep2LjSLj   = ntup.Mlep2LjSLj;
  BDTG_Mlep012LjSLj = ntup.Mlep012LjSLj;
  BDTG_DRl0l1       = ntup.DRl0l1;
  BDTG_DRlep1lep2   = ntup.DRlep1lep2;
  BDTG_DRlep2CloseJ = ntup.DRlep2CloseJ;
  BDTG_leadJetPt    = ntup.lead_jetPt/1000.;
  BDTG_leadJetE     = ntup.lead_jetE/1000.;
  BDTG_lep_Pt_0     = ntup.lep_Pt_0/1000.;
  BDTG_lep_Pt_1     = ntup.lep_Pt_1/1000.;
  BDTG_lep_Pt_2     = ntup.lep_Pt_2/1000.;
  BDTG_lep_E_0      = ntup.lep_E_0/1000.;
  BDTG_lep_E_1      = ntup.lep_E_1/1000.;
  BDTG_lep_E_2      = ntup.lep_E_2/1000.;
  BDTG_best_Z_Mll   = ntup.best_Z_Mll/1000.;
  BDTG_MET          = ntup.met_met/1000.;
  BDTG_HT           = ntup.HT/1000.;
  BDTG_HT_lep       = ntup.HT_lep/1000.;


  BDTG_weight = reader_3l->EvaluateMVA("BDT_hh3l");
  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_4lbb(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_lep_Pt_0      = ntup.lep_Pt_0;
  BDTG_lep_Pt_1      = ntup.lep_Pt_1;
  BDTG_lep_Pt_2      = ntup.lep_Pt_2;
  BDTG_lep_Pt_3      = ntup.lep_Pt_3;
  BDTG_leadJetPt     = ntup.lead_jetPt;
  BDTG_sublead_JetPt = ntup.sublead_jetPt;
  BDTG_EtCone20Pt_0  = 1/ntup.lep_Pt_0; //
  BDTG_EtCone20Pt_1  = 1/ntup.lep_Pt_1; //
  BDTG_EtCone20Pt_2  = 1/ntup.lep_Pt_2; //
  BDTG_EtCone20Pt_3  = 1/ntup.lep_Pt_3; //
  BDTG_MLep12_4l     = ntup.MLep12_4l;
  BDTG_MLep34_4l     = ntup.MLep34_4l;
  BDTG_M4_4l         = ntup.M4_4l;
  BDTG_MLjSLj_4l     = ntup.MLjSLj_4l;
  BDTG_PtLjSLj_4l    = ntup.PtLjSLj_4l;
  BDTG_DPhiJetMET    = ntup.DPhiJetMET;
  BDTG_nJets         = float(ntup.nJets_OR);
  BDTG_nJets_OR_DL1r_77 = float(ntup.nJets_OR_DL1r_77);

  BDTG_weight = reader_4lbb->EvaluateMVA("BDT_hh4lbb");

  return BDTG_weight;
}
