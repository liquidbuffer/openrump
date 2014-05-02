###############################################################################

cmake_minimum_required (VERSION 2.8.11)
project (AppOpenRump)

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

add_definitions (-DOPENRUMP_DYNAMIC)


###############################################################################
# Detect internal dependencies
###############################################################################
if (EXISTS dep/)
	add_subdirectory ("dep")
	set (OpenRump_USE_INTERNAL_DEPENDENCIES:BOOL=TRUE)
else ()
	set (_dep_message "WARNING: Dependencies directory \"dep\" not found. If the project failes to compile, \n")
	set (_dep_message ${_dep_message} "   try adding the dependency repository as a submodule like so:\n")
	set (_dep_message ${_dep_message} "       $ git submodule add git://github.com/openrump-dep.git dep\n")
	message (STATUS ${_dep_message})
	set (OpenRump_USE_INTERNAL_DEPENDENCIES:BOOL=FALSE)
endif ()

add_subdirectory ("openrump")
add_subdirectory ("app")

