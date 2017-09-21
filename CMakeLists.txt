project( "xmlrip-root" )

cmake_minimum_required( VERSION 2.8.10 )

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CODELITE_USE_TARGETS "ON" )

#
# Configuration
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_configuration.cmake" )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules" )

#
# Build
#

# link_libraries( jsoncpp ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_subdirectory (libxmlrip)
add_subdirectory (xmlrip)


#
# Install
#
#include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

#install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
#install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
#install( TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION "library"
#         ARCHIVE DESTINATION "library" COMPONENT library )
