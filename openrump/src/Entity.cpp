// ----------------------------------------------------------------------------
// Entity.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Entity.hpp>

#include <OgreSceneManager.h>
#include <OgreEntity.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Entity::Entity(Ogre::SceneManager* sm, std::string instanceName, std::string meshName) :
    m_SceneManager(sm),
    m_OgreEntity(nullptr),
    m_OgreEntityNode(nullptr),
    m_CameraOrbitRotateNode(nullptr),
    m_CameraOrbitAttachNode(nullptr),
    m_OrbitingCamera(nullptr),
    m_Name(instanceName)
{
    m_OgreEntity = m_SceneManager->createEntity(instanceName, meshName);
    m_OgreEntityNode = m_SceneManager->getRootSceneNode()->createChildSceneNode(m_Name + "RootNode");
    m_OgreEntityNode->attachObject(m_OgreEntity);
}

// ----------------------------------------------------------------------------
Entity::~Entity()
{
    if(this->hasCameraOrbit())
        this->destroyCameraOrbit();
    m_OgreEntityNode->detachObject(m_OgreEntity);
    m_SceneManager->destroyEntity(m_OgreEntity);
    m_SceneManager->getRootSceneNode()->removeChild(m_OgreEntityNode);
    m_SceneManager->destroySceneNode(m_OgreEntityNode);
}

// ----------------------------------------------------------------------------
Entity* Entity::createCameraOrbit()
{
    if(m_CameraOrbitRotateNode)
        return this;

    std::cout << "creating camera orbit" << std::endl;
    m_CameraOrbitRotateNode = m_OgreEntityNode->createChildSceneNode(m_Name + "OrbitRotateNode");
    m_CameraOrbitAttachNode = m_CameraOrbitRotateNode->createChildSceneNode(m_Name + "OrbitAttachNode");

    return this;
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* Entity::attachCameraToOrbit(Ogre::Camera* cam, float distance)
{
    if(m_OrbitingCamera)
        return m_CameraOrbitRotateNode;

    if(!m_CameraOrbitRotateNode)
        this->createCameraOrbit();

    m_OrbitingCamera = cam;
    m_CameraOrbitAttachNode->attachObject(m_OrbitingCamera);
    m_CameraOrbitAttachNode->setPosition(0, 0, distance);

    return m_CameraOrbitRotateNode;
}

// ----------------------------------------------------------------------------
Ogre::Camera* Entity::detachCameraFromOrbit()
{
    if(!m_OrbitingCamera)
        return nullptr;

    m_CameraOrbitAttachNode->detachObject(m_OrbitingCamera);
    Ogre::Camera* cam = m_OrbitingCamera;
    m_OrbitingCamera = nullptr;

    return cam;
}

// ----------------------------------------------------------------------------
Ogre::Camera* Entity::getCamera() const
{
    return m_OrbitingCamera;
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* Entity::getCameraRotateNode() const
{
    return m_CameraOrbitRotateNode;
}

// ----------------------------------------------------------------------------
Ogre::Camera* Entity::destroyCameraOrbit()
{
    Ogre::Camera* cam = this->detachCameraFromOrbit();

    if(!m_CameraOrbitRotateNode)
        return cam;

    m_CameraOrbitRotateNode->removeChild(m_CameraOrbitAttachNode);
    m_SceneManager->destroySceneNode(m_CameraOrbitAttachNode);
    m_CameraOrbitAttachNode = nullptr;
    m_OgreEntityNode->removeChild(m_CameraOrbitRotateNode);
    m_SceneManager->destroySceneNode(m_CameraOrbitRotateNode);
    m_CameraOrbitRotateNode = nullptr;

    return cam;
}

// ----------------------------------------------------------------------------
bool Entity::hasCameraOrbit() const
{
    return (m_CameraOrbitRotateNode != nullptr);
}

} // namespace OpenRump
