#ifndef HHMLSYS_EVENTSAVER_H
#define HHMLSYS_EVENTSAVER_H

/***********************************************************
 * @Package: HHMLSys
 * @Class  : HHMLSys_EventSaver
 * @Author : Babar Ali <babar.ali@cern.ch>
 *
 *
 * @Brief  : Main Class for HHMLSys
 *           All the cuts are applied in this class.
 *
 ***********************************************************/

#include "HHMLSys/HHMLSys_Base.h"

const float GeV = 1000.;
const float ZMass = 91187.6;

class HHMLSys_EventSaver: public HHMLSys_Base {

 public:

  //Constructor
  HHMLSys_EventSaver(const std::string& name = "HHMLSys_EventSaver");

  //Destructor
  ~HHMLSys_EventSaver();

  //Initialize this class
  StatusCode initialize(const TString& configFile, const std::string& samplePath, const TString& outDir, TString& sampleName, const TString& mcRun);

  //Execute event loop. This is main Event Loop, all the other methods should be called inside it.
  StatusCode executeEventLoop(unsigned int max_evt = -1);

  //Finalize this class
  StatusCode finalize();

 private:

  double getMCweight(const std::string& channel);

  //
  //Set out TTree and it's branches
  //
  void SetOutTree(TTree* outTree, bool setNom);

  //
  //Fill out Tree
  //
  void FillTree(TTree* outTree);

  //
  //SR event selection
  //
  //0tau channels: 2l, 3l, 4l, 4lbb
  void SR2lSelection();
  void SR3lSelection();
  void SR4lSelection();
  void SR4lbbSelection();

  //Tau channles: 2l+1tau, 1l+2tau, 2l+2tau
  void SR2l1TauSelection();
  void SR1l2TauSelection();
  void SR2l2TauSelection();

  //
  //Booleans of each SR
  //
  bool is2Lep{false};
  bool is3Lep{false};
  bool is4Lep{false};
  bool is4Lepbb{false};
  bool is2Lep1Tau{false};
  bool is1Lep2Tau{false};
  bool is2Lep2Tau{false};

  //
  //Def. of each CRs and samples for 3 Lepton
  //
  void CR3lSelection();
  void Sample3lSelection();
  /* Regions
   * 0: Material Conversion
   * 1: HF e
   * 2: HF m
   * 3: WZ
   */
  int CR3Lep{-1};

  /* Samples
   * -1: Prompt
   * 0: QMisID
   * 1: ExtConv
   * 2: IntConv
   * 3: HF_e
   * 4: HF_m
   * 5: LF_e
   * 6: LF_m
   */
  int Sample3Lep{-2};

  //
  //MC weights per event per channel
  //
  Double_t weight_2l     = -99999;
  Double_t weight_3l     = -99999;
  Double_t weight_4l     = -99999;
  Double_t weight_4lbb   = -99999;
  Double_t weight_2l1tau = -99999;
  Double_t weight_1l2tau = -99999;
  Double_t weight_2l2tau = -99999;

  //
  //Compute new variables
  //
  void AddVars();

  //
  //BDT output
  //
  Float_t BDTOutput_2l_1;
  Float_t BDTOutput_2l_2;
  Float_t BDTOutput_2l_VV;
  Float_t BDTOutput_2l_tt;
  Float_t BDTOutput_2l_Vjets;
  Float_t BDTOutput_3l;
  Float_t BDTOutput_4lbb;
  Float_t BDTOutput_2l1tau;
  Float_t BDTOutput_1l2tau;
  Float_t BDTOutput_2l2tau;

  //
  // Helper Functions
  //

  float DeltaPhi(float Phi1, float Phi2);
  float DeltaR(float DEta, float DPhi);
  float getRMS(const std::vector<float>& values);

  //Tight single lepton selection cuts
  bool Tight1LepCuts();
  
  //Tight di-lepton selection cuts
  bool Tight2LepCuts(const std::string& channel);
  
  //Tight tri-lepton selection cuts
  bool Tight3LepCuts();

  //Tight tetra-lep selection cuts
  bool Tight4LepCuts();
  bool Tight4LepbbCuts();

  //Single Lepton Triggers Run-2 (2015-2018)
  bool OneLepTriggers();
  
  //DiLepton Triggers Run-2 (2015-2018)
  bool DiLepTriggers();
  
  //Tigger matching
  bool LepTrigMatch(const std::string& matching);

  //Single lepton pt cut. el:25GeV, mu:21GeV for RunYear:2015. 27GeV for other Run Years
  bool OneLepPtCut();
  
  //Di lep pt cuts, take values in GeV
  bool DiLepPtCuts(const float lep0Pt, const float lep1Pt);

  //Tri lep pt cuts, take values in GeV
  bool TriLepPtCuts(const float lep0Pt, const float lep1Pt, const float lep2Pt);
  
  //Jet Cut takes njet value. Condition is >= njet
  bool JetCut(int njet);
  
  //BJet Cut takes nbjet value. Condition is >= nbjet. Default BTag wp is 77% (DL1r)
  bool BJetCut(int nbjet);
  
  //BJet Veto. Default BTag wp is 77% (DL1r)
  bool BJetVeto();

  //Individual lepton pt cut. Takes value in GeV.
  bool Lep0PtCut(const float lep0Pt);
  bool Lep1PtCut(const float lep1Pt);
  bool Lep2PtCut(const float lep2Pt);
  bool Lep3PtCut(const float lep3Pt);

  //Check if Lepton 0 is Elec or Muon
  bool isLep0Elec();
  bool isLep0Muon();

  //Check flavor of di lepton pair (lepton_0 & lepton_1)
  bool isMuonPair();
  bool isOFPair();
  bool isElecPair();
  bool isMuElPair();
  bool isElMuPair();

  //Check flavor of lepton_1 and lepton_2
  bool isLep12ElPair();
  bool isLep12MuPair();
  bool isLep12ElMuPair();
  bool isLep12MuElPair();

  //Check di lepton SS or OS pair
  bool isSSPair();
  bool isOSPair();

  //Leading tau selection
  bool OneTauCuts(const std::string& selection);
  
  //DiTau selection
  bool DiTauCuts(const std::string& selection);

  //Leading tau pt cut
  bool OneTauPtCut(const float taupt);
  
  //DiTau pt cuts
  bool DiTauPtCuts(const float tau0pt, const float tau1pt);

  //Opposite sign tau pair
  bool OSTauPair();

  //Same sign tau pair
  bool SSTauPair();

  //Tau OS to lep
  bool isTauOSToLep();
  
  //Z mass veto
  bool ZVeto(const std::string& channel);
  
  //Mll01 for same-flavor leptons, takes value in GeV
  bool Mll01SFCut(const float mllcut);

  //Mll01 cut, takes value in GeV
  bool Mll01Cut(const float mllcut);

  //MET cut, takes value in GeV
  bool METCut(const float met);

};

#endif
