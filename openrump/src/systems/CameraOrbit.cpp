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
    m_Distance(0)
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
void CameraOrbit::onNewCameraAngle(float x, float y)
{
    m_Angle.x += x;
    m_Angle.y += y;
}

// ----------------------------------------------------------------------------
void CameraOrbit::onNewCameraDistance(float distance)
{
    m_Distance += distance;
}

} // namespace OpenRump
