set (AppOpenRump_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
set (AppOpenRump_SOURCES
	"${AppOpenRump_SOURCE_DIR}/src/main.cpp"
)
set (AppOpenRump_HEADERS
)

include_directories (${OpenRump_INCLUDE_DIR})

add_executable (AppOpenRump
	${AppOpenRump_SOURCES}
	${AppOpenRump_HEADERS}
)
target_link_libraries (AppOpenRump
        OgreMain
        OpenRump
)
