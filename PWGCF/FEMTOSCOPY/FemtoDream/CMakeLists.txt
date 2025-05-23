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
set(MODULE PWGCFFemtoDream)
add_definitions(-D_MODULE_="${MODULE}")

# Module include folder
include_directories(${AliPhysics_SOURCE_DIR}/PWGCF/FEMTOSCOPY/FemtoDream
                    ${AliPhysics_SOURCE_DIR}/PWGGA/GammaConvBase
                    ${AliPhysics_SOURCE_DIR}/PWGGA/Common
                    ${AliPhysics_SOURCE_DIR}/PWG/DevNanoAOD)

# Additional includes - alphabetical order except ROOT
include_directories(${ROOT_INCLUDE_DIRS}
                    ${AliPhysics_SOURCE_DIR}/OADB
                    ${AliPhysics_SOURCE_DIR}/OADB/COMMON/MULTIPLICITY/
		    ${AliPhysics_SOURCE_DIR}/PWGHF/vertexingHF
)

# Additional includes that work only with ROOT6 - alphabetical order except ROOT
if(ROOT_VERSION_MAJOR EQUAL 6)
include_directories(${AliPhysics_SOURCE_DIR}/ML
                    ${AliPhysics_SOURCE_DIR}/PWGHF/vertexingHF/vHFML)
endif()

if(KFParticle_FOUND)
    get_target_property(KFPARTICLE_INCLUDE_DIR KFParticle::KFParticle INTERFACE_INCLUDE_DIRECTORIES)
    include_directories(${KFPARTICLE_INCLUDE_DIR})
    add_definitions("-DWITH_KFPARTICLE")
endif(KFParticle_FOUND)

# pulled in for HF vertexing
if(FASTJET_FOUND)
    include_directories(SYSTEM ${FASTJET_INCLUDE_DIR})
    link_directories(${FASTJET_LIBS_DIR})
    add_definitions(${FASTJET_DEFINITIONS})
    list(APPEND HDRS FJ_includes.h)
endif(FASTJET_FOUND)

# Sources - alphabetical order
set(SRCS
  AliFemtoDreamEvent.cxx
  AliFemtoDreamEventHist.cxx
  AliFemtoDreamEventCuts.cxx
  AliFemtoDreamBasePart.cxx
  AliFemtoDreamTrack.cxx
  AliFemtoDreamTrackHist.cxx
  AliFemtoDreamTrackMCHist.cxx
  AliFemtoDreamTrackCuts.cxx
  AliFemtoDreamv0.cxx
  AliFemtoDreamv0Hist.cxx
  AliFemtoDreamv0MCHist.cxx
  AliFemtoDreamv0Cuts.cxx
  AliFemtoDreamCascade.cxx
  AliFemtoDreamCascadeHist.cxx
  AliFemtoDreamCascadeCuts.cxx
  AliFemtoDreamControlSample.cxx
  AliFemtoDreamPairCleanerHists.cxx
  AliFemtoDreamPairCleaner.cxx
  AliFemtoDreamCollConfig.cxx
  AliFemtoDreamCorrHists.cxx
  AliFemtoDreamPartContainer.cxx
  AliFemtoDreamZVtxMultContainer.cxx
  AliFemtoDreamPartCollection.cxx
  AliFemtoDreamAnalysis.cxx
  AliAnalysisTaskFemtoDream.cxx
  AliAnalysisTaskFemtoDreamDeuteron.cxx
  AliAnalysisTaskNanoPt.cxx
  AliAnalysisTaskNanoXioton.cxx
  AliAnalysisTaskAODXioton.cxx
  AliAnalysisTaskNanoLoton.cxx
  AliAnalysisTaskLeuteronAOD.cxx
  AliAnalysisTaskLeuteronNanoAOD.cxx
  AliAnalysisTaskAODLoton.cxx
  AliAnalysisTaskNanoBBar.cxx
  AliAnalysisTaskFemtoDreamPhi.cxx
  AliAnalysisTaskNanoAODFemtoDreamPhi.cxx
  AliAnalysisTaskNanoAODFemtoDreamLambdaPhi.cxx
  AliAnalysisTaskFemtoDreamRho.cxx
  AliAnalysisTaskFemtoDreamSigPi.cxx
  AliAnalysisTaskNanoAODFemtoDreamSigPi.cxx
  AliAnalysisTaskFemtoDreamPion.cxx
  AliAnalysisTaskDeuteronProtonEfficiency.cxx
  AliAnalysisTaskNanoAODFemtoDreamPion.cxx
  AliAnalysisTaskNanoAODSigma0Femto.cxx
  AliAnalysisTaskNanoSigmaPlus.cxx
  AliAnalysisTaskNanoLD.cxx
  AliAnalysisTaskLD.cxx
  AliAnalysisTaskGrandma.cxx
  AliAnalysisTaskOtonOmega.cxx
  AliOtonOmegaAnalysis.cxx
  AliOtonOmegaCascadeCuts.cxx
  AliOtonOmegaCascade.cxx
  AliFemtoDreamHigherPairMath.cxx
  AliAnalysisTaskNanoLX.cxx
  AliAnalysisTaskOtonOmegaNanoAOD.cxx
  AliAnalysisTaskOtonkd.cxx
  AliAnalysisTaskOtonkdAOD.cxx
  AliAnalysisTaskGeorgiosNTuple.cxx
  AliAnalysisTaskPOmegaPenne.cxx
  AliFemtoDreamBaseDump.cxx
  AliAnalysisTaskThreeBodyFemto.cxx
  AliAnalysisTaskNanoPPCoalescence.cxx
  AliAnalysisTaskFemtoSMI.cxx
  AliAnalysisTaskThreeBodyFemtoAOD.cxx
  AliAnalysisTaskThreeBodyFemtoAODPionProton.cxx
  AliAnalysisTaskThreeBodyFemtoPionProton.cxx
  AliAnalysisTaskThreeBodyProtonPrimary.cxx
  AliSigma0AODPhotonMotherCuts.cxx;
  AliSigma0PhotonCuts.cxx;
  AliAnalysisTaskNanoTreeLPhi.cxx;
  AliAnalysisTaskNanoLambdaKaon.cxx;
  AliAnalysisTaskNanoLambdaPion.cxx;
  AliAnalysisTaskNanoFromAODLambdaPion.cxx;
  AliAnalysisTaskLambdaPion.cxx;
  AliAnalysisTaskNanoLKr.cxx
  AliAnalysisTaskThreeBodyFemtoMixedCharge.cxx;
  AliAnalysisTaskNanoBenchmark.cxx
  AliAnalysisTaskNanoFemtoProtonPion.cxx
  AliAnalysisTaskFemtoProtonPion.cxx
  AliAnalysisTaskNanoXiPi.cxx
  AliAnalysisTaskOtonXx.cxx
  AliAnalysisTaskNanoFemtoProtonKaonPlus.cxx
  AliAnalysisTaskFemtoProtonKaonPlus.cxx
  AliAnalysisTaskAODThreeBodyProtonPrimary.cxx
  )

if(ROOT_VERSION_MAJOR EQUAL 6)
set(SRCS
    ${SRCS}
    AliAnalysisTaskCharmingFemto.cxx
    AliEasyFemto.cxx
    AliAnalysisTaskPionDeuteronMC.cxx
    AliAnalysisTaskPionDeuteron.cxx
    AliAnalysisTaskCharmingFemto_og.cxx)
endif()

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")
if(ROOT_VERSION_MAJOR EQUAL 6)
	set(HDRS
	  ${HDRS}
      CustomQueue.h
	)
endif()

# Generate the dictionary
# It will create G_ARG1.cxx and G_ARG1.h / ARG1 = function first argument
get_directory_property(incdirs INCLUDE_DIRECTORIES)
generate_dictionary("${MODULE}" "${MODULE}LinkDef.h" "${HDRS}" "${incdirs}")

set(ROOT_DEPENDENCIES Core EG GenVector Geom Gpad Hist MathCore Matrix Net Physics RIO Tree)
set(ALIROOT_DEPENDENCIES ANALYSIS ANALYSISalice AOD PWGGAGammaConvBase PWGGAHyperon)

# Generate the ROOT map
# Dependecies
set(LIBDEPS ${ALIROOT_DEPENDENCIES} ${ROOT_DEPENDENCIES})

# set dependecies to HF
set(LIBDEPS ${LIBDEPS} PWGHFvertexingHF)
if(ROOT_VERSION_MAJOR EQUAL 6)
set(LIBDEPS ${LIBDEPS} ML PWGHFvertexingHFML)
endif()

if(KFParticle_FOUND)
    get_target_property(KFPARTICLE_LIBRARY KFParticle::KFParticle IMPORTED_LOCATION)
    set(LIBDEPS ${LIBDEPS} ${KFPARTICLE_LIBRARY})
endif(KFParticle_FOUND)

generate_rootmap("${MODULE}" "${LIBDEPS}" "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}LinkDef.h")

# Generate a PARfile target for this library
add_target_parfile(${MODULE} "${SRCS}" "${HDRS}" "${MODULE}LinkDef.h" "${LIBDEPS}")

# Create an object to be reused in case of static libraries
# Otherwise the sources will be compiled twice
add_library(${MODULE}-object OBJECT ${SRCS} G__${MODULE}.cxx)

# Add a library to the project using the object
add_library_tested(${MODULE} SHARED $<TARGET_OBJECTS:${MODULE}-object>)

target_link_libraries(${MODULE} ${LIBDEPS})

# Setting the correct headers for the object as gathered from the dependencies
target_include_directories(${MODULE}-object PUBLIC $<TARGET_PROPERTY:${MODULE},INCLUDE_DIRECTORIES>)
set_target_properties(${MODULE}-object PROPERTIES COMPILE_DEFINITIONS $<TARGET_PROPERTY:${MODULE},COMPILE_DEFINITIONS>)

# Public include folders that will be propagated to the dependecies
target_include_directories(${MODULE} PUBLIC ${incdirs})

set(MODULE_COMPILE_FLAGS)
set(MODULE_LINK_FLAGS)

if(DATE_FOUND)
    set(MODULE_COMPILE_FLAGS "${DATE_CFLAGS}")
    set(MODULE_LINK_FLAGS "${DATE_LDFLAGS} ${DATE_LIBS}")
endif(DATE_FOUND)

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


# generate_par("Hyperon")

# Installation
install(TARGETS ${MODULE}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(FILES ${HDRS} DESTINATION include)
