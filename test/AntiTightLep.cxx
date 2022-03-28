#include "HHMLSys/HHMLSys_EventSaver.h"

using namespace std;
using namespace Fakes;

//
// Anti-tight leptons.
//

//These methods used in FakeFactor. Do not use it other than that if you want to have at least 1 anti-tight lepton.

//2l

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::AntiTight2LepCuts(const string& chan) {

  if( !ntup.dilep_type ) return false;

  
    //In each sub-channel at least 1 lepton is anti-tight
    if(chan == "ee") {
      if( abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 11 &&
	  abs(ntup.lep_Z0SinTheta_0) < 0.5 && abs(ntup.lep_Z0SinTheta_1) < 0.5 &&
	  abs(ntup.lep_sigd0PV_0) < 5 && abs(ntup.lep_sigd0PV_1) < 5 &&
	  !ntup.lep_ambiguityType_0 && ntup.lep_chargeIDBDTLoose_0 && !ntup.lep_ambiguityType_1 && ntup.lep_chargeIDBDTLoose_1 &&
	  ((ntup.lep_plvWP_Tight_0 && ntup.lep_isTightLH_0 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isTightLH_1)) ||
	   (ntup.lep_plvWP_Tight_1 && ntup.lep_isTightLH_1 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isTightLH_0))) ) return true;
    }
    else if(chan == "mm") {
      if( abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 13 &&
	  abs(ntup.lep_Z0SinTheta_0) < 0.5 && abs(ntup.lep_Z0SinTheta_1) < 0.5 &&
	  abs(ntup.lep_sigd0PV_0) < 3 && abs(ntup.lep_sigd0PV_1) < 3 &&
	  ((ntup.lep_plvWP_Tight_0 && ntup.lep_isMedium_0 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isMedium_1)) ||
	   (ntup.lep_plvWP_Tight_1 && ntup.lep_isMedium_1 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isMedium_0))) ) return true;
    }
    
    else if(chan == "elNotmu") {
      if( abs(ntup.lep_Z0SinTheta_0) < 0.5 && abs(ntup.lep_Z0SinTheta_1) < 0.5 &&
	  (((abs(ntup.lep_ID_0) == 13 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isMedium_0) && abs(ntup.lep_sigd0PV_0) < 3) &&
	    (abs(ntup.lep_ID_1) == 11 && ntup.lep_plvWP_Tight_1 && ntup.lep_isTightLH_1 && abs(ntup.lep_sigd0PV_1) < 5 && !ntup.lep_ambiguityType_1 && ntup.lep_chargeIDBDTLoose_1))
	   ||
	   ((abs(ntup.lep_ID_0) == 11 && ntup.lep_plvWP_Tight_0 && ntup.lep_isTightLH_0 && abs(ntup.lep_sigd0PV_0) < 5 && !ntup.lep_ambiguityType_0 && ntup.lep_chargeIDBDTLoose_0) &&
	    (abs(ntup.lep_ID_1) == 13 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isMedium_1) && abs(ntup.lep_sigd0PV_1) < 3))) ) return true;
    }
    else if(chan == "muNotel") {
      if( abs(ntup.lep_Z0SinTheta_0) < 0.5 && abs(ntup.lep_Z0SinTheta_1) < 0.5 &&
	  (((abs(ntup.lep_ID_0) == 13 && ntup.lep_plvWP_Tight_0 && ntup.lep_isMedium_0 && abs(ntup.lep_sigd0PV_0) < 3) &&
	    (abs(ntup.lep_ID_1) == 11 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isTightLH_1) && abs(ntup.lep_sigd0PV_1) < 5 && !ntup.lep_ambiguityType_1 && ntup.lep_chargeIDBDTLoose_1))
	   ||
	   ((abs(ntup.lep_ID_0) == 11 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isTightLH_0) && abs(ntup.lep_sigd0PV_0) < 5 && !ntup.lep_ambiguityType_0 && ntup.lep_chargeIDBDTLoose_0) &&
	    (abs(ntup.lep_ID_1) == 13 && ntup.lep_plvWP_Tight_1 && ntup.lep_isMedium_1 && abs(ntup.lep_sigd0PV_1) < 3))) ) return true;
    }
    else {
      ATH_MSG_WARNING("AntiTight2LepCuts - wrong channel. NO anti-tight cuts are applied.");
      return false;
    }

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isTLPair01() {

  if( !ntup.dilep_type ) return false;

  
	if( (abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 11 && ntup.lep_plvWP_Tight_0 && ntup.lep_isTightLH_0 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isTightLH_1))
	||
	(abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 13 && ntup.lep_isMedium_0 && ntup.lep_plvWP_Tight_0 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isMedium_1 ))
	||
	(abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 13 && ntup.lep_plvWP_Tight_0 && ntup.lep_isTightLH_0 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isMedium_1)
	||
	(abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 11 && ntup.lep_plvWP_Tight_0 && ntup.lep_isMedium_1 && (!ntup.lep_plvWP_Tight_1 || !ntup.lep_isTightLH_1))
	) return true;  

  return false;
}

//-----------------------------------------------------------------------------------------------
bool HHMLSys_EventSaver::isLTPair01() {

  if( !ntup.dilep_type ) return false;


    if( (abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 11 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isTightLH_0) && ntup.lep_plvWP_Tight_1 && ntup.lep_isTightLH_1)
	||
	(abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 13 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isMedium_0) && ntup.lep_plvWP_Tight_1 && ntup.lep_isMedium_1)
	||
	(abs(ntup.lep_ID_0) == 11 && abs(ntup.lep_ID_1) == 13 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isTightLH_0) && ntup.lep_plvWP_Tight_1 && ntup.lep_isMedium_1)
	||
	(abs(ntup.lep_ID_0) == 13 && abs(ntup.lep_ID_1) == 11 && (!ntup.lep_plvWP_Tight_0 || !ntup.lep_isMedium_1) && ntup.lep_plvWP_Tight_1 && ntup.lep_isTightLH_1)
	) return true;

  return false;
}

