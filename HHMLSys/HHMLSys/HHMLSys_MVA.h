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
    if(reader_2l_1)     delete reader_2l_1;
    if(reader_2l_2)     delete reader_2l_2;
    if(reader_2l_VV)    delete reader_2l_VV;
    if(reader_2l_tt)    delete reader_2l_tt;
    if(reader_2l_Vjets) delete reader_2l_Vjets;
    if(reader_3l)       delete reader_3l;
    if(reader_1l2tau)   delete reader_1l2tau;
    if(reader_2l2tau)   delete reader_2l2tau;
    if(reader_2l1tau)   delete reader_2l1tau;
  }

  //HHMLSys_nTuple class
  HHMLSys_Ntuple ntup;
  
  //Non-tau channels
  StatusCode BookMVA_2l(const std::string& xmlFile1, const std::string& xmlFile2, const std::string& xmlFile_VV, const std::string& xmlFile_tt, const std::string& xmlFile_Vjets);
  StatusCode BookMVA_3l(const std::string& xmlFile);
  StatusCode BookMVA_4lbb(const std::string& xmlFile);

  void  EvaluateMVA_2l(const HHMLSys_Ntuple& ntup, float& BDTG_weight_2l_1, float& BDTG_weight_2l_2, float& BDTG_weight_2l_VV, float& BDTG_weight_2l_tt, float& BDTG_weight_2l_Vjets);
  float EvaluateMVA_3l(const HHMLSys_Ntuple& ntup);
  float EvaluateMVA_4lbb(const HHMLSys_Ntuple& ntup);

  //Tau channels
  StatusCode BookMVA_1l2tau(const std::string& xmlEvenFile, const std::string& xmlOddFile);
  StatusCode BookMVA_2l2tau(const std::string& xmlFile);
  StatusCode BookMVA_2l1tau(const std::string& xmlFile);
  
  float EvaluateMVA_1l2tau(const HHMLSys_Ntuple& ntup);
  float EvaluateMVA_2l2tau(const HHMLSys_Ntuple& ntup);
  float EvaluateMVA_2l1tau(const HHMLSys_Ntuple& ntup);
  
 private:

  TMVA::Reader *reader_2l_1     = nullptr;
  TMVA::Reader *reader_2l_2     = nullptr;
  TMVA::Reader *reader_2l_VV    = nullptr;
  TMVA::Reader *reader_2l_tt    = nullptr;
  TMVA::Reader *reader_2l_Vjets = nullptr;
  TMVA::Reader *reader_3l       = nullptr; 
  TMVA::Reader *reader_4lbb     = nullptr;
  TMVA::Reader *reader_1l2tau   = nullptr;
  TMVA::Reader *reader_2l2tau   = nullptr;
  TMVA::Reader *reader_2l1tau   = nullptr;
  
  StatusCode CheckXMLFile(const std::string& xmlFile);
  StatusCode CheckXMLFiles(const std::string& xmlEvenFile, const std::string& xmlOddFile);

  //Declaration of BDT input vars.
  //1l+2tau & 2l+2tau channels
  Float_t BDTG_Mtau0tau1;
  Float_t BDTG_DRlep0Lj;
  Float_t BDTG_DRlep0SLj;
  Float_t BDTG_minDR_LJ_0;
  Float_t BDTG_DRtau0tau1lep0;
  Float_t BDTG_DRtau0tau1lep1;
  Float_t BDTG_SumPttau0tau1;
  Float_t BDTG_Mlep0tau0;
  Float_t BDTG_Mlep0tau1;
  Float_t BDTG_MLep0Jet;
  Float_t BDTG_HT;
  Float_t BDTG_MET;
  Float_t BDTG_tau_pt_0;
  Float_t BDTG_tau_pt_1;
  Float_t BDTG_Mll01;
  Float_t BDTG_DRll01;
  Float_t BDTG_DRlep1tau0;
  //2lSS+1tau
  Float_t BDTG_DRlep0lep1;
  Float_t BDTG_DRl0Lj;
  Float_t BDTG_DRlep1Lj;
  Float_t BDTG_DPhilep0Lj;
  Float_t BDTG_Mlep0Lj;
  Float_t BDTG_Mlep1Lj;
  Float_t BDTG_Mlep0SLj;
  Float_t BDTG_Mlep01LjSLj;
  Float_t BDTG_minDRlep0Jet;
  Float_t BDTG_farDRlep0Jet;
  Float_t BDTG_minDRLepTau0;
  Float_t BDTG_minDRLep1Jet;
  Float_t BDTG_MCloserLepTau0;
  Float_t BDTG_MCloserJetlep0;
  Float_t BDTG_RSumPtlep01tau0Jets;
  Float_t BDTG_LBoost2L_ThetaLjTau0;
  Float_t BDTG_LBoost2L_ThetaSLjTau0;
  Float_t BDTG_LBoostLep0Tau0_DRlep0SLj;
  Float_t BDTG_LBoostLep1Tau0_DRlep1Lj;

  //2l
  Float_t BDTG_VV;
  Float_t BDTG_tt;
  Float_t BDTG_Vjets;
  Float_t BDTG_MAll;
  Float_t BDTG_MetAll;
  Float_t BDTG_RMS;
  Float_t BDTG_MLep1Jet;
  Float_t BDTG_AbsDEtalep01;
  Float_t BDTG_MaxEtalep01;
  Float_t BDTG_DEtalep01;
  Float_t BDTG_DR_min_LepJet;
  Float_t BDTG_HT_lep;
  Float_t BDTG_MLep0MET;
  Float_t BDTG_MLep1MET;
  Float_t BDTG_dilep_type;
  Float_t BDTG_total_charge;
  Float_t BDTG_DR_min_lep_jet;
  Float_t BDTG_lep_Eta_0;
  Float_t BDTG_lep_Eta_1;
  Float_t BDTG_minDR_LJ_1;
  //3l
  Int_t   BDTG_EventNo;
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
  Float_t BDTG_best_Z_Mll;
  //4l
  Float_t BDTG_lep_Pt_3;
  Float_t BDTG_sublead_JetPt;
  Float_t BDTG_EtCone20Pt_0;
  Float_t BDTG_EtCone20Pt_1;
  Float_t BDTG_EtCone20Pt_2;
  Float_t BDTG_EtCone20Pt_3;
  Float_t BDTG_MLep12_4l;
  Float_t BDTG_MLep34_4l;
  Float_t BDTG_M4_4l;
  Float_t BDTG_MLjSLj_4l;
  Float_t BDTG_PtLjSLj_4l;
  Float_t BDTG_DPhiJetMET;
  Float_t BDTG_nJets_OR_DL1r_77;
};

#endif
