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
