###############################################################################
# Input variables
#   CMAKE_COMMON_ARGS:list
#     - a list of cmake arguments to pass to the cmake command when configuring
###############################################################################

macro (link_bullet TARGET_NAME)    
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
    target_link_libraries (${TARGET_NAME} ${BULLET_LIBRARIES})
    
    add_dependencies (${TARGET_NAME} Bullet_PROJECT)
endmacro (link_bullet)