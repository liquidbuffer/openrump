// ----------------------------------------------------------------------------
// Entity.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

//#include <openrump/EntityBase.hpp>
#include <openrump/AnimationController.hpp>
#include <openrump/OgreRenderSystem.hpp>

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreRoot.h>

#include <iostream>

namespace OpenRump {
/*
// ----------------------------------------------------------------------------
EntityBase::EntityBase() :
    m_SceneManager(nullptr),
    m_OgreEntity(nullptr),
    m_OgreEntityTranslateNode(nullptr),
    m_OgreEntityRotateNode(nullptr),
    m_CameraOrbitRotateNode(nullptr),
    m_CameraOrbitAttachNode(nullptr),
    m_OrbitingCamera(nullptr),
    m_Name("")
{
}

// ----------------------------------------------------------------------------
EntityBase::EntityBase(OgreRenderer* renderer) :
    EntityBase()
{
    m_SceneManager = renderer->getMainSceneManager();
}

// ----------------------------------------------------------------------------
void EntityBase::load(Ogre::String instanceName, Ogre::String meshName)
{
#ifdef _DEBUG
    if(m_Name != "")
    {
        std::cout << "[Entity::load] Warning: Entity "
                  << instanceName << "already loaded!";
        return;
    }
#endif
    m_Name = instanceName;
    m_OgreEntity = m_SceneManager->createEntity(instanceName, meshName);
    m_OgreEntityTranslateNode = m_SceneManager->getRootSceneNode()
            ->createChildSceneNode(m_Name + "TranslateNode");
    m_OgreEntityRotateNode = m_OgreEntityTranslateNode
            ->createChildSceneNode(m_Name + "RotateNode");
    m_OgreEntityRotateNode->attachObject(m_OgreEntity);
}

// ----------------------------------------------------------------------------
EntityBase::EntityBase(OgreRenderer* renderer,
                       Ogre::String instanceName,
                       Ogre::String meshName) :
    EntityBase()
{
    m_SceneManager = renderer->getMainSceneManager();
    this->load(instanceName, meshName);
}

// ----------------------------------------------------------------------------
EntityBase::~EntityBase()
{
    if(this->hasCameraOrbit())
        this->destroyCameraOrbit();

    assert(m_OgreEntity != nullptr);
    assert(m_OgreEntityRotateNode != nullptr);
    assert(m_OgreEntityTranslateNode != nullptr);

    m_OgreEntityRotateNode->detachObject(m_OgreEntity);
    m_SceneManager->destroyEntity(m_OgreEntity);
    m_OgreEntityTranslateNode->removeChild(m_OgreEntityRotateNode);
    m_SceneManager->destroySceneNode(m_OgreEntityRotateNode);
    m_SceneManager->getRootSceneNode()->removeChild(m_OgreEntityTranslateNode);
    m_SceneManager->destroySceneNode(m_OgreEntityTranslateNode);
}

// ----------------------------------------------------------------------------
EntityBase* EntityBase::createCameraOrbit()
{
    if(m_CameraOrbitRotateNode)
        return this;

    m_CameraOrbitRotateNode = m_OgreEntityTranslateNode
            ->createChildSceneNode(m_Name + "OrbitRotateNode");
    m_CameraOrbitAttachNode = m_CameraOrbitRotateNode
            ->createChildSceneNode(m_Name + "OrbitAttachNode");

    return this;
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* EntityBase::attachCameraToOrbit(Ogre::Camera* cam, float distance)
{
    if(m_OrbitingCamera)
        return m_CameraOrbitRotateNode;

    if(!m_CameraOrbitRotateNode)
        this->createCameraOrbit();

    m_OrbitingCamera = cam;
    m_CameraOrbitAttachNode->attachObject(m_OrbitingCamera);
    this->setCameraDistance(distance);

    return m_CameraOrbitRotateNode;
}

// ----------------------------------------------------------------------------
Ogre::Camera* EntityBase::detachCameraFromOrbit()
{
    if(!m_OrbitingCamera)
        return nullptr;

    m_CameraOrbitAttachNode->detachObject(m_OrbitingCamera);
    Ogre::Camera* cam = m_OrbitingCamera;
    m_OrbitingCamera = nullptr;

    return cam;
}

// ----------------------------------------------------------------------------
void EntityBase::setCameraDistance(float distance)
{
    if(!m_CameraOrbitAttachNode)
        return;
    m_CameraOrbitAttachNode->setPosition(0, 0, distance);
}

// ----------------------------------------------------------------------------
Ogre::Camera* EntityBase::getCamera() const
{
    assert(m_OrbitingCamera != nullptr);
    return m_OrbitingCamera;
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* EntityBase::getCameraRotateNode() const
{
    assert(m_CameraOrbitRotateNode != nullptr);
    return m_CameraOrbitRotateNode;
}

// ----------------------------------------------------------------------------
Ogre::Camera* EntityBase::destroyCameraOrbit()
{
    Ogre::Camera* cam = this->detachCameraFromOrbit();

    if(!m_CameraOrbitRotateNode)
        return cam;  // return nullptr

    m_CameraOrbitRotateNode->removeChild(m_CameraOrbitAttachNode);
    m_SceneManager->destroySceneNode(m_CameraOrbitAttachNode);
    m_CameraOrbitAttachNode = nullptr;
    m_OgreEntityTranslateNode->removeChild(m_CameraOrbitRotateNode);
    m_SceneManager->destroySceneNode(m_CameraOrbitRotateNode);
    m_CameraOrbitRotateNode = nullptr;

    return cam;
}

// ----------------------------------------------------------------------------
bool EntityBase::hasCameraOrbit() const
{
    return (m_CameraOrbitRotateNode != nullptr);
}

// ----------------------------------------------------------------------------
void EntityBase::extractAnimation(Ogre::Animation* source,
                              Ogre::Animation* dest,
                              Ogre::Real startTime,
                              Ogre::Real endTime)
{
    Ogre::Real timeScale = dest->getLength() / (endTime - startTime);
    dest->destroyAllTracks();

    // loop through all animation node tracks in source and copy them to
    // destination
    for(Ogre::Animation::NodeTrackIterator srcNodeTrackIt =
                source->getNodeTrackIterator();
        srcNodeTrackIt.hasMoreElements()
        ;)
    {
        Ogre::NodeAnimationTrack* srcNodeTrack = srcNodeTrackIt.getNext();
        unsigned short trackHandle = srcNodeTrack->getHandle();
        Ogre::NodeAnimationTrack* destNodeTrack =
                dest->createNodeTrack(trackHandle);

        // loop through all transforms of current source track and copy them to
        // destination if they are within the time frame specified
        for(unsigned short keyFrameHandle = 0;
            keyFrameHandle != srcNodeTrack->getNumKeyFrames();
            ++keyFrameHandle)
        {
            Ogre::TransformKeyFrame* srcKeyFrame = srcNodeTrack
                    ->getNodeKeyFrame(keyFrameHandle);
            if(srcKeyFrame->getTime() < startTime
                    || srcKeyFrame->getTime() > endTime)
                continue;

            Ogre::Real scaledTime = (srcKeyFrame->getTime()-startTime)
                    * timeScale;
            Ogre::TransformKeyFrame* destKeyFrame = destNodeTrack
                    ->createNodeKeyFrame(scaledTime);

            destKeyFrame->setTranslate(srcKeyFrame->getTranslate());
            destKeyFrame->setRotation(srcKeyFrame->getRotation());
            destKeyFrame->setScale(srcKeyFrame->getScale());
        }
    }
}

// ----------------------------------------------------------------------------
void EntityBase::enableAnimation()
{
    m_AnimationController = std::unique_ptr<AnimationController>(
            new AnimationController(m_OgreEntity)
    );
}

// ----------------------------------------------------------------------------
void EntityBase::disableAnimation()
{
    m_AnimationController.reset(nullptr);
}

// ----------------------------------------------------------------------------
bool EntityBase::isAnimated() const
{
    return (m_AnimationController != nullptr);
}

// ----------------------------------------------------------------------------
AnimationController* EntityBase::getAnimationController() const
{
    if(!this->isAnimated())
        throw std::runtime_error("[Entity::getAnimationController] Error: \
Animation not enabled");
    return m_AnimationController.get();
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* EntityBase::getTranslateSceneNode()
{
    assert(m_OgreEntityTranslateNode != nullptr);
    return m_OgreEntityTranslateNode;
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* EntityBase::getRotateSceneNode()
{
    assert(m_OgreEntityRotateNode != nullptr);
    return m_OgreEntityRotateNode;
}
*/
} // namespace OpenRump
