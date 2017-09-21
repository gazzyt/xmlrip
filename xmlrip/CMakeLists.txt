# Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.

project( "xmlrip" )

#
# Configuration
#

#
# Dependencies
#

#
# Build
#

set( BUILD_XMLRIP_MANIFEST
    main.cpp
)

set( BUILD_XMLRIP_MANIFEST_HEADERS
)

add_executable( xmlrip ${BUILD_XMLRIP_MANIFEST} ${BUILD_XMLRIP_MANIFEST_HEADERS})

target_link_libraries( xmlrip libxmlrip)
target_include_directories( xmlrip PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/libxmlrip" )


#
# Install
#
#include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

#install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
#install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
#install( TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION "library"
#         ARCHIVE DESTINATION "library" COMPONENT library )
