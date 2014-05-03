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
# ".lib" files are exportet to the "lib" folder
# ".exe" and ".dll" files are exported to the "bin" folder
###############################################################################
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Packages")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Utils")

add_definitions (
    -DOPENRUMP_DYNAMIC
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(
        -D_DEBUG
        -DDEBUG
    )
endif ()


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

add_subdirectory ("openrump")
add_subdirectory ("app")

