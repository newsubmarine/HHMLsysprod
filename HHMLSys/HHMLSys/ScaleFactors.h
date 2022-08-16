#ifndef SCALEFACTORS_H
#define SCALEFACTORS_H

/***********************************************************
 * @Package: HHMLSys
 * @Class  : ScaleFactors
 * @Author : Babar Ali <babar.ali@cern.ch>
 *
 *
 * @Brief  : Class for scale factor application
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

class ScaleFactors: public asg::AsgMessaging
{

 public:

  ScaleFactors(const std::string& name = "ScaleFactors");
  ~ScaleFactors() {
    if (fileFakeTauSF_2l1tau) delete fileFakeTauSF_2l1tau;
  }

  //HHMLSys_nTuple class
  HHMLSys_Ntuple ntup;
  
  //tau channels
  StatusCode ImportFakeTauSFs_2l1tau(const std::string& sfFile);

  double ApplyFakeTauSF_2l1tau(const HHMLSys_Ntuple& ntup, TString sys);
  
 private:

  TFile *fileFakeTauSF_2l1tau = nullptr;

  TH1F *SF_nom_1p_2l1tau = nullptr;
  TH1F *SF_nom_1p_Composition_sys_2l1tau = nullptr;
  TH1F *SF_nom_1p_Numerator_sys_2l1tau = nullptr;
  TH1F *SF_nom_3p_2l1tau = nullptr;
  TH1F *SF_nom_3p_Composition_sys_2l1tau = nullptr;
  TH1F *SF_nom_3p_Numerator_sys_2l1tau = nullptr;

};

#endif
