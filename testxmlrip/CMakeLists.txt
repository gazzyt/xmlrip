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

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)

# Add gtest
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.7.0.zip
    TIMEOUT 10
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

#
# Build
#

set( BUILD_TEST_MANIFEST
    main.cpp
	tokeniser-test.cpp
)

set( BUILD_TEST_MANIFEST_HEADERS
)

add_executable( testxmlrip ${BUILD_TEST_MANIFEST} ${BUILD_TEST_MANIFEST_HEADERS})

add_dependencies (testxmlrip googletest)

target_link_libraries( testxmlrip  libxmlrip)
target_include_directories( testxmlrip PUBLIC "${CMAKE_SOURCE_DIR}/libxmlrip"  )

# Specify link libraries
ExternalProject_Get_Property(googletest binary_dir)

if(MSVC)
  set(Suffix ".lib")
else()
  set(Suffix ".a")
  set(Pthread "-pthread")
endif()
target_link_libraries(
    testxmlrip
    debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    ${Pthread})


#
# Install
#
#include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

#install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
#install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
#install( TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION "library"
#         ARCHIVE DESTINATION "library" COMPONENT library )
