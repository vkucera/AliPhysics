# **************************************************************************
# * Copyright(c) 1998-2014, ALICE Experiment at CERN, All rights reserved. *
# *                                                                        *
# * Author: The ALICE Off-line Project.                                    *
# * Contributors are mentioned in the code where appropriate.              *
# *                                                                        *
# * Permission to use, copy, modify and distribute this software and its   *
# * documentation strictly for non-commercial purposes is hereby granted   *
# * without fee, provided that the above copyright notice appears in all   *
# * copies and that both the copyright notice and this permission notice   *
# * appear in the supporting documentation. The authors make no claims     *
# * about the suitability of this software for any purpose. It is          *
# * provided "as is" without express or implied warranty.                  *
# **************************************************************************/

#Module
set(MODULE PWGLFnuclex)
add_definitions(-D_MODULE_="${MODULE}")

# Module include folder
include_directories(${AliPhysics_SOURCE_DIR}/PWGLF/NUCLEX
                    ${AliPhysics_SOURCE_DIR}/PWGLF/NUCLEX/Utils/RecoDecay
                    ${AliPhysics_SOURCE_DIR}/PWGLF/NUCLEX/Utils/NuclexFilter
  )

# Additional includes - alphabetical order except ROOT
include_directories(${ROOT_INCLUDE_DIRS}
                    ${ALIROOT_INCLUDE_DIRS}
                    ${AliPhysics_SOURCE_DIR}/CORRFW
                    ${AliPhysics_SOURCE_DIR}/OADB
                    ${AliPhysics_SOURCE_DIR}/OADB/COMMON/MULTIPLICITY
                    ${AliPhysics_SOURCE_DIR}/PWG/Tools
                    ${AliPhysics_SOURCE_DIR}/PWG/DevNanoAOD
		                ${AliPhysics_SOURCE_DIR}/PWGCF/Correlations/Base
                    ${AliPhysics_SOURCE_DIR}/PWGLF/CommonUtils
                    ${AliPhysics_SOURCE_DIR}/PWGPP/EVCHAR/FlowVectorCorrections/QnCorrections
		                ${AliPhysics_SOURCE_DIR}/PWGPP/EVCHAR/FlowVectorCorrections/QnCorrectionsInterface/
  )
if(KFParticle_FOUND)
  get_target_property(KFPARTICLE_INCLUDE_DIR KFParticle::KFParticle INTERFACE_INCLUDE_DIRECTORIES)
  include_directories(${KFPARTICLE_INCLUDE_DIR})
  add_definitions("-DWITH_KFPARTICLE")
endif(KFParticle_FOUND)

if(ROOT_VERSION_MAJOR EQUAL 6)
# Additional includes for ROOT 6 only dependencies - alphabetical order except ROOT
  include_directories(${AliPhysics_SOURCE_DIR}/ML
                    ${TREELITE_ROOT}/include
                    ${TREELITE_ROOT}/runtime/native/include
                    ${YAML_CPP_SOURCE_DIR}/include
    )
endif()

set(SRCS
  Exotica/Hdibaryon/AliAnalysisTaskHdibaryonLPpi.cxx
  Exotica/Dibaryons/AliAnalysisTaskDibaryons.cxx
  Exotica/Dibaryons/AliAnalysisTaskMSDibaryons.cxx
  Exotica/Dibaryons/AliAnalysisTaskpOmegaDibaryon.cxx
  Exotica/LambdaN/AliAnalysisTaskLambdaNAOD.cxx
  Exotica/LambdaN/AliAnalysisTaskLambdaNRun2.cxx
  Exotica/LambdaNN/AliAnalysisTaskLNNntuple.cxx
  Exotica/LambdaNN/AliAnalysisTaskLNNv0Bkg.cxx
  Exotica/LambdaNN/AliAnalysisTaskLambdaNNRun2.cxx
  Exotica/Ps/AliAnalysisTaskPsEfficiency.cxx
  Exotica/dStar/AliAnalysisTaskdStar.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskHelium3Pi.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskHelium3PiAOD.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskHelium3PiMC.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskHypCrossCheck.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskHypV0s.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskReducedTreeHypertritonBindingEnergy.cxx
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisTaskS3ParticleYields.cxx
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisTaskHe3EffTree.cxx
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisTaskHypTritTestAOD.cxx  
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisTaskHypTritKf.cxx
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisCODEXS3task.cxx
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisTaskTRDtriggerTracks.cxx
  Hypernuclei/Hyp2Body/HypTritYield/Sigma_Baryons/AliAnalysisTaskSigmaPlus.cxx
  Hypernuclei/Hyp2Body/HypTritYield/pdLd/AliAnalysisTask_pdLd.cxx
  Hypernuclei/Hyp2Body/HypTritYield/pd/AliAnalysisTask_pd.cxx
  Hypernuclei/Hyp2Body/HypTritYield/pd/AliAnalysisTask_pd_CreateTrees_PairsOnly.cxx
  Hypernuclei/Hyp2Body/HypTritYield/pd/AliAnalysisTask_pd_PurityTOF.cxx
  Hypernuclei/Hyp2Body/HypTritYield/pp/AliAnalysisTask_pp_CreateTrees_PairsOnly.cxx
  Hypernuclei/Hyp2Body/HypTritYield/Ld/AliAnalysisTask_Ld_CreateTrees_PairsOnly.cxx
  Hypernuclei/Hyp2Body/AliReducedHypTritEvent.cxx
  Hypernuclei/Hyp2Body/AliAnalysisTaskHypTritEventTree.cxx
  Hypernuclei/Hyp2Body/HypTritYield/AliAnalysisTaskHe3TriTree.cxx
  Hypernuclei/Hyp3Body/AliAnalysisTaskFindableHypertriton3.cxx
  Hypernuclei/Vertexer2Body/AliVertexerHyperTriton2Body.cxx
  Hypernuclei/Vertexer3Body/AliVertexerHyperTriton3Body.cxx
  Hypernuclei/KFHypertriton/AliAnalysisTaskHypertritonKFTree.cxx
  Hypernuclei/DoubleHypNuc/AliAnalysisTaskDoubleHypNucTree.cxx
  Hypernuclei/DoubleHypNuc/AliAnalysisTaskDoubleHypNucTreeLS.cxx
  Nuclei/Absorption/AliAnalysisTaskDeuteronAbsorption.cxx
  Nuclei/AbsorptionRatios/AliAnalysisTaskLightN.cxx
  Nuclei/AbsorptionRatios/AliLightNEventHist.cxx
  Nuclei/AbsorptionRatios/AliLightNAnalysis.cxx
  Nuclei/AbsorptionRatios/AliLightNTrack.cxx
  Nuclei/AbsorptionRatios/AliLightNBasePart.cxx
  Nuclei/AbsorptionRatios/AliLightNTrackCuts.cxx
  Nuclei/AbsorptionRatios/AliLightNEvent.cxx
  Nuclei/AbsorptionRatios/AliLightNTrackHist.cxx
  Nuclei/AbsorptionRatios/AliLightNEventCuts.cxx
  Nuclei/AbsorptionRatios/AliLightNTrackMCHist.cxx
  Nuclei/AbsorptionRatios/AliAnalysisTaskHe3.cxx
  Nuclei/AbsorptionRatios/AliAnalysisH3MC.cxx
  Nuclei/AbsorptionRatios/AliAnalysisHe3MC.cxx
  Nuclei/AbsorptionRatios/AliAnalysisH3MC.cxx
  Nuclei/AbsorptionRatios/AliAnalysisTaskHe3_ESD.cxx
  Nuclei/AbsorptionRatios/AliAnalysisTaskNuclei.cxx
  Nuclei/AbsorptionRatios/HMAnalysis/AliAnalysisTaskAntipd.cxx
  Nuclei/DeltaMasses/AliAnalysisNucleiMass.cxx
  Nuclei/DeltaMasses/AliAnalysisNuclMult.cxx
  Nuclei/He4/AliAnalysisTaskAntiHe4.cxx
  Nuclei/He4pp/AliAnalysisHe4.cxx
  Nuclei/Nuclei_UE/AliAnalysisTaskDeuteronsRT.cxx
  Nuclei/Nuclei_UE/AliAnalysisTaskDeuteronCoalescence.cxx
  Nuclei/Nuclei_UE/AliAnalysisTaskPythiaCoalescence.cxx
  Nuclei/Nuclei_UE/AliAnalysisTaskSimpleCoalescenceHelium3.cxx
  Nuclei/Nuclei_UE/AliAnalysisTaskSimpleCoalescenceDeuteronInJets.cxx
  Nuclei/NucleiPbPb/AliAnalysisTaskNucleiYield.cxx
  Nuclei/NucleiPbPb/AliAnalysisTaskNucleiPIDqa.cxx
  Nuclei/NucleiPbPb/AliAnalysisTaskSignalLoss.cxx
  Nuclei/NucleiReducedTree/AliAnalysisTaskReducedTreeNuclei.cxx
  Nuclei/NucleiReducedTree/AliAnalysisTaskReducedTreeHypertriton.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskTritonVsMultiplicity_PbPb.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskTritonESD_PbPb.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskTritonVsMultiplicity_XeXe.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskHe3VsMultiplicity_XeXe.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskDeuteronVsMultiplicity_XeXe.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskLightNuclei_XeXe_MC.cxx
  Nuclei/TritonAnalysis/AliAnalysisTaskDeuteron_XeXe_MC.cxx    
  Nuclei/TritonAnalysis/AliAnalysisTaskDeuteron_XeXe_MC_noMult.cxx
  Nuclei/v2/AliAnalysisTaskNucleiv2.cxx
  Nuclei/v2/AliAnalysisTaskNucleiv2SP.cxx
  Nuclei/v2/AliAnalysisTaskNucleiv2pPb.cxx
  Nuclei/v2/AliAnalysisTaskAllPtcv2.cxx
  Nuclei/v2/AliAnalysishDEventCollection.cxx
  Nuclei/v2/AliAnalysisTaskDeuFlow2PC.cxx
  Nuclei/v2/AliAnalysisTaskHypv2PbPb18.cxx
  Nuclei/v2/AliAnalysisTaskNucleiv2PbPb18.cxx
  Nuclei/NucleiKine/AliAnalysisTaskNucleiKine.cxx
  Nuclei/NucleiKine/AliAnalysisTaskNucleiKineCor.cxx
  Nuclei/NeutronCEX/AliAnalysisTaskAntineutron.cxx
  Utils/CODEX/AliAnalysisCODEX.cxx
  Utils/CODEX/AliAnalysisCODEXtask.cxx
  Utils/NanoAOD/AliNanoFilterPID.cxx
  Utils/NanoAOD/AliNanoSkimmingPID.cxx
  Utils/NanoAOD/AliNanoSkimmingV0s.cxx
  Utils/ChunkFilter/AliAnalysisTaskFilterHe3.cxx
  )

if(ROOT_VERSION_MAJOR EQUAL 6)
	set(SRCS
	  ${SRCS}
      Hypernuclei/Hyp2Body/AliAnalysisTaskHyperTriton2He3piML.cxx
      Hypernuclei/Hyp2Body/AliAnalysisTaskHe3piAOD.cxx
      Hypernuclei/Hyp2Body/AliAnalysisTaskHe3piKF.cxx
      Hypernuclei/Hyp2Body/AliAnalysisTaskAlphaPiAOD.cxx
      Hypernuclei/Hyp2Body/AliAnalysisTaskAlphaPiAODtrk.cxx
			Hypernuclei/Hyp3Body/selector/AliSelectorFindableHyperTriton3Body.cxx
      Hypernuclei/Hyp3Body/AliAnalysisTaskHypertriton3.cxx
      Hypernuclei/Hyp3Body/Hypertriton3structures.cxx
      Utils/O2vertexer/Primitive2D.cxx
      Utils/O2vertexer/DCAFitterN.cxx
	  )
endif()

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

if(ROOT_VERSION_MAJOR EQUAL 6)
	set(HDRS
	  ${HDRS}
      Utils/O2vertexer/HelixHelper.h
      Utils/O2vertexer/MathUtils.h
      Utils/O2vertexer/Track.h
	  )
endif()

# Generate the dictionary
# It will create G_ARG1.cxx and G_ARG1.h / ARG1 = function first argument
get_directory_property(incdirs INCLUDE_DIRECTORIES)
generate_dictionary("${MODULE}" "${MODULE}LinkDef.h" "${HDRS}" "${incdirs}")

set(ROOT_DEPENDENCIES)
set(ALIROOT_DEPENDENCIES ANALYSISalice OADB PWGPPevcharQn PWGflowTasks EVGEN PWGLFcommonutils PWGDevNanoAOD)

# Generate the ROOT map
# Dependencies
set(LIBDEPS ${ALIROOT_DEPENDENCIES} ${ROOT_DEPENDENCIES})
if(KFParticle_FOUND)
    get_target_property(KFPARTICLE_LIBRARY KFParticle::KFParticle IMPORTED_LOCATION)
    set(LIBDEPS ${LIBDEPS} ${KFPARTICLE_LIBRARY})
endif(KFParticle_FOUND)
if(ROOT_VERSION_MAJOR EQUAL 6)
  set(LIBDEPS ${LIBDEPS} ML yaml-cpp)
endif()

generate_rootmap("${MODULE}" "${LIBDEPS}" "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}LinkDef.h")

# Generate a PARfile target for this library. Note the extra includes ("Tracks UserTasks")
add_target_parfile(${MODULE} "${SRCS}" "${HDRS}" "${MODULE}LinkDef.h" "${LIBDEPS}" "Tracks UserTasks")

# Create an object to be reused in case of static libraries
# Otherwise the sources will be compiled twice
add_library(${MODULE}-object OBJECT ${SRCS} G__${MODULE}.cxx)

# Add a library to the project using the object
add_library_tested(${MODULE} SHARED $<TARGET_OBJECTS:${MODULE}-object>)
target_link_libraries(${MODULE} ${LIBDEPS})
if(ROOT_VERSION_MAJOR EQUAL 6)
  # For macOS: Add TREELITE_ROOT to RPATH
  target_link_directories(${MODULE} PUBLIC ${TREELITE_ROOT}/lib)
endif()

# Setting the correct headers for the object as gathered from the dependencies
target_include_directories(${MODULE}-object PUBLIC $<TARGET_PROPERTY:${MODULE},INCLUDE_DIRECTORIES>)
set_target_properties(${MODULE}-object PROPERTIES COMPILE_DEFINITIONS $<TARGET_PROPERTY:${MODULE},COMPILE_DEFINITIONS>)

# Public include folders that will be propagated to the dependecies
target_include_directories(${MODULE} PUBLIC ${incdirs})

set(MODULE_COMPILE_FLAGS)
set(MODULE_LINK_FLAGS)

# Additional compilation and linking flags
set(MODULE_COMPILE_FLAGS " ${MODULE_COMPILE_FLAGS}")

# System dependent: Modify the way the library is build
if(${CMAKE_SYSTEM} MATCHES Darwin)
    set(MODULE_LINK_FLAGS "-undefined dynamic_lookup ${MODULE_LINK_FLAGS}")
endif(${CMAKE_SYSTEM} MATCHES Darwin)

# Setting compilation flags for the object
set_target_properties(${MODULE}-object PROPERTIES COMPILE_FLAGS "${MODULE_COMPILE_FLAGS}")
# Setting the linking flags for the library
set_target_properties(${MODULE} PROPERTIES LINK_FLAGS "${MODULE_LINK_FLAGS}")

# Installation
install(TARGETS ${MODULE}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(FILES ${HDRS} DESTINATION include)

# install macros
install(DIRECTORY . DESTINATION PWGLF/NUCLEX FILES_MATCHING PATTERN "*.C")

