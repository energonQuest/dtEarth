#It may work on an older version, but it hasn't been tested.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1 FATAL_ERROR)

# see cmake --help-policy C/0003 for more information
IF(COMMAND cmake_policy)
   CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

PROJECT(dtEarth)

ADD_DEFINITIONS(-DSIGSLOT_PURE_ISO)
IF(MSVC)
  ADD_DEFINITIONS(-wd4290 -DNOMINMAX)
ENDIF(MSVC)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DELTA_DIR}/CMakeModules;${CMAKE_SOURCE_DIR}/cmake")
INCLUDE(UtilityMacros)

FIND_PACKAGE(OpenThreads REQUIRED)
FIND_PACKAGE(OSG COMPONENTS osg osgDB osgFX osgGA osgParticle osgShadow osgSim osgTerrain osgText osgUtil osgViewer REQUIRED)
# FIND_PACKAGE(Delta3D REQUIRED)
FIND_PACKAGE(Delta3D REQUIRED dtABC dtActors dtCore dtGame dtUtil)
FIND_PACKAGE(OSGEARTH REQUIRED)
FIND_PACKAGE(ODE REQUIRED)
LINK_DIRECTORIES(${DELTA3D_LIB_DIR})
INCLUDE_DIRECTORIES(
  ${DELTA3D_INCLUDE_DIR}
  ${DELTA3D_EXT_DIR}/inc
  ${DELTA3D_EXT_DIR}/include
  ${OSG_INCLUDE_DIR}
  ${ODE_INCLUDE_DIR}
  ${OSGEARTH_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/dtEarth/include  
  ${CMAKE_SOURCE_DIR}/include 
  ${CMAKE_SOURCE_DIR}/source/dtEarth/include
)

################################################################################
# Now add subdirectories for the library itself and for examples
################################################################################

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(examples)

################################################################################
# User options
################################################################################

OPTION(BUILD_EXAMPLES "Enables the building of the dtEarth example project(s)" ON)
