// ----------------------------------------------------------------------------
// AnimationController.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <OgreFrameListener.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class EntityBase;
    class AnimationState;
}

namespace OpenRump {

class AnimationController :
    public Ogre::FrameListener
{
private:

    struct Animation
    {
        Animation(Ogre::AnimationState* animState, float speed) :
            animationState(animState),
            speed(speed),
            paused(false)
        {}

        Ogre::AnimationState* animationState;
        float speed;
        bool paused;
    };

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
     * @note The animation is reset to the beginning.
     * @param name The name of the animatino.
     * @param speed Optional: The speed factor of the animation. A value of 1.0
     * is the default speed.
     */
    void play(std::string name, float speed=1.0f);

    /*!
     * @brief Loops an animation from the entity.
     * @note The animation is reset to the beginning
     * @param name The name of the animation.
     * @param speed Optional: The speed factor of the animation. A value of 1.0
     * is the default speed.
     */
    void loop(std::string name, float speed=1.0f);

    /*!
     * @brief Stops a playing animation, if it is playing.
     * The animation is completely removed from being updated.
     * @note Speed settings aren't preserved when you play this animation again.
     * @param name The name of the animation.
     */
    void stop(std::string name);

    /*!
     * @brief Pauses the animation, if it is playing.
     * The animation is not removed from being updated.
     * @param name The name of the animation.
     */
    void pause(std::string name);

    /*!
     * @brief Resumes the animation, if it is paused.
     * @param name The name of the animation.
     */
    void resume(std::string name);

    /*!
     * @brief Sets the speed factor of an animation.
     * A speed factor of 1.0 is the default value.
     * @note If the specified animation isn't playing to begin with, this
     * will have no effect.
     * @param name The name of the animation.
     * @param speed the speed factor to set.
     */
    void setSpeed(std::string name, float speed);

private:

    // override virtual functions
    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    std::vector<Animation> m_ActiveAnimations;

    const Ogre::Entity* m_OgreEntity;
};

} // namespace OpenRump
