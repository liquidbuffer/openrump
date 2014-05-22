// ----------------------------------------------------------------------------
// Entity.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <string>

#include <OgreFrameListener.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class SceneManager;
    class Entity;
    class SceneNode;
    class Camera;
}

namespace OpenRump {

class Entity :
    public Ogre::FrameListener
{
public:

    /*!
     * @brief Constructs an entity
     * The entity will use the specified scene manager to load itself into
     * memory with the specified instance name and mesh name. If the mesh does
     * not exist, an exception is thrown.
     * @param sm The Ogre scene manager to use.
     * @param instanceName A unique identifier for this instance.
     * @param meshName The name of the mesh file to load.
     */
    Entity(Ogre::SceneManager* sm, std::string instanceName, std::string meshName);

    /*!
     * @brief Allow destruction through base class pointer
     */
    virtual ~Entity();

    /*!
     * @brief Creates scene nodes to support an orbiting camera around the entity
     * Will create two scene nodes, one for rotating, and one for attaching the
     * a camera. It is recommended to use attachCameraToOrbit() instead of
     * calling this method directly - the orbit is created automatically.
     * @return Returns itself for chaining.
     */
    Entity* createCameraOrbit();

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

    /*!
     * @brief Extracts a section of an animation into a new animation state.
     */
    void extractAnimation(Ogre::Animation* source,
                          Ogre::Animation* target,
                          Ogre::Real startTime,
                          Ogre::Real endTime);

private:

    // override virtual functions
    bool frameRenderingQueued(const Ogre::FrameEvent&);

    Ogre::SceneManager* m_SceneManager;
    Ogre::Entity* m_OgreEntity;
    Ogre::SceneNode* m_OgreEntityNode;
    Ogre::SceneNode* m_CameraOrbitRotateNode;
    Ogre::SceneNode* m_CameraOrbitAttachNode;
    Ogre::Camera* m_OrbitingCamera;

    Ogre::AnimationState* m_WalkAnimState;
    std::string m_Name;

};

} // namespace OpenRump
