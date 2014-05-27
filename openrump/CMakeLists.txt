###############################################################################
# Input variables
#     OpenRump_USE_INTERNAL_DEPENDENCIES:BOOL
#       - Set to true if the folder "dep" exists in the source root
###############################################################################

project (OpenRump)

set (OpenRump_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
set (OpenRump_SOURCES
    "${OpenRump_SOURCE_DIR}/src/AnimationController.cpp"
	"${OpenRump_SOURCE_DIR}/src/App.cpp"
	"${OpenRump_SOURCE_DIR}/src/BaseApp.cpp"
	"${OpenRump_SOURCE_DIR}/src/Entity.cpp"
	"${OpenRump_SOURCE_DIR}/src/EntityPlayer.cpp"
	"${OpenRump_SOURCE_DIR}/src/Input.cpp"
	"${OpenRump_SOURCE_DIR}/src/InputListener.cpp"
	"${OpenRump_SOURCE_DIR}/src/OgreRenderer.cpp"
	"${OpenRump_SOURCE_DIR}/src/OISInput.cpp"
	"${OpenRump_SOURCE_DIR}/src/RendererFrameListener.cpp"
)
set (OpenRump_HEADERS
    "${OpenRump_SOURCE_DIR}/include/openrump/AnimationController.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/App.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/BaseApp.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/Entity.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/EntityPlayer.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/Input.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/InputListener.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/ListenerDispatcher.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/ListenerDispatcher.hxx"
	"${OpenRump_SOURCE_DIR}/include/openrump/OgreRenderer.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/OISInput.hpp"
	"${OpenRump_SOURCE_DIR}/include/openrump/RendererFrameListener.hpp"
)

set (OpenRump_INCLUDE_DIR "${OpenRump_SOURCE_DIR}/include" CACHE PATH "" FORCE)
include_directories (${OpenRump_INCLUDE_DIR})

add_library (OpenRump SHARED
	${OpenRump_SOURCES}
	${OpenRump_HEADERS}
)

if (NOT OpenRump_USE_INTERNAL_DEPENDENCIES)
	find_package (OGRE REQUIRED)
	include_directories (${OGRE_INCLUDE_DIRS})
	message(${OGRE_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${OGRE_LIBRARIES})

	find_package (OIS REQUIRED)
	include_directories (${OIS_INCLUDE_DIRS})
	target_link_libraries (OpenRump ${OIS_LIBRARIES})
else ()
	include_directories ("${CMAKE_SOURCE_DIR}/dep/ogre_src_v1-9-0/OgreMain/include")
	include_directories ("${CMAKE_BINARY_DIR}/dep/ogre_src_v1-9-0/include")
	target_link_libraries (OpenRump OgreMain)
endif ()
