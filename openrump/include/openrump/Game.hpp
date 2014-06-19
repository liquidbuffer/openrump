// ----------------------------------------------------------------------------
// Game.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/InputListener.hpp>

#include <OgreFrameListener.h>

#include <string>
#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class OgreRenderer;
    class Input;
}

namespace OpenRump {

class Game :
    public Ogre::FrameListener,
    public InputListener
{
public:

    /*!
     * @brief Constructor
     */
    Game();

    /*!
     * @brief Default destructor
     */
    ~Game();

    /*!
     * @brief Stops the game and shuts down.
     */
    void stop();

    /*!
     * @brief Begins running the game (main loop).
     */
    void run();

private:

    /*!
     * @brief Initialises the game so it's ready to run.
     */
    void initialise();

    /*!
     * @brief Cleans up everything.
     */
    void cleanUp();

    // override ogre frame listener methods
    virtual bool frameStarted(const Ogre::FrameEvent&);

    // override input listener methods
    virtual void onButtonExit();

    std::unique_ptr<OgreRenderer> m_OgreRenderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
    bool m_IsInitialised;
};

} // namespace OpenRump
