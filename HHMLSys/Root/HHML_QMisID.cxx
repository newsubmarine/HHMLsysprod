#include "HHMLSys/HHMLSys_EventSaver.h"



//--------------------------------------------------------------------------------------------
void HHMLSys_EventSaver::getQMisIdRates(TH3D* rate_map, TH1D* proj_Eta, TH1D* proj_Pt, TH1D* proj_R,
			    float eta, float pt, float rg,
			    float& r, float& r_up, float& r_dn )
{
  Double_t this_low_edge(-999.0),this_up_edge(-999.0);
  int xbin_nr(-1), ybin_nr(-1), zbin_nr(-1);
  
  // Loop over the projections, and keep track of the bin number where (x,y) is found
  
  for(int xbin = 0; xbin < proj_Eta->GetNbinsX()+1; ++xbin)
    {
      this_low_edge = proj_Eta->GetXaxis()->GetBinLowEdge(xbin);
      this_up_edge  = proj_Eta->GetXaxis()->GetBinLowEdge(xbin+1);

      if(fabs(eta) >= this_low_edge && fabs(eta) < this_up_edge)
	{
	  xbin_nr = proj_Eta->GetBin(xbin);
	  break;
	}
    }
  
  for(int ybin = 0; ybin < proj_Pt->GetNbinsX()+1; ++ybin)
    {
      this_low_edge = proj_Pt->GetXaxis()->GetBinLowEdge(ybin);
      this_up_edge  = proj_Pt->GetXaxis()->GetBinLowEdge(ybin+1);
      
      if( pt >= this_low_edge && pt < this_up_edge )
	{
	  ybin_nr = proj_Pt->GetBin(ybin);
	  break;
	}
    }

    for(int zbin = 0; zbin < proj_Pt->GetNbinsZ()+1; ++zbin)
    {
      this_low_edge = proj_R->GetXaxis()->GetBinLowEdge(zbin);
      this_up_edge  = proj_R->GetXaxis()->GetBinLowEdge(zbin+1);
      
      if( rg >= this_low_edge && rg < this_up_edge )
	{
	  zbin_nr = proj_R->GetBin(zbin);
	  break;
	}
    }


  // Now get the NOMINAL rate via global bin number (x,y)

  r = rate_map->GetBinContent( rate_map->GetBin( xbin_nr, ybin_nr, zbin_nr) );
  
  r_up = r + rate_map->GetBinErrorUp( rate_map->GetBin( xbin_nr, ybin_nr, zbin_nr ) );
  r_dn = r - rate_map->GetBinErrorUp( rate_map->GetBin( xbin_nr, ybin_nr, zbin_nr ) );
  r_dn = ( r_dn > 0.0 ) ? r_dn : 0.0;

}

//---------------------------------------------------------------------------------------------------
void HHMLSys_EventSaver::calcQMisIdWeights(float &weight_Nom, float &weight_Up, float &weight_Dn)
{

  if( !ntup.dilep_type ) return;
  if(isMuonPair()) return;

  float Pt0(-999.0), Eta0(999.0), Pt1(-999.0), Eta1(999.0);
  int R0(-1), R1(-1);

  //r0 and r1 Up & Dn as well must be initialize with 0 and not with any other number.  
  float r0(0.0), r0_up(0.0), r0_dn(0.0), 
        r1(0.0), r1_up(0.0), r1_dn(0.0);

  Pt0  = ntup.lep_Pt_0/GeV;
  Pt1  = ntup.lep_Pt_1/GeV;

  Eta0 = std::fabs(ntup.lep_Eta_0);
  Eta1 = std::fabs(ntup.lep_Eta_1);

  R0   = QMisID_Region_Lep0();
  //TH1D* proj_eta_T  = hist_QMisID_T->ProjectionX("proj_eta_T");
  //TH1D* proj_pt_T   = hist_QMisID_T->ProjectionY("proj_pt_T");
  
  // Tight or Anti-tight
  bool  is_lep_0_tight(false), is_lep_1_tight(false);
  
  if(QMisID_Tight_Lep0){
    
    is_lep_0_tight = true;
    TH1D* proj_eta  = hist_QMisID_T->ProjectionX("proj_eta");
    TH1D* proj_pt   = hist_QMisID_T->ProjectionY("proj_pt" );
    TH1D* proj_rg   = hist_QMisID_T->ProjectionZ("proj_rg" );
    getQMisIdRates(hist_QMisID_T, proj_eta, proj_pt, proj_rg, Eta0, Pt0, R0, r0, r0_up, r0_dn);

  }
  else{

    is_lep_0_tight = false;
    TH1D* proj_eta  = hist_QMisID_AT->ProjectionX("proj_eta");
    TH1D* proj_pt   = hist_QMisID_AT->ProjectionY("proj_pt" );
    TH1D* proj_rg   = hist_QMisID_AT->ProjectionZ("proj_rg" );
    getQMisIdRates(hist_QMisID_AT, proj_eta, proj_pt, proj_rg, Eta0, Pt0, R0, r0, r0_up, r0_dn);

  }
    
  if(QMisID_Tight_Lep1){
    
    is_lep_1_tight = true;
    TH1D* proj_eta  = hist_QMisID_T->ProjectionX("proj_eta");
    TH1D* proj_pt   = hist_QMisID_T->ProjectionY("proj_pt" );
    TH1D* proj_rg   = hist_QMisID_T->ProjectionZ("proj_rg" );
    getQMisIdRates(hist_QMisID_T, proj_eta, proj_pt, proj_rg, Eta1, Pt1, R1, r1, r1_up, r1_dn);

  }
  else{

    is_lep_1_tight = false;
    TH1D* proj_eta  = hist_QMisID_AT->ProjectionX("proj_eta");
    TH1D* proj_pt   = hist_QMisID_AT->ProjectionY("proj_pt" );
    TH1D* proj_rg   = hist_QMisID_AT->ProjectionZ("proj_rg" );

    getQMisIdRates(hist_QMisID_AT, proj_eta, proj_pt, proj_rg, Eta1, Pt1, R1, r1, r1_up, r1_dn);

  }
  




  //getQMisIdRates(hist_QMisID_T, proj_eta_T, proj_pt_T, Eta0, Pt0, r0, r0_up, r0_dn);
  //getQMisIdRates(hist_QMisID_T, proj_eta_T, proj_pt_T, Eta1, Pt1, r1, r1_up, r1_dn);

  if (abs(ntup.lep_ID_0)==13) {
    r0=0;
    r0_up=0;
    r0_dn=0;
  }
  if (abs(ntup.lep_ID_1)==13) {
    r1=0;
    r1_up=0;
    r1_dn=0;
  }

  
  // Event weight + variations
  
  if ( !(std::isnan(r0)) && !(std::isnan(r1)) && !(std::isinf(r0)) && !(std::isinf(r1)) ) {
    
    weight_Nom = ( r0 + r1 - 2.0 * r0 * r1 ) / ( 1.0 - r0 - r1 + 2.0 * r0 * r1 );
    weight_Up  = ( r0_up + r1_up - 2.0 * r0_up * r1_up ) / ( 1.0 - r0_up - r1_up + 2.0 * r0_up * r1_up );
    weight_Dn  = ( r0_dn + r1_dn - 2.0 * r0_dn * r1_dn ) / ( 1.0 - r0_dn - r1_dn + 2.0 * r0_dn * r1_dn );
  }

  delete proj_eta_T;
  delete proj_pt_T;
}

//--------------------------------------------------------------
void HHMLSys_EventSaver::SR2LSS0Tau_QMisIDCuts() {

  isLep2SS0tau_ee_QMisID = false;
  isLep2SS0tau_OF_QMisID = false;

  //ntup.total_charge_QMisID = ntup.total_charge;
  if( !ntup.dilep_type ) return;
  if( !(ntup.GlobalTrigDecision > 0) ) return;
  if( !Tight2LepCuts("2l") ) return;
  if( !LepTrigMatch("SLTorDLT_Tight") ) return;
  if( !DiLepPtCuts(20, 20) ) return;
  if( !(ntup.nTaus_OR_Pt25_RNN == 0) ) return;
  if( !Mll01Cut(12) ) return;
  if( !JetCut(2) ) return;
  if( !BJetVeto() ) return;  
  if( isMuonPair() ) return;

  float weight_Nom(1.0), weight_Up(1.0), weight_Dn(1.0);
  calcQMisIdWeights(weight_Nom, weight_Up, weight_Dn);

  if( isElecPair() ) {
    is2LSS0tau_ee_QMisID = true;
  }
  else if( isOFPair() ) {
    is2LSS0tau_OF_QMisID = true;
  }
}

//-----------------------------------------------
void HHMLSys_EventSaver::getQMisIDWeights() {

  ntup.QMisID_EventWeight    = -99;
  ntup.QMisID_EventWeight_Up = -99;
  ntup.QMisID_EventWeight_Dn = -99;


  if( !m_isData ) return;
  //if( !ntup.passEventCleaning ) return;
  //if( !(SLTrigCuts() || DLTrigCuts()) ) return;
  //if( !ntup.dilep_type ) return;
  //if( !LepTrigMatch("SLTorDLT_Tight") ) return;
  if( !isOSPair() ) return;        //OS pair
  if( isMuonPair() ) return;

  float weight_T_Nom(1.0), weight_T_Up(1.0), weight_T_Dn(1.0);
  calcQMisIdWeights(weight_T_Nom, weight_T_Up, weight_T_Dn);
  
  ntup.QMisID_EventWeight    = weight_T_Nom;
  ntup.QMisID_EventWeight_Up = weight_T_Up;
  ntup.QMisID_EventWeight_Dn = weight_T_Dn;

}

