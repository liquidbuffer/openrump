###############################################################################
# Input variables
#     OpenRump_USE_INTERNAL_DEPENDENCIES:BOOL
#       - Set to true if the folder "dep" exists in the source root
###############################################################################

project (OpenRump)

set (OpenRump_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
set (OpenRump_SOURCES
	"src/AnimationController.cpp"
	"src/App.cpp"
	"src/BaseApp.cpp"
	"src/EntityBase.cpp"
	"src/EntityPlayer.cpp"
	"src/Game.cpp"
	"src/Input.cpp"
	"src/InputListener.cpp"
	"src/LoopTimer.cpp"
	"src/OgreRenderComponent.cpp"
	"src/OISInput.cpp"
	"src/PyCallbackDispatcher.cpp"
	"src/PyEntityPlayerInterface.cpp"
	"src/PyGameInterface.cpp"
	"src/PyInterface.cpp"
	"src/RendererFrameListener.cpp"
)
set (OpenRump_HEADERS
	"include/openrump/AnimationController.hpp"
	"include/openrump/App.hpp"
	"include/openrump/BaseApp.hpp"
	"include/openrump/Config.hpp"
	"include/openrump/EntityBase.hpp"
	"include/openrump/EntityPlayer.hpp"
	"include/openrump/Export.hpp"
	"include/openrump/Game.hpp"
	"include/openrump/Input.hpp"
	"include/openrump/InputListener.hpp"
	"include/openrump/ListenerDispatcher.hpp"
	"include/openrump/ListenerDispatcher.hxx"
	"include/openrump/LoopTimer.hpp"
	"include/openrump/OgreRenderComponent.hpp"
	"include/openrump/OISInput.hpp"
	"include/openrump/PyCallbackDispatcher.hpp"
	"include/openrump/PyInterface.hpp"
	"include/openrump/RendererFrameListener.hpp"
)

add_library (OpenRump SHARED
	${OpenRump_SOURCES}
	${OpenRump_HEADERS}
)

if (NOT OpenRump_USE_INTERNAL_DEPENDENCIES)
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
	# Boost - Ogre requires at least 1.46.0
	find_package (Boost 1.46.0 REQUIRED COMPONENTS
		python)
	include_directories (${Boost_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${Boost_python_LIBRARY})

	###############################################################################
	# Python
	set (Python_ADDITIONAL_VERSIONS "2.7")
	find_package (PythonLibs REQUIRED)
	include_directories (${PYTHON_INCLUDE_DIRS})
else ()
	include_directories ("${CMAKE_SOURCE_DIR}/dep/ogre_src_v1-9-0/OgreMain/include")
	include_directories ("${CMAKE_BINARY_DIR}/dep/ogre_src_v1-9-0/include")
	target_link_libraries (OpenRump OgreMain)
endif ()
