#include "HHMLSys/HHMLSys_MVA.h"

using namespace std;

//-----------------------------------------------------------------------------------
HHMLSys_MVA::HHMLSys_MVA(const std::string& name) :
  asg::AsgMessaging(name)
{
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
  reader_1l2tau->AddVariable("minDR_LJ_0"    , &BDTG_minDR_LJ_0); 
  reader_1l2tau->AddVariable("DRtau0tau1lep0", &BDTG_DRtau0tau1lep0); 
  reader_1l2tau->AddVariable("SumPttau0tau1" , &BDTG_SumPttau0tau1); 
  reader_1l2tau->AddVariable("Mlep0tau0"     , &BDTG_Mlep0tau0); 
  reader_1l2tau->AddVariable("Mlep0tau1"     , &BDTG_Mlep0tau1); 
  reader_1l2tau->AddVariable("MLep0Jet"      , &BDTG_MLep0Jet); 
  reader_1l2tau->AddVariable("HT"            , &BDTG_HT);  
  
  reader_1l2tau->BookMVA("BDTG method even", xmlEvenFile);
  reader_1l2tau->BookMVA("BDTG method odd" , xmlOddFile);
  
  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_2l2tau(const string& xmlEvenFile, const string& xmlOddFile) {

  StatusCode sc = StatusCode::SUCCESS;

  sc = CheckXMLFiles(xmlEvenFile, xmlOddFile);

  if(sc.isFailure()) return StatusCode::FAILURE;
  
  TMVA::Tools::Instance();
  
  reader_2l2tau = new TMVA::Reader( "!Color:!Silent" );
  
  reader_2l2tau->AddVariable("DRtau0tau1lep1" , &BDTG_DRtau0tau1lep1);
  reader_2l2tau->AddVariable("Mtau0tau1"      , &BDTG_Mtau0tau1);
  reader_2l2tau->AddVariable("MaxEtalep01"    , &BDTG_MaxEtalep01);
  reader_2l2tau->AddVariable("DEtalep01"      , &BDTG_DEtalep01);
  reader_2l2tau->AddVariable("lep_flavor"     , &BDTG_lep_flavor);
  reader_2l2tau->AddVariable("Mlep1tau0tau1"  , &BDTG_Mlep1tau0tau1);
  reader_2l2tau->AddVariable("MET"            , &BDTG_MET);
  reader_2l2tau->AddVariable("tau_pt_0"       , &BDTG_tau_pt_0);
  reader_2l2tau->AddVariable("tau_pt_1"       , &BDTG_tau_pt_1);
  reader_2l2tau->AddVariable("Mll01"          , &BDTG_Mll01);
  reader_2l2tau->AddVariable("DRll01"         , &BDTG_DRll01);
  reader_2l2tau->AddVariable("HT"             , &BDTG_HT);
  
  reader_2l2tau->BookMVA("BDTG method even", xmlEvenFile);
  reader_2l2tau->BookMVA("BDTG method odd" , xmlOddFile);
  
  return sc;
}

//-----------------------------------------------------------------------------------
StatusCode HHMLSys_MVA::BookMVA_2l1tau(const string& xmlFile) {

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
  
  reader_2l1tau = new TMVA::Reader( "!Color:!Silent" );
  
  reader_2l1tau->AddVariable("tau_pt_0"              , &BDTG_tau_pt_0); 
  reader_2l1tau->AddVariable("p_DR_l1_l2"            , &BDTG_DRlep0lep1); 
  reader_2l1tau->AddVariable("p_Dphi_l1_j1"          , &BDTG_DPhilep0Lj); 
  reader_2l1tau->AddVariable("p_DR_l1_j1"            , &BDTG_DRl0Lj); 
  reader_2l1tau->AddVariable("p_DR_l2_j1"            , &BDTG_DRlep1Lj); 
  reader_2l1tau->AddVariable("p_invMass_l1_j1"       , &BDTG_Mlep0Lj); 
  reader_2l1tau->AddVariable("p_invMass_l2_j1"       , &BDTG_Mlep1Lj); 
  reader_2l1tau->AddVariable("p_drCloserLepToTau"    , &BDTG_minDRLepTau0); 
  reader_2l1tau->AddVariable("p_invMCloserLepToTau"  , &BDTG_MCloserLepTau0); 
  reader_2l1tau->AddVariable("p_drCloserJetToLeadLep", &BDTG_minDRlep0Jet);
  reader_2l1tau->AddVariable("p_drFarestJetToLeadLep", &BDTG_farDRlep0Jet);  
  reader_2l1tau->AddVariable("p_sumPtleptauAll_Ptjet", &BDTG_RSumPtlep01tau0Jets);  
  reader_2l1tau->AddVariable("p_invMl2j1j2"          , &BDTG_Mlep01LjSLj);  

  int EventNo2;
  reader_2l1tau->AddSpectator("p_Event_No2", &EventNo2);

  reader_2l1tau->BookMVA("BDTG", xmlFile);
  
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
  reader_3l->AddVariable("dR_l1l2"  , &BDTG_DRlep0lep1);
  reader_3l->AddVariable("dR_l2l3"  , &BDTG_DRlep1lep2);
  reader_3l->AddVariable("dR_l3j"   , &BDTG_DRlep2CloseJ);
  reader_3l->AddVariable("m_l1l2"   , &BDTG_Mlep0lep1);
  reader_3l->AddVariable("m_l2l3"   , &BDTG_Mlep1lep2);
  reader_3l->AddVariable("m_l1l3"   , &BDTG_Mlep0lep2);
  reader_3l->AddVariable("m_l3jj"   , &BDTG_Mlep2LjSLj);
  reader_3l->AddVariable("m_llljj"  , &BDTG_Mlep012LjSLj);
  reader_3l->AddVariable("m_lll"    , &BDTG_Mlep012);
  reader_3l->AddVariable("MET_ET"   , &BDTG_MET);
  reader_3l->AddVariable("leadJetPt", &BDTG_leadJetPt);
  reader_3l->AddVariable("leadJetE" , &BDTG_leadJetE);
  reader_3l->AddVariable("lep_Pt_0" , &BDTG_lep_Pt_0);
  reader_3l->AddVariable("lep_Pt_1" , &BDTG_lep_Pt_1);
  reader_3l->AddVariable("lep_Pt_2" , &BDTG_lep_Pt_1);
  reader_3l->AddVariable("lep_E_0"  , &BDTG_lep_E_0);
  reader_3l->AddVariable("lep_E_1"  , &BDTG_lep_E_1);
  reader_3l->AddVariable("lep_E_2"  , &BDTG_lep_E_2);
  reader_3l->AddVariable("HT"       , &BDTG_HT);
  reader_3l->AddVariable("HT_lep"   , &BDTG_HT_lep);
  reader_3l->AddVariable("best_Z_Mll" , &BDTG_Best_Z_Mll);

  int EventNo;
  reader_3l->AddSpectator("EventNum", &EventNo);

  reader_3l->BookMVA("BDTG", xmlFile);
  
  return sc;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_1l2tau(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;
 
  BDTG_Mtau0tau1      = ntup.Mtau0tau1;
  BDTG_DRlep0Lj       = ntup.DRlep0Lj;
  BDTG_DRlep0SLj      = ntup.DRlep0SLj;
  BDTG_minDR_LJ_0     = ntup.minDR_LJ_0;
  BDTG_DRtau0tau1lep0 = ntup.DRtau0tau1lep0;
  BDTG_SumPttau0tau1  = ntup.SumPttau0tau1;
  BDTG_Mlep0tau0      = ntup.Mlep0tau0;
  BDTG_Mlep0tau1      = ntup.Mlep0tau1;
  BDTG_MLep0Jet       = ntup.MLep0Jet;
  BDTG_HT             = ntup.HT;
  
  /*cout << "EvntNo: " << ntup.eventNumber << endl;
    cout << "var1: "  << BDTG_Mtau0tau1      << endl;
    cout << "var2: "  << BDTG_DRlep0Lj       << endl;
    cout << "var3: "  << BDTG_DRlep0SLj      << endl;
    cout << "var4: "  << BDTG_minDR_LJ_0     << endl;
    cout << "var5: "  << BDTG_DRtau0tau1lep0 << endl;
    cout << "var6: "  << BDTG_SumPttau0tau1  << endl;
    cout << "var7: "  << BDTG_Mlep0tau0      << endl;
    cout << "var8: "  << BDTG_Mlep0tau1      << endl;
    cout << "var9: "  << BDTG_MLep0Jet       << endl;*/

  if( ntup.eventNumber%2 == 1 ) {
    BDTG_weight = reader_1l2tau->EvaluateMVA("BDTG method even");
  }
  else {
    BDTG_weight = reader_1l2tau->EvaluateMVA("BDTG method odd");
  }

  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_2l2tau(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_DRtau0tau1lep1 = ntup.DRtau0tau1lep1;
  BDTG_Mtau0tau1      = ntup.Mtau0tau1;
  BDTG_MaxEtalep01    = ntup.MaxEtalep01;
  BDTG_DEtalep01      = ntup.DEtalep01;
  BDTG_lep_flavor     = ntup.lep_flavor;
  BDTG_Mlep1tau0tau1  = ntup.Mlep1tau0tau1;
  BDTG_MET            = ntup.met_met;
  BDTG_tau_pt_0       = ntup.tau_pt_0;
  BDTG_tau_pt_1       = ntup.tau_pt_1;
  BDTG_Mll01          = ntup.Mll01;
  BDTG_DRll01         = ntup.DRll01;
  BDTG_HT             = ntup.HT;

  if( ntup.eventNumber%2 == 1 ) {
    BDTG_weight = reader_2l2tau->EvaluateMVA("BDTG method even");
  }
  else {
    BDTG_weight = reader_2l2tau->EvaluateMVA("BDTG method odd");
  }
  
  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_2l1tau(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_tau_pt_0       = ntup.tau_pt_0;
  BDTG_DRlep0lep1     = ntup.DRlep0lep1;
  BDTG_DRl0Lj         = ntup.DRl0Lj;
  BDTG_DRlep1Lj       = ntup.DRlep1Lj;
  BDTG_DPhilep0Lj     = ntup.DPhilep0Lj;
  BDTG_Mlep0Lj        = ntup.Mlep0Lj; 
  BDTG_Mlep1Lj        = ntup.Mlep1Lj;
  BDTG_Mlep01LjSLj    = ntup.Mlep01LjSLj;
  BDTG_minDRlep0Jet   = ntup.minDRlep0Jet;
  BDTG_farDRlep0Jet   = ntup.farDRlep0Jet;
  BDTG_minDRLepTau0   = ntup.minDRLepTau0;
  BDTG_MCloserLepTau0 = ntup.MCloserLepTau0;
  BDTG_RSumPtlep01tau0Jets = ntup.RSumPtlep01tau0Jets;

  BDTG_weight = reader_2l1tau->EvaluateMVA("BDTG");
  
  return BDTG_weight;
}

//-----------------------------------------------------------------------------------
float HHMLSys_MVA::EvaluateMVA_3l(const HHMLSys_Ntuple& ntup) {

  float BDTG_weight = -99;

  BDTG_FlavorCat    = ntup.FlavorCat;
  BDTG_Mlep0lep1    = ntup.Mlep0lep1;
  BDTG_Mlep0lep2    = ntup.Mlep0lep2;
  BDTG_Mlep1lep2    = ntup.Mlep1lep2;
  BDTG_Mlep012      = ntup.Mlep012;
  BDTG_Mlep2LjSLj   = ntup.Mlep2LjSLj;
  BDTG_Mlep012LjSLj = ntup.Mlep012LjSLj;
  BDTG_DRl0l1       = ntup.DRl0l1;
  BDTG_DRlep1lep2   = ntup.DRlep1lep2;
  BDTG_DRlep2CloseJ = ntup.DRlep2CloseJ;
  BDTG_nJets        = ntup.nJets_OR;
  BDTG_leadJetPt    = ntup.lead_jetPt/1000.;
  BDTG_leadJetE     = ntup.lead_jetE/1000.;
  BDTG_lep_Pt_0     = ntup.lep_Pt_0;
  BDTG_lep_Pt_1     = ntup.lep_Pt_1;
  BDTG_lep_Pt_2     = ntup.lep_Pt_2;
  BDTG_lep_E_0      = ntup.lep_E_0;
  BDTG_lep_E_1      = ntup.lep_E_0;
  BDTG_lep_E_2      = ntup.lep_E_0;
  BDTG_HT           = ntup.HT/1000;
  BDTG_HT_lep       = ntup.HT_lep/1000.;
  BDTG_Best_Z_Mll   = ntup.best_Z_Mll/1000.;

  BDTG_weight = reader_3l->EvaluateMVA("BDTG");
  
  return BDTG_weight;
}
