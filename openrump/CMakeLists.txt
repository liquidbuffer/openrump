project (OpenRump)

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
# Dependencies
###############################################################################

# TODO remove
find_package (OIS REQUIRED)
include_directories (${OIS_INCLUDE_DIRS})
target_link_libraries (OpenRump ${OIS_LIBRARIES})

include (link_ogredeps)
link_ogredeps (OpenRump)
include (link_python)
link_python (OpenRump)
include (link_boost)
link_boost (OpenRump)
include (link_sdl2)
link_sdl2 (OpenRump)
include (link_bullet)
link_bullet (OpenRump)
include (link_ogre)
link_ogre (OpenRump)
include (link_ontology)
link_ontology (OpenRump)

