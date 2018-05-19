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
    xmlelement.cpp
	xmlattribute.cpp
    xmlpredicate.cpp
	xpathtoken.cpp
	xpathtokeniser.cpp
	xmlexpression.cpp
	stringutils.cpp
	customstreamflags.cpp
	xmlstreammodifiers.cpp
	libxmlprint.cpp
	libxmlxpathprocessor.cpp
	libxmlutils.cpp
	porting.cpp
	exception/baseexception.cpp
	exception/xpathexception.cpp
	exception/printexception.cpp
)

set( BUILD_LIBXMLRIP_MANIFEST_HEADERS
    xmlelement.h
	xmlattribute.h
    xmlpredicate.h
	xpathtoken.h
	xpathtokeniser.h
	xmlexpression.h
	stringutils.h
	memoryutils.h
	customstreamflags.h
	xmlstreammodifiers.h
	libxmlprint.h
	libxmlxpathprocessor.h
	libxmlattributecollection.h
	libxmlattributecollection-iterator.h
	libxmlutils.h
	porting.h
	exception/baseexception.h
	exception/xpathexception.h
	exception/printexception.h
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
