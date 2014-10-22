###############################################################################
# Input variables
#     OpenRump_USE_INTERNAL_DEPENDENCIES:BOOL
#       - Set to true if the folder "dep" exists in the source root
###############################################################################

project (OpenRump)
include (ExternalProject)

set (OpenRump_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
file (GLOB_RECURSE OpenRump_SOURCES "src/*.cpp")
file (GLOB_RECURSE OpenRump_HEADERS "include/openrump/*.hpp" "include/openrump/*.h")

add_library (OpenRump SHARED
	${OpenRump_SOURCES}
	${OpenRump_HEADERS}
)

set (COMMON_CMAKE_FLAGS
	-DCMAKE_INSTALL_PREFIX=${EXTERNAL_DEP_DIR}
	-DCMAKE_PREFIX_PATH=${EXTERNAL_DEP_DIR}
	-DCMAKE_INCLUDE_PATH=${EXTERNAL_DEP_DIR}/include
	-DCMAKE_LIBRARY_PATH=${EXTERNAL_DEP_DIR}/lib
)

# the default stdlibc++ when using C++11 in the main project. Additionally,
# disable the -Wdeprecated-register warning.
if (APPLE)
	set (COMMON_CMAKE_FLAGS ${COMMON_CMAKE_FLAGS}
		-DCMAKE_OSX_ARCHITECTURES="x86_64"
		-DCMAKE_C_FLAGS="-stdlib=libc++"
		"-DCMAKE_CXX_FLAGS='-std=c++11 -stdlib=libc++ -Wno-deprecated-register'"
	)
endif (APPLE)

###############################################################################
# install ogre's dependencies if required
# zlib, zziplib, freetype, freeimage
find_package (ZLIB)
find_package (ZZip)
find_package (Freetype)
find_package (FreeImage)
if ((NOT ZLIB_FOUND) OR (NOT ZZip_FOUND) OR (NOT FREETYPE_FOUND) OR (NOT FreeImage_FOUND))
	message (STATUS "OGREDEPS will be downloaded automatically")
	externalproject_add (OGREDEPS_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		HG_REPOSITORY "https://bitbucket.org/cabalistic/ogredeps/"
		HG_TAG "default"
		CMAKE_ARGS ${COMMON_CMAKE_FLAGS}
	)
else ()
	add_custom_target (OGREDEPS_PROJECT)
endif ()

###############################################################################
# Python
message (STATUS "Looking for Python...")
find_package (PythonLibs 2.7 REQUIRED)
# hack to force python 2.7
string (REGEX REPLACE "[0-9]\\.[0-9]" "2.7" PYTHON_LIBRARIES
	${PYTHON_LIBRARIES})
string (REGEX REPLACE "[0-9]\\.[0-9]" "2.7" PYTHON_INCLUDE_DIRS
	${PYTHON_INCLUDE_DIRS})
# make sure the replaced version exists
if (NOT EXISTS ${PYTHON_LIBRARIES} OR NOT EXISTS ${PYTHON_INCLUDE_DIRS})
        message (FATAL "Could NOT Find Python 2.7. Please download and install Python 2.7.")
endif ()
message (STATUS "Found Python library: ${PYTHON_LIBRARIES}")
message (STATUS "Found Python headers: ${PYTHON_INCLUDE_DIRS}")
include_directories (${PYTHON_INCLUDE_DIRS})
target_link_libraries (OpenRump ${PYTHON_LIBRARIES})

###############################################################################
# Boost - Ogre requires at least 1.46.0
find_package (Boost 1.46.0 COMPONENTS
	system
	python)
if (Boost_FOUND)
	add_custom_target (BOOST_PROJECT)
	# hack to force boost to use python2.7
	string (REGEX REPLACE "[0-9]\\.[0-9]" "2.7" Boost_PYTHON_LIBRARY ${Boost_PYTHON_LIBRARY})
	# make sure the replaced version exists
	if (NOT EXISTS ${Boost_PYTHON_LIBRARY})
		message (FATAL "Failed to downgrade Boost.Python to version 2.7. Please make sure you've built Boost.Python with python 2.7 support.")
	endif ()
	include_directories (${Boost_INCLUDE_DIRS})
	target_link_libraries (OpenRump
		${Boost_SYSTEM_LIBRARY}
		${Boost_PYTHON_LIBRARY}
	)
	message (STATUS "python library is: ${Boost_PYTHON_LIBRARY}")
else (Boost_FOUND)
	message (STATUS "Boost will be downloaded automatically")

	# windows specific settings
	if (WIN32)
		set (BOOST_CONFIGURE_COMMAND "bootstrap.bat"
			"--with-python-version=2.7")
		set (BOOST_BUILD_COMMAND "b2")
	else (WIN32)
		set (BOOST_CONFIGURE_COMMAND "./bootstrap.sh"
			"--with-python-version=2.7")
		set (BOOST_BUILD_COMMAND "./b2")
	endif (WIN32)
	set (BOOST_BUILD_COMMAND ${BOOST_BUILD_COMMAND}
		"install"
		"link=shared"
		"--ignore-site-config"
		"--prefix=${EXTERNAL_DEP_DIR}"
		"--with-date_time"
		"--with-chrono"
		"--with-thread"
		"--with-atomic"
		"--with-system"
		"--with-python"
		"--with-signals"
	)

	externalproject_add (BOOST_PROJECT
		DEPENDS OGREDEPS_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		URL "http://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.tar.bz2"
		CONFIGURE_COMMAND ${BOOST_CONFIGURE_COMMAND}
		BUILD_COMMAND ${BOOST_BUILD_COMMAND}
		BUILD_IN_SOURCE 1
		INSTALL_COMMAND ""
	)
	target_link_libraries (OpenRump
		boost_system
		boost_python
	)
endif (Boost_FOUND)

###############################################################################
# Bullet
find_package (BULLET)
if (BULLET_FOUND)
	add_custom_target (Bullet_PROJECT)
else (BULLET_FOUND)
	message (STATUS "Bullet will be downloaded automatically")
	externalproject_add (Bullet_PROJECT
		DEPENDS OGREDEPS_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		GIT_REPOSITORY "git://github.com/bulletphysics/bullet3"
		GIT_TAG "Bullet-2.83-alpha"
		CMAKE_ARGS ${COMMON_CMAKE_FLAGS}
		-DBUILD_EXTRAS=0
		-DBUILD_UNIT_TESTS=0
		-DBUILD_CPU_DEMOS=0
		-DBUILD_BULLET2_DEMOS=0
		-DBUILD_BULLET3=0
		-DBUILD_BULLET3_DEMOS=0
	)
	set (BULLET_INCLUDE_DIR "${EXTERNAL_DEP_DIR}/include/bullet")
	set (BULLET_LIBRARIES
		BulletDynamics
		BulletCollision
		LinearMath
	)
endif (BULLET_FOUND)

include_directories (${BULLET_INCLUDE_DIR})
target_link_libraries (OpenRump ${BULLET_LIBRARIES})

###############################################################################
# Ogre3D
find_package (OGRE)
if (OGRE_FOUND)
	add_custom_target (Ogre_PROJECT)
else (OGRE_FOUND)
	message (STATUS "Ogre will be downloaded automatically")
	externalproject_add (Ogre_PROJECT
		DEPENDS OGREDEPS_PROJECT BOOST_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		HG_REPOSITORY "https://bitbucket.org/sinbad/ogre"
		HG_TAG "v1-9-0"
		CMAKE_ARGS ${COMMON_CMAKE_FLAGS}
		-DOGRE_BUILD_SAMPLES=0
		-DOGRE_BUILD_TOOLS=0
		-DOGRE_INSTALL_SAMPLES=0
	)
	set (OGRE_INCLUDE_DIRS "${EXTERNAL_DEP_DIR}/include/OGRE")
	if (APPLE)
		set (OGRE_LIBRARIES "${EXTERNAL_DEP_DIR}/lib/RelWithDebInfo/Ogre.framework")
		set (OGRE_PLUGIN_DIR_REL "${EXTERNAL_DEP_DIR}/lib/RelWithDebInfo")
	else (APPLE)
		set (OGRE_LIBRARIES "OgreMain")
		set (OGRE_PLUGIN_DIR_REL "${EXTERNAL_DEP_DIR}/lib/OGRE")
	endif (APPLE)
endif (OGRE_FOUND)

include_directories (${OGRE_INCLUDE_DIRS})
target_link_libraries (OpenRump ${OGRE_LIBRARIES})

# copy required plugins to local plugins folder
if (CMAKE_BUILD_TYPE MATCHES Release)
	set (OGRE_PLUGIN_DIR ${OGRE_PLUGIN_DIR_REL})
else ()
	set (OGRE_PLUGIN_DIR ${OGRE_PLUGIN_DIR_DBG})
endif ()
message (STATUS "Ogre plugin dir: ${OGRE_PLUGIN_DIR}")
file (GLOB OGRE_PLUGINS
	"${OGRE_PLUGIN_DIR}/RenderSystem_GL*"
	"${OGRE_PLUGIN_DIR}/Plugin_OctreeSceneManager*"
)
message (STATUS "Copying plugins: ${OGRE_PLUGINS}")
file (COPY ${OGRE_PLUGINS}
	DESTINATION "${CMAKE_SOURCE_DIR}/res/plugins")

###############################################################################
# OIS
find_package (OIS REQUIRED)
include_directories (${OIS_INCLUDE_DIRS})
target_link_libraries (OpenRump ${OIS_LIBRARIES})

###############################################################################
# Ontology
if (EXISTS "${EXTERNAL_DEP_DIR}/src/ontology_PROJECT-stamp/ontology_PROJECT-done")
	add_custom_target (ontology_PROJECT)
else ()
	externalproject_add (ontology_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		GIT_REPOSITORY "git://github.com/TheComet93/ontology.git"
		GIT_TAG "master"
		CMAKE_ARGS ${COMMON_CMAKE_FLAGS}
	)
endif ()
target_link_libraries (OpenRump ontology)

add_dependencies (OpenRump
	BOOST_PROJECT
	Bullet_PROJECT
	Ogre_PROJECT
	ontology_PROJECT
)
