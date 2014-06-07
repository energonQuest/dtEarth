# Locate osgearth
# This module defines
# DTEARTH_LIBRARY
# DTEARTH_INCLUDE_DIR, where to find the headers
#
# $DTEARTH_ROOT are environment variables.
#
# Created by Jason Massey repurposed from dtOcean.
INCLUDE(delta3d_common)

FIND_PATH(DTEARTH_INCLUDE_DIR dtEarth/oceanactor.h
          PATH_SUFFIXES
            include
          HINTS
            $ENV{DTEARTH_ROOT}
            ${CMAKE_SOURCE_DIR}/ext/
          PATHS
            $ENV{ProgramFiles}/dtEarth/
          DOC "The path to the folder containing dtEarth/oceanactor.h"
)

#where to find the dtEarth lib dir
SET(DTEARTH_LIB_SEARCH_PATH
    $ENV{DTEARTH_ROOT}/build
    ${CMAKE_SOURCE_DIR}/ext
    ${DTEARTH_INCLUDE_DIR}/../build
    $ENV{ProgramFiles}/dtEarth/
)

MACRO(FIND_DTEARTH_LIBRARY LIB_VAR LIB_NAME)
      FIND_LIBRARY(${LIB_VAR} NAMES ${LIB_NAME}
                   PATH_SUFFIXES 
                      lib
                   PATHS
                      ${DTEARTH_LIB_SEARCH_PATH}
)
ENDMACRO(FIND_DTEARTH_LIBRARY LIB_VAR LIB_NAME)

FIND_DTEARTH_LIBRARY(DTEARTH_LIBRARY       dtEarth)
FIND_DTEARTH_LIBRARY(DTEARTH_LIBRARY_DEBUG dtEarthd)

#convienent list of libraries to link with when using dtCore
SET(DTEARTH_LIBRARIES
    optimized ${DTEARTH_LIBRARY} debug ${DTEARTH_LIBRARY_DEBUG}
    )
    
    
#handle the QUIETLY and REQUIRED arguments and set DTEARTH to TRUE if
#all listed vairables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(dtEarth DEFAULT_MSG DTEARTH_INCLUDE_DIR
                                                      DTEARTH_LIBRARY     )
