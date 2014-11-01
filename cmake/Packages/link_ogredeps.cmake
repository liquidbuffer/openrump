###############################################################################
# install ogre's dependencies if required
# zlib, zziplib, freetype, freeimage
include (ExternalProject)
macro (link_ogredeps TARGET_NAME)
    find_package (ZLIB)
    find_package (ZZip)
    find_package (Freetype)
    find_package (FreeImage)
    if ((NOT ZLIB_FOUND) OR (NOT ZZip_FOUND) OR (NOT FREETYPE_FOUND) OR (NOT FreeImage_FOUND))
        message (STATUS "OGREDEPS will be downloaded automatically")

        # needs to be patched so SDK version on mac is ignored
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set (PATCH_COMMAND patch ${EXTERNAL_DEP_DIR}/src/OGREDEPS_PROJECT/CMakeLists.txt < ${CMAKE_SOURCE_DIR}/cmake/Patches/OgreDepsCMakeLists.patch)
        endif ()
        externalproject_add (OGREDEPS_PROJECT
            PREFIX ${EXTERNAL_DEP_DIR}
            HG_REPOSITORY "https://bitbucket.org/cabalistic/ogredeps/"
            HG_TAG "default"
            PATCH_COMMAND ${PATCH_COMMAND}
            CMAKE_ARGS ${COMMON_CMAKE_FLAGS}
        )
    else ()
        add_custom_target (OGREDEPS_PROJECT)
    endif ()
    add_dependencies (${TARGET_NAME} OGREDEPS_PROJECT)
endmacro (link_ogredeps)
