// ----------------------------------------------------------------------------
// EntityPlayer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityPlayer.hpp>
#include <openrump/Input.hpp>

#include <OgreRoot.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityPlayer::EntityPlayer(Input* input,
                           Ogre::SceneManager* sm,
                           std::string instanceName,
                           std::string meshName) :
    m_Input(input),
    m_CameraDistance(200),
    m_MaxCameraDistance(500),
    m_MinCameraDistance(100),
    m_PlayerDirection(0, 0, 1),
    m_TargetPlayerDirection(0, 0, 1),
    m_TargetPlayerSpeed(0),
    m_PlayerSpeed(0),
    m_MaxPlayerSpeed(1),
    m_PlayerTurnAccelerationFactor(10),
    m_RollAngleIntensityFactor(100),
    m_RollAngleAccelerationFactor(0.01),
    m_RollAngle(0),
    m_MaxRollAngle(Ogre::Degree(40)),
    m_CameraAngle(Ogre::Radian(0), Ogre::Radian(0)),
    Entity(sm, instanceName, meshName)
{
    m_Input->event.addListener(this, "EntityPlayer");
    Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

// ----------------------------------------------------------------------------
EntityPlayer::~EntityPlayer()
{
    Ogre::Root::getSingletonPtr()->removeFrameListener(this);
    m_Input->event.removeListener(this);
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeDirectionAndVelocity(float x, float y)
{
    // rotate vector by camera angle to get real world direction
    if(x != 0 || y != 0)
    {
        Ogre::Real cs = Ogre::Math::Cos(-m_CameraAngle.y);
        Ogre::Real sn = Ogre::Math::Sin(-m_CameraAngle.y);
        m_TargetPlayerDirection = Ogre::Matrix3(
                cs,  0, -sn,
                0,   1,   0,
                sn,  0,  cs
        ) * Ogre::Vector3(x, 0, y);

        m_TargetPlayerSpeed = m_MaxPlayerSpeed;

    // directional vector of length 0.0 means target speed is 0
    }else
        m_TargetPlayerSpeed = 0.0;
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY)
{
    // add deltas and limit X angle to +90° and -90°
    m_CameraAngle.x -= Ogre::Radian(deltaAngleX);
    m_CameraAngle.y -= Ogre::Radian(deltaAngleY);
    if(m_CameraAngle.x < Ogre::Radian(-Ogre::Math::PI*0.5))
        m_CameraAngle.x = Ogre::Radian(-Ogre::Math::PI*0.5);
    if(m_CameraAngle.x > Ogre::Radian(Ogre::Math::PI*0.5))
        m_CameraAngle.x = Ogre::Radian(Ogre::Math::PI*0.5);

    // apply to camera
    this->getCameraRotateNode()->setOrientation(Ogre::Quaternion());
    this->getCameraRotateNode()->yaw(m_CameraAngle.y);
    this->getCameraRotateNode()->pitch(m_CameraAngle.x);
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeCameraDistanceDelta(float deltaDistance)
{
    m_CameraDistance = Ogre::Math::Clamp(
        (m_MinCameraDistance - m_CameraDistance) * Ogre::Real(0.05) * deltaDistance + m_CameraDistance,
        m_MinCameraDistance,
        m_MaxCameraDistance
    );

    this->setCameraDistance(m_CameraDistance);
}

// ----------------------------------------------------------------------------
bool EntityPlayer::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // asymptotically approach target speed
    m_PlayerSpeed = Ogre::Math::Clamp(
        m_PlayerSpeed + (m_TargetPlayerSpeed - m_PlayerSpeed) * evt.timeSinceLastFrame * Ogre::Real(5),
        Ogre::Real(0),
        m_MaxPlayerSpeed
    );

    // interpolate directional vector towards target direction
    Ogre::Quaternion targetRotation(m_PlayerDirection.getRotationTo(m_TargetPlayerDirection));
    Ogre::Quaternion actualRotation(Ogre::Quaternion::Slerp(
            evt.timeSinceLastFrame * m_PlayerSpeed * m_PlayerTurnAccelerationFactor,
            Ogre::Quaternion::IDENTITY,
            targetRotation
    ));
    m_PlayerDirection = actualRotation * m_PlayerDirection;
    m_PlayerDirection.normalise();

    // calculate roll angle
    m_RollAngle += (Ogre::Math::Clamp(
                            actualRotation.getYaw()*m_RollAngleIntensityFactor,
                            -m_MaxRollAngle,
                            m_MaxRollAngle
                    ) - m_RollAngle) * m_RollAngleAccelerationFactor;

    // move and rotate player
    this->getRotateSceneNode()->setOrientation(
            Ogre::Quaternion(Ogre::Vector3(0, 1, 0).crossProduct(m_PlayerDirection),
                             Ogre::Vector3(0, 1, 0),
                             m_PlayerDirection)
          * Ogre::Quaternion(m_RollAngle, Ogre::Vector3(0, 0, -1))
    );
    this->getTranslateSceneNode()->translate(m_PlayerDirection * m_PlayerSpeed);

    return true;
}

} // namespace OpenRump
