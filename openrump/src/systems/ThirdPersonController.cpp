// ----------------------------------------------------------------------------
// ThirdPersonController.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "openrump/systems/ThirdPersonController.hpp"
#include "openrump/components/OgreCameraOrbitNode.hpp"
#include "openrump/components/OgreTranslateRotateNode.hpp"
#include "openrump/components/Direction2D.hpp"
#include "openrump/components/Speed.hpp"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "OgreSceneNode.h"

#include "ontology/Entity.hpp"

namespace OpenRump {

// ----------------------------------------------------------------------------
ThirdPersonController::ThirdPersonController() :
    m_TargetSpeed(0),
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
    m_MaxPitchAngle(0)
{
}

// ----------------------------------------------------------------------------
ThirdPersonController::ThirdPersonController(std::string fileName) :
    ThirdPersonController()
{
    this->loadFromXML(fileName);
}

// ----------------------------------------------------------------------------
void ThirdPersonController::loadFromXML(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    file.exceptions(std::ifstream::failbit);
    this->loadFromXML(file);
}

// ----------------------------------------------------------------------------
void ThirdPersonController::loadFromXML(std::istream& stream)
{
    using boost::property_tree::ptree;

    // read xml
    ptree pt;
    read_xml(stream, pt);

    // extract mode parameters
    for(auto& modes : pt.get_child("parameters").get_child("modes"))
    {
        // only interested in third person mode
        if(modes.second.get<Ogre::String>("<xmlattr>.type") == "3rd_person")
            for(auto& mode : modes.second)
            {
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
}

// ----------------------------------------------------------------------------
void ThirdPersonController::onDirectionChange(float x, float y)
{
    if(x != 0.0 || y != 0.0)
    {
        m_TargetDirection = Ogre::Vector2(x, y);
        m_TargetSpeed = m_MaxSpeed;
        std::cout << "direction: " << x << "," << y << std::endl;
    }
    else
    {
        // direction vector with length 0 means target speed of 0
        m_TargetSpeed = 0.0;
    }
}

// ----------------------------------------------------------------------------
void ThirdPersonController::initialise()
{
}

// ----------------------------------------------------------------------------
void ThirdPersonController::processEntity(Ontology::Entity& e)
{
    // get camera angle of this entity
    Ogre::Radian camAngleY = e.getComponent<OgreCameraOrbitNode>().rotation->getOrientation().getYaw();
    
    Ogre::Vector2& targetDirection = e.getComponent<Direction2D>().targetDirection;
    Ogre::Vector2& currentDirection = e.getComponent<Direction2D>().currentDirection;
    Ogre::Real& currentSpeed = e.getComponent<Speed>().currentSpeed;
    
    // rotate vector by camera angle to get real world direction using a
    // rotation matrix
    Ogre::Real cs = Ogre::Math::Cos(camAngleY);
    Ogre::Real sn = Ogre::Math::Sin(camAngleY);
    targetDirection.x = m_TargetDirection.x * cs - m_TargetDirection.y * sn;
    targetDirection.y = m_TargetDirection.y * sn + m_TargetDirection.y * cs;
    
    // asymptotically approach target speed
    Ogre::Real acceleration = (m_TargetSpeed - currentSpeed) * m_AccelerationFactor;
    currentSpeed = Ogre::Math::Clamp(
        currentSpeed + acceleration,
        Ogre::Real(0),
        m_MaxSpeed
    );
    
    // TODO interpolate directional vector towards target direction
    currentDirection = targetDirection;
    
    // position player accordingly
    Ogre::Vector3 direction(currentDirection.x,
                            0,
                            currentDirection.y);
    e.getComponent<OgreTranslateRotateNode>().translation->translate(
        direction * currentSpeed
    );
    
    std::cout << e.getComponent<OgreTranslateRotateNode>().translation->getPosition() << std::endl;
}

// ----------------------------------------------------------------------------
void ThirdPersonController::configureEntity(Ontology::Entity&, std::string)
{
}

} // namespace OpenRump