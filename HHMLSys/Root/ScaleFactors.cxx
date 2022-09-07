#include "HHMLSys/ScaleFactors.h"

using namespace std;

//-----------------------------------------------------------------------------------
ScaleFactors::ScaleFactors(const std::string& name) :
  asg::AsgMessaging(name)
{
}

//-----------------------------------------------------------------------------------
StatusCode ScaleFactors::ImportFakeTauSFs_2l1tau(const string& sfFile) {

  ATH_MSG_INFO("Reading scale factor file " << sfFile);

  fileFakeTauSF_2l1tau = new TFile(sfFile.data(), "read");

  SF_nom_1p_2l1tau = (TH1F*)fileFakeTauSF_2l1tau->Get("SF_nom_1p");
  SF_nom_1p_Composition_sys_2l1tau = (TH1F*)fileFakeTauSF_2l1tau->Get("SF_nom_1p_Composition_sys");
  SF_nom_1p_Numerator_sys_2l1tau = (TH1F*)fileFakeTauSF_2l1tau->Get("SF_nom_1p_Numerator_sys");
  SF_nom_3p_2l1tau = (TH1F*)fileFakeTauSF_2l1tau->Get("SF_nom_3p");
  SF_nom_3p_Composition_sys_2l1tau = (TH1F*)fileFakeTauSF_2l1tau->Get("SF_nom_3p_Composition_sys");
  SF_nom_3p_Numerator_sys_2l1tau = (TH1F*)fileFakeTauSF_2l1tau->Get("SF_nom_3p_Numerator_sys");

  return StatusCode::SUCCESS;
}

//-----------------------------------------------------------------------------------
double ScaleFactors::ApplyFakeTauSF_2l1tau(const HHMLSys_Ntuple& ntup, TString sys) {
  double tauSF = 1.;

  int ntrk = ntup.tau_numTrack_0;
  double tauPt = ntup.tau_pt_0/1000;
  tauPt = tauPt < 200? tauPt : 200;
  bool isTrue = (ntup.tau_truthType_0 > 0 && ntup.tau_truthType_0<=12);

  if (isTrue) return 1.;

  if (sys == "nom"){
    if (ntrk==1){
      tauSF = SF_nom_1p_2l1tau->GetBinContent(SF_nom_1p_2l1tau->FindBin(tauPt));
    }
    else if (ntrk==3){
      tauSF = SF_nom_3p_2l1tau->GetBinContent(SF_nom_3p_2l1tau->FindBin(tauPt));
    }
  }

  if (sys == "composition_up"){
    if (ntrk==1){
      tauSF = SF_nom_1p_Composition_sys_2l1tau->GetBinContent(SF_nom_1p_Composition_sys_2l1tau->FindBin(tauPt)) + SF_nom_1p_Composition_sys_2l1tau->GetBinError(SF_nom_1p_Composition_sys_2l1tau->FindBin(tauPt));
    }
    else if (ntrk==3){
      tauSF = SF_nom_3p_Composition_sys_2l1tau->GetBinContent(SF_nom_3p_Composition_sys_2l1tau->FindBin(tauPt)) + SF_nom_3p_Composition_sys_2l1tau->GetBinError(SF_nom_3p_Composition_sys_2l1tau->FindBin(tauPt));
    }
  }

  if (sys == "composition_dn"){
    if (ntrk==1){
      tauSF = SF_nom_1p_Composition_sys_2l1tau->GetBinContent(SF_nom_1p_Composition_sys_2l1tau->FindBin(tauPt)) - SF_nom_1p_Composition_sys_2l1tau->GetBinError(SF_nom_1p_Composition_sys_2l1tau->FindBin(tauPt));
    }
    else if (ntrk==3){
      tauSF = SF_nom_3p_Composition_sys_2l1tau->GetBinContent(SF_nom_3p_Composition_sys_2l1tau->FindBin(tauPt)) - SF_nom_3p_Composition_sys_2l1tau->GetBinError(SF_nom_3p_Composition_sys_2l1tau->FindBin(tauPt));
    }
  }

  if (sys == "numerator_up"){
    if (ntrk==1){
      tauSF = SF_nom_1p_Numerator_sys_2l1tau->GetBinContent(SF_nom_1p_Numerator_sys_2l1tau->FindBin(tauPt)) + SF_nom_1p_Numerator_sys_2l1tau->GetBinError(SF_nom_1p_Numerator_sys_2l1tau->FindBin(tauPt));
    }
    else if (ntrk==3){
      tauSF = SF_nom_3p_Numerator_sys_2l1tau->GetBinContent(SF_nom_3p_Numerator_sys_2l1tau->FindBin(tauPt)) + SF_nom_3p_Numerator_sys_2l1tau->GetBinError(SF_nom_3p_Numerator_sys_2l1tau->FindBin(tauPt));
    }
  }

  if (sys == "numerator_dn"){
    if (ntrk==1){
      tauSF = SF_nom_1p_Numerator_sys_2l1tau->GetBinContent(SF_nom_1p_Numerator_sys_2l1tau->FindBin(tauPt)) - SF_nom_1p_Numerator_sys_2l1tau->GetBinError(SF_nom_1p_Numerator_sys_2l1tau->FindBin(tauPt));
    }
    else if (ntrk==3){
      tauSF = SF_nom_3p_Numerator_sys_2l1tau->GetBinContent(SF_nom_3p_Numerator_sys_2l1tau->FindBin(tauPt)) - SF_nom_3p_Numerator_sys_2l1tau->GetBinError(SF_nom_3p_Numerator_sys_2l1tau->FindBin(tauPt));
    }
  }

  return tauSF;
}
