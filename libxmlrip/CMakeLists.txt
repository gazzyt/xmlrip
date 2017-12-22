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
	token.cpp
    tokeniser.cpp
    xmlelement.cpp
	xmlattribute.cpp
    xmlelementreader.cpp
    xmlpredicate.cpp
	xmlexpression.cpp
	stringutils.cpp
	xmlelementreader-iterator.cpp
	customstreamflags.cpp
	xmlstreammodifiers.cpp
	inlinebuffer.cpp
	internalparserxpathprocessor.cpp
	libxmlxpathprocessor.cpp
	exception/baseexception.cpp
	exception/xpathexception.cpp
)

set( BUILD_LIBXMLRIP_MANIFEST_HEADERS
    token.h
    tokeniser.h
    xmlelement.h
	xmlattribute.h
    xmlelementreader.h
    xmlpredicate.h
	xmlexpression.h
	stringutils.h
	memoryutils.h
	xmlelementreader-iterator.h
	customstreamflags.h
	xmlstreammodifiers.h
	inlinebuffer.h
	internalparserxpathprocessor.h
	libxmlxpathprocessor.h
	libxmlattributecollection.h
	libxmlattributecollection-iterator.h
	exception/baseexception.h
	exception/xpathexception.h
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
