// ----------------------------------------------------------------------------
// EntityPlayer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Entity.hpp>
#include <openrump/InputListener.hpp>
#include <OgreFrameListener.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Input;
}

namespace OpenRump {

class EntityPlayer :
    public Entity,
    public InputListener,
    public Ogre::FrameListener
{
public:

    /*!
     * @brief Constructs a player using the specified ogre scene manager
     */
    EntityPlayer(Input* inputDispatcher,
                 Ogre::SceneManager*,
                 std::string instanceName,
                 std::string meshName);

    /*!
     * @brief Default destructor
     */
    ~EntityPlayer();

private:

    // override input events
    virtual void onChangeDirectionAndVelocity(float x, float y);
    virtual void onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY);
    virtual void onChangeCameraDistanceDelta(float deltaDistance);

    // override renderer events
    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    Input* m_Input;

    float m_CameraDistance;
    float m_MaxCameraDistance;
    float m_MinCameraDistance;

    Ogre::Vector3 m_PlayerDirection;
    Ogre::Vector3 m_TargetPlayerDirection;

    Ogre::Real m_TargetPlayerSpeed;
    Ogre::Real m_PlayerSpeed;
    Ogre::Real m_MaxPlayerSpeed;

    // camera
    struct CameraAngle_t
    {
        CameraAngle_t(Ogre::Radian x, Ogre::Radian y) : x(x), y(y) {}
        Ogre::Radian x;
        Ogre::Radian y;
    } m_CameraAngle;
};

} // namespace OpenRump
