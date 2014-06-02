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
    m_CameraDistance(200.0f),
    m_CameraDistanceMax(500.0f),
    m_CameraDistanceMin(100.0f),
    m_PlayerDirection(),
    m_TargetPlayerDirection(),
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
void EntityPlayer::onChangeDirectionAndVelocity(float x, float y)
{
    // rotate vector by camera angle to get real world direction
    if(x != 0.0f || y != 0.0f)
    {
        float cs = Ogre::Math::Cos(m_CameraAngle.y);
        float sn = Ogre::Math::Sin(m_CameraAngle.y);
        m_TargetPlayerDirection = Ogre::Vector2(
                x*cs - y*sn,
                x*sn + y*cs
        );
    }
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
    m_CameraDistance = Ogre::Math::Clamp(
        (m_CameraDistanceMin - m_CameraDistance) * 0.05f * deltaDistance + m_CameraDistance,
        m_CameraDistanceMin,
        m_CameraDistanceMax
    );

    this->setCameraDistance(m_CameraDistance);
}

} // namespace OpenRump
