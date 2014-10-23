###############################################################################
# Input variables
#   CMAKE_COMMON_ARGS:list
#     - a list of cmake arguments to pass to the cmake command when configuring
###############################################################################

macro (link_sdl2 TARGET_NAME)
    find_package (SDL2)
    if (SDL2_FOUND)
        add_custom_target (SDL2_PROJECT)
    else (SDL2_FOUND)
        message (STATUS "SDL2 will be downloaded automatically")
        
        externalproject_add (SDL2_PROJECT
            PREFIX ${EXTERNAL_DEP_DIR}
            URL "https://www.libsdl.org/release/SDL2-2.0.3.tar.gz"
            CMAKE_ARGS ${COMMON_CMAKE_FLAGS}
        )
        
        set (SDL2_INCLUDE_DIR "${EXTERNAL_DEP_DIR}/include/SDL2")
        set (SDL2_LIBRARY SDL2)
    endif (SDL2_FOUND)

    include_directories (${SDL2_INCLUDE_DIR})
    target_link_libraries (${TARGET_NAME} ${SDL2_LIBRARY})
    
    add_dependencies (${TARGET_NAME} SDL2_PROJECT)
endmacro (link_sdl2)