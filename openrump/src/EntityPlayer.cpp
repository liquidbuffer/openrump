// ----------------------------------------------------------------------------
// EntityPlayer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityPlayer.hpp>
#include <openrump/Input.hpp>
#include <openrump/OgreRenderSystem.hpp>

#include <OgreRoot.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

namespace OpenRump {
/*
// ----------------------------------------------------------------------------
EntityPlayer::EntityPlayer(OgreRenderer* renderer) :
    m_Input(nullptr),
    m_Renderer(renderer),
    m_CameraDistance(0),
    m_MaxCameraDistance(0),
    m_MinCameraDistance(0),
    m_Direction(0, 0, 1),
    m_TargetSpeed(0),
    m_Speed(0),
    m_MaxSpeed(0),
    m_AccelerationFactor(0),
    m_TurnAccelerationFactor(0),
    m_RollAngleIntensityFactor(0),
    m_RollAngleAccelerationFactor(0),
    m_PitchAngleIntensityFactor(0),
    m_PitchAngleAccelerationFactor(0),
    m_RollAngle(0),
    m_MaxRollAngle(0),
    m_PitchAngle(0),
    m_MaxPitchAngle(0),
    m_CameraAngle(Ogre::Radian(0), Ogre::Radian(0)),
    EntityBase(renderer)
{
}

// ----------------------------------------------------------------------------
// DEPRECATED
EntityPlayer::EntityPlayer(Input* input,
                           OgreRenderer* renderer,
                           Ogre::String instanceName,
                           Ogre::String meshName) :
    EntityPlayer(renderer)
{
    m_Input = input;

    this->load(instanceName, meshName);

    m_CameraDistance = 5;
    m_MaxCameraDistance = 15;
    m_MinCameraDistance = 1;
    m_MaxSpeed = 10;
    m_AccelerationFactor = 4;
    m_TurnAccelerationFactor = 4;
    m_RollAngleIntensityFactor = 100;
    m_RollAngleAccelerationFactor = 0.01;
    m_PitchAngleIntensityFactor = 0.05;
    m_PitchAngleAccelerationFactor = 0.005;
    m_MaxRollAngle = Ogre::Degree(40);
    m_MaxPitchAngle = Ogre::Degree(30);

    m_Input->event.addListener(this, "EntityPlayer"+instanceName);
    m_Renderer->frameEvent.addListener(this, "EntityPlayer"+instanceName);
}

// ----------------------------------------------------------------------------
EntityPlayer::EntityPlayer(Input* input,
                           OgreRenderer* renderer,
                           Ogre::String fileName) :
    EntityPlayer(renderer)
{
    m_Input = input;

    // open file stream and load from XML
    std::ifstream file(fileName);
    if(!file.is_open())
        throw std::runtime_error("[EntityPlayer::loadFromXML] Error: Unable to\
open file \"" + fileName + "\"");
    Ogre::String instanceName = this->loadFromXML(file);

    m_Input->event.addListener(this, "EntityPlayer"+instanceName);
    m_Renderer->frameEvent.addListener(this, "EntityPlayer"+instanceName);
}

// ----------------------------------------------------------------------------
Ogre::String EntityPlayer::loadFromXML(std::istream& stream)
{
    using boost::property_tree::ptree;

    // various temporaries
    Ogre::String instanceName;
    Ogre::String meshName;

    // read xml
    ptree pt;
    read_xml(stream, pt);

    // extract mesh information
    {
        instanceName = pt.get_child("mesh").get
                <Ogre::String>("<xmlattr>.global_id");
        meshName = pt.get_child("mesh").get
                <Ogre::String>("<xmlattr>.mesh");
    }

    // extract mode parameters
    for(auto& modes : pt.get_child("parameters").get_child("modes"))
    {
        // third person mode
        if(modes.second.get<Ogre::String>("<xmlattr>.type") == "3rd_person")
            for(auto& mode : modes.second)
            {
                if(mode.first == "camera")
                {
                    m_CameraDistance = mode.second.get
                            <Ogre::Real>("<xmlattr>.distance");
                    m_MaxCameraDistance = mode.second.get
                            <Ogre::Real>("<xmlattr>.max_distance");
                    m_MinCameraDistance  =mode.second.get
                            <Ogre::Real>("<xmlattr>.min_distance");
                }
                if(mode.first == "movement")
                {
                    m_MaxSpeed = mode.second.get
                            <Ogre::Real>("<xmlattr>.max_speed");
                    m_AccelerationFactor = mode.second.get
                            <Ogre::Real>("<xmlattr>.acceleration_factor");
                }
                if(mode.first == "turn")
                {
                    m_TurnAccelerationFactor = mode.second.get
                            <Ogre::Real>("<xmlattr>.acceleration_factor");
                }
                if(mode.first == "roll")
                {
                    m_RollAngleIntensityFactor = mode.second.get
                            <Ogre::Real>("<xmlattr>.intensity_factor");
                    m_RollAngleAccelerationFactor = mode.second.get
                            <Ogre::Real>("<xmlattr>.acceleration_factor");
                    m_MaxRollAngle = Ogre::Degree(mode.second.get
                            <Ogre::Real>("<xmlattr>.max_angle"));
                }
                if(mode.first == "pitch")
                {
                    m_PitchAngleIntensityFactor = mode.second.get
                            <Ogre::Real>("<xmlattr>.intensity_factor");
                    m_PitchAngleAccelerationFactor = mode.second.get
                            <Ogre::Real>("<xmlattr>.acceleration_factor");
                    m_MaxPitchAngle = Ogre::Degree(mode.second.get
                            <Ogre::Real>("<xmlattr>.max_angle"));
                }
            }
    }

    // load mesh
    this->load(instanceName, meshName);
    return instanceName;
}

// ----------------------------------------------------------------------------
EntityPlayer::~EntityPlayer()
{
    m_Renderer->frameEvent.removeListener(this);
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
        m_TargetDirection = Ogre::Matrix3(
                cs,  0, -sn,
                0,   1,   0,
                sn,  0,  cs
        ) * Ogre::Vector3(x, 0, y);

        m_TargetSpeed = m_MaxSpeed;

    // directional vector of length 0.0 means target speed is 0
    }else
        m_TargetSpeed = 0.0;
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
    if(this->hasCameraOrbit())
    {
        this->getCameraRotateNode()->setOrientation(Ogre::Quaternion());
        this->getCameraRotateNode()->yaw(m_CameraAngle.y);
        this->getCameraRotateNode()->pitch(m_CameraAngle.x);
    }
}

// ----------------------------------------------------------------------------
void EntityPlayer::onChangeCameraDistanceDelta(float deltaDistance)
{
    m_CameraDistance = Ogre::Math::Clamp(
        (m_MinCameraDistance - m_CameraDistance - Ogre::Real(1))
                * deltaDistance
                + m_CameraDistance,
        m_MinCameraDistance,
        m_MaxCameraDistance
    );

    if(this->hasCameraOrbit())
        this->setCameraDistance(m_CameraDistance);
}

// ----------------------------------------------------------------------------
bool EntityPlayer::onUpdateGameLoop(const float timeStep)
{
    // asymptotically approach target speed
    Ogre::Real acceleration = (m_TargetSpeed - m_Speed)
            * m_AccelerationFactor;
    m_Speed = Ogre::Math::Clamp(
            m_Speed + acceleration,
            Ogre::Real(0),
            m_MaxSpeed
    );

    // interpolate directional vector towards target direction
    Ogre::Quaternion actualRotation(Ogre::Quaternion::Slerp(
            (m_Speed/m_MaxSpeed) * m_TurnAccelerationFactor,
            Ogre::Quaternion::IDENTITY,
            m_Direction.getRotationTo(m_TargetDirection)
    ));
    m_Direction = actualRotation * m_Direction;
    m_Direction.normalise();

    // calculate roll angle
    m_RollAngle += (Ogre::Math::Clamp(
            actualRotation.getYaw()*m_RollAngleIntensityFactor,
            -m_MaxRollAngle,
            m_MaxRollAngle
    ) - m_RollAngle) * m_RollAngleAccelerationFactor;

    // calculate pitch angle
    m_PitchAngle += (Ogre::Math::Clamp(
            Ogre::Radian(acceleration * m_PitchAngleIntensityFactor),
            -m_MaxPitchAngle,
            m_MaxPitchAngle
    ) - m_PitchAngle) * m_PitchAngleAccelerationFactor;

    // rotate player accordingly
    this->getRotateSceneNode()->setOrientation(
            Ogre::Quaternion(
                    Ogre::Vector3(0, 1, 0).crossProduct(m_Direction),
                    Ogre::Vector3(0, 1, 0),
                    m_Direction)
            * Ogre::Quaternion(m_RollAngle, Ogre::Vector3(0, 0, -1))
            * Ogre::Quaternion(m_PitchAngle, Ogre::Vector3(1, 0, 0))
    );

    // position player accordingly
    this->getTranslateSceneNode()->translate(
            m_Direction * m_Speed
    );

    return true;
}*/

} // namespace OpenRump
