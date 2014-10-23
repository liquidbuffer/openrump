###############################################################################
# Input variables
#   CMAKE_COMMON_ARGS:list
#     - a list of cmake arguments to pass to the cmake command when configuring
###############################################################################

macro (link_ogre TARGET_NAME)
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
    target_link_libraries (${TARGET_NAME} ${OGRE_LIBRARIES})
    
    add_dependencies (${TARGET_NAME} Ogre_PROJECT)

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
endmacro (link_ogre)