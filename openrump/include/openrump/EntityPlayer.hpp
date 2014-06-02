// ----------------------------------------------------------------------------
// EntityPlayer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Entity.hpp>
#include <openrump/InputListener.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Input;
}

namespace OpenRump {

class EntityPlayer :
    public Entity,
    public InputListener
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

    Input* m_Input;

    float m_CameraDistance;
    float m_CameraDistanceMax;
    float m_CameraDistanceMin;

    Ogre::Vector2 m_PlayerDirection;
    Ogre::Vector2 m_TargetPlayerDirection;


    // camera
    struct CameraAngle_t
    {
        Ogre::Radian x;
        Ogre::Radian y;
    } m_CameraAngle;
};

} // namespace OpenRump
