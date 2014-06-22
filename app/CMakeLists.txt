set (AppOpenRump_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
set (AppOpenRump_SOURCES
	"${AppOpenRump_SOURCE_DIR}/src/main.cpp"
)
set (AppOpenRump_HEADERS
)

include_directories ("${OpenRump_INCLUDE_DIR}")
include_directories ("${CMAKE_SOURCE_DIR}/build.dep/include")
include_directories ("${CMAKE_SOURCE_DIR}/build.dep/include/python2.7")

add_executable (AppOpenRump
	${AppOpenRump_SOURCES}
	${AppOpenRump_HEADERS}
)
target_link_libraries (AppOpenRump
        OpenRump
        "${CMAKE_SOURCE_DIR}/build.dep/lib/libpython2.7.so"
		"${CMAKE_SOURCE_DIR}/build.dep/lib/libboost_python.so"
)
