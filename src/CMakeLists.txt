SET(LIB_NAME dtEarth)

SET(EARTH_SRCS
  ${CMAKE_SOURCE_DIR}/src/actorregistry.cpp
  ${CMAKE_SOURCE_DIR}/src/earthactor.cpp
)

SET(EARTH_HDRS
  ${CMAKE_SOURCE_DIR}/include/dtEarth/actorregistry.h
  ${CMAKE_SOURCE_DIR}/include/dtEarth/export.h  
  ${CMAKE_SOURCE_DIR}/include/dtEarth/earthactor.h  
)

ADD_LIBRARY(${LIB_NAME} SHARED ${EARTH_SRCS} ${EARTH_HDRS})

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES DEFINE_SYMBOL DT_EARTH_LIBRARY)
SET_TARGET_PROPERTIES(${LIB_NAME} 
                       PROPERTIES FRAMEWORK TRUE 
                       PUBLIC_HEADER "${EARTH_HDRS}"
                       )

# little hack to get the .dll into /bin and .lib into /lib
IF (MSVC)
  SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES PREFIX "../../bin/")
  SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES IMPORT_PREFIX "../../lib/")
ENDIF (MSVC)

TARGET_LINK_LIBRARIES(${LIB_NAME}
                      optimized ${DTUTIL_LIBRARY}      debug ${DTUTIL_LIBRARY_DEBUG}
                      # optimized ${DTDAL_LIBRARY}       debug ${DTDAL_LIBRARY_DEBUG}
                      optimized ${DTCORE_LIBRARY}      debug ${DTCORE_LIBRARY_DEBUG}
                      optimized ${DTABC_LIBRARY}       debug ${DTABC_LIBRARY_DEBUG}
                      optimized ${DTGAME_LIBRARY}      debug ${DTGAME_LIBRARY_DEBUG}
                      optimized ${DTACTORS_LIBRARY}    debug ${DTACTORS_LIBRARY_DEBUG}
                      #optimized ${DTQT_LIBRARY}        debug ${DTQT_LIBRARY_DEBUG}
                      optimized ${OPENTHREADS_LIBRARY} debug ${OPENTHREADS_LIBRARY_DEBUG}
                      optimized ${OSG_LIBRARY}         debug ${OSG_LIBRARY_DEBUG}
                      optimized ${OSGDB_LIBRARY}       debug ${OSGDB_LIBRARY_DEBUG}
                      optimized ${OSGUTIL_LIBRARY}     debug ${OSGUTIL_LIBRARY_DEBUG}
                      optimized ${OSGEARTH_LIBRARY}  debug ${OSGEARTH_LIBRARY_DEBUG}
)
								
IF (MSVC)
  SET(CMAKE_DEBUG_POSTFIX "d")
  SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
ENDIF (MSVC)

INSTALL(TARGETS ${LIB_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/dtEarth
)

IF (MSVC)
  FILE(TO_CMAKE_PATH $ENV{DELTA_BUILD}/bin/ path)
  GET_TARGET_PROPERTY(location ${LIB_NAME} DEBUG_LOCATION)
  GET_TARGET_PROPERTY(location_r ${LIB_NAME} RELEASE_LOCATION)
  ADD_CUSTOM_COMMAND(TARGET ${LIB_NAME}
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${location} ${path}
                     COMMAND ${CMAKE_COMMAND} -E echo "Copying ${location} to ${path}")
  ADD_CUSTOM_COMMAND(TARGET ${LIB_NAME}
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${location_r} ${path}
                     COMMAND ${CMAKE_COMMAND} -E echo "Copying ${location_r} to ${path}")
ENDIF (MSVC)
