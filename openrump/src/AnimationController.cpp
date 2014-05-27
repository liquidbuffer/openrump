// ----------------------------------------------------------------------------
// AnimationController.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/AnimationController.hpp>

#include <OgreRoot.h>
#include <OgreEntity.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
AnimationController::AnimationController(const Ogre::Entity* entity) :
    m_OgreEntity(entity)
{
    Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

// ----------------------------------------------------------------------------
AnimationController::~AnimationController()
{
    Ogre::Root::getSingletonPtr()->removeFrameListener(this);
}

// ----------------------------------------------------------------------------
void AnimationController::play(std::string name, float speed)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    animationState->setEnabled(true);
    animationState->setLoop(false);
    animationState->setTimePosition(0);
    for(auto it : m_ActiveAnimations)
        if(it.animationState == animationState)
            return;
    m_ActiveAnimations.push_back(Animation(animationState, speed));
}

// ----------------------------------------------------------------------------
void AnimationController::loop(std::string name, float speed)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    animationState->setEnabled(true);
    animationState->setLoop(true);
    animationState->setTimePosition(0);
    for(auto it : m_ActiveAnimations)
        if(it.animationState == animationState)
            return;
    m_ActiveAnimations.push_back(Animation(animationState, speed));
}

// ----------------------------------------------------------------------------
void AnimationController::stop(std::string name)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    animationState->setEnabled(false);
    for(auto it = m_ActiveAnimations.begin(); it != m_ActiveAnimations.end(); ++it)
        if(it->animationState == animationState)
        {
            m_ActiveAnimations.erase(it);
            return;
        }
}

// ----------------------------------------------------------------------------
void AnimationController::pause(std::string name)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    for(auto it : m_ActiveAnimations)
        if(it.animationState == animationState)
        {
            it.paused = true;
            return;
        }
}

// ----------------------------------------------------------------------------
void AnimationController::resume(std::string name)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    for(auto it : m_ActiveAnimations)
        if(it.animationState == animationState)
        {
            it.paused = false;
            return;
        }
}

// ----------------------------------------------------------------------------
void AnimationController::setSpeed(std::string name, float speed)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    for(auto it : m_ActiveAnimations)
        if(it.animationState == animationState)
        {
            it.speed = speed;
            return;
        }
}

// ----------------------------------------------------------------------------
bool AnimationController::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    auto it = m_ActiveAnimations.begin();
    while(it != m_ActiveAnimations.end())
    {
        if(!it->paused)
            it->animationState->addTime(evt.timeSinceLastFrame * it->speed);

        if(it->animationState->hasEnded())
        {
            it->animationState->setEnabled(false);
            it = m_ActiveAnimations.erase(it);
        }
        else
            ++it;
    }
    return true;
}

} // namespace OpenRump
