set (AppOpenRump_SOURCES
	"src/main.cpp"
)
set (AppOpenRump_HEADERS
)

add_executable (AppOpenRump
	${AppOpenRump_SOURCES}
	${AppOpenRump_HEADERS}
)
target_link_libraries (AppOpenRump
	OpenRump
)
