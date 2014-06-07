# Locate osgearth
# This module defines
# OSGEARTH_LIBRARY
# OSGEARTH_FOUND, if false, do not try to link to osgEarth 
# OSGEARTH_INCLUDE_DIR, where to find the headers
#
# $OSGEARTH_INC and $OSGEARTH_LIB are environment variables.
#
# Created by Jason Massey, repurposed from Danny J. McCue.

FIND_PATH(OSGEARTH_INCLUDE_DIR osgEarth#/OceanScene
          ${OSGEARTH_DIR}/include
          $ENV{OSGEARTH_DIR}/include
          $ENV{OSGEARTH_DIR}
          $ENV{OSGEARTH_INC}
          ${DELTA3D_EXT_DIR}/inc
          ${DELTA3D_EXT_DIR}/include
          $ENV{DELTA_ROOT}/ext/inc
          $ENV{DELTA_ROOT}
          $ENV{OSG_ROOT}/include
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include
          /sw/include # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include # Blastwave
          /opt/include
          [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/include
          /usr/freeware/include
)

MACRO(FIND_OSGEARTH_LIBRARY MYLIBRARY MYLIBRARYNAME)
  FIND_LIBRARY(${MYLIBRARY} 
    NAMES ${MYLIBRARYNAME}
    PATHS
    $ENV{OSG_DIR}/build/lib
    ${OSGEARTH_DIR}/lib
    $ENV{OSGEARTH_DIR}/lib
    $ENV{OSGEARTH_DIR}/build/lib
	$ENV{OSGEARTH_DIR}/build/lib/Debug
	$ENV{OSGEARTH_DIR}/build/lib/RelWithDebInfo
    $ENV{OSGEARTH_DIR}/lib64
    $ENV{OSGEARTH_DIR}
    $ENV{OSGEARTH_LIB}
    ${DELTA3D_EXT_DIR}/lib
    ${DELTA3D_EXT_DIR}/lib64
    $ENV{DELTA_ROOT}/ext/lib
    $ENV{DELTA_ROOT}/ext/lib64
    $ENV{DELTA_ROOT}
    $ENV{OSG_ROOT}/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
    /usr/freeware/lib64
  )
ENDMACRO(FIND_OSGEARTH_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_OSGEARTH_LIBRARY(OSGEARTH_LIBRARY osgEarth)
FIND_OSGEARTH_LIBRARY(OSGEARTH_LIBRARY_DEBUG osgEarthd)

SET(OSGEARTH_FOUND "NO")
IF(OSGEARTH_LIBRARY AND OSGEARTH_INCLUDE_DIR)
  SET(OSGEARTH_FOUND "YES")
ENDIF(OSGEARTH_LIBRARY AND OSGEARTH_INCLUDE_DIR)
