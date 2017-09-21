# Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.

project( "libxmlrip" )

#
# Configuration
#

#
# Dependencies
#

#
# Build
#

set( BUILD_LIBXMLRIP_MANIFEST
    tokeniser.cpp
)

set( BUILD_LIBXMLRIP_MANIFEST_HEADERS
    token.h
    tokeniser.h
)

add_library( libxmlrip ${BUILD_LIBXMLRIP_MANIFEST} ${BUILD_LIBXMLRIP_MANIFEST_HEADERS})
target_include_directories( libxmlrip PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )


#
# Install
#
#include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

#install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
#install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
#install( TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION "library"
#         ARCHIVE DESTINATION "library" COMPONENT library )
