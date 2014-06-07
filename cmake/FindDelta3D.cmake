# Locate Delta3D
# This module defines
# DTCORE_DEBUG_LIBRARY
# DELTA3D_EXT_DIR
# DELTA3D_FOUND, if false, do not try to link to gdal 
# DELTA3D_INCLUDE_DIR, where to find the headers
#
# $DELTA3D_DIR is an environment variable that would
# correspond to the ./configure --prefix=$DELTA3D
#
# Created by David Guthrie. 
# Edited by energonQuest
INCLUDE(delta3d_common)

FIND_PATH(PROJ_3RD_PARTY_ROOT NAMES inc/dtCore/base.h include/dtCore/base.h
	HINTS
		${CMAKE_SOURCE_DIR}
		$ENV{DELTA_ROOT}
		$ENV{DELTA_INC}
	PATHS
		~/Library/Frameworks
		/Library/Frameworks
		/usr/local
)

FIND_PATH(DELTA_DIR NAMES inc/dtCore/base.h include/dtCore/base.h
	HINTS
		${PROJ_3RD_PARTY_ROOT}
		${CMAKE_SOURCE_DIR}
		$ENV{DELTA_ROOT}
		$ENV{DELTA_INC}
	PATHS
		~/Library/Frameworks
		/Library/Frameworks
		/usr/local
)

FIND_PATH(DELTA3D_INCLUDE_DIR NAMES dtCore/base.h
	HINTS
		${DELTA_DIR}
    PATH_SUFFIXES
       inc
       include
)

FIND_PATH( DELTA3D_LIB_DIR NAMES libdtCore.so libdtCore.dylib dtCore.lib .
    HINTS
       ${DELTA_DIR}
    PATH_SUFFIXES
       build/lib
       Build/lib
       Debug/lib
       Release/lib
       lib
    NO_DEFAULT_PATH
)

#where to find the Delta3D "ext" folder.  Look for one of the headers that might be in there.
#SET(DELTA3D_EXT_DIR ${DELTA_DIR} CACHE PATH "The root of the Delta3D external dependency folder")
FIND_PATH(DELTA3D_EXT_DIR NAMES inc/osg/Object include/osg/Object
	HINTS
		${PROJ_3RD_PARTY_ROOT}
		${CMAKE_SOURCE_DIR}
		$ENV{DELTA_ROOT}
		$ENV{DELTA_INC}
	PATHS
		~/Library/Frameworks
		/Library/Frameworks
		/usr/local
)

IF(DELTA3D_EXT_DIR)
  #for aiding FIND_FILE() and FIND_PATH() searches
  list(APPEND CMAKE_PREFIX_PATH ${DELTA3D_EXT_DIR})
  list(APPEND CMAKE_FRAMEWORK_PATH ${DELTA3D_EXT_DIR}/Frameworks)
  list(APPEND CMAKE_INCLUDE_PATH ${DELTA3D_EXT_DIR}/inc)
  list(APPEND CMAKE_INCLUDE_PATH ${DELTA3D_EXT_DIR}/include)
ENDIF(DELTA3D_EXT_DIR)

# Find release (optimized) libs
DELTA3D_FIND_LIBRARY(DTUTIL dtUtil)
DELTA3D_FIND_LIBRARY(DTCORE dtCore)
DELTA3D_FIND_LIBRARY(DTABC dtABC)
DELTA3D_FIND_LIBRARY(DTDIRECTOR dtDirector)
DELTA3D_FIND_LIBRARY(DTDIRECTORNodes dtDirectorNodes)
DELTA3D_FIND_LIBRARY(DTDIRECTORQt dtDirectorQt)
DELTA3D_FIND_LIBRARY(DTAI dtAI)
DELTA3D_FIND_LIBRARY(DTGAME dtGame)
DELTA3D_FIND_LIBRARY(DTPHYSICS dtPhysics)
DELTA3D_FIND_LIBRARY(DTAUDIO dtAudio)
DELTA3D_FIND_LIBRARY(DTANIM dtAnim)
DELTA3D_FIND_LIBRARY(DTINSPECTORQt dtInspectorQt)
# DELTA3D_FIND_LIBRARY(DTSCRIPT dtScript)
DELTA3D_FIND_LIBRARY(DTTERRAIN dtTerrain)
DELTA3D_FIND_LIBRARY(DTNET dtNet)
DELTA3D_FIND_LIBRARY(DTNETGM dtNetGM)
DELTA3D_FIND_LIBRARY(DTHLAGM dtHLAGM)
# DELTA3D_FIND_LIBRARY(DTDIS dtDIS)
DELTA3D_FIND_LIBRARY(DTINPUTPLIB dtInputPLIB)
DELTA3D_FIND_LIBRARY(DTACTORS dtActors)
# DELTA3D_FIND_LIBRARY(DTLMS dtLMS)
# DELTA3D_FIND_LIBRARY(DTQT dtQt)
# DELTA3D_FIND_LIBRARY(STAGE STAGE)
# DELTA3D_FIND_LIBRARY(TEST_ACTOR testActorLibrary)
# DELTA3D_FIND_LIBRARY(TEST_GAME_ACTOR testGameActorLibrary)
# DELTA3D_FIND_LIBRARY(FIREFIGHTER_DEMO fireFighter)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Delta3D  DEFAULT_MSG
                                  DTCORE_LIBRARY DELTA3D_INCLUDE_DIR)
# SET(DELTA3D_FOUND "NO")
# IF(DTCORE_LIBRARY AND DELTA3D_INCLUDE_DIR AND DELTA3D_LIB_DIR)
    # SET(DELTA3D_FOUND "YES")
# ENDIF(DTCORE_LIBRARY AND DELTA3D_INCLUDE_DIR AND DELTA3D_LIB_DIR)
