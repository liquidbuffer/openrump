// ----------------------------------------------------------------------------
// Entity.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <string>

#include <Ogre.h>
#include <OgrePrerequisites.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class SceneManager;
    class EntityBase;
    class SceneNode;
    class Camera;
}

namespace OpenRump {
    class AnimationController;
}

namespace OpenRump {

class EntityBase
{
private:

    /*!
     * @brief Default constructor - only for delegating.
     */
    EntityBase();

protected:

    /*!
     * @brief Constructs an entity.
     * The entity will use the specified scene manager to load itself into
     * memory.
     * @param sm The Ogre scene manager to use.
     */
    EntityBase(Ogre::SceneManager* sm);

    /*!
     * @brief Loads the entity from a mesh name.
     * @param instanceName A globally unique name for this entity.
     * @param meshName The mesh file name to load.
     */
    void load(Ogre::String instanceName, Ogre::String meshName);

public:

    /*!
     * @brief Constructs an entity and loads the specified mesh.
     * @param sm The Ogre scene manager to use.
     * @param instanceName A globally unique name for this entity.
     * @param meshName The mesh file name to load.
     */
    EntityBase(Ogre::SceneManager* sm,
           Ogre::String instanceName,
           Ogre::String meshName);

    /*!
     * @brief Allow destruction through base class pointer
     */
    virtual ~EntityBase();

    /*!
     * @brief Creates scene nodes to support an orbiting camera around the entity
     * Will create two scene nodes, one for rotating, and one for attaching the
     * a camera. It is recommended to use attachCameraToOrbit() instead of
     * calling this method directly - the orbit is created automatically.
     * @return Returns itself for chaining.
     */
    EntityBase* createCameraOrbit();

    /*!
     * @brief Attaches a camera to an orbiting scene node.
     * Will create the orbit nodes if they don't already exist, and attach
     * the camera to it. The rotation scene node is returned - rotating it will
     * rotate the camera in its orbit.
     * @param cam The camera to attach.
     * @param distance The distance the camera should have from the center of
     * orbit.
     * @return Returns the rotation scene node so the camera's orbit can be
     * controlled.
     */
    Ogre::SceneNode* attachCameraToOrbit(Ogre::Camera* cam, float distance=100.0f);

    /*!
     * @brief Detaches the camera from orbit
     * @note This does not remove the camera orbit nodes. If you wish to
     * destroy the camera orbit nodes, use destroyCameraOrbit() instead.
     * @return The camera that was detached is returned. If not camera was
     * attached to begin with, nullptr is returned.
     */
    Ogre::Camera* detachCameraFromOrbit();

    /*!
     * @brief Sets the camera's distance from the centre rotation point.
     * @param distance The distance to set.
     */
    void setCameraDistance(float distance);

    /*!
     * @brief Gets the attached camera
     * @return A pointer to the attached camera, or a nullptr if no camera is
     * attached.
     */
    Ogre::Camera* getCamera() const;

    /*!
     * @brief Gets the rotation scene node for rotatin the camera
     */
    Ogre::SceneNode* getCameraRotateNode() const;

    /*!
     * @brief Destroys the camera orbit, and returns the camera if attached
     * @return Returns the attached camera, or nullptr if there was no camera
     * attached.
     */
    Ogre::Camera* destroyCameraOrbit();

    /*!
     * @brief Check to see if a camera orbit exists
     * @return True if it exists, false if not.
     */
    bool hasCameraOrbit() const;

    Ogre::SceneNode* getTranslateSceneNode();
    Ogre::SceneNode* getRotateSceneNode();

protected:

    /*!
     * @brief Extracts a section from one animation into another animation.
     * The specified section of key frames are extracted from the source
     * animation, scaled to the length of the destination animation and
     * copied. The time frame to extract is specified in seconds.
     * @note The source and destination skeletons should have the same amount
     * of nodes. Copying an animation to a skeleton with less nodes or more
     * nodes doesn't crash, but not sure what that does.
     * @note All existing key frames are erased in the destination animation.
     * @param source The source animation to copy from.
     * @param dest The destination animation to copy to.
     * @param startTime Where to begin copying from the source animation.
     * @param endTime Where to stop copying from the source animation.
     */
    void extractAnimation(Ogre::Animation* source,
                          Ogre::Animation* dest,
                          Ogre::Real startTime,
                          Ogre::Real endTime);

    /*!
     * @brief Enables animation for this entity.
     * Instantiates an animation controller for this entity.
     */
    void enableAnimation();

    /*!
     * @brief Disables animation for this entity.
     */
    void disableAnimation();

    /*!
     * @brief Returns true if animation is enabled.
     */
    bool isAnimated() const;

    AnimationController* getAnimationController() const;

private:

    Ogre::SceneManager* m_SceneManager;
    Ogre::EntityBase* m_OgreEntity;
    Ogre::SceneNode* m_OgreEntityTranslateNode;
    Ogre::SceneNode* m_OgreEntityRotateNode;
    Ogre::SceneNode* m_CameraOrbitRotateNode;
    Ogre::SceneNode* m_CameraOrbitAttachNode;
    Ogre::Camera* m_OrbitingCamera;

    std::unique_ptr<AnimationController> m_AnimationController;

    Ogre::String m_Name;

};

} // namespace OpenRump
