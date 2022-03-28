#include "HHMLSys/ApplyFF.h"

using namespace std;

//---------------------------------------------------------------------
ApplyFF::ApplyFF(const string& name) :
  asg::AsgMessaging(name)
{
}

//---------------------------------------------------------------------
ApplyFF::~ApplyFF()
{
}

//-----------------------------------------------------------------------
StatusCode ApplyFF::initialize(std::string& fakeFactor_filePath, const string& chan)
{
  StatusCode sc = StatusCode::SUCCESS;

  if(fakeFactor_filePath == "") {
    ATH_MSG_FATAL("Fake factor file path is not given.  Exiting!!");
    return StatusCode::FAILURE;
  }

  ATH_MSG_INFO("Reading fake factor file " << fakeFactor_filePath);

  //Open the fake factor root file
  TFile* FakeFactorFile = TFile::Open(fakeFactor_filePath.c_str(), "READ");

  if(!FakeFactorFile) {
    ATH_MSG_FATAL("Invalid fake factor file " << fakeFactor_filePath << " Exiting!!");
    return StatusCode::FAILURE;
  }

  //Load all the hists
  sc  = Load1DHists(FakeFactorFile, chan);

  FakeFactorFile->Close();
  delete FakeFactorFile;
  
  return sc;
}

//-------------------------------------------------------------------------
StatusCode ApplyFF::finalize()
{
  StatusCode sc = StatusCode::SUCCESS;

  return sc;
}

//-----------------------------------------------------------------------------------
void ApplyFF::ApplyFFWeight(float& weight, float& weight_up, float& weight_dn, 
			    int& bin_num, float pt, LepEnum::LepType typeOfLep) {

  shared_ptr<TH1> hist = 0;
  
  if(typeOfLep == LepEnum::Electron)  hist = m_el_FakeFactors.at("nom");
  else if(typeOfLep == LepEnum::Muon) hist = m_mu_FakeFactors.at("nom");
  else if(typeOfLep == LepEnum::Tau)  hist = m_tau_FakeFactors.at("nom");
  else {
    ATH_MSG_ERROR("ApplyFFWeight - Unknown Lepton type " << typeOfLep);
  }
  
  if(!hist){
    ATH_MSG_ERROR("ApplyFFWeight - Fake factor hist for lepton type " << typeOfLep << " cannot be found!");
  }

  // don't read values from over/underflow bins
  int bin = hist->FindBin(pt);
  if(bin == 0) bin += 1;
  if(bin == hist->GetNbinsX()+1) bin -= 1;

  bin_num = bin;

  weight    = hist->GetBinContent(bin);
  weight_up = std::fabs(hist->GetBinContent(bin) + hist->GetBinError(bin));
  weight_dn = std::fabs(hist->GetBinContent(bin) - hist->GetBinError(bin));
}

//-----------------------------------------------------------------------------------------------------------
StatusCode ApplyFF::Load1DHists(TFile* FakeFactor_File, const string& chan) {

  StatusCode sc = StatusCode::SUCCESS;

  vector<shared_ptr<TH1> > ff_hists;
  vector<TString> ff_hname;

  TDirectory* dir;
  if(chan == "OS") {
    dir = FakeFactor_File->GetDirectory("Data");
  }
  else dir = FakeFactor_File->GetDirectory("");
  
  TIter next( dir->GetListOfKeys() );
  TKey *key;
  bool NoHist = false;
  while((key = (TKey*)next()))
    {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *h = (TH1*)key->ReadObj();
      if(!h) {
	NoHist = true;
	break;
      }
      ff_hists.push_back(shared_ptr<TH1>(h));
      ff_hname.push_back(h->GetName());
      std::cout<<h->GetName()<<std::endl;
    }
  
  if(NoHist || ff_hists.empty() || ff_hname.empty()) {
    ATH_MSG_FATAL("Load1DHists - Failed to find any fake factor 1D hists in file " << FakeFactor_File->GetName() << " Exiting!!");
    return StatusCode::FAILURE;
  }
  
  if(chan == "SS") {
    for(size_t it = 0;  it < ff_hname.size(); ++it) {
      
      shared_ptr<TH1> hist = ff_hists[it];
      TString name = ff_hname[it];
      
      if(name.Contains("el")) {
	if(name.Contains("nom"))                               FFHistsMap(name, "nom"     , hist, m_el_FakeFactors); 
	else if(name.Contains("ttw")  && name.Contains("up"))  FFHistsMap(name, "ttwUp"   , hist, m_el_FakeFactors); 
	else if(name.Contains("ttz")  && name.Contains("up"))  FFHistsMap(name, "ttzUp"   , hist, m_el_FakeFactors); 
	else if(name.Contains("vv")   && name.Contains("up"))  FFHistsMap(name, "vvUp"    , hist, m_el_FakeFactors); 
	else if(name.Contains("oth")  && name.Contains("up"))  FFHistsMap(name, "rareUp"  , hist, m_el_FakeFactors); 
	else if(name.Contains("tth")  && name.Contains("up"))  FFHistsMap(name, "tthUp"   , hist, m_el_FakeFactors); 
	else if(name.Contains("QMis") && name.Contains("up"))  FFHistsMap(name, "QMisIDUp", hist, m_el_FakeFactors); 
	else if(name.Contains("ttw")  && name.Contains("dn"))  FFHistsMap(name, "ttwDn"   , hist, m_el_FakeFactors); 
	else if(name.Contains("ttz")  && name.Contains("dn"))  FFHistsMap(name, "ttzDn"   , hist, m_el_FakeFactors); 
	else if(name.Contains("vv")   && name.Contains("dn"))  FFHistsMap(name, "vvDn"    , hist, m_el_FakeFactors); 
	else if(name.Contains("oth")  && name.Contains("dn"))  FFHistsMap(name, "rareDn"  , hist, m_el_FakeFactors); 
	else if(name.Contains("tth")  && name.Contains("dn"))  FFHistsMap(name, "tthDn"   , hist, m_el_FakeFactors); 
	else if(name.Contains("QMis") && name.Contains("dn"))  FFHistsMap(name, "QMisIDDn", hist, m_el_FakeFactors); 
      }
      if(name.Contains("mu")) {
	if(name.Contains("nom"))                              FFHistsMap(name, "nom"    , hist, m_mu_FakeFactors); 
	else if(name.Contains("ttw") && name.Contains("up"))  FFHistsMap(name, "ttwUp"  , hist, m_mu_FakeFactors); 
	else if(name.Contains("ttz") && name.Contains("up"))  FFHistsMap(name, "ttzUp"  , hist, m_mu_FakeFactors); 
	else if(name.Contains("vv")  && name.Contains("up"))  FFHistsMap(name, "vvUp"   , hist, m_mu_FakeFactors); 
	else if(name.Contains("oth") && name.Contains("up"))  FFHistsMap(name, "rareUp" , hist, m_mu_FakeFactors); 
	else if(name.Contains("tth") && name.Contains("up"))  FFHistsMap(name, "tthUp"  , hist, m_mu_FakeFactors); 
	else if(name.Contains("ttw") && name.Contains("dn"))  FFHistsMap(name, "ttwDn"  , hist, m_mu_FakeFactors); 
	else if(name.Contains("ttz") && name.Contains("dn"))  FFHistsMap(name, "ttzDn"  , hist, m_mu_FakeFactors); 
	else if(name.Contains("vv")  && name.Contains("dn"))  FFHistsMap(name, "vvDn"   , hist, m_mu_FakeFactors); 
	else if(name.Contains("oth") && name.Contains("dn"))  FFHistsMap(name, "rareDn" , hist, m_mu_FakeFactors); 
	else if(name.Contains("tth") && name.Contains("dn"))  FFHistsMap(name, "tthDn"  , hist, m_mu_FakeFactors); 
      }
      if(name.Contains("tau") && (!(name.Contains("wBJet")))) {
	if(name.Contains("nom"))                                 FFHistsMap(name, "nom"        , hist, m_tau_FakeFactors); 
	else if(name.Contains("Realtau") && name.Contains("up")) FFHistsMap(name, "RealtauUp"  , hist, m_tau_FakeFactors); 
	else if(name.Contains("tth")     && name.Contains("up")) FFHistsMap(name, "tthUp"      , hist, m_tau_FakeFactors); 
	else if(name.Contains("Realtau") && name.Contains("dn")) FFHistsMap(name, "RealtauDn"  , hist, m_tau_FakeFactors); 
	else if(name.Contains("tth")     && name.Contains("dn")) FFHistsMap(name, "tthDn"      , hist, m_tau_FakeFactors);
      }
    }
    sc = FileCheck2LSS1Tau();
  }
  else if(chan == "OS") {
    for(size_t it = 0;  it < ff_hname.size(); ++it) {
      
      shared_ptr<TH1> hist = ff_hists[it];
      TString name = ff_hname[it];
      
      if(name.Contains("tau") && (!(name.Contains("1p")) || name.Contains("3p"))) {
	if(name.Contains("nom"))                                 FFHistsMap(name, "nom"        , hist, m_tau_FakeFactors); 
	else if(name.Contains("Realtau") && name.Contains("up")) FFHistsMap(name, "RealtauUp"  , hist, m_tau_FakeFactors); 
	else if(name.Contains("tth")     && name.Contains("up")) FFHistsMap(name, "tthUp"      , hist, m_tau_FakeFactors); 
	else if(name.Contains("Realtau") && name.Contains("dn")) FFHistsMap(name, "RealtauDn"  , hist, m_tau_FakeFactors); 
	else if(name.Contains("tth")     && name.Contains("dn")) FFHistsMap(name, "tthDn"      , hist, m_tau_FakeFactors);
	else if(name.Contains("composition_exc2j1b") )           FFHistsMap(name, "Composition_exc2j1b", hist, m_tau_FakeFactors);
	else if(name.Contains("composition_3j0b_onZ") )          FFHistsMap(name, "Composition_3j0b_onZ", hist, m_tau_FakeFactors); 
      }
    }
  }
  else {
    ATH_MSG_FATAL("Load1DHists - Wrong sting name. Exiting!!");
    return StatusCode::FAILURE;
  }

  return sc;
}

//-------------------------------------------------------------------------------------------------------------------------
void ApplyFF::FFHistsMap(TString& name, const TString& key, shared_ptr<TH1> hist, std::map<const TString, shared_ptr<TH1> >&  m_FakeFactor) {
  
  std::string sym = "_";

  hist->SetDirectory(0);

  if(name.EndsWith((sym+"pt").c_str())) m_FakeFactor.insert(std::pair<const TString, shared_ptr<TH1> >(key , hist));
  else {
    ATH_MSG_WARNING("FFHistsMap - No pt hist found!!");
  }
}
