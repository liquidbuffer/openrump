// ----------------------------------------------------------------------------
// AnimationController.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <OgreFrameListener.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class Entity;
    class AnimationState;
}

namespace OpenRump {

class AnimationController :
    public Ogre::FrameListener
{
public:

    /*!
     * @brief Constructor.
     * @param entity The ogre entity to control.
     */
    AnimationController(const Ogre::Entity* entity);

    /*!
     * @brief Default destructor.
     */
    ~AnimationController();

    /*!
     * @brief Plays an animation from the entity.
     */
    void playAnimation(std::string name, float speed=1.0f);

    /*!
     * @brief Loops an animation fromt he entity.
     */
    void loopAnimation(std::string name, float speed=1.0f);

private:

    // override virtual functions
    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    struct Animation
    {
        Animation(Ogre::AnimationState* animState, float speed) :
            animationState(animState),
            speed(speed)
        {}

        Ogre::AnimationState* animationState;
        float speed;
    };
    std::vector<Animation> m_AnimationList;

    const Ogre::Entity* m_OgreEntity;
};

} // namespace OpenRump
