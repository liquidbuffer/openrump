// ----------------------------------------------------------------------------
// CameraOrbit.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/systems/CameraOrbit.hpp>
#include <openrump/components/OgreCameraOrbitNode.hpp>
#include <ontology/Entity.hpp>

#include <OgreSceneNode.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
CameraOrbit::CameraOrbit() :
    m_Distance(4),
    m_MinDistance(1),
    m_MaxDistance(100)
{
}

// ----------------------------------------------------------------------------
void CameraOrbit::initialise()
{

}

// ----------------------------------------------------------------------------
void CameraOrbit::processEntity(Ontology::Entity& e)
{
    //boost::recursive_mutex::scoped_lock lock(m_Mutex);
    e.getComponent<OgreCameraOrbitNode>().rotation->setOrientation(Ogre::Quaternion());
    e.getComponent<OgreCameraOrbitNode>().rotation->yaw(Ogre::Degree(m_Angle.y));
    e.getComponent<OgreCameraOrbitNode>().rotation->pitch(Ogre::Degree(m_Angle.x));
    e.getComponent<OgreCameraOrbitNode>().translation->setPosition(0, 0, m_Distance);
}

// ----------------------------------------------------------------------------
void CameraOrbit::configureEntity(Ontology::Entity& e, std::string)
{
}

// ----------------------------------------------------------------------------
void CameraOrbit::onNewCameraAngle(float x, float y)
{
    m_Angle.x -= y * 0.1;
    m_Angle.y -= x * 0.1;
    
    // wrap angles to 360
    while(m_Angle.x > 360.0)
        m_Angle.x -= 360.0;
    while(m_Angle.x < 0.0)
        m_Angle.x += 360.0;
    
    // clamp x angle to -90/+90
    if(m_Angle.x > 180.0 && m_Angle.x < 270.0)
        m_Angle.x = 270.0;
    if(m_Angle.x < 180.0 && m_Angle.x > 90.0)
        m_Angle.x = 90.0;
}

// ----------------------------------------------------------------------------
void CameraOrbit::onNewCameraDistance(float distance)
{
    m_Distance = Ogre::Math::Clamp(
        m_Distance * (1.0f - distance*0.1f),
        m_MinDistance,
        m_MaxDistance
    );
}

} // namespace OpenRump
