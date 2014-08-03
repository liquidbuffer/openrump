// ----------------------------------------------------------------------------
// Entity.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityBase.hpp>
#include <openrump/EntityControllerCameraOrbit.hpp>
#include <openrump/OgreRenderer.hpp>

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreRoot.h>

#include <iostream>
#include <stdexcept>
#include <string>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityBase::EntityBase() :
    m_SceneManager(nullptr),
    m_OgreEntity(nullptr),
    m_OgreEntityTranslateNode(nullptr),
    m_OgreEntityRotateNode(nullptr),
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
    // remove all controllers - controllers need to be notified before entity destruction
    for(auto it : m_EntityControllerList)
        this->removeController(it);

    // destroy 3D object and all scene nodes
    m_OgreEntityRotateNode->detachObject(m_OgreEntity);
    m_SceneManager->destroyEntity(m_OgreEntity);
    m_OgreEntityTranslateNode->removeChild(m_OgreEntityRotateNode);
    m_SceneManager->destroySceneNode(m_OgreEntityRotateNode);
    m_SceneManager->getRootSceneNode()->removeChild(m_OgreEntityTranslateNode);
    m_SceneManager->destroySceneNode(m_OgreEntityTranslateNode);
}

// ----------------------------------------------------------------------------
std::string EntityBase::getName() const
{
    return m_Name;
}

// ----------------------------------------------------------------------------
void EntityBase::addController(boost::shared_ptr<EntityController> controller)
{
    // check for existing name
    for(auto it : m_EntityControllerList)
        if(it == controller)
            throw std::runtime_error("[EntityBase::addController] Error: \
Controller already exists");
    m_EntityControllerList.push_back(controller);
    controller->notifyEntityChange(this);
}

// ----------------------------------------------------------------------------
void EntityBase::removeController(boost::shared_ptr<EntityController> controller)
{
    for(auto it = m_EntityControllerList.begin(); it != m_EntityControllerList.end(); ++it)
        if(*it == controller)
        {
            (*it)->notifyEntityChange(nullptr);
            m_EntityControllerList.erase(it);
            return;
        }

    throw std::runtime_error("[EntityBase::destroyController] Error: \
Controller not registered");
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

} // namespace OpenRump
