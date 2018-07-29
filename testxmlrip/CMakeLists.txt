project( "testxmlrip" )

#
# Configuration
#

#
# Dependencies
#

# Enable ExternalProject CMake module
include(ExternalProject)

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


#
# Build
#

set( BUILD_TEST_MANIFEST
    main.cpp
	recordingprinter.cpp
    xmlstepexpr-test.cpp
	xpathtoken-test.cpp
	xpathtokeniser-test.cpp
	xmlexpression-test.cpp
	xpath-test.cpp
	xmlelement-test.cpp
	xmlattribute-test.cpp
	xmlattributepredicate-test.cpp
	libxmlattributecollection-test.cpp
	libxmlattributecollection-iterator-test.cpp
	libxmlutils-test.cpp
)

set( BUILD_TEST_MANIFEST_HEADERS
	recordingprinter.h
	recordingprinteritem.h
)

add_executable( testxmlrip ${BUILD_TEST_MANIFEST} ${BUILD_TEST_MANIFEST_HEADERS})

#add_dependencies (testxmlrip googletest)

target_link_libraries( testxmlrip libxmlrip ${LIBXML2_LIBRARIES} gtest)
target_include_directories( testxmlrip PUBLIC "${CMAKE_SOURCE_DIR}/libxmlrip"  )


if(MSVC)
  set(Suffix ".lib")
else()
  set(Suffix ".a")
  set(Pthread "-pthread")
endif()

add_test(TESTS testxmlrip)

#
# Install
#
#include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

#install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
#install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
#install( TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION "library"
#         ARCHIVE DESTINATION "library" COMPONENT library )
