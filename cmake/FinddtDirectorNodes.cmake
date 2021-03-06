# Locate dtDirector
#

INCLUDE(delta3d_common)
  
#variable names of the individual Delta3D libraries.  Can be used in application cmakelist.txt files.
FIND_DELTA3D_LIBRARY(DTDIRECTOR_NODES_LIBRARY         dtDirectorNodes)
FIND_DELTA3D_LIBRARY(DTDIRECTOR_NODES_DEBUG_LIBRARY   dtDirectorNodesD)


IF (NOT DTDIRECTOR_NODES_DEBUG_LIBRARY)
  SET(DTDIRECTOR_DEBUG_NODES_LIBRARY ${DTDIRECTOR_LIBRARY})
  MESSAGE(STATUS "No debug library was found for DTDIRECTOR_NODES_DEBUG_LIBRARY")
ENDIF()

SET(DTDIRECTOR_NODES_LIBRARIES
    optimized ${DTDIRECTOR_NODES_LIBRARY}      debug ${DTDIRECTOR_NODES_DEBUG_LIBRARY}
    )
    
SET(DTDIRECTOR_NODES_INCLUDE_DIRECTORIES ${DELTA3D_INCLUDE_DIR}
    )


# handle the QUIETLY and REQUIRED arguments and set DELTA3D_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(dtDirectorNodes DEFAULT_MSG DELTA3D_INCLUDE_DIR     DTDIRECTOR_NODES_LIBRARY
                                  )
