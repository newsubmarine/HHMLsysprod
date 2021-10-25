#ifndef HHMLSYS_MVA_H
#define HHMLSYS_MVA_H

/***********************************************************
 * @Package: HHMLSys
 * @Class  : HHMLSys_MVA
 * @Author : Babar Ali <babar.ali@cern.ch>
 *
 *
 * @Brief  : Class for TMVA classification and evaluation
 *
 ***********************************************************/

//C++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

//Asg Tools
#include "AsgTools/MessageCheck.h"
#include "AsgTools/AsgMessaging.h"

//Root
#include <TString.h>

//TMVA
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

//Local include(s)
#include "HHMLSys/HHMLSys_Ntuple.h"

class HHMLSys_MVA: public asg::AsgMessaging
{

 public:

  HHMLSys_MVA(const std::string& name = "HHMLSys_MVA");
  ~HHMLSys_MVA() {
    delete reader_2lss;
    delete reader_3l;
    delete reader_1l2tau;
    delete reader_2l2tau;
    delete reader_2l1tau;
  }

  //HHMLSys_nTuple class
  HHMLSys_Ntuple ntup;
  
  //Non-tau channels
  StatusCode BookMVA_2lss(const std::string& xmlFile);
  StatusCode BookMVA_3l(const std::string& xmlFile);

  float EvaluateMVA_2lss(const HHMLSys_Ntuple& ntup);
  float EvaluateMVA_3l(const HHMLSys_Ntuple& ntup);

  //Tau channels
  StatusCode BookMVA_1l2tau(const std::string& xmlEvenFile, const std::string& xmlOddFile);
  StatusCode BookMVA_2l2tau(const std::string& xmlEvenFile, const std::string& xmlOddFile);
  StatusCode BookMVA_2l1tau(const std::string& xmlFile);
  
  float EvaluateMVA_1l2tau(const HHMLSys_Ntuple& ntup);
  float EvaluateMVA_2l2tau(const HHMLSys_Ntuple& ntup);
  float EvaluateMVA_2l1tau(const HHMLSys_Ntuple& ntup);
  
 private:

  TMVA::Reader *reader_2lss;
  TMVA::Reader *reader_3l;

  TMVA::Reader *reader_1l2tau;
  TMVA::Reader *reader_2l2tau;
  TMVA::Reader *reader_2l1tau;
  
  StatusCode CheckXMLFiles(const std::string& xmlEvenFile, const std::string& xmlOddFile);

  //Declaration of BDT input vars.
  //2lss channel
  Float_t  BDTG_dilep_type;  
  //Float_t  BDTG_nJets;       
  Float_t  BDTG_lep_Eta_0;
  Float_t  BDTG_lep_Eta_1;
  //Float_t  BDTG_leadJetPt; 
  //Float_t  BDTG_MET;
  //Float_t  BDTG_Mll01;   
  Float_t  BDTG_minDR_LJ_0;
  Float_t  BDTG_minDR_LJ_1;
  Float_t  BDTG_MLep1Jet;      
  Float_t  BDTG_MLep0Jet;      
  Float_t  BDTG_Mlep0jj;     
  Float_t  BDTG_Mlep1jj;     
  Float_t  BDTG_Mjj4;        
  Float_t  BDTG_Mj0j1;       
  Float_t  BDTG_Mall;       
  Float_t  BDTG_Mt;          
  //Float_t  BDTG_max_eta;     
  Float_t  BDTG_MLepMet;     
  //Float_t  BDTG_DRll01;      
  //Float_t  BDTG_HT;          
  Float_t  BDTG_HT_lep;   
  Float_t  BDTG_RMS;         


  //1l+2tau & 2l+2tau channels
  Float_t BDTG_Mtau0tau1;
  Float_t BDTG_DRlep0Lj;
  Float_t BDTG_DRlep0SLj;
  //Float_t BDTG_minDR_LJ_0;
  Float_t BDTG_DRtau0tau1lep0;
  Float_t BDTG_DRtau0tau1lep1;
  Float_t BDTG_SumPttau0tau1;
  Float_t BDTG_Mlep0tau0;
  Float_t BDTG_Mlep0tau1;
  //Float_t BDTG_MLep0Jet;
  Float_t BDTG_HT;
  Float_t BDTG_MaxEtalep01;
  Float_t BDTG_DEtalep01;
  Float_t BDTG_lep_flavor;
  Float_t BDTG_Mlep1tau0tau1;
  Float_t BDTG_MET;
  Float_t BDTG_tau_pt_0;
  Float_t BDTG_tau_pt_1;
  Float_t BDTG_Mll01;
  Float_t BDTG_DRll01;
  //2lSS+1tau
  Float_t BDTG_DRlep0lep1;
  Float_t BDTG_DRl0Lj;
  Float_t BDTG_DRlep1Lj;
  Float_t BDTG_DPhilep0Lj;
  Float_t BDTG_Mlep0Lj;
  Float_t BDTG_Mlep1Lj;
  Float_t BDTG_Mlep01LjSLj;
  Float_t BDTG_minDRlep0Jet;
  Float_t BDTG_farDRlep0Jet;
  Float_t BDTG_minDRLepTau0;
  Float_t BDTG_MCloserLepTau0;
  Float_t BDTG_RSumPtlep01tau0Jets;
  //3l
  Float_t BDTG_FlavorCat;
  Float_t BDTG_Mlep0lep1;
  Float_t BDTG_Mlep0lep2;
  Float_t BDTG_Mlep1lep2;
  Float_t BDTG_Mlep012;
  Float_t BDTG_Mlep2LjSLj;
  Float_t BDTG_Mlep012LjSLj;
  Float_t BDTG_DRl0l1;
  Float_t BDTG_DRlep1lep2;
  Float_t BDTG_DRlep2CloseJ;
  Float_t BDTG_nJets;
  Float_t BDTG_leadJetPt;
  Float_t BDTG_leadJetE;
  Float_t BDTG_lep_Pt_0;
  Float_t BDTG_lep_Pt_1;
  Float_t BDTG_lep_Pt_2;
  Float_t BDTG_lep_E_0;
  Float_t BDTG_lep_E_1;
  Float_t BDTG_lep_E_2;
};

#endif
