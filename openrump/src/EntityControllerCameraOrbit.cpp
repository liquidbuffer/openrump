// ----------------------------------------------------------------------------
// EntityControllerCameraOrbit.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityControllerCameraOrbit.hpp>
#include <openrump/EntityBase.hpp>
#include <openrump/Input.hpp>

#include <OgreMath.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityControllerCameraOrbit::EntityControllerCameraOrbit(Ogre::SceneManager* sm,
                                                         Input* input) :
    m_CameraDistance(0),
    m_MaxCameraDistance(0),
    m_MinCameraDistance(0),
    m_SceneManager(sm),
    m_CameraOrbitRotateNode(nullptr),
    m_CameraOrbitAttachNode(nullptr),
    m_OrbitingCamera(nullptr),
    m_Input(input),
    m_CameraAngle(Ogre::Radian(0), Ogre::Radian(0), Ogre::Radian(0))
{
    m_Input->event.addListener(this, "EntityControllerCameraOrbit");
}

// ----------------------------------------------------------------------------
EntityControllerCameraOrbit::~EntityControllerCameraOrbit()
{
    m_Input->event.removeListener(this);
    this->destroyCameraOrbit();
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setCamera(Ogre::Camera* cam)
{
    m_OrbitingCamera = cam;

    if(m_OrbitingCamera && m_CameraOrbitAttachNode)
        m_CameraOrbitAttachNode->attachObject(m_OrbitingCamera);
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::pySetCamera(std::string cameraName)
{
    this->setCamera(m_SceneManager->getCamera(cameraName));
}

// ----------------------------------------------------------------------------
Ogre::Camera* EntityControllerCameraOrbit::removeCamera()
{
    if(m_OrbitingCamera && m_CameraOrbitAttachNode)
        m_CameraOrbitAttachNode->detachObject(m_OrbitingCamera);

    Ogre::Camera* cam = m_OrbitingCamera;
    m_OrbitingCamera = nullptr;
    return cam;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::pyRemoveCamera()
{
    m_OrbitingCamera = nullptr;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setDistanceConstraints(float min, float max)
{
    m_MinCameraDistance = min;
    m_MaxCameraDistance = max;
    this->setDistance(min);
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setDistance(float distance)
{
    if(m_CameraOrbitAttachNode)
        m_CameraOrbitAttachNode->setPosition(0, 0, distance);
    m_CameraDistance = distance;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setRotationZYX(Ogre::Radian x, Ogre::Radian y, Ogre::Radian z)
{
    if(!m_CameraOrbitRotateNode)
        return;
    this->getCameraRotateNode()->setOrientation(Ogre::Quaternion());
    this->getCameraRotateNode()->roll(z);
    this->getCameraRotateNode()->yaw(y);
    this->getCameraRotateNode()->pitch(x);
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::pySetRotation(float x, float y, float z)
{
    this->setRotationZYX(
            Ogre::Radian(x),
            Ogre::Radian(y),
            Ogre::Radian(z)
    );
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setOrbitPosition(float x, float y, float z)
{
    if(!m_CameraOrbitRotateNode)
        return;
    this->getCameraRotateNode()->setPosition(x, y, z);
}

// ----------------------------------------------------------------------------
Ogre::Camera* EntityControllerCameraOrbit::getCamera() const
{
    assert(m_OrbitingCamera != nullptr);
    return m_OrbitingCamera;
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* EntityControllerCameraOrbit::getCameraRotateNode() const
{
    assert(m_CameraOrbitRotateNode != nullptr);
    return m_CameraOrbitRotateNode;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::createCameraOrbit(EntityBase* entity)
{
    m_CameraOrbitRotateNode = entity->getTranslateSceneNode()
            ->createChildSceneNode(entity->getName() + "OrbitRotateNode");
    m_CameraOrbitAttachNode = m_CameraOrbitRotateNode
            ->createChildSceneNode(entity->getName() + "OrbitAttachNode");

    this->setCamera(m_OrbitingCamera);
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::destroyCameraOrbit()
{
    if(!m_CameraOrbitAttachNode)
        return;

    m_OrbitingCamera = this->removeCamera();

    m_CameraOrbitRotateNode->removeChild(m_CameraOrbitAttachNode);
    m_SceneManager->destroySceneNode(m_CameraOrbitAttachNode);
    m_CameraOrbitAttachNode = nullptr;
    m_Entity->getTranslateSceneNode()->removeChild(m_CameraOrbitRotateNode);
    m_SceneManager->destroySceneNode(m_CameraOrbitRotateNode);
    m_CameraOrbitRotateNode = nullptr;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY)
{
    // add deltas and limit X angle to +90° and -90°
    m_CameraAngle.x -= Ogre::Radian(deltaAngleX);
    m_CameraAngle.y -= Ogre::Radian(deltaAngleY);
    if(m_CameraAngle.x < Ogre::Radian(-Ogre::Math::PI*0.5))
        m_CameraAngle.x = Ogre::Radian(-Ogre::Math::PI*0.5);
    if(m_CameraAngle.x > Ogre::Radian(Ogre::Math::PI*0.5))
        m_CameraAngle.x = Ogre::Radian(Ogre::Math::PI*0.5);

    if(m_CameraOrbitRotateNode)
        this->setRotationZYX(m_CameraAngle.x, m_CameraAngle.y, Ogre::Radian(0));
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::onChangeCameraDistanceDelta(float deltaDistance)
{
    this->setDistance(Ogre::Math::Clamp(
        (m_MinCameraDistance - m_CameraDistance - Ogre::Real(2))
                * deltaDistance
                + m_CameraDistance,
        m_MinCameraDistance,
        m_MaxCameraDistance
    ));
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::notifyEntityChange(EntityBase* newEntity)
{
    // m_Entity is set to the new entity after this method returns

    this->destroyCameraOrbit();

    if(newEntity)
        this->createCameraOrbit(newEntity);
}

} // namespace OpenRump
