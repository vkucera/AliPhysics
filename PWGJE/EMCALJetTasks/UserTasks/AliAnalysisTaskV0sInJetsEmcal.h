#ifndef AliAnalysisTaskV0sInJetsEmcal_cxx
#define AliAnalysisTaskV0sInJetsEmcal_cxx

//-------------------------------------------------------------------------
//     task for analysis of V0s (K0S, (anti-)Lambda) in charged jets (+ Xi analysis)
//     fork of AliAnalysisTaskV0sInJets for the EMCal framework
//     Author: Vit Kucera (vit.kucera@cern.ch)                       (Xi analysis added by Ekaterina Grecka)
//-------------------------------------------------------------------------

class TH1D;
class TH2D;
class THnSparse;
class TClonesArray;
class TRandom;

class AliAODv0;
class AliAODVertex;
class AliAODJet;
class AliAODcascade;

class AliJetContainer;
class AliParticleContainer;
class AliClusterContainer;

class AliEventPoolManager;
class AliEventCuts;
#include "AliESDtrackCuts.h"

#include "AliAnalysisTaskEmcalJet.h"

class AliAnalysisTaskV0sInJetsEmcal : public AliAnalysisTaskEmcalJet
{
public:
  AliAnalysisTaskV0sInJetsEmcal(); // Default constructor
  AliAnalysisTaskV0sInJetsEmcal(const char* name); // Constructor
  virtual ~AliAnalysisTaskV0sInJetsEmcal(); // Destructor
  void UserCreateOutputObjects();
  void Terminate(Option_t*) {}

  // data selection
  void SetIsPbPb(Bool_t val = 1) {fbIsPbPb = val;}
  void SetMCAnalysis(Bool_t select = kTRUE) {fbMCAnalysis = select;}
  void SetGeneratorName(TString name) {fsGeneratorName = name;}
  Bool_t IsFromGoodGenerator(Int_t index); // True if the MC particle with the given index comes from the selected generator

  // event selection
  void SetEventCuts(Double_t z = 10, Double_t r = 1, Double_t cL = 0, Double_t cH = 80, Double_t dZ = 0.1, Int_t iNC = 1) {fdCutVertexZ = z; fdCutVertexR2 = r * r; fdCutCentLow = cL; fdCutCentHigh = cH; fdCutDeltaZMax = dZ; fiNContribMin = iNC;}
  void SetUseMultiplicity(Bool_t val = kTRUE) {fbUseMultiplicity = val;}
  void SetCentralityEstimator(TString CentEstimator){fCentEstimator = CentEstimator;};
  void SetUseIonutCut(Bool_t val = kTRUE) {fbUseIonutCut = val;}

  // mixed events
  void SetCorrelations(Bool_t val = kTRUE) {fbCorrelations = val;}
  void SetPoolParam(Int_t sizepool = 1000, Int_t jetsperpool = 1, Float_t fractionmin = 1., Int_t neventsmin = 0) {fiSizePool = sizepool; fiNJetsPerPool = jetsperpool; ffFractionMin = fractionmin; fiNEventsMin = neventsmin;}
  void SetDeltaEtaMax(Double_t val = kTRUE) {fdDeltaEtaMax = val;}

  // jet selection
  void SetJetSelection(Bool_t select = kTRUE) {fbJetSelection = select;}
  void SetPtJetMin(Double_t ptMin = 0) {fdCutPtJetMin = ptMin;}
  void SetPtTrackJetMin(Double_t ptMin = 0) {fdCutPtTrackJetMin = ptMin;}
  void SetAreaPercJetMin(Double_t area = 0) {fdCutAreaPercJetMin = area;}
  void SetDistanceV0JetMax(Double_t val = 0.4) {fdDistanceV0JetMax = val;}
  void SetBgSubtraction(Int_t val = 1) {fiBgSubtraction = val;}

  // pt correlations of jets with trigger tracks
  void SetCompareTriggerTracks(Bool_t val = kTRUE) {fbCompareTriggers = val;}

  void FillQAHistogramV0(AliAODVertex* vtx, const AliAODv0* vZero, Int_t iIndexHisto, Bool_t IsCandK0s, Bool_t IsCandLambda, Bool_t IsCandALambda, Bool_t IsInPeakK0s, Bool_t IsInPeakLambda, Bool_t IsInPeakALambda);
  void FillCandidates(Double_t mK, Double_t mL, Double_t mAL, Bool_t isK, Bool_t isL, Bool_t isAL, Int_t iCut, Int_t iCent);
  Bool_t IsParticleInCone(const AliVParticle* part1, const AliVParticle* part2, Double_t dRMax) const; // decides whether a particle is inside a jet cone
  Bool_t OverlapWithJets(const TClonesArray* array, const AliVParticle* cone, Double_t dDistance) const; // decides whether a cone overlaps with other jets
  AliAODJet* GetRandomCone(const TClonesArray* array, Double_t dEtaConeMax, Double_t dDistance) const; // generate a random cone which does not overlap with selected jets
  AliEmcalJet* GetMedianCluster(AliJetContainer* cont, Double_t dEtaConeMax) const; // get median kt cluster
  Double_t AreaCircSegment(Double_t dRadius, Double_t dDistance) const; // area of circular segment
  Double_t GetD(const AliVParticle* part1, const AliVParticle* part2) const; // returns distance between two particles

  // V0 selection
  void SetCutTPCRefit(Bool_t val = kTRUE) {fbTPCRefit = val;}
  void SetCutRejectKinks(Bool_t val = kTRUE) {fbRejectKinks = val;}
  void SetCutFindableClusters(Bool_t val = kTRUE) {fbFindableClusters = val;}
  void SetCutNCrossedRowsTPCMin(Double_t val = 70.) {fdCutNCrossedRowsTPCMin = val;}
  void SetCutCrossedRowsOverFindMin(Double_t val = 0.8) {fdCutCrossedRowsOverFindMin = val;}
  void SetCutCrossedRowsOverFindMax(Double_t val = 1e3) {fdCutCrossedRowsOverFindMax = val;}
  void SetCutPtDaughterMin(Double_t val = 0.150) {fdCutPtDaughterMin = val;}
  void SetCutDCAToPrimVtxMin(Double_t val = 0.1) {fdCutDCAToPrimVtxMin = val;}
  void SetCutDCADaughtersMax(Double_t val = 1.) {fdCutDCADaughtersMax = val;}
  void SetCutEtaDaughterMax(Double_t val = 0.8) {fdCutEtaDaughterMax = val;}
  void SetCutNSigmadEdxMax(Double_t val = 3.) {fdCutNSigmadEdxMax = val;}
  void SetOnFly(Bool_t val = 0) {fbOnFly = val;}
  void SetCutCPAKMin(Double_t val = 0.998) {fdCutCPAKMin = val;}
  void SetCutCPALMin(Double_t val = 0.998) {fdCutCPALMin = val;}
  void SetCutRadiusDecayMin(Double_t val = 5.) {fdCutRadiusDecayMin = val;}
  void SetCutRadiusDecayMax(Double_t val = 100.) {fdCutRadiusDecayMax = val;}
  void SetCutEtaV0Max(Double_t val = 0.7) {fdCutEtaV0Max = val;}
  void SetCutRapV0Max(Double_t val = 0.75) {fdCutRapV0Max = val;}
  void SetCutNTauKMax(Double_t val = 5.0) {fdCutNTauKMax = val;}
  void SetCutNTauLMax(Double_t val = 5.0) {fdCutNTauLMax = val;}
  void SetCutArmPod(Bool_t val = kTRUE) {fbCutArmPod = val;}
  void SetCutArmPodpT(Double_t val = 0.13) {fdCutArmPodpT = val;}
  void SetCutCross(Bool_t val = kTRUE) {fbCutCross = val;}

  void SetCutChi2PerTPCCluster(Double_t val = 2.5) {fdCutChi2PerTPCCluster = val;}
  void SetCutITSTOFtracks(Int_t val = 1) {fdCutITSTOFtracks = val;}
  void SetCutTPCsignalNCut(Int_t val = 50) {fdTPCsignalNCut = val;}
  void SetCutGeo(Bool_t val = 1) {fbGeoCut = val;}
  void SetCutDeadZoneWidth(Float_t val = 3.) {fDeadZoneWidth = val;}
  void SetCutNcrNclLength(Float_t val = 130.) {fNcrNclLength = val;}


  Bool_t IsSelectedForAnalysis();
  Int_t GetCentralityBinIndex(Double_t centrality);
  Int_t GetCentralityBinEdge(Int_t index);
  TString GetCentBinLabel(Int_t index);
  Double_t MassPeakSigmaOld(Double_t pt, Int_t particle);
  static bool CompareClusters(const std::vector<Double_t> cluster1, const std::vector<Double_t> cluster2); // compare clusters by their pt/area
  Double_t GetNormalPhi(Double_t phi) {while(phi >= fgkdDeltaPhiMax) phi -= TMath::TwoPi(); while(phi < fgkdDeltaPhiMin) phi += TMath::TwoPi(); return phi;} // restrict azimuth to desired range

  // upper edges of centrality bins
  static const Int_t fgkiNBinsCent = 1; // number of centrality bins
  static const Int_t fgkiCentBinRanges[fgkiNBinsCent]; // upper edges of centrality bins
  // centrality bins for event mixing
  static const Int_t fgkiNBinsCentMix = 2; // number of centrality bins for event mixing
  static Double_t fgkiCentMixBinRanges[fgkiNBinsCentMix + 1]; // edges of centrality bins for event mixing
  // z_vtx bins for event mixing
  static const Int_t fgkiNBinsZVtxMix = 10; // number of z_vtx bins for event mixing
  static Double_t fgkiZVtxMixBinRanges[fgkiNBinsZVtxMix + 1]; // edges of z_vtx bins for event mixing
  // axis: pT of V0
  static const Double_t fgkdBinsPtV0[2]; // [GeV/c] minimum and maximum or desired binning of the axis (intended for the rebinned axis)
  static const Int_t fgkiNBinsPtV0; // number of bins (intended for the rebinned axis)
  static const Int_t fgkiNBinsPtV0Init; // initial number of bins (uniform binning)
  static const Int_t fgkiNBinsPtV0InitInJet; // initial number of bins for V0s in jets (uniform binning)
  // axis: pT of jets
  static const Double_t fgkdBinsPtJet[2]; // [GeV/c] minimum and maximum or desired binning of the axis (intended for the rebinned axis)
  static const Int_t fgkiNBinsPtJet; // number of bins (intended for the rebinned axis)
  static const Int_t fgkiNBinsPtJetInit; // initial number of bins (uniform binning)
  // axis: K0S invariant mass
  static const Int_t fgkiNBinsMassK0s; // number of bins (uniform binning)
  static const Double_t fgkdMassK0sMin; // minimum K0S mass
  static const Double_t fgkdMassK0sMax; // maximum K0S mass
  // axis: Lambda invariant mass
  static const Int_t fgkiNBinsMassLambda; // number of bins (uniform binning)
  static const Double_t fgkdMassLambdaMin; // minimum Lambda mass
  static const Double_t fgkdMassLambdaMax; // maximum Lambda mass
  // delta phi range
  static const Double_t fgkdDeltaPhiMin; // minimum delta-phi_V0-jet
  static const Double_t fgkdDeltaPhiMax; // maximum delta-phi_V0-jet
//New public functions and parameters for the Xi analysis
//------------------------------------------------------------------------------------------
  void FillCascadeCandidates(Double_t mXi, Double_t mOmega, Bool_t isXiMinus, Bool_t isXiPlus, Bool_t isOmegaMinus, Bool_t isOmegaPlus, Int_t iCut, Int_t iCent);
  void FillQAHistogramXi(AliAODVertex* vtx, const AliAODcascade* cascade, Int_t iIndexHisto,  Bool_t IsCandXiMinus, Bool_t IsCandXiPlus, Bool_t IsCandOmegaMinus, Bool_t IsCandOmegaPlus, Bool_t IsInPeakXi, Bool_t IsInPeakOmega);
  // set functions 
  void SetCutDCACascadeBachToPrimVtxMin(Double_t val = 0.04) {fdCutDCACascadeBachToPrimVtxMin = val;}
  void SetCutDCACascadeV0ToPrimVtxMin(Double_t val = 0.06) {fdCutDCACascadeV0ToPrimVtxMin = val;}
  void SetCutDCACascadeDaughtersToPrimVtxMin(Double_t val = 0.03) {fdCutDCACascadeDaughtersToPrimVtxMin = val;}
  void SetCutDCACascadeV0DaughtersMax(Double_t val = 1.5) {fdCutDCACascadeV0DaughtersMax = val;}
  void SetCutDCACascadeBachToV0Max(Double_t val = 1.3) {fdCutDCACascadeBachToV0Max = val;}
  void SetCutCPACascadeMin(Double_t val = 0.97) {fdCutCPACascadeMin = val;} 
  void SetCutCPACascadeV0Min(Double_t val = 0.97) {fdCutCPACascadeV0Min = val;} 
  void SetCutEtaCascadeMax(Double_t val = 0.7) {fdCutEtaCascadeMax = val;}
  void SetCutEtaCascadeDaughtersMax(Double_t val = 0.8) {fdCutCascadeEtaDaughterMax = val;}
  void SetCutCascadeRadiusDecayMin(Double_t val = 0.6) {fdCutCascadeRadiusDecayMin = val;}
  void SetCutCascadeV0RadiusDecayMin(Double_t val = 1.2) {fdCutCascadeV0RadiusDecayMin = val;}
  void SetCutCascadeV0RadiusDecayMax(Double_t val = 1.2) {fdCutCascadeV0RadiusDecayMax = val;}
  void SetCutNTauXMax(Double_t val = 5.0) {fdCutNTauXMax = val;}
  void SetCutV0MassDiff(Double_t val = 0.005) {fdCutV0MassDiff = val;}
  void SetCutNSigmadEdxMaxCasc(Double_t val = 4.) {fdCutNSigmadEdxMaxCasc = val;}
  
  // axis: Xi invariant mass
  static const Int_t fgkiNBinsMassXi; // number of bins (uniform binning)
  static const Double_t fgkdMassXiMin; // minimum
  static const Double_t fgkdMassXiMax; // maximum  
//------------------------------------------------------------------------------------------
  // axis: Omega invariant mass
  static const Int_t fgkiNBinsMassOmega; // number of bins (uniform binning)
  static const Double_t fgkdMassOmegaMin; // minimum
  static const Double_t fgkdMassOmegaMax; // maximum  
//------------------------------------------------------------------------------------------


protected:
  void ExecOnce();
  Bool_t FillHistograms();
  Bool_t Run();
  virtual Bool_t IsEventSelected();  // override EMCal base method

private:
  AliAODEvent* fAODIn; //! Input AOD event
  AliAODEvent* fAODOut; //! Output AOD event
  AliMCEvent* fEventMC; //! MC event
  AliAODMCHeader* headerMC; //!MC header
  TClonesArray* arrayMC; //!MC particle array
  TRandom* fRandom; //! random-number generator
  AliEventPoolManager* fPoolMgr; //! event pool manager
  AliEventCuts fEventCuts; //! Event cuts class
  TList* fOutputListStd; //! Output list for inclusive analysis results
  TList* fOutputListJet; //! Output list for jet analysis results
  TList* fOutputListQA; //! Output list for quality assurance
  TList* fOutputListCuts; //! Output list for checking cuts
  TList* fOutputListMC; //! Output list for MC related results
//------------------------------------------------------------------------------------------
  TList* fOutputListStdCascade; //! Output list for inclusive analysis results for cascades
  TList* fOutputListJetCascade; //! Output list for jet analysis results for cascades
  TList* fOutputListQACascade; //! Output list for quality assurance for cascades
//------------------------------------------------------------------------------------------

  // Data selection
  Bool_t fbIsPbPb; // switch: Pb+Pb / p+p collisions
  Bool_t fbMCAnalysis; // switch: simulated / real data
  TString fsGeneratorName; // pattern for selecting only V0s from a specific MC generator
  TString fCentEstimator;  //Centrality estimator
  // Event selection
  Double_t fdCutVertexZ; // [cm] maximum |z| of primary vertex
  Double_t fdCutVertexR2; // [cm^2] maximum r^2 of primary vertex
  Double_t fdCutCentLow; // [%] minimum centrality
  Double_t fdCutCentHigh; // [%] maximum centrality
  Double_t fdCutDeltaZMax; // [cm] maximum |Delta z| between nominal prim vtx and SPD vtx
  Int_t fiNContribMin; // minimum number of prim vtx contributors
  Double_t fdCentrality; //! [%] centrality
  Bool_t fbUseMultiplicity; // switch for getting centrality from AliMultSelection instead of from AliCentrality
  Int_t fbUseIonutCut; // Pile up (Ionut's if =2) cut on the correlation between event variables
  // Mixed events parameters
  Bool_t fbCorrelations; // switch for V0-jet correlations
  Int_t fiSizePool; // available number of events per pool, currently ignored in AliEventPoolManager
  Int_t fiNJetsPerPool; // required number of jets available in each pool
  Float_t ffFractionMin; // minimum fraction of fiNJetsPerPool at which pool is ready (default: 1.0)
  Int_t fiNEventsMin; // if non-zero: number of filled events after which pool is ready regardless of fiNJetsPerPool (default: 0)
  Double_t fdDeltaEtaMax; // maximum delta-eta_V0-jet for angular correlations

  // V0 selection
  // Daughter tracks
  Bool_t fbTPCRefit; // (yes) TPC refit for daughter tracks
  Bool_t fbRejectKinks; // (no) reject kink-like production vertices of daughter tracks
  Bool_t fbFindableClusters; // (no) require positive number of findable clusters
  Double_t fdCutNCrossedRowsTPCMin; // (70.) min number of crossed TPC rows
  Double_t fdCutCrossedRowsOverFindMin; // (0.8) min ratio crossed rows / findable clusters
  Double_t fdCutCrossedRowsOverFindMax; // (1e3) max ratio crossed rows / findable clusters
  Double_t fdCutPtDaughterMin; // (0.150) [GeV/c] min transverse momentum of daughter tracks, to reject primaries which do not make it to the TPC
  Double_t fdCutDCAToPrimVtxMin; // (0.1) [cm] min DCA of daughters to the prim vtx
  Double_t fdCutDCADaughtersMax; // (1.) [sigma of TPC tracking] max DCA between daughters
  Double_t fdCutEtaDaughterMax; // (0.8) max |pseudorapidity| of daughter tracks, historical reasons: tracking in MC for 2010 was restricted to 0.7
  Double_t fdCutNSigmadEdxMax; // (3.) [sigma dE/dx] max difference between measured and expected signal of dE/dx in the TPC
  Double_t fdCutChi2PerTPCCluster; //(2.5) maximum daughters Chi2 per TPC Cluster 
  Int_t fdCutITSTOFtracks; //(1)  minimum number of tracks with ITS refit or hit in TOF
  Int_t fdTPCsignalNCut; //(50) minimum number of points in TPC (track length)
  Bool_t fbGeoCut; //1.
  AliESDtrackCuts fESDTrackCuts;
  Float_t fDeadZoneWidth;                              //
  Float_t fNcrNclLength;                               //

  // V0 candidate
  Bool_t fbOnFly; // (0) on-the-fly (yes) or offline (no) reconstructed
  Double_t fdCutCPAKMin; // (0.998) min cosine of the pointing angle, K0S
  Double_t fdCutCPALMin; // (0.998) min cosine of the pointing angle, Lambda
  Double_t fdCutRadiusDecayMin; // (5.) [cm] min radial distance of the decay vertex
  Double_t fdCutRadiusDecayMax; // (100.) [cm] max radial distance of the decay vertex
  Double_t fdCutEtaV0Max; // (0.7) max |pseudorapidity| of V0
  Double_t fdCutRapV0Max; // (0.75) max |rapidity| of V0 (turned off)
  Double_t fdCutNTauKMax; // (5.0) [tau] max proper lifetime in multiples of the mean lifetime, K0S
  Double_t fdCutNTauLMax; // (5.0) [tau] max proper lifetime in multiples of the mean lifetime, Lambda
  Bool_t fbCutArmPod; // (yes) Armenteros-Podolanski for K0S
  Double_t fdCutArmPodpT; //(0.13) GeV/c Armenteros-Podolanski for K0S only in pT (for spectra comparison with LF)
  Bool_t fbCutCross; // (no) cross-contamination

  // Jet selection
  Bool_t fbJetSelection; // (yes) switch for the analysis of V0s in jets
  Double_t fdCutPtJetMin; // [GeV/c] minimum jet pt
  Double_t fdCutPtTrackJetMin; // [GeV/c] minimum pt of leading jet-track
  Double_t fdCutAreaPercJetMin; // [pi*R^2] minimum jet area with respect to the expected value
  Double_t fdDistanceV0JetMax; // (R) D - maximum distance between V0 and jet axis used for finding V0s in the jet cone
  Int_t fiBgSubtraction; // subtraction of rho from jet pt, 0 - no subtraction, 1 - scalar subtraction, 2 - vector subtraction

  // Correlations of pt_jet with pt_trigger-track
  Bool_t fbCompareTriggers; // switch for pt correlations of jets with trigger tracks

  // EMCal containers
  AliJetContainer* fJetsCont; //! Signal Jets
  AliJetContainer* fJetsBgCont; //! Background Jets
  AliTrackContainer* fTracksCont; //! Tracks

  // event histograms
  TH1D* fh1EventCounterCut; //! number of events for different selection steps
  TH1D* fh1EventCounterCutCent[fgkiNBinsCent]; //! number of events for different selection steps and different centralities
  TH1D* fh1EventCent; //! number of events for different centralities
  TH1D* fh1EventCent2; //! number of events for different centralities
  TH1D* fh1EventCent2Jets; //! number of events for different centralities
  TH1D* fh1EventCent2NoJets; //! number of events for different centralities
  TH2D* fh2EventCentTracks; //! number of tracks vs centrality
  TH2D* fh2EventCentMult; //! reference multiplicity vs centrality
  TH1D* fh1VtxZ[fgkiNBinsCent]; //! z coordinate of the primary vertex
  TH1D* fh1VtxZME[fgkiNBinsCent]; //! z coordinate of the primary vertex for events used in mixed events
  TH2D* fh2VtxXY[fgkiNBinsCent]; //! xy coordinates of the primary vertex
  TH1D* fh1V0CandPerEvent; //! number of V0 cand per event

  // jet histograms
  TH1D* fh1PtJet[fgkiNBinsCent]; //! pt spectra of jets for normalisation of in-jet V0 spectra
  TH1D* fh1EtaJet[fgkiNBinsCent]; //! jet eta
  TH2D* fh2EtaPtJet[fgkiNBinsCent]; //! jet eta-pT
  TH1D* fh1PhiJet[fgkiNBinsCent]; //! jet phi
  TH2D* fh2PtJetPtTrackLeading[fgkiNBinsCent]; //! pt_jet; pt of leading jet track
  TH2D* fh2PtJetPtTrigger[fgkiNBinsCent]; //! pt_jet; pt of trigger track
  TH1D* fh1PtTrigger[fgkiNBinsCent]; //! pt of trigger track
  TH1D* fh1NJetPerEvent[fgkiNBinsCent]; //! number of jets per event
  TH1D* fh1NRndConeCent; //! number of generated random cones in centrality bins
  TH2D* fh2EtaPhiRndCone[fgkiNBinsCent]; //! random cone eta-pT
  TH1D* fh1NMedConeCent; //! number of found median-cluster cones in centrality bins
  TH2D* fh2EtaPhiMedCone[fgkiNBinsCent]; //! median-cluster cone eta-phi
  TH1D* fh1AreaExcluded; //! area of excluded cones for outside-cones V0s
  TH1D* fh1DistanceJets[fgkiNBinsCent]; //! distance in eta-phi between jets within events
  TH1D* fh1DistanceV0JetsK0s[fgkiNBinsCent]; //! distance in eta-phi between V0 and the closest jet
  TH1D* fh1DistanceV0JetsLambda[fgkiNBinsCent]; //! distance in eta-phi between V0 and the closest jet
  TH1D* fh1DistanceV0JetsALambda[fgkiNBinsCent]; //! distance in eta-phi between V0 and the closest jet

  static const Int_t fgkiNCategV0 = 18; // number of V0 selection steps

  // QA histograms
  static const Int_t fgkiNQAIndeces = 2; // 0 - before cuts, 1 - after cuts
  TH1D* fh1QAV0Status[fgkiNQAIndeces]; //! online vs offline reconstructed V0 candidates
  TH1D* fh1QAV0TPCRefit[fgkiNQAIndeces]; //! TPC refit on vs off
  TH1D* fh1QAV0TPCRows[fgkiNQAIndeces]; //! crossed TPC pad rows
  TH1D* fh1QAV0TPCFindable[fgkiNQAIndeces]; //! findable clusters
  TH2D* fh2QAV0PtNCls[fgkiNQAIndeces]; //! pt vs TPC clusters
  TH2D* fh2QAV0PtChi[fgkiNQAIndeces]; //! pt vs Chi2/ndf
  TH1D* fh1QAV0TPCRowsFind[fgkiNQAIndeces]; //! ratio rows/clusters
  TH1D* fh1QAV0Eta[fgkiNQAIndeces]; //! pseudorapidity
  TH2D* fh2QAV0EtaRows[fgkiNQAIndeces]; //! pseudorapidity vs TPC rows
  TH2D* fh2QAV0PtRows[fgkiNQAIndeces]; //! pt vs TPC rows
  TH2D* fh2QAV0PhiRows[fgkiNQAIndeces]; //! azimuth vs TPC rows
  TH2D* fh2QAV0NClRows[fgkiNQAIndeces]; //! clusters vs TPC rows
  TH2D* fh2QAV0EtaNCl[fgkiNQAIndeces]; //! pseudorapidity vs clusters

  // K0s
  TH1D* fh1V0CounterCentK0s[fgkiNBinsCent]; //! number of K0s candidates after various cuts
  TH1D* fh1V0InvMassK0sAll[fgkiNCategV0]; //! V0 invariant mass for each selection steps
  TH2D* fh2QAV0EtaPtK0sPeak[fgkiNQAIndeces]; //! daughters pseudorapidity vs V0 pt, in mass peak
  TH2D* fh2QAV0EtaEtaK0s[fgkiNQAIndeces]; //! daughters pseudorapidity vs pseudorapidity
  TH2D* fh2QAV0PhiPhiK0s[fgkiNQAIndeces]; //! daughters azimuth vs azimuth
  TH1D* fh1QAV0RapK0s[fgkiNQAIndeces]; //! V0 rapidity
  TH2D* fh2QAV0PtPtK0sPeak[fgkiNQAIndeces]; //! daughters pt vs pt, in mass peak
  TH2D* fh2ArmPodK0s[fgkiNQAIndeces]; //! Armenteros-Podolanski
  TH1D* fh1V0CandPerEventCentK0s[fgkiNBinsCent]; //! number of K0s candidates per event, in centrality bins
  TH1D* fh1V0InvMassK0sCent[fgkiNBinsCent]; //! V0 invariant mass, in centrality bins
  // K0s Inclusive
  THnSparse* fhnV0InclusiveK0s[fgkiNBinsCent]; //! V0 inclusive, in a centrality bin, m_V0; pt_V0; eta_V0
  // K0s Cones
  THnSparse* fhnV0InJetK0s[fgkiNBinsCent]; //! V0 in jet cones, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet
  THnSparse* fhnV0InPerpK0s[fgkiNBinsCent]; //! V0 in perpendicular cones, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet
  THnSparse* fhnV0InRndK0s[fgkiNBinsCent]; //! V0 in random cones, in a centrality bin, m_V0; pt_V0; eta_V0
  THnSparse* fhnV0InMedK0s[fgkiNBinsCent]; //! V0 in medium cones, in a centrality bin, m_V0; pt_V0; eta_V0
  THnSparse* fhnV0OutJetK0s[fgkiNBinsCent]; //! V0 outside jet cones, in a centrality bin, m_V0; pt_V0; eta_V0
  THnSparse* fhnV0NoJetK0s[fgkiNBinsCent]; //! V0 in no-jet events, in a centrality bin, m_V0; pt_V0; eta_V0

  THnSparse* fhnPtDaughterK0s[fgkiNBinsCent]; //! pt correlations, in a centrality bin, pt_neg-daughter;pt_pos-daughter;pt_V0;pt_jet;pt_leading-track

  // K0S correlations
  THnSparse* fhnV0CorrelSEK0s[fgkiNBinsCent]; //! V0-jet phi,eta correlations in same events, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet; delta-phi_V0-jet; delta-eta_V0-jet; delta R_V0-jet
  THnSparse* fhnV0CorrelMEK0s[fgkiNBinsCent]; //! V0-jet phi,eta correlations in mixed events, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet; delta-phi_V0-jet; delta-eta_V0-jet

  TH2D* fh2V0PtJetAngleK0s[fgkiNBinsCent]; //! pt jet vs angle V0-jet, in centrality bins
  // MC histograms
  // inclusive
  TH1D* fh1V0K0sPtMCGen[fgkiNBinsCent]; //! pt spectrum of all generated K0s in event
  TH2D* fh2V0K0sCentMCGen[fgkiNBinsCent];  //! centrality of all generated K0s in event
  TH2D* fh2V0K0sPtMassMCRec[fgkiNBinsCent]; //! pt-mass spectrum of successfully reconstructed K0s in event
  TH1D* fh1V0K0sPtMCRecFalse[fgkiNBinsCent]; //! pt spectrum of false reconstructed K0s in event
  // inclusive eta-pT efficiency
  TH2D* fh2V0K0sEtaPtMCGen[fgkiNBinsCent]; //! eta-pt spectrum of all generated K0s in event
  THnSparse* fh3V0K0sEtaPtMassMCRec[fgkiNBinsCent]; //! eta-pt-mass spectrum of successfully reconstructed K0s in event
  // MC daughter eta inclusive
  THnSparse* fhnV0K0sInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! V0 inclusive, reconstructed: charge_daughter; eta_daughter; pt_daughter; eta_V0; pt_V0; pt_jet
  // in jets
  TH2D* fh2V0K0sInJetPtMCGen[fgkiNBinsCent]; //! pt spectrum of generated K0s in jet
  THnSparse* fh3V0K0sInJetPtMassMCRec[fgkiNBinsCent]; //! mass-pt spectrum of successfully reconstructed K0s in jet
  // in jets eta-pT efficiency
  THnSparse* fh3V0K0sInJetEtaPtMCGen[fgkiNBinsCent]; //! eta-pt spectrum of generated K0s in jet
  THnSparse* fh4V0K0sInJetEtaPtMassMCRec[fgkiNBinsCent]; //! mass-eta-pt spectrum of successfully reconstructed K0s in jet
  // MC daughter eta in JC
  THnSparse* fhnV0K0sInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! V0 in jets, reconstructed: charge_daughter; eta_daughter; pt_daughter; eta_V0; pt_V0; pt_jet

  // resolution
  TH2D* fh2V0K0sMCResolMPt[fgkiNBinsCent]; //! K0s mass resolution vs pt
  TH2D* fh2V0K0sMCPtGenPtRec[fgkiNBinsCent]; //! K0s generated pt vs reconstructed pt

  // Lambda
  TH1D* fh1V0CounterCentLambda[fgkiNBinsCent]; //! number of Lambda candidates after various cuts
  TH1D* fh1V0InvMassLambdaAll[fgkiNCategV0]; //!
  TH2D* fh2QAV0EtaPtLambdaPeak[fgkiNQAIndeces]; //!
  TH2D* fh2QAV0EtaEtaLambda[fgkiNQAIndeces]; //!
  TH2D* fh2QAV0PhiPhiLambda[fgkiNQAIndeces]; //!
  TH1D* fh1QAV0RapLambda[fgkiNQAIndeces]; //!
  TH2D* fh2QAV0PtPtLambdaPeak[fgkiNQAIndeces]; //!
  TH2D* fh2ArmPodLambda[fgkiNQAIndeces]; //!
  TH1D* fh1V0CandPerEventCentLambda[fgkiNBinsCent]; //!
  TH1D* fh1V0InvMassLambdaCent[fgkiNBinsCent]; //!
  // Lambda Inclusive
  THnSparse* fhnV0InclusiveLambda[fgkiNBinsCent]; //!
  // Lambda Cones
  THnSparse* fhnV0InJetLambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0InPerpLambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0InRndLambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0InMedLambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0OutJetLambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0NoJetLambda[fgkiNBinsCent]; //!

  THnSparse* fhnPtDaughterLambda[fgkiNBinsCent]; //! pt correlations, in a centrality bin, pt_neg-daughter;pt_pos-daughter;pt_V0;pt_jet;pt_leading-track

  // Lambda correlations
  THnSparse* fhnV0CorrelSELambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0CorrelMELambda[fgkiNBinsCent]; //!

  TH2D* fh2V0PtJetAngleLambda[fgkiNBinsCent]; //!
  // MC histograms
  // inclusive
  TH1D* fh1V0LambdaPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2V0LambdaCentMCGen[fgkiNBinsCent];  //! 
  TH2D* fh2V0LambdaPtMassMCRec[fgkiNBinsCent]; //!
  TH1D* fh1V0LambdaPtMCRecFalse[fgkiNBinsCent]; //!
  // inclusive eta-pT efficiency
  TH2D* fh2V0LambdaEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3V0LambdaEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta inclusive
  THnSparse* fhnV0LambdaInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! V0 inclusive, reconstructed: charge_daughter; eta_daughter; pt_daughter; eta_V0; pt_V0; pt_jet
  // in jets
  TH2D* fh2V0LambdaInJetPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3V0LambdaInJetPtMassMCRec[fgkiNBinsCent]; //!
  // in jets eta-pT efficiency
  THnSparse* fh3V0LambdaInJetEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh4V0LambdaInJetEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta in JC
  THnSparse* fhnV0LambdaInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! V0 in jets, reconstructed: charge_daughter; eta_daughter; pt_daughter; eta_V0; pt_V0; pt_jet

  // resolution
  TH2D* fh2V0LambdaMCResolMPt[fgkiNBinsCent]; //!
  TH2D* fh2V0LambdaMCPtGenPtRec[fgkiNBinsCent]; //!
  // feed-down
  THnSparse* fhnV0LambdaInclMCFromXi[fgkiNBinsCent]; //!
  THnSparse* fhnV0LambdaInclMCFromXi0[fgkiNBinsCent]; //!
  THnSparse* fhnV0LambdaInJetsMCFD[fgkiNBinsCent]; //!
  THnSparse* fhnV0LambdaBulkMCFD[fgkiNBinsCent]; //!
  TH2D* fh1V0XiPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh1V0Xi0PtMCGen[fgkiNBinsCent]; //!

  // ALambda
  TH1D* fh1V0CounterCentALambda[fgkiNBinsCent]; //! number of ALambda candidates after various cuts
  TH1D* fh1V0InvMassALambdaAll[fgkiNCategV0]; //!
  TH2D* fh2QAV0EtaPtALambdaPeak[fgkiNQAIndeces]; //!
  TH2D* fh2QAV0EtaEtaALambda[fgkiNQAIndeces]; //!
  TH2D* fh2QAV0PhiPhiALambda[fgkiNQAIndeces]; //!
  TH1D* fh1QAV0RapALambda[fgkiNQAIndeces]; //!
  TH2D* fh2QAV0PtPtALambdaPeak[fgkiNQAIndeces]; //!
  TH2D* fh2ArmPodALambda[fgkiNQAIndeces]; //!
  TH1D* fh1V0CandPerEventCentALambda[fgkiNBinsCent]; //!
  TH1D* fh1V0InvMassALambdaCent[fgkiNBinsCent]; //!
  // ALambda Inclusive
  THnSparse* fhnV0InclusiveALambda[fgkiNBinsCent]; //!
  // ALambda Cones
  THnSparse* fhnV0InJetALambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0InPerpALambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0InRndALambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0InMedALambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0OutJetALambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0NoJetALambda[fgkiNBinsCent]; //!

  THnSparse* fhnPtDaughterALambda[fgkiNBinsCent]; //! pt correlations, in a centrality bin, pt_neg-daughter;pt_pos-daughter;pt_V0;pt_jet;pt_leading-track

  // ALambda correlations
  THnSparse* fhnV0CorrelSEALambda[fgkiNBinsCent]; //!
  THnSparse* fhnV0CorrelMEALambda[fgkiNBinsCent]; //!


  TH2D* fh2V0PtJetAngleALambda[fgkiNBinsCent]; //!
  // MC histograms
  // inclusive
  TH1D* fh1V0ALambdaPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2V0ALambdaCentMCGen[fgkiNBinsCent];  //! 
  TH2D* fh2V0ALambdaPtMassMCRec[fgkiNBinsCent]; //!
  TH1D* fh1V0ALambdaPtMCRecFalse[fgkiNBinsCent]; //!
  // inclusive eta-pT efficiency
  TH2D* fh2V0ALambdaEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3V0ALambdaEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta inclusive
  THnSparse* fhnV0ALambdaInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! V0 inclusive, reconstructed: charge_daughter; eta_daughter; pt_daughter; eta_V0; pt_V0; pt_jet
  // in jets
  TH2D* fh2V0ALambdaInJetPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3V0ALambdaInJetPtMassMCRec[fgkiNBinsCent]; //!
  // in jets eta-pT efficiency
  THnSparse* fh3V0ALambdaInJetEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh4V0ALambdaInJetEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta in JC
  THnSparse* fhnV0ALambdaInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! V0 in jets, reconstructed: charge_daughter; eta_daughter; pt_daughter; eta_V0; pt_V0; pt_jet

  // resolution
  TH2D* fh2V0ALambdaMCResolMPt[fgkiNBinsCent]; //!
  TH2D* fh2V0ALambdaMCPtGenPtRec[fgkiNBinsCent]; //!
  // feed-down
  THnSparse* fhnV0ALambdaInclMCFromAXi[fgkiNBinsCent]; //!
  THnSparse* fhnV0ALambdaInclMCFromAXi0[fgkiNBinsCent]; //!
  THnSparse* fhnV0ALambdaInJetsMCFD[fgkiNBinsCent]; //!
  THnSparse* fhnV0ALambdaBulkMCFD[fgkiNBinsCent]; //!
  TH2D* fh1V0AXiPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh1V0AXi0PtMCGen[fgkiNBinsCent]; //!

  TH2D* fh2QAV0PhiPtK0sPeak[fgkiNQAIndeces]; //! K0S candidate in peak: azimuth; pt
  TH2D* fh2QAV0PhiPtLambdaPeak[fgkiNQAIndeces]; //! Lambda candidate in peak: azimuth; pt
  TH2D* fh2QAV0PhiPtALambdaPeak[fgkiNQAIndeces]; //! anti-Lambda candidate in peak: azimuth; pt
  TH1D* fh1QAV0Pt[fgkiNQAIndeces]; //! pt daughter
  TH1D* fh1QAV0Charge[fgkiNQAIndeces]; //! charge
  TH1D* fh1QAV0DCAVtx[fgkiNQAIndeces]; //! DCA of daughters to prim vtx
  TH1D* fh1QAV0DCAV0[fgkiNQAIndeces]; //! DCA between daughters
  TH1D* fh1QAV0Cos[fgkiNQAIndeces]; //! cosine of pointing angle (CPA)
  TH1D* fh1QAV0R[fgkiNQAIndeces]; //! radial distance between prim vtx and decay vertex
  TH1D* fh1QACTau2D[fgkiNQAIndeces]; //! lifetime calculated in xy
  TH1D* fh1QACTau3D[fgkiNQAIndeces]; //! lifetime calculated in xyz
  TH2D* fh2ArmPod[fgkiNQAIndeces]; //! Armenteros-Podolanski
  TH2D* fh2CCK0s; //! K0s candidates in Lambda peak
  TH2D* fh2CCLambda; //! Lambda candidates in K0s peak
  THnSparse* fh3CCMassCorrelBoth; //! mass correlation of candidates
  THnSparse* fh3CCMassCorrelKNotL; //! mass correlation of candidates
  THnSparse* fh3CCMassCorrelLNotK; //! mass correlation of candidates

  // Cut tuning
  // crossed/findable, daughter pt, dca, cpa, r, pseudorapidity, y, decay length, PID sigma
  TH2D* fh2CutTPCRowsK0s[fgkiNQAIndeces]; //! inv mass vs TPC rows
  TH2D* fh2CutTPCRowsLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutPtPosK0s[fgkiNQAIndeces]; //! inv mass vs pt of positive daughter
  TH2D* fh2CutPtNegK0s[fgkiNQAIndeces]; //! inv mass vs pt of negative daughter
  TH2D* fh2CutPtPosLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutPtNegLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutDCAVtx[fgkiNQAIndeces]; //! inv mass vs DCA of daughters to prim vtx
  TH2D* fh2CutDCAV0[fgkiNQAIndeces]; //! inv mass vs DCA between daughters
  TH2D* fh2CutCos[fgkiNQAIndeces]; //! inv mass vs CPA
  TH2D* fh2CutR[fgkiNQAIndeces]; //! inv mass vs R
  TH2D* fh2CutEtaK0s[fgkiNQAIndeces]; //! inv mass vs pseudorapidity
  TH2D* fh2CutEtaLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutRapK0s[fgkiNQAIndeces]; //! inv mass vs rapidity
  TH2D* fh2CutRapLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutCTauK0s[fgkiNQAIndeces]; //! inv mass vs lifetime
  TH2D* fh2CutCTauLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutPIDPosK0s[fgkiNQAIndeces]; //! inv mass vs number of dE/dx sigmas for positive daughter
  TH2D* fh2CutPIDNegK0s[fgkiNQAIndeces]; //! inv mass vs number of dE/dx sigmas for negative daughter
  TH2D* fh2CutPIDPosLambda[fgkiNQAIndeces]; //!
  TH2D* fh2CutPIDNegLambda[fgkiNQAIndeces]; //!
  TH2D* fh2Tau3DVs2D[fgkiNQAIndeces]; //! pt vs ratio 3D lifetime / 2D lifetime

//New private parameters and histograms for the Xi selection
//------------------------------------------------------------------------------------------
  Double_t fdCutDCACascadeBachToPrimVtxMin; // [cm] min DCA of bachelor track to the prim vtx
  Double_t fdCutDCACascadeV0ToPrimVtxMin;   // [cm] min DCA of V0 (from cascade decay) to the prim vtx
  Double_t fdCutDCACascadeDaughtersToPrimVtxMin; // [cm] min DCA of daughters (from secondary V0 decay) to the prim vtx
  Double_t fdCutDCACascadeV0DaughtersMax; // 1.5; // [sigma of TPC tracking] max DCA between Cascade V0 daughters
  Double_t fdCutDCACascadeBachToV0Max; // 1.3; // [cm] max DCA between bachelor track to V0   
  Double_t fdCutCPACascadeMin;   // min cosine of the pointing angle of the cascade
  Double_t fdCutCPACascadeV0Min; // min cosine of the pointing angle of the V0 in the cascade
  Double_t fdCutEtaCascadeMax; // (0.7) max |pseudorapidity| of Cascade
  Double_t fdCutCascadeEtaDaughterMax; //(0.8) max |pseudorapidity| of Cascade daughter tracks
  Double_t fdCutCascadeRadiusDecayMin; //(0.6) min cascade decay radius
  Double_t fdCutCascadeV0RadiusDecayMin; //(1.2) min V0 from cascade decay radius
  Double_t fdCutCascadeV0RadiusDecayMax; //(100.) max V0 from cascade decay radius

  Double_t fdCutNTauXMax; // (5.0) [tau] max proper lifetime in multiples of the mean lifetime, Xi
  Double_t fdCutV0MassDiff; //(0.005) [GeV] V0 daughter mass difference from Lambda mass
  Double_t fdCutNSigmadEdxMaxCasc; //(4.0)
 
  static const Int_t fgkiNCategCascade = 22; // number of Cascade selection steps  
  //Histograms 
  TH1D* fh1CascadeCandPerEvent; //! number of Cascade cand per event
   //QA 
  TH1D* fh1QACascadeStatus[fgkiNQAIndeces]; //! online vs offline reconstructed Cascade candidates
  TH1D* fh1QACascadeTPCRefit[fgkiNQAIndeces]; //! TPC refit on vs off
  TH1D* fh1QACascadeTPCRows[fgkiNQAIndeces]; //! crossed TPC pad rows
  TH1D* fh1QACascadeTPCFindable[fgkiNQAIndeces]; //! findable clusters
  TH1D* fh1QACascadeTPCRowsFind[fgkiNQAIndeces]; //! ratio rows/clusters
  TH1D* fh1QACascadeEta[fgkiNQAIndeces]; //! pseudorapidity
  TH2D* fh2QACascadeEtaRows[fgkiNQAIndeces]; //! pseudorapidity vs TPC rows
  TH2D* fh2QACascadePtRows[fgkiNQAIndeces]; //! pt vs TPC rows
  TH2D* fh2QACascadePhiRows[fgkiNQAIndeces]; //! azimuth vs TPC rows
  TH2D* fh2QACascadeNClRows[fgkiNQAIndeces]; //! clusters vs TPC rows
  TH2D* fh2QACascadeEtaNCl[fgkiNQAIndeces]; //! pseudorapidity vs clusters
  // XiMinus
  //-------------------------
  TH1D* fh1CascadeCounterCentXiMinus[fgkiNBinsCent]; //! number of Xi candidates after various cuts
  TH1D* fh1CascadeInvMassXiMinusAll[fgkiNCategCascade]; //! 
  TH2D* fh2QACascadeEtaPtXiMinusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadeEtaEtaXiMinus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePhiPhiXiMinus[fgkiNQAIndeces]; //!
  TH1D* fh1QACascadeRapXiMinus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePtPtXiMinusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2ArmPodXiMinus[fgkiNQAIndeces]; //! ??
  TH1D* fh1CascadeCandPerEventCentXiMinus[fgkiNBinsCent]; //!
  TH1D* fh1CascadeInvMassXiMinusCent[fgkiNBinsCent]; //!
  // XiMinus Inclusive
  THnSparse* fhnCascadeInclusiveXiMinus[fgkiNBinsCent]; //!
  // XiMinus Cones
  THnSparse* fhnCascadeInJetXiMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInPerpXiMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInRndXiMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInMedXiMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeOutJetXiMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeNoJetXiMinus[fgkiNBinsCent]; //!
  TH2D* fh2CascadePtJetAngleXiMinus[fgkiNBinsCent]; //!
  TH1D* fh1DCAInXiMinus[fgkiNBinsCent]; //!
  TH1D* fh1DCAOutXiMinus[fgkiNBinsCent]; //! 
  // MC histograms
  // inclusive
  TH1D* fh1CascadeXiMinusPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiMinusCentMCGen[fgkiNBinsCent];  //! 
  TH1D* fh1CascadeXiMinusPtMCRec[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiMinusPtMassMCRec[fgkiNBinsCent]; //!
  TH1D* fh1CascadeXiMinusPtMCRecFalse[fgkiNBinsCent]; //!
  // inclusive eta-pT efficiency
  TH2D* fh2CascadeXiMinusEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeXiMinusEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta inclusive  //  THnSparse* fhnCascadeXiMinusInclDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade generated
  THnSparse* fhnCascadeXiMinusInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade reconstructed
  // in jets
  TH2D* fh2CascadeXiMinusInJetPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiMinusInJetPtMCRec[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeXiMinusInJetPtMassMCRec[fgkiNBinsCent]; //!
  // in jets eta-pT efficiency
  THnSparse* fh3CascadeXiMinusInJetEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh4CascadeXiMinusInJetEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta in  CascadeXiMinusInJetsDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 generated
  THnSparse* fhnCascadeXiMinusInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 reconstructed
  // resolution
  TH2D* fh2CascadeXiMinusMCResolMPt[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiMinusMCPtGenPtRec[fgkiNBinsCent]; //!

  //jet histograms
  TH1D* fh1DistanceCascadeJetsXiMinus[fgkiNBinsCent]; //! distance in eta-phi between Cascade and the closest jet
  //XiMinus-------------------------
  // XiPlus
  //-------------------------
  TH1D* fh1CascadeCounterCentXiPlus[fgkiNBinsCent]; //! number of Xi candidates after various cuts
  TH1D* fh1CascadeInvMassXiPlusAll[fgkiNCategCascade]; //! 
  TH2D* fh2QACascadeEtaPtXiPlusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadeEtaEtaXiPlus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePhiPhiXiPlus[fgkiNQAIndeces]; //!
  TH1D* fh1QACascadeRapXiPlus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePtPtXiPlusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2ArmPodXiPlus[fgkiNQAIndeces]; //! ??
  TH1D* fh1CascadeCandPerEventCentXiPlus[fgkiNBinsCent]; //!
  TH1D* fh1CascadeInvMassXiPlusCent[fgkiNBinsCent]; //!
  // XiPlus Inclusive
  THnSparse* fhnCascadeInclusiveXiPlus[fgkiNBinsCent]; //!
  // XiPlus Cones
  THnSparse* fhnCascadeInJetXiPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInPerpXiPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInRndXiPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInMedXiPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeOutJetXiPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeNoJetXiPlus[fgkiNBinsCent]; //!
  TH2D* fh2CascadePtJetAngleXiPlus[fgkiNBinsCent]; //!
  TH1D* fh1DCAInXiPlus[fgkiNBinsCent]; //!
  TH1D* fh1DCAOutXiPlus[fgkiNBinsCent]; //! 
  //Correlations
  THnSparse* fhnV0CorrelSEXiMinus[fgkiNBinsCent]; //! V0-jet phi,eta correlations in same events, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet; delta-phi_V0-jet; delta-eta_V0-jet; delta R_V0-jet
  THnSparse* fhnV0CorrelSEXiPlus[fgkiNBinsCent]; //! V0-jet phi,eta correlations in same events, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet; delta-phi_V0-jet; delta-eta_V0-jet; delta R_V0-jet
  // MC histograms
  // inclusive
  TH1D* fh1CascadeXiPlusPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiPlusCentMCGen[fgkiNBinsCent];  //! 
  TH1D* fh1CascadeXiPlusPtMCRec[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiPlusPtMassMCRec[fgkiNBinsCent]; //!
  TH1D* fh1CascadeXiPlusPtMCRecFalse[fgkiNBinsCent]; //!
  // inclusive eta-pT efficiency
  TH2D* fh2CascadeXiPlusEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeXiPlusEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta inclusive  //  THnSparse* fhnCascadeXiPlusInclDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade generated
  THnSparse* fhnCascadeXiPlusInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade reconstructed
  // in jets
  TH2D* fh2CascadeXiPlusInJetPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiPlusInJetPtMCRec[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeXiPlusInJetPtMassMCRec[fgkiNBinsCent]; //!
  // in jets eta-pT efficiency
  THnSparse* fh3CascadeXiPlusInJetEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh4CascadeXiPlusInJetEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta in  CascadeXiPlusInJetsDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 generated
  THnSparse* fhnCascadeXiPlusInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 reconstructed
  // resolution
  TH2D* fh2CascadeXiPlusMCResolMPt[fgkiNBinsCent]; //!
  TH2D* fh2CascadeXiPlusMCPtGenPtRec[fgkiNBinsCent]; //!

  //jet histograms
  TH1D* fh1DistanceCascadeJetsXiPlus[fgkiNBinsCent]; //! distance in eta-phi between Cascade and the closest jet
  //XiPlus------------------------
  
  TH1D* fh1QACascadePt[fgkiNQAIndeces]; //! pt
  TH1D* fh1QACascadeCharge[fgkiNQAIndeces]; //! charge
  TH1D* fh1QACascadeDCAVtx[fgkiNQAIndeces]; //! DCA of daughters to prim vtx
  TH1D* fh1QACascadeDCAV0[fgkiNQAIndeces]; //! DCA between daughters
  TH1D* fh1QACascadeDCAV0ToPrimVtx[fgkiNQAIndeces];  // dca V0 to primary vertex
  TH1D* fh1QACascadeDCABachToPrimVtx[fgkiNQAIndeces]; // dca bachelor to primary vertex
  TH1D* fh1QACascadeDCABachToV0[fgkiNQAIndeces];   // dca bachelor to V0  
  TH1D* fh1QACascadeV0Cos[fgkiNQAIndeces]; //! cosine of pointing angle (CPA)
  TH1D* fh1QACascadeXiCos[fgkiNQAIndeces]; //! cosine of pointing angle (CPA) (Xi)

  TH1D* fh1QACascadeV0R[fgkiNQAIndeces]; //! radial distance between prim vtx and V0 decay vertex
  TH1D* fh1QACascadeCTau2D[fgkiNQAIndeces]; //! lifetime calculated in xy
  TH1D* fh1QACascadeCTau3D[fgkiNQAIndeces]; //! lifetime calculated in xyz

// OmegaMinus
  //-------------------------
  TH1D* fh1CascadeCounterCentOmegaMinus[fgkiNBinsCent]; //! number of Omega candidates after various cuts
  TH1D* fh1CascadeInvMassOmegaMinusAll[fgkiNCategCascade]; //! 
  TH2D* fh2QACascadeEtaPtOmegaMinusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadeEtaEtaOmegaMinus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePhiPhiOmegaMinus[fgkiNQAIndeces]; //!
  TH1D* fh1QACascadeRapOmegaMinus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePtPtOmegaMinusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2ArmPodOmegaMinus[fgkiNQAIndeces]; //! ??
  TH1D* fh1CascadeCandPerEventCentOmegaMinus[fgkiNBinsCent]; //!
  TH1D* fh1CascadeInvMassOmegaMinusCent[fgkiNBinsCent]; //!
  // OmegaMinus Inclusive
  THnSparse* fhnCascadeInclusiveOmegaMinus[fgkiNBinsCent]; //!
  // OmegaMinus Cones
  THnSparse* fhnCascadeInJetOmegaMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInPerpOmegaMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInRndOmegaMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInMedOmegaMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeOutJetOmegaMinus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeNoJetOmegaMinus[fgkiNBinsCent]; //!
  TH2D* fh2CascadePtJetAngleOmegaMinus[fgkiNBinsCent]; //!
  TH1D* fh1DCAInOmegaMinus[fgkiNBinsCent]; //!
  TH1D* fh1DCAOutOmegaMinus[fgkiNBinsCent]; //! 
  // MC histograms
  // inclusive
  TH1D* fh1CascadeOmegaMinusPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaMinusCentMCGen[fgkiNBinsCent];  //! 
  TH1D* fh1CascadeOmegaMinusPtMCRec[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaMinusPtMassMCRec[fgkiNBinsCent]; //!
  TH1D* fh1CascadeOmegaMinusPtMCRecFalse[fgkiNBinsCent]; //!
  // inclusive eta-pT efficiency
  TH2D* fh2CascadeOmegaMinusEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeOmegaMinusEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta inclusive  //  THnSparse* fhnCascadeOmegaMinusInclDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade generated
  THnSparse* fhnCascadeOmegaMinusInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade reconstructed
  // in jets
  TH2D* fh2CascadeOmegaMinusInJetPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaMinusInJetPtMCRec[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeOmegaMinusInJetPtMassMCRec[fgkiNBinsCent]; //!
  // in jets eta-pT efficiency
  THnSparse* fh3CascadeOmegaMinusInJetEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh4CascadeOmegaMinusInJetEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta in  CascadeOmegaMinusInJetsDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 generated
  THnSparse* fhnCascadeOmegaMinusInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 reconstructed
  // resolution
  TH2D* fh2CascadeOmegaMinusMCResolMPt[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaMinusMCPtGenPtRec[fgkiNBinsCent]; //!

  //jet histograms
  TH1D* fh1DistanceCascadeJetsOmegaMinus[fgkiNBinsCent]; //! distance in eta-phi between Cascade and the closest jet
  //OmegaMinus-------------------------
  // OmegaPlus
  //-------------------------
  TH1D* fh1CascadeCounterCentOmegaPlus[fgkiNBinsCent]; //! number of Omega candidates after various cuts
  TH1D* fh1CascadeInvMassOmegaPlusAll[fgkiNCategCascade]; //! 
  TH2D* fh2QACascadeEtaPtOmegaPlusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadeEtaEtaOmegaPlus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePhiPhiOmegaPlus[fgkiNQAIndeces]; //!
  TH1D* fh1QACascadeRapOmegaPlus[fgkiNQAIndeces]; //!
  TH2D* fh2QACascadePtPtOmegaPlusPeak[fgkiNQAIndeces]; //!
  TH2D* fh2ArmPodOmegaPlus[fgkiNQAIndeces]; //! ??
  TH1D* fh1CascadeCandPerEventCentOmegaPlus[fgkiNBinsCent]; //!
  TH1D* fh1CascadeInvMassOmegaPlusCent[fgkiNBinsCent]; //!
  // OmegaPlus Inclusive
  THnSparse* fhnCascadeInclusiveOmegaPlus[fgkiNBinsCent]; //!
  // OmegaPlus Cones
  THnSparse* fhnCascadeInJetOmegaPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInPerpOmegaPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInRndOmegaPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeInMedOmegaPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeOutJetOmegaPlus[fgkiNBinsCent]; //!
  THnSparse* fhnCascadeNoJetOmegaPlus[fgkiNBinsCent]; //!
  TH2D* fh2CascadePtJetAngleOmegaPlus[fgkiNBinsCent]; //!
  TH1D* fh1DCAInOmegaPlus[fgkiNBinsCent]; //!
  TH1D* fh1DCAOutOmegaPlus[fgkiNBinsCent]; //! 
  // MC histograms
  // inclusive
  TH1D* fh1CascadeOmegaPlusPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaPlusCentMCGen[fgkiNBinsCent];  //! 
  TH1D* fh1CascadeOmegaPlusPtMCRec[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaPlusPtMassMCRec[fgkiNBinsCent]; //!
  TH1D* fh1CascadeOmegaPlusPtMCRecFalse[fgkiNBinsCent]; //!
  // inclusive eta-pT efficiency
  TH2D* fh2CascadeOmegaPlusEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeOmegaPlusEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta inclusive  //  THnSparse* fhnCascadeOmegaPlusInclDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade generated
  THnSparse* fhnCascadeOmegaPlusInclDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_Cascade reconstructed
  // in jets
  TH2D* fh2CascadeOmegaPlusInJetPtMCGen[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaPlusInJetPtMCRec[fgkiNBinsCent]; //!
  THnSparse* fh3CascadeOmegaPlusInJetPtMassMCRec[fgkiNBinsCent]; //!
  // in jets eta-pT efficiency
  THnSparse* fh3CascadeOmegaPlusInJetEtaPtMCGen[fgkiNBinsCent]; //!
  THnSparse* fh4CascadeOmegaPlusInJetEtaPtMassMCRec[fgkiNBinsCent]; //!
  // MC daughter eta in  CascadeOmegaPlusInJetsDaughterEtaPtPtMCGen[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 generated
  THnSparse* fhnCascadeOmegaPlusInJetsDaughterEtaPtPtMCRec[fgkiNBinsCent]; //! eta_daughter-pt_daughter-pt_V0 reconstructed
  // resolution
  TH2D* fh2CascadeOmegaPlusMCResolMPt[fgkiNBinsCent]; //!
  TH2D* fh2CascadeOmegaPlusMCPtGenPtRec[fgkiNBinsCent]; //!

  //jet histograms
  TH1D* fh1DistanceCascadeJetsOmegaPlus[fgkiNBinsCent]; //! distance in eta-phi between Cascade and the closest jet
  //OmegaPlus------------------------
  
  //TH1D* fh1QACascadeOmegaCos[fgkiNQAIndeces]; //! cosine of pointing angle (CPA) (Omega)


//-------------------------------------------------------------------------------------------

  AliAnalysisTaskV0sInJetsEmcal(const AliAnalysisTaskV0sInJetsEmcal&); // not implemented
  AliAnalysisTaskV0sInJetsEmcal& operator=(const AliAnalysisTaskV0sInJetsEmcal&); // not implemented

  ClassDef(AliAnalysisTaskV0sInJetsEmcal, 31) // task for analysis of V0s (K0S, (anti-)Lambda) in charged jets
};

#endif
