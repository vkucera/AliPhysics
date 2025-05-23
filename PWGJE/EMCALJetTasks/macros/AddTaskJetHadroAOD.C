// R__ADD_INCLUDE_PATH($PWD)
#include "AliAnalysisTaskJetHadroAOD.h"
#include "AliAnalysisManager.h"
#include "AliMCEventHandler.h"
#include "AliLog.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom.h"
#include "AliJetContainer.h"

AliAnalysisTask *AddTaskJetHadroAOD(Bool_t getFromAlien=kTRUE, TString configFileName = "Config_siweyhmi_JetHadro_AOD.C",Int_t settingType = 0,Int_t year = 2018, TString periodName="18q", Int_t passIndex = 3, const char* suffix = "", Int_t containerNameMode=0, Bool_t postTrees=kFALSE)
{
  //
  //get the current analysis manager
  //
  /*
  =================================================================================================
  ======= eta Range --> [-0.8,0.8], momentum Range --> [0.2,3.2], dEdx Range --> [20,1020]* =======
  Parameter 1: getFromAlien     --> decide if the config file will be taken from alien or hera
  Parameter 2: configFileName   --> config file which should exist both in alicen and hera
  Parameter 3: settingType      --> an integer to decide which setting to use
  Parameter 4: year             --> year
  Parameter 5: suffix           --> used for naming conflicts in lego train --> each wagon has a different suffix
  Parameter 6: containerNameMode--> decide either dump output files in a TDirectoryFile or not. 0 without 1 and 2 with TDirectoryFile,
  =================================================================================================
  */
  std::cout << " Info::siweyhmi: ===== In the AddTaskJetHadroAOD ===== " << std::endl;
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTaskJetHadroAOD", "No analysis manager found.");
    return 0;
  }
  // Switch off all AliInfo (too much output!!!)
  AliLog::SetGlobalLogLevel(AliLog::kError);
  mgr->SetDebugLevel(0);

  AliMCEventHandler* handler = new AliMCEventHandler;
  handler->SetReadTR(kFALSE);
  mgr->SetMCtruthEventHandler(handler);
  //
  //==================================================
  //      Add task to the ANALYSIS manager
  //==================================================
  //
  //Get the current train configuration
  TString configBasePath;
  if (getFromAlien)
  {
    // gSystem->Exec(Form("alien_cp alien:///alice/cern.ch/user/m/marsland/PWGCF/EBYE/IdentityMethodEbyeFluctuations/macros/%s .",configFileName.Data()));
    // TString configFileName = "Config_marsland_EbyeIterPID.C";
    //    gSystem->Exec(Form("alien_cp /alice/cern.ch/user/m/marsland/PWGCF/EBYE/IdentityMethodEbyeFluctuations/macros/%s file:%s",configFileName.Data(),configFileName.Data()));
    gSystem->Exec(Form("alien_cp /alice/cern.ch/user/s/siweyhmi/%s file:%s",configFileName.Data(),configFileName.Data()));
    configBasePath=Form("%s/",gSystem->pwd());
  } else {
    std::cout << " Info::siweyhmi: Settings for local testing " << std::endl;
    configBasePath = "";
    //
    // gSystem->Load("libANALYSIS");
    // gSystem->Load("libANALYSISalice");
    // gSystem->AddIncludePath("-I$ALICE_ROOT/include");
    // gSystem->AddIncludePath("-I$ALICE_PHYSICS/include");
    //
    // MC closure for higher moments
    // settingType = 64;   // 1 for Real data 50 for full MC
    // year   = 2; periodName="15o"; passIndex=2  // 1 for 10h, 2 for 15o, 3 for 18[q,r]
    suffix = "test";
    containerNameMode=0;
  }
  TString combinedName;
  combinedName.Form("siweyhmi_%s", suffix);
  TString configFilePath(configBasePath+configFileName);
  std::cout << " Info::siweyhmi: Configpath:  " << configFilePath << " year = " << year << " --- period name = " << periodName << " --- pass = " << passIndex << " --- settingType = " << settingType << std::endl;

  AliAnalysisTaskJetHadroAOD* task(0x0);
  #ifdef __CLING__
      std::stringstream triggermakeradd;
      triggermakeradd << ".x " << configFilePath.Data() << "(";
      triggermakeradd << (getFromAlien ? "kTRUE" : "kFALSE") << ", ";
      triggermakeradd << settingType << ", ";
      triggermakeradd << year << ", ";
      triggermakeradd << "\"" << periodName.Data() << "\"" << ", ";
      triggermakeradd << passIndex << ", ";
      triggermakeradd << "\"" << combinedName.Data() << "\"";
      triggermakeradd << ")";
      std::string triggermakeraddstring = triggermakeradd.str();
      std::cout << triggermakeraddstring << std::endl;
      task = (AliAnalysisTaskJetHadroAOD*)gROOT->ProcessLine(triggermakeraddstring.c_str());
  #else
      gROOT->LoadMacro(configFilePath.Data());
      task = Config_siweyhmi_JetHadro_AOD(getFromAlien,settingType,year,periodName,passIndex,combinedName);
  #endif

  Bool_t hasMC = (AliAnalysisManager::GetAnalysisManager()->GetMCtruthEventHandler()!=0x0);
  //task->SetIsMCtrue(hasMC);
//  task->SetUseCouts(kTRUE);
  printf(" ========================= MC info %d ========================= \n",hasMC);
  mgr->AddTask(task);
  // mgr->Dump(); task->Dump();
  //
  //==================================================
  //      Add task to the PID Response
  //==================================================
  //
  // gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
  // Bool_t isMC=kTRUE; // kTRUE in case of MC
  // AddTaskPIDResponse(isMC);
  //
  // gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
  // AddTaskPIDResponse(hasMC, kTRUE, kFALSE, "", kFALSE, "TPC-OADB:COMMON/PID/data/TPCPIDResponseOADB_pileupCorr.root;TPC-Maps:$ALICE_PHYSICS/OADB/COMMON/PID/data/TPCetaMaps_pileupCorr.root" );
  //
  //================================================
  //              data containers
  //================================================
  //
  // ****** Do not forget to "DefineOutput(5, TTree::Class());" In the contructor of the task ******
  //define output containers, please use 'username'_'somename'
  AliAnalysisDataContainer *cinput, *coutput1, *coutput2, *coutput3, *coutput4;
  AliAnalysisDataContainer *coutput5, *coutput6, *coutput7, *coutput8, *coutput9;
  AliAnalysisDataContainer *coutput10, *coutput11, *coutput12, *coutput13;
  //
  //  find and connect input container // Output files --> File opening order is important
  cinput  = mgr->GetCommonInputContainer();
  mgr->ConnectInput(task, 0, cinput);
  //
  // Get the output file name which is by default "AnalysisResults.root" --> Either write output into a TDirectoryFile or directly in "AnalysisResults.root"
  const char* outputFileName = AliAnalysisManager::GetCommonFileName();
  TString dirName = "";
  TString fileDirStructure = "";
  TString listName = "";
  if (containerNameMode==0){
    fileDirStructure = Form("%s", outputFileName);  // TDirectoryFile name to put all containers; AnalysisResults.root --> trees and hists
    listName = "jetHadroHists";
  } else if (containerNameMode==1){
    dirName = "PWGJE_siweyhmi";                     // TDirectoryFile name to put all containers; AnalysisResults.root --> PWGJE_siweyhmi --> trees and hists
    fileDirStructure = Form("%s:%s", outputFileName, dirName.Data());
    listName = combinedName+"_jetHadroHists";
  } else if (containerNameMode==2){
    dirName = Form("PWGJE_siweyhmi_%s",suffix);     // TDirectoryFile name to put all containers; AnalysisResults.root --> PWGJE_siweyhmi_<setting> --> trees and hists
    fileDirStructure = Form("%s:%s", outputFileName, dirName.Data());
    listName = combinedName+"_jetHadroHists";
  }
  //
  // Output containers
  coutput1  = mgr->CreateContainer(combinedName+"_EMCalFWhistos",  TList::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
  mgr->ConnectOutput (task,  1, coutput1);
  
  coutput2  = mgr->CreateContainer(listName, TList::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
  mgr->ConnectOutput (task,  2, coutput2);

  if (postTrees){
    coutput3  = mgr->CreateContainer(combinedName+"_jetsEMCconst",  TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput4  = mgr->CreateContainer(combinedName+"_jetsEMCBGconst",  TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput5  = mgr->CreateContainer(combinedName+"_jetsFJ",        TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput6  = mgr->CreateContainer(combinedName+"_jetsFJBG",      TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput7 = mgr->CreateContainer(combinedName+"_jetsFJconst",    TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput8 = mgr->CreateContainer(combinedName+"_jetsFJBGconst",    TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput9 = mgr->CreateContainer(combinedName+"_jeteventInfo",   TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput10 = mgr->CreateContainer(combinedName+"_jetsEMC",         TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput11 = mgr->CreateContainer(combinedName+"_jetsEMCBG",         TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput12  = mgr->CreateContainer(combinedName+"_fTreeMC",       TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);
    coutput13  = mgr->CreateContainer(combinedName+"_tracks",        TTree::Class(), AliAnalysisManager::kOutputContainer, fileDirStructure);

    mgr->ConnectOutput (task,  3, coutput3);
    mgr->ConnectOutput (task,  4, coutput4);
    mgr->ConnectOutput (task,  5, coutput5);
    mgr->ConnectOutput (task,  6, coutput6);
    mgr->ConnectOutput (task,  7, coutput7);
    mgr->ConnectOutput (task,  8, coutput8);
    mgr->ConnectOutput (task,  9, coutput9);
    mgr->ConnectOutput (task,  10, coutput10);
    mgr->ConnectOutput (task,  11, coutput11);
    mgr->ConnectOutput (task,  12, coutput12);
    mgr->ConnectOutput (task,  13, coutput13);
}



  std::cout << " Info::siweyhmi: === Containers are ready === " << std::endl;
  return task;
}
