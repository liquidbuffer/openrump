###############################################################################

cmake_minimum_required (VERSION 2.8.11)
project (AppOpenRump)

#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation, otherwise
# set MAKE_BUILD_TYPE to Debug prior to calling PROJECT()
if (DEFINED CMAKE_BUILD_TYPE)
	if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
		set (CMAKE_BUILD_TYPE Debug)
	endif ()
	set (CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
else()
	set (CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif()

###############################################################################
# set output locations
###############################################################################
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
if (MSVC)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
else ()
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Packages")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Utils")

###############################################################################
# library definitions
###############################################################################
add_definitions (
	-DOPENRUMP_DYNAMIC
)

###############################################################################
# compiler definitions and flags
###############################################################################

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	add_definitions (-std=c++11 -pedantic)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	add_definitions (-std=c++11 -pedantic)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(
		-D_DEBUG
		-DDEBUG
	)
endif ()

###############################################################################
# generate ignored folders
# these are populate later on during configuration of individual targets
###############################################################################

# generate ignored folders
file (MAKE_DIRECTORY "res/plugins")
file (WRITE "res/plugins/.gitignore" "*")
file (MAKE_DIRECTORY "res/mesh")
file (WRITE "res/mesh/.gitignore" "*")

# cmake's external dependencies
set (EXTERNAL_DEP_DIR "${CMAKE_SOURCE_DIR}/cmake-dep")
set (CMAKE_PREFIX_PATH "${EXTERNAL_DEP_DIR}")
set (CMAKE_INCLUDE_PATH "${EXTERNAL_DEP_DIR}/include")
set (CMAKE_LIBRARY_PATH "${EXTERNAL_DEP_DIR}/lib")
file (MAKE_DIRECTORY ${EXTERNAL_DEP_DIR})
file (WRITE "${EXTERNAL_DEP_DIR}/.gitignore" "*")
link_directories ("${EXTERNAL_DEP_DIR}/lib")
include_directories ("${EXTERNAL_DEP_DIR}/include")

###############################################################################
# Dependency settings
###############################################################################

include_directories ("openrump/include")

add_subdirectory ("openrump")
add_subdirectory ("app")

