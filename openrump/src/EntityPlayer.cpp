// ----------------------------------------------------------------------------
// EntityPlayer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityPlayer.hpp>
#include <openrump/Input.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityPlayer::EntityPlayer(Input* input,
                           Ogre::SceneManager* sm,
                           std::string instanceName,
                           std::string meshName) :
    m_Input(input),
    Entity(sm, instanceName, meshName)
{
    m_Input->event.addListener(this, "EntityPlayer");
}

// ----------------------------------------------------------------------------
EntityPlayer::~EntityPlayer()
{
    m_Input->event.removeListener(this);
}

// ----------------------------------------------------------------------------
void EntityPlayer::onButtonExit()
{
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeDirectionAndVelocity(float x, float y)
{
    // rotate vector by camera angle to get real world direction
    float cs = Ogre::Math::Cos(Ogre::Radian(m_CameraAngleY));
    float sn = Ogre::Math::Sin(Ogre::Radian(m_CameraAngleY));
    Ogre::Vector2 targetPlayerDirection(
            x*cs - y*sn,
            x*sn + y*cs
    );

    //
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY)
{
    // add deltas and limit X angle to +90° and -90°
    m_CameraAngle.x -= Ogre::Radian(deltaAngleX);
    m_CameraAngle.y -= Ogre::Radian(deltaAngleY);
    if(m_CameraAngle.x < Ogre::Radian(-Ogre::Math::PI*0.5f))
        m_CameraAngle.x = Ogre::Radian(-Ogre::Math::PI*0.5f);
    if(m_CameraAngle.x > Ogre::Radian(Ogre::Math::PI*0.5f))
        m_CameraAngle.x = Ogre::Radian(Ogre::Math::PI*0.5f);

    // apply to camera
    this->getCameraRotateNode()->setOrientation(Ogre::Quaternion());
    this->getCameraRotateNode()->yaw(m_CameraAngle.y);
    this->getCameraRotateNode()->pitch(m_CameraAngle.x);
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeCameraDistanceDelta(float deltaDistance)
{
}

} // namespace OpenRump
