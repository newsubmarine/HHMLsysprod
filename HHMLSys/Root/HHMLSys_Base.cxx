#include "HHMLSys/HHMLSys_Base.h"

//---------------------------------------------------------------------
HHMLSys_Base::HHMLSys_Base(const std::string& name) :
  asg::AsgMessaging(name)
{
}

//---------------------------------------------------------------------
HHMLSys_Base::~HHMLSys_Base() {
}

//---------------------------------------------------------------------
StatusCode HHMLSys_Base::initialize(const TString& configFile, const std::string& samplePath, const TString& outDir, const TString& mcRun) {

  StatusCode sc = StatusCode::SUCCESS;
  
  //
  //Read the config file
  //
  TEnv rEnv;
  int success = -1;
  success = rEnv.ReadFile(configFile.Data(), kEnvAll);
  
  if( success != 0 ) {
    ATH_MSG_FATAL("Unable to read config file " << configFile); 
    return StatusCode::FAILURE;
  }
  else {
    ATH_MSG_INFO("Reading config file " << configFile);
  }

  Config(m_isData, "isData", rEnv);

  //2l
  Config(m_do_2lSR  , "do_2lSR" , rEnv);
  Config(m_do_2lMVA , "do_2lMVA", rEnv);

  Config(m_2l_BDTGEvenxmlFile, "2l_BDTGEvenxmlFile", rEnv);
  Config(m_2l_BDTGOddxmlFile , "2l_BDTGOddxmlFile" , rEnv);

  //3l
  Config(m_do_3lSR  , "do_3lSR" , rEnv);
  Config(m_do_3lMVA , "do_3lMVA", rEnv);

  Config(m_3l_BDTGEvenxmlFile, "3l_BDTGEvenxmlFile", rEnv);
  Config(m_3l_BDTGOddxmlFile , "3l_BDTGOddxmlFile" , rEnv);

  //4l
  Config(m_do_4lSR  , "do_4lSR" , rEnv);
  Config(m_do_4lMVA , "do_4lMVA", rEnv);

  Config(m_4l_BDTGEvenxmlFile, "4l_BDTGEvenxmlFile", rEnv);
  Config(m_4l_BDTGOddxmlFile , "4l_BDTGOddxmlFile" , rEnv);
  
  //4lbb
  Config(m_do_4lbbSR  , "do_4lbbSR" , rEnv);
  Config(m_do_4lbbMVA , "do_4lbbMVA", rEnv);

  Config(m_4lbb_BDTGEvenxmlFile, "4lbb_BDTGEvenxmlFile", rEnv);
  Config(m_4lbb_BDTGOddxmlFile , "4lbb_BDTGOddxmlFile" , rEnv);

  //2l+1tau
  Config(m_do_2l1tauSR,  "do_2l1tauSR" , rEnv);
  Config(m_do_2l1tauMVA, "do_2l1tauMVA", rEnv);

  Config(m_2l1tau_BDTGEvenxmlFile, "2l1tau_BDTGEvenxmlFile", rEnv);
  Config(m_2l1tau_BDTGOddxmlFile , "2l1tau_BDTGOddxmlFile" , rEnv);

  //1l+2tau
  Config(m_do_1l2tauSR  , "do_1l2tauSR" , rEnv);
  Config(m_do_1l2tauMVA , "do_1l2tauMVA", rEnv);

  Config(m_1l2tau_BDTGEvenxmlFile, "1l2tau_BDTGEvenxmlFile", rEnv);
  Config(m_1l2tau_BDTGOddxmlFile , "1l2tau_BDTGOddxmlFile" , rEnv);

  //2l+2tau
  Config(m_do_2l2tauSR,  "do_2l2tauSR" , rEnv);
  Config(m_do_2l2tauMVA, "do_2l2tauMVA", rEnv);

  Config(m_2l2tau_BDTGEvenxmlFile, "2l2tau_BDTGEvenxmlFile", rEnv);
  Config(m_2l2tau_BDTGOddxmlFile , "2l2tau_BDTGOddxmlFile" , rEnv);
  
  //Control regions
  Config(m_do_1l2tauCR, "do_1l2tauCR", rEnv);
  Config(m_do_2l2tauCR, "do_2l2tauCR", rEnv);
  
  //
  //Read the input root file
  //
  if(samplePath != "" && samplePath.find(".root") != std::string::npos) {
    ATH_MSG_INFO("Reading root file " << samplePath);
    m_samplePath = samplePath;
  }
  else {
    ATH_MSG_FATAL("Unable to read input root file!!");
    return StatusCode::FAILURE;
  }

  //
  //Get sumWeights TTree entries
  //
  if(!m_isData) SumWeights(samplePath);
  
  //
  //Fill vector with TTree names
  //
  m_treeVec = std::make_unique<std::vector<std::string>>();

  if(!m_isData) {
    TFile* rootFile = TFile::Open(samplePath.c_str(), "READ");
    TIter nextkey( rootFile->GetListOfKeys() );
    TKey *key;
    while( (key = (TKey*)nextkey()) ) {
      TObject *obj = key->ReadObj();
      if( obj->IsA()->InheritsFrom( TTree::Class())) {
	TTree* tree_data = (TTree*)obj;
	m_treeVec->push_back(tree_data->GetName());
      }
    }
    rootFile->Close();
    delete rootFile;
  }
  else {
    m_treeVec->push_back("nominal");
  }

  //
  // MVA Classification or Evaluation
  //

  //Book MVA's
  if(m_do_1l2tauMVA) sc = mva.BookMVA_1l2tau(m_1l2tau_BDTGEvenxmlFile, m_1l2tau_BDTGOddxmlFile);
  if(m_do_2l2tauMVA) sc = mva.BookMVA_2l2tau(m_2l2tau_BDTGEvenxmlFile, m_2l2tau_BDTGOddxmlFile);

  //
  //Create the output root file
  //

  //Check the mc campaign. For data the Run Number is used.
  if(!m_isData) {
    
    if(mcRun != "" and mcRun.BeginsWith("mc")) {
      ATH_MSG_INFO("Running " << mcRun << " campaign");
      
      //Flag to initialize some branches only for mc16a campaign
      m_setmc16a = mcRun.Contains("mc16a");
    }
    else {
      ATH_MSG_FATAL("Missing MC campaign. see help!  runHHMLAna --help");
      return StatusCode::FAILURE;
    }
  }
  
  TString sampleName = SetOutputName(samplePath);

  if(m_isData) {
    
    if(outDir != "") m_outputFile = TFile::Open(outDir + "/" + "out_" + sampleName + ".root", "RECREATE");
    else             m_outputFile = TFile::Open("out_" + sampleName + ".root", "RECREATE");
  }
  else {
    
    TString mc_chan = TString::Itoa(m_dsid, 10);

    if(outDir != "") m_outputFile = TFile::Open(outDir + "/" + "out_" + mcRun + "_" + mc_chan + "_" + sampleName + ".root", "RECREATE");
    else             m_outputFile = TFile::Open("out_" + mcRun + "_" + mc_chan + "_" + sampleName + ".root", "RECREATE");
  }

  return sc;
}

//-----------------------------------------------------------------------
StatusCode HHMLSys_Base::finalize()
{
  StatusCode sc = StatusCode::SUCCESS;

  m_outputFile->Write(0, TObject::kWriteDelete);
  m_outputFile->Close();

  return sc;
}

//--------------------------------------------------------------
std::string HHMLSys_Base::SetOutputName(const std::string& InputSamplePath) {

  unsigned first_delim = InputSamplePath.find_last_of("/");
  unsigned last_delim  = InputSamplePath.find(".root");
  
  std::string sample_name = InputSamplePath.substr(first_delim + 1, (last_delim - 1) - first_delim);

  return sample_name;
}

//--------------------------------------------------------------
void HHMLSys_Base::SumWeights(const std::string &SamplePath) {

  float sum_weight(0.0), tot_evt(0.0);

  ntup.ReadSumWeight(SamplePath);

  for(unsigned int il = 0; il < ntup.fChainSumWeight->GetEntries(); il++)
    {
      ntup.fChainSumWeight->GetEntry(il);

      sum_weight += ntup.totalEventsWeighted;
      tot_evt    += ntup.totalEvents;
      m_dsid = ntup.dsid;
    }

  //std::cout << "Sum Weight: " << sum_weight << std::endl;

  m_scale = sum_weight;
}
