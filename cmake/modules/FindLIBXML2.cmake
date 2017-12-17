# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

IF(WIN32)
	include(${CMAKE_SOURCE_DIR}/cmake/DownloadProject.cmake)

	download_project(PROJ                libiconv 
					 PREFIX   3rd_party
					 URL      https://github.com/ShiftMediaProject/libiconv/releases/download/v1.15-2/libiconv_v1.15-2_msvc15.zip
					 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
	)

	download_project(PROJ                libxml2 
					 PREFIX   3rd_party
					 URL      https://github.com/ShiftMediaProject/libxml2/releases/download/v2.9.7/libxml2_v2.9.7_msvc15.zip
					 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
	)

	find_path(LIBXML2_INCLUDE_DIR libxml/xpath.h
			  HINTS ${CMAKE_BINARY_DIR}/3rd_party/libxml2-src/include
			  PATH_SUFFIXES libxml2 )

	find_path(LIBXML2_ICONV_INCLUDE_DIR iconv.h
			  HINTS ${CMAKE_BINARY_DIR}/3rd_party/libiconv-src/include )

	find_library(LIBXML2_LIBRARY NAMES libxml2 xml2
				 HINTS ${CMAKE_BINARY_DIR}/3rd_party/libxml2-src/lib/$ENV{VSCMD_ARG_TGT_ARCH} )

ELSE()
	find_package(PkgConfig)
	pkg_check_modules(PC_LIBXML QUIET libxml-2.0)
	set(LIBXML2_DEFINITIONS ${PC_LIBXML_CFLAGS_OTHER})

	find_path(LIBXML2_INCLUDE_DIR NAMES libxml/xpath.h
		HINTS ${PC_LIBXML_INCLUDEDIR} ${PC_LIBXML_INCLUDE_DIRS}
		PATH_SUFFIXES libxml2)

	# Assume that iconv.h is in the same place as libxml/xpath.h
	set(LIBXML2_ICONV_INCLUDE_DIR ${LIBXML2_INCLUDE_DIR})

	find_library(LIBXML2_LIBRARY NAMES xml2 libxml2
		HINTS ${PC_LIBXML_LIBDIR} ${PC_LIBXML_LIBRARY_DIRS})

ENDIF()

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBXML2  DEFAULT_MSG
                                  LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR LIBXML2_ICONV_INCLUDE_DIR)

mark_as_advanced(LIBXML2_INCLUDE_DIR LIBXML2_LIBRARY LIBXML2_ICONV_INCLUDE_DIR)

set(LIBXML2_LIBRARIES ${LIBXML2_LIBRARY} )
set(LIBXML2_INCLUDE_DIRS ${LIBXML2_INCLUDE_DIR} ${LIBXML2_ICONV_INCLUDE_DIR})