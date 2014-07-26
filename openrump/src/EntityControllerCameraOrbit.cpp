// ----------------------------------------------------------------------------
// EntityControllerCameraOrbit.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityControllerCameraOrbit.hpp>
#include <openrump/EntityBase.hpp>

#include <OgreMath.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityControllerCameraOrbit::EntityControllerCameraOrbit(Ogre::SceneManager* sm,
                                                         Input* input,
                                                         Ogre::Camera* camera,
                                                         float distance) :
    m_CameraDistance(0),
    m_MaxCameraDistance(0),
    m_MinCameraDistance(0),
    m_SceneManager(sm),
    m_CameraOrbitRotateNode(nullptr),
    m_CameraOrbitAttachNode(nullptr),
    m_OrbitingCamera(nullptr),
    m_Entity(nullptr),
    m_Input(input),
    m_CameraAngle(Ogre::Radian(0), Ogre::Radian(0), Ogre::Radian(0))
{
    this->createCameraOrbit();
    if(camera)
        this->attachCameraToOrbit(camera, distance);
}

// ----------------------------------------------------------------------------
EntityControllerCameraOrbit::~EntityControllerCameraOrbit()
{
    this->destroyCameraOrbit();
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::attachToEntity(std::weak_ptr<EntityBase> entity)
{
    m_Entity = entity;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::detachFromEntity()
{
    m_Entity = std::weak_ptr<EntityBase>(nullptr);
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* EntityControllerCameraOrbit::attachCameraToOrbit(Ogre::Camera* cam, float distance)
{
    if(m_OrbitingCamera)
        m_CameraOrbitAttachNode->detachObject(m_OrbitingCamera);

    m_OrbitingCamera = cam;
    m_CameraOrbitAttachNode->attachObject(m_OrbitingCamera);
    this->setDistance(distance);

    return m_CameraOrbitRotateNode;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::pyAttachCameraToOrbit(std::string camName, float distance)
{
    this->attachCameraToOrbit(m_SceneManager->getCamera(camName), distance);
}

// ----------------------------------------------------------------------------
Ogre::Camera* EntityControllerCameraOrbit::detachCameraFromOrbit()
{
    if(!m_OrbitingCamera)
        throw std::runtime_error("[EntityBase::detachCameraFromOrbit] Error: No\
camera to detach");

    m_CameraOrbitAttachNode->detachObject(m_OrbitingCamera);
    Ogre::Camera* cam = m_OrbitingCamera;
    m_OrbitingCamera = nullptr;

    return cam;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::pyDetachCameraFromOrbit()
{
    this->detachCameraFromOrbit();
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setDistanceConstraints(float min, float max)
{
    m_MinCameraDistance = min;
    m_MaxCameraDistance = max;
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setDistance(float distance)
{
    m_CameraOrbitAttachNode->setPosition(0, 0, distance);
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::setRotationZYX(Ogre::Radian x, Ogre::Radian y, Ogre::Radian z)
{
    this->getCameraRotateNode()->setOrientation(Ogre::Quaternion());
    this->getCameraRotateNode()->roll(z);
    this->getCameraRotateNode()->yaw(y);
    this->getCameraRotateNode()->pitch(z);
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
void EntityControllerCameraOrbit::createCameraOrbit()
{
    assert(m_CameraOrbitRotateNode == nullptr);

    m_CameraOrbitRotateNode = m_Entity->getTranslateSceneNode()
            ->createChildSceneNode(m_Entity->getName() + "OrbitRotateNode");
    m_CameraOrbitAttachNode = m_CameraOrbitRotateNode
            ->createChildSceneNode(m_Entity->getName() + "OrbitAttachNode");
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::destroyCameraOrbit()
{
    assert(m_CameraOrbitRotateNode != nullptr);

    this->detachCameraFromOrbit();

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

    this->setRotationZYX(m_CameraAngle.x, m_CameraAngle.y, Ogre::Radian(0));
}

// ----------------------------------------------------------------------------
void EntityControllerCameraOrbit::onChangeCameraDistanceDelta(float deltaDistance)
{
    this->setDistance(Ogre::Math::Clamp(
        (m_MinCameraDistance - m_CameraDistance - Ogre::Real(1))
                * deltaDistance
                + m_CameraDistance,
        m_MinCameraDistance,
        m_MaxCameraDistance
    ));
}

} // namespace OpenRump
