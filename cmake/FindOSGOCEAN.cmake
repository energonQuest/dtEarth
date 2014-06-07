# Locate OsgOcean
# This module defines
# OSGOCEAN_LIBRARY
# OSGOCEAN_FOUND, if false, do not try to link to OsgOcean 
# OSGOCEAN_INCLUDE_DIR, where to find the headers
#
# $OSGOCEAN_INC and $OSGOCEAN_LIB are environment variables.
#
# Created by Danny J. McCue.

FIND_PATH(OSGOCEAN_INCLUDE_DIR osgOcean/OceanScene
          ${OSGOCEAN_DIR}/include
          $ENV{OSGOCEAN_DIR}/include
          $ENV{OSGOCEAN_DIR}
          $ENV{OSGOCEAN_INC}
          ${DELTA3D_EXT_DIR}/inc
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

MACRO(FIND_OSGOCEAN_LIBRARY MYLIBRARY MYLIBRARYNAME)
  FIND_LIBRARY(${MYLIBRARY} 
    NAMES ${MYLIBRARYNAME}
    PATHS
    $ENV{OSG_DIR}/build/lib
    ${OSGOCEAN_DIR}/lib
    $ENV{OSGOCEAN_DIR}/lib
    $ENV{OSGOCEAN_DIR}/build/lib
	$ENV{OSGOCEAN_DIR}/build/lib/Debug
	$ENV{OSGOCEAN_DIR}/build/lib/RelWithDebInfo
    $ENV{OSGOCEAN_DIR}/lib64
    $ENV{OSGOCEAN_DIR}
    $ENV{OSGOCEAN_LIB}
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
ENDMACRO(FIND_OSGOCEAN_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_OSGOCEAN_LIBRARY(OSGOCEAN_LIBRARY osgOceanrd)
FIND_OSGOCEAN_LIBRARY(OSGOCEAN_LIBRARY_DEBUG osgOceanD)

SET(OSGOCEAN_FOUND "NO")
IF(OSGOCEAN_LIBRARY AND OSGOCEAN_INCLUDE_DIR)
  SET(OSGOCEAN_FOUND "YES")
ENDIF(OSGOCEAN_LIBRARY AND OSGOCEAN_INCLUDE_DIR)
