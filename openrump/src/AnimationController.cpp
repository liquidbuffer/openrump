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
void AnimationController::playAnimation(std::string name, float speed)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    animationState->setEnabled(true);
    animationState->setLoop(false);
    animationState->setTimePosition(0);
    for(auto it : m_AnimationList)
        if(it.animationState == animationState)
            return;
    m_AnimationList.push_back(Animation(animationState, speed));
}

// ----------------------------------------------------------------------------
void AnimationController::loopAnimation(std::string name, float speed)
{
    Ogre::AnimationState* animationState = m_OgreEntity->getAnimationState(name);
    animationState->setEnabled(true);
    animationState->setLoop(true);
    animationState->setTimePosition(0);
    for(auto it : m_AnimationList)
        if(it.animationState == animationState)
            return;
    m_AnimationList.push_back(Animation(animationState, speed));
}

// ----------------------------------------------------------------------------
bool AnimationController::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    auto it = m_AnimationList.begin();
    while(it != m_AnimationList.end())
    {
        it->animationState->addTime(evt.timeSinceLastFrame * it->speed);

        if(it->animationState->hasEnded())
        {
            it->animationState->setEnabled(false);
            it = m_AnimationList.erase(it);
        }
        else
            ++it;
    }
    return true;
}

} // namespace OpenRump
