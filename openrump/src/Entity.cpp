// ----------------------------------------------------------------------------
// Entity.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Entity.hpp>

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreRoot.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Entity::Entity(Ogre::SceneManager* sm, std::string instanceName, std::string meshName) :
    m_SceneManager(sm),
    m_OgreEntity(nullptr),
    m_OgreEntityNode(nullptr),
    m_CameraOrbitRotateNode(nullptr),
    m_CameraOrbitAttachNode(nullptr),
    m_OrbitingCamera(nullptr),
    m_WalkAnimState(nullptr),
    m_Name(instanceName)
{
    m_OgreEntity = m_SceneManager->createEntity(instanceName, meshName);
    m_OgreEntityNode = m_SceneManager->getRootSceneNode()->createChildSceneNode(m_Name + "RootNode");
    m_OgreEntityNode->attachObject(m_OgreEntity);

    this->extractAnimation(
            m_OgreEntity->getSkeleton()->getAnimation("Anim_1"),
            m_OgreEntity->getSkeleton()->createAnimation("walk", 0.6f),
            41.0f,
            71.0f
    );

    m_OgreEntity->refreshAvailableAnimationState();
    m_WalkAnimState = m_OgreEntity->getAnimationState("walk");
    m_WalkAnimState->setEnabled(true);
    m_WalkAnimState->setLoop(true);

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

// ----------------------------------------------------------------------------
void Entity::extractAnimation(Ogre::Animation* source,
                              Ogre::Animation* dest,
                              Ogre::Real startTime,
                              Ogre::Real endTime)
{
    Ogre::Real timeScale = dest->getLength() / (endTime - startTime);

    // loop through all animation node tracks in source and copy them to destination
    for(Ogre::Animation::NodeTrackIterator srcNodeTrackIt = source->getNodeTrackIterator();
        srcNodeTrackIt.hasMoreElements()
        ;)
    {
        Ogre::NodeAnimationTrack* srcNodeTrack = srcNodeTrackIt.getNext();
        unsigned short trackHandle = srcNodeTrack->getHandle();
        Ogre::NodeAnimationTrack* destNodeTrack = dest->createNodeTrack(trackHandle);

        // loop through all transforms of current source track and copy them to destination
        // if they are within the time frame specified
        for(unsigned short keyFrameHandle = 0;
            keyFrameHandle != srcNodeTrack->getNumKeyFrames();
            ++keyFrameHandle)
        {
            Ogre::TransformKeyFrame* srcKeyFrame = srcNodeTrack->getNodeKeyFrame(keyFrameHandle);
            if(srcKeyFrame->getTime() < startTime || srcKeyFrame->getTime() > endTime)
                continue;

            Ogre::Real scaledTime = (srcKeyFrame->getTime()-startTime) * timeScale;
            Ogre::TransformKeyFrame* destKeyFrame = destNodeTrack->createNodeKeyFrame(scaledTime);

            destKeyFrame->setTranslate(srcKeyFrame->getTranslate());
            destKeyFrame->setRotation(srcKeyFrame->getRotation());
            destKeyFrame->setScale(srcKeyFrame->getScale());
        }
    }
}

// ----------------------------------------------------------------------------
Entity::~Entity()
{
    Ogre::Root::getSingletonPtr()->removeFrameListener(this);

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

// ----------------------------------------------------------------------------
bool Entity::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    m_WalkAnimState->addTime(evt.timeSinceLastFrame);
    return true;
}

} // namespace OpenRump
