// ----------------------------------------------------------------------------
// EntityControllerCameraOrbit.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityController.hpp>
#include <openrump/InputListener.hpp>
#include <OgreMath.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class EntityBase;
    class Input;
}

namespace OpenRump {

class EntityControllerCameraOrbit :
    public EntityController,
    public InputListener
{
public:

    struct CameraAngle
    {
        CameraAngle(Ogre::Radian x, Ogre::Radian y, Ogre::Radian z) : x(x), y(y), z(z) {}
        Ogre::Radian x;
        Ogre::Radian y;
        Ogre::Radian z;
    };

    /*!
     * @brief Construct and attach to entity.
     * @param sm The Ogre scene manager that holds the camera(s) that could be attached.
     * @param entity The entity to take control of.
     */
    EntityControllerCameraOrbit(Ogre::SceneManager* sm,
                                Input* input);

    /*!
     * @brief Default destructor
     */
    ~EntityControllerCameraOrbit();

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
    void setCamera(Ogre::Camera* cam);

    /*!
     * @brief Python binding for setting the camera
     * @param cameraName The global identifier of the camera to set.
     */
    void pySetCamera(std::string cameraName);

    /*!
     * @brief Detaches the camera from orbit
     * @note This does not remove the camera orbit nodes. If you wish to
     * destroy the camera orbit nodes, use destroyCameraOrbit() instead.
     * @return The camera that was detached is returned. If not camera was
     * attached to begin with, nullptr is returned.
     */
    Ogre::Camera* removeCamera();

    /*!
     * @brief Detaches the camera from the orbit.
     * @note This does the same as detachCameraFromOrbit.
     */
    void pyRemoveCamera();

    /*!
     * @brief Sets the distance constraints of the camera.
     * The default behaviour is for everything to be 0.
     * @param min The minimum distance allowed from the center of rotation.
     * @param max The maximum distance allowed from the center of rotation.
     */
    void setDistanceConstraints(float min, float max);

    /*!
     * @brief Sets the distance of the camera from the center of rotation.
     * @param distance The distance to set. This value is clamped to the min
     * and max values.
     */
    void setDistance(float distance);

    /*!
     * @brief Rotates the camera around the orbit it is attached to.
     */
    void setRotationZYX(Ogre::Radian x, Ogre::Radian y, Ogre::Radian z);

    /*!
     * @brief Python exposed version
     * Parameters are in radian.
     */
    void pySetRotation(float x, float y, float z);

    /*!
     * @brief Gets the attached camera
     * @return A pointer to the attached camera, or a nullptr if no camera is
     * attached.
     */
    Ogre::Camera* getCamera() const;

    /*!
     * @brief Gets the rotation scene node for rotating the camera
     */
    Ogre::SceneNode* getCameraRotateNode() const;

private:

    /*!
     * @brief Will reconstruct all the supporting scene nodes and camera if required.
     */
    void reconstructSceneNodesAndCamera();

    /*!
     * @brief Creates the supporting scene node structure to attach the camera to.
     * The scene nodes are attached to the entity's translate scene node.
     * @param entity The entity to create the scene nodes on.
     */
    void createCameraOrbit(EntityBase* entity);

    /*!
     * @brief Removes the supporting scene node structure and detaches the camera.
     */
    void destroyCameraOrbit();

    // override input events
    virtual void onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY);
    virtual void onChangeCameraDistanceDelta(float deltaDistance);

    // override entity registration events
    virtual void notifyEntityChange(EntityBase*);

    Ogre::Real m_CameraDistance;
    Ogre::Real m_MaxCameraDistance;
    Ogre::Real m_MinCameraDistance;

    Ogre::SceneManager* m_SceneManager;

    Ogre::SceneNode* m_CameraOrbitRotateNode;
    Ogre::SceneNode* m_CameraOrbitAttachNode;
    Ogre::Camera* m_OrbitingCamera;

    Input* m_Input;

    CameraAngle m_CameraAngle;
};

} // namespace OpenRump
