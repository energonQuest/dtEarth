SET(LIB_NAME testEarth)

ADD_LIBRARY(${LIB_NAME} SHARED
            testentrypoint.cpp
            testexport.h
            readme.txt
)

SET_TARGET_PROPERTIES(${LIB_NAME}
                     PROPERTIES DEFINE_SYMBOL TEST_EARTH_LIBRARY)

TARGET_LINK_LIBRARIES(${LIB_NAME}
                      optimized ${DTUTIL_LIBRARY}      debug ${DTUTIL_LIBRARY_DEBUG}
                      optimized ${DTCORE_LIBRARY}      debug ${DTCORE_LIBRARY_DEBUG}
                      optimized ${DTABC_LIBRARY}       debug ${DTABC_LIBRARY_DEBUG}
                      optimized ${DTGAME_LIBRARY}      debug ${DTGAME_LIBRARY_DEBUG}
                      optimized ${DTACTORS_LIBRARY}    debug ${DTACTORS_LIBRARY_DEBUG}
                      optimized ${OPENTHREADS_LIBRARY} debug ${OPENTHREADS_LIBRARY_DEBUG}
                      optimized ${OSG_LIBRARY}         debug ${OSG_LIBRARY_DEBUG}
                      optimized ${OSGUTIL_LIBRARY}     debug ${OSGUTIL_LIBRARY_DEBUG}
                      dtEarth # optimized dtOcean                debug dtOceanD
)

IF (MSVC)
  SET(CMAKE_DEBUG_POSTFIX "d")
  SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
ENDIF (MSVC)

# little hack to get the .dll into /bin and .lib into /lib
IF (MSVC_IDE)
  SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES PREFIX "../../../bin/")
  SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES IMPORT_PREFIX "../../")
ENDIF (MSVC_IDE)
