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
if (WIN32)
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
if (MSVC)
elseif (MINGW)
elseif (APPLE)
elseif (UNIX)
    add_definitions(
        -std=c++0x
    )
else ()
    message(FATAL_ERROR "Unsupported OS")
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

###############################################################################
# Detect internal dependencies
###############################################################################
if (EXISTS "${CMAKE_SOURCE_DIR}/dep/")
	add_subdirectory ("dep")
	set (OpenRump_USE_INTERNAL_DEPENDENCIES 1)
else ()
	set (_dep_message "WARNING: Dependencies directory \"dep\" not found. If the project failes to compile, \n")
	set (_dep_message ${_dep_message} "   try adding the dependency repository as a submodule like so:\n")
	set (_dep_message ${_dep_message} "       $ git submodule add git://github.com/openrump-dep.git dep\n")
	message (STATUS ${_dep_message})
	set (OpenRump_USE_INTERNAL_DEPENDENCIES 0)
endif ()

include_directories ("openrump/include")

add_subdirectory ("openrump")
add_subdirectory ("app")

