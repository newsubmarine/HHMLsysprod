#ifndef HHMLSYS_BASE_H
#define HHMLSYS_BASE_H

/***********************************************************
* @Package: HHMLSys
* @Class  : HHMLSys_Base
* @Author : Babar Ali <babar.ali@cern.ch>
*
*
* @Brief  : Base class for HHMLSys
*
***********************************************************/

//C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

//ROOT
#include "TFile.h"
#include "TDirectoryFile.h"
#include "TEnv.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include <ROOT/RVec.hxx>

//AsgTools
#include "AsgTools/MessageCheck.h"
#include "AsgTools/AsgMessaging.h"

//Local include(s)
#include "HHMLSys/HHMLSys_Ntuple.h"
#include "HHMLSys/HHMLSys_MVA.h"
#include "HHMLSys/ScaleFactors.h"

class HHMLSys_Base: public asg::AsgMessaging {
  
 public:
  
  //Constructor
  HHMLSys_Base(const std::string& name = "HHMLSys_Base");
  
  //Destructor
  ~HHMLSys_Base();
  
  //Initialize the Base class
  StatusCode initialize(const TString& configFile, const std::string& samplePath, const TString& outDir, TString& sampleName, const TString& mcRun);
  
  //Finalize the Base class
  StatusCode finalize();

  //HHMLSys_Ntuple class where all the branches of ntuple are initialized
  HHMLSys_Ntuple ntup;

  //HHMLSys_MVA class
  HHMLSys_MVA mva;

  //ScaleFactors class
  ScaleFactors sfcalc;

 protected:
  
  //Config file and its properties
  
  //Methods to get the value from configuration files
  
  void Config(bool& property, const std::string &propname, TEnv &rEnv) {
    property = rEnv.GetValue(propname.c_str(), (int) property);
  }
  void Config(std::string& property, const std::string &propname, TEnv &rEnv) {
    property = rEnv.GetValue(propname.c_str(), property.c_str());
  }
  void Config(int property, const std::string& propname, TEnv& rEnv) {
    property = rEnv.GetValue(propname.c_str(), property);
  }
  void Config(float property, const std::string& propname, TEnv& rEnv) {
    property = rEnv.GetValue(propname.c_str(), property);
  }

  //dsid of MC (for setting the name of output root file)
  Int_t m_dsid = 0;

  //SR's flags (to be set to true/false in the config file)
  bool m_isData = false;
  std::string m_treeNames = "";
  //std::vector<std::string> m_inputTrees;
  //2l
  bool m_do_2lSR  = false;
  bool m_do_2lCR  = false;
  bool m_do_2lMVA = false;
  std::string m_2l_BDTxmlFile     = "";
  std::string m_2l_VV_BDTxmlFile    = "";
  std::string m_2l_tt_BDTxmlFile    = "";
  std::string m_2l_Vjets_BDTxmlFile = "";
  
  //3l
  bool m_do_3lSR  = false;
  bool m_do_3lMVA = false;
  std::string m_3l_BDTxmlFile  = "";

  //4l
  bool m_do_4lSR  = false;

  //4l+bb
  bool m_do_4lbbSR  = false;
  bool m_do_4lbbMVA = false;
  std::string m_4lbb_BDTxmlFile  = "";

  //2l+1tau
  bool m_do_2l1tauSR = false;
  bool m_do_2l1tauCRWZ = false;
  bool m_do_fakeTauSFCR = false;
  bool m_do_2l1tauMVA = false;
  bool m_do_2l1tauFakeTauSF = false;
  std::string m_2l1tau_BDTGxmlFile = "";
  std::string m_2l1tau_fakeTauSFFile = "";

  //1l+2tau
  bool m_do_1l2tauSR  = false;
  bool m_do_1l2tauMVA = false;
  std::string m_1l2tau_BDTGOddxmlFile  = "";
  std::string m_1l2tau_BDTGEvenxmlFile = "";
  
  //2l+2tau
  bool m_do_2l2tauSR  = false;
  bool m_do_2l2tauMVA = false;
  std::string m_2l2tau_BDTGOddxmlFile  = "";
  std::string m_2l2tau_BDTGEvenxmlFile = "";

  //Flags for Control regions
  bool m_do_1l2tauCR = false;
  bool m_do_2l2tauCR = false;

  //To scale MC samples
  float m_scale = -9999;

  //Output File
  TFile* m_outputFile = 0;

  //Out TTree
  TTree* m_outTree = 0;

  //Get the names of all TTrees of systematic
  std::unique_ptr<std::vector<std::string>> m_treeVec;

  std::string m_samplePath = "";
  bool m_setmc16a = false;

 private:

  //Simple method to set the name of output file
  TString SetOutputName(const std::string& InputSamplePath);

  //Get sumWeight Tree entries and fill the histogram (in case later use for normalization)
  void SumWeights(const std::string& SamplePath);
  
  //Convert strings to vector from config file
  void InterpString(const std::string &s, std::vector<std::string> &f);

};

#endif
