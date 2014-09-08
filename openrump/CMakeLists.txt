###############################################################################
# Input variables
#     OpenRump_USE_INTERNAL_DEPENDENCIES:BOOL
#       - Set to true if the folder "dep" exists in the source root
###############################################################################

project (OpenRump)

set (OpenRump_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
file (GLOB OpenRump_SOURCES "src/*.cpp")
file (GLOB OpenRump_HEADERS "include/openrump/*.hpp" "include/openrump/*.h")

add_library (OpenRump SHARED
	${OpenRump_SOURCES}
	${OpenRump_HEADERS}
)

if (NOT OpenRump_USE_INTERNAL_DEPENDENCIES)

	###############################################################################
	# Boost - Ogre requires at least 1.46.0
	find_package (Boost 1.46.0 REQUIRED COMPONENTS
		python)
	include_directories (${Boost_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${Boost_PYTHON_LIBRARY})

	###############################################################################
	# Python
	set (Python_ADDITIONAL_VERSIONS "2.7")
	find_package (PythonLibs REQUIRED)
	include_directories (${PYTHON_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${PYTHON_LIBRARIES})

	###############################################################################
	# Ogre3D
	find_package (OGRE REQUIRED)
	include_directories (${OGRE_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${OGRE_LIBRARIES})

	# copy required plugins to local plugins folder
	file (GLOB OGRE_PLUGINS
		"${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL*")
	file (COPY ${OGRE_PLUGINS}
		DESTINATION "${CMAKE_SOURCE_DIR}/res/plugins")

	###############################################################################
	# OIS
	find_package (OIS REQUIRED)
	include_directories (${OIS_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${OIS_LIBRARIES})

	###############################################################################
	# Artemis-CPP
	include (ExternalProject)
	externalproject_add (ArtemisCPP_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		GIT_REPOSITORY "git://github.com/TheComet93/Artemis-Cpp.git"
		GIT_TAG "master"
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_DEP_DIR}
		-DPOSITION_INDEPENDENT_CODE=ON
	)
	target_link_libraries (OpenRump ArtemisCpp)

else ()
	include_directories ("${CMAKE_SOURCE_DIR}/dep/ogre_src_v1-9-0/OgreMain/include")
	include_directories ("${CMAKE_BINARY_DIR}/dep/ogre_src_v1-9-0/include")
	target_link_libraries (OpenRump OgreMain)
endif ()
