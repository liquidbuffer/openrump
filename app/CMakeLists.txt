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

###############################################################################
# Boost - Ogre requires at least 1.46.0
#find_package (Boost 1.46.0 REQUIRED COMPONENTS
#		python)
#include_directories (${Boost_INCLUDE_DIRS})
#target_link_libraries (AppOpenRump ${Boost_PYTHON_LIBRARY})

###############################################################################
# Python
#set (Python_ADDITIONAL_VERSIONS "2.7")
#find_package (PythonLibs REQUIRED)
#include_directories (${PYTHON_INCLUDE_DIRS})
#target_link_libraries (AppOpenRump ${PYTHON_LIBRARIES})
