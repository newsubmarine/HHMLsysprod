#include "HHMLSys/HHMLSys_EventSaver.h"

using namespace std;

//-----------------------------------------------------------------------------
HHMLSys_EventSaver::HHMLSys_EventSaver(const string& name) :
  HHMLSys_Base(name)
{
}

//-----------------------------------------------------------------------------
HHMLSys_EventSaver::~HHMLSys_EventSaver() {
}

//-----------------------------------------------------------------------------
StatusCode HHMLSys_EventSaver::initialize(const TString& configFile, const string& samplePath, const TString& outDir, TString& sampleName, const TString& mcRun) {

  StatusCode sc = StatusCode::SUCCESS;
  
  //Initialize Base class
  sc = HHMLSys_Base::initialize(configFile, samplePath, outDir, sampleName, mcRun);
  
  if(!sc) {
    ATH_MSG_FATAL("HHMLSys_Base initialized failed!");
    return sc;
  }

  if(sc.isFailure()) return StatusCode::FAILURE;

  return sc;
}

//-----------------------------------------------------------------------------
StatusCode HHMLSys_EventSaver::finalize() {

  //Finalize Base class
  StatusCode sc = HHMLSys_Base::finalize();

  if(!sc){
    ATH_MSG_FATAL("HHMLSys_Base finalized failed!");
    return sc;
  }

  return sc;
}

//-----------------------------------------------------------------------------
StatusCode HHMLSys_EventSaver::executeEventLoop(unsigned int max_evnt) {

  StatusCode sc = StatusCode::SUCCESS;

  ATH_MSG_INFO("Execute Event Loop ...");

  vector<string>::iterator itr = m_treeVec->begin();

  bool setNominal;

  //Loop over all TTree's.
  for(itr = m_treeVec->begin(); itr != m_treeVec->end(); ++itr) {
    
    if(*itr == "AnalysisTracking" or *itr == "particleLevel" or *itr == "truth" or *itr == "sumWeights") continue;
    
    ATH_MSG_INFO("Reading TTree " << *itr);

    //Read the TTree
    ntup.ReadFiles(m_samplePath, *itr);
    
    //Set flag for nominal TTree
    setNominal = false;
    if(*itr == "nominal") setNominal = true;

    //Initialize all the branches
    ntup.Init(m_setmc16a, setNominal, m_isData);
              
    unsigned int tot_evnt = ntup.fChain->GetEntries();
    
    //If entries are 0 that means TTree name is worng. TChain::LoadTTree will return NULL pointer.
    if(tot_evnt == 0) {
      ATH_MSG_FATAL("Entries are 0. Probabily a Wrong TTree name.");
    }
    
    //Option to run over a small number of events
    if(max_evnt > 0 && max_evnt < tot_evnt) tot_evnt = max_evnt;

    ATH_MSG_INFO("Number of events to be process:  " << tot_evnt);

    //Set the TTree name of output TTree
    m_outputFile->cd();
    m_outTree = new TTree((*itr).c_str(), "Mini Ntuple HH ML channels");

    //Set the branches of output TTree to be saved
    SetOutTree(m_outTree, setNominal);

    //Loop over enetries
    for(unsigned int il = 0; il < tot_evnt; il++)
      {
	if(il%10000 == 0) ATH_MSG_INFO("Events " << il << "/" << tot_evnt << " done.");
	
	ntup.fChain->GetEntry(il);
	
	//Add new variables
	AddVars();
   
	//Fill Tree
	FillTree(m_outTree);

      } //End loop over entries

    //Get the current output file and write the output TTree to it.
    m_outputFile = m_outTree->GetCurrentFile();
    m_outputFile->Write(0, TObject::kWriteDelete);
    
  } //End loop over TTrees strings

  return sc;
}

//-----------------------------------------------------------------------------------------
void HHMLSys_EventSaver::FillTree(TTree* outTree) {

  //2l selection
  if(m_do_2lSR) SR2lSelection();

  //3l selection
  if(m_do_3lSR) SR3lSelection();

  //4l selection
  if(m_do_4lSR) SR4lSelection();

  //4lbb selection
  if(m_do_4lbbSR) SR4lbbSelection();

  //2l+1tau selection
  if(m_do_2l1tauSR) SR2l1TauSelection();

  //1l+2tau selection
  if(m_do_1l2tauSR) SR1l2TauSelection();
  
  //2l+2tau selection
  if(m_do_2l2tauSR) SR2l2TauSelection();
  
  if( is2Lep or is3Lep or is4Lep or is4Lepbb or is2Lep1Tau or is1Lep2Tau or is2Lep2Tau ) outTree->Fill();
}

//-----------------------------------------------------------------------
double HHMLSys_EventSaver::getMCweight(const string& channel) {

  double event_weight(1.0), lumi(1.0);

  lumi = (36074.6 * (ntup.RunYear == 2015 or ntup.RunYear == 2016) + 43813.7 * (ntup.RunYear == 2017) + 58450.1 * (ntup.RunYear == 2018));

  event_weight = ntup.weight_mc * ntup.weight_pileup * ntup.jvtSF_customOR * ntup.bTagSF_weight_DL1r_77 * ntup.mc_rawXSection * ntup.mc_kFactor * lumi;

  if(channel =="2l") {
    event_weight *= ntup.lep_SF_El_Reco_AT_0 * ntup.lep_SF_El_Reco_AT_1 * ntup.lep_SF_El_ID_TightLH_AT_0 * ntup.lep_SF_El_ID_TightLH_AT_1 * ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_0 * ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_1 * ntup.lep_SF_Mu_TTVA_AT_0 * ntup.lep_SF_Mu_TTVA_AT_1 * ntup.lep_SF_Mu_ID_Medium_AT_0 * ntup.lep_SF_Mu_ID_Medium_AT_1 * ntup.custTrigSF_TightElMediumMuID_FCLooseIso_SLTorDLT * (abs(ntup.lep_ID_0) == 11 ? ntup.lep_SF_El_PLVTight_0: ntup.lep_SF_Mu_PLVTight_0) * (abs(ntup.lep_ID_1) == 11 ? ntup.lep_SF_El_PLVTight_1: ntup.lep_SF_Mu_PLVTight_1);
  }
  else if(channel == "3l") {
    event_weight *= ntup.custTrigSF_LooseID_FCLooseIso_SLTorDLT;
    event_weight *= ( ((abs(ntup.lep_ID_0) == 11) ? ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_0 : 1) * ((abs(ntup.lep_ID_1) == 11) ? ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_1 : 1) * ((abs(ntup.lep_ID_2) == 11) ? ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_2 : 1) );
    event_weight *= ( (abs(ntup.lep_ID_0) == 11) ? (ntup.lep_SF_El_Reco_AT_0 * ntup.lep_SF_El_ID_LooseAndBLayerLH_AT_0 * ntup.lep_SF_El_PLVLoose_0) : (ntup.lep_SF_Mu_TTVA_AT_0 * ntup.lep_SF_Mu_ID_Loose_AT_0 * ntup.lep_SF_Mu_PLVLoose_0) );
    event_weight *= ( (abs(ntup.lep_ID_1) == 11) ? (ntup.lep_SF_El_Reco_AT_1 * ntup.lep_SF_El_ID_TightLH_AT_1 * ntup.lep_SF_El_PLVTight_1) : (ntup.lep_SF_Mu_TTVA_AT_1 * ntup.lep_SF_Mu_ID_Tight_1 * ntup.lep_SF_Mu_PLVTight_1) );
    event_weight *= ( (abs(ntup.lep_ID_2) == 11) ? (ntup.lep_SF_El_Reco_AT_2 * ntup.lep_SF_El_ID_TightLH_AT_2 * ntup.lep_SF_El_PLVTight_2) : (ntup.lep_SF_Mu_TTVA_AT_2 * ntup.lep_SF_Mu_ID_Tight_2 * ntup.lep_SF_Mu_PLVTight_2) );
  }
  else if(channel == "4l") {
    event_weight *= ntup.lepSFObjLoose;
  }
  else if(channel == "4lbb") {
    event_weight *= ntup.lepSFObjLoose * ntup.custTrigSF_LooseID_FCLooseIso_SLTorDLT;
  }
  else if(channel == "2l1tau") {
    event_weight *= ntup.custTrigSF_LooseID_FCLooseIso_SLTorDLT * ntup.tauSFRNNMedium_TAU_SF_NOMINAL;
    if( abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 11 ) event_weight *= ntup.lep_SF_El_Reco_AT_0 * ntup.lep_SF_El_Reco_AT_1 * ntup.lep_SF_El_ID_LooseAndBLayerLH_AT_0 * ntup.lep_SF_El_ID_LooseAndBLayerLH_AT_1 * ntup.lep_SF_El_Iso_FCTight_0 * ntup.lep_SF_El_Iso_FCTight_1 * ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_0 * ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_1;
    else if( abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 13 ) event_weight *= ntup.lep_SF_El_Reco_AT_0 * ntup.lep_SF_El_ID_LooseAndBLayerLH_AT_0 * ntup.lep_SF_El_Iso_FCTight_0 * ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_0 * ntup.lep_SF_Mu_TTVA_AT_1 * ntup.lep_SF_Mu_ID_Medium_AT_1 * ntup.lep_SF_Mu_Iso_FCLoose_AT_1;
    else if( abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 11 ) event_weight *= ntup.lep_SF_Mu_TTVA_AT_0 * ntup.lep_SF_Mu_ID_Medium_AT_0 * ntup.lep_SF_Mu_Iso_FCLoose_AT_0 * ntup.lep_SF_El_Reco_AT_1 * ntup.lep_SF_El_ID_LooseAndBLayerLH_AT_1 * ntup.lep_SF_El_Iso_FCTight_1 * ntup.lep_SF_El_ChargeMisID_LooseAndBLayerLH_FCLoose_AT_1;
    else if( abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1 == 13) ) event_weight *= ntup.lep_SF_Mu_TTVA_AT_0 * ntup.lep_SF_Mu_TTVA_AT_1 * ntup.lep_SF_Mu_ID_Medium_AT_0 * ntup.lep_SF_Mu_ID_Medium_AT_1 * ntup.lep_SF_Mu_Iso_FCLoose_AT_0 * ntup.lep_SF_Mu_Iso_FCLoose_AT_1;  
  }
  else if(channel == "1l2tau") {
    event_weight *= ntup.lepSFObjLoose * ntup.custTrigSF_LooseID_FCLooseIso_SLT * ntup.tauSFRNNMedium_TAU_SF_NOMINAL;
  }
  else if(channel == "2l2tau") {
    event_weight *= ntup.lepSFObjLoose * ntup.custTrigSF_LooseID_FCLooseIso_SLTorDLT * ntup.tauSFRNNMedium_TAU_SF_NOMINAL;
  }

  //Divided by total weighted events (normalization)
  event_weight = event_weight / m_scale;

  return event_weight;
}
