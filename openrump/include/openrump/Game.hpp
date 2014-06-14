// ----------------------------------------------------------------------------
// Game.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/InputListener.hpp>
#include <openrump/PyGameInterface.hpp>

#include <OgreFrameListener.h>

#include <string>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class OgreRenderer;
    class Input;
}

namespace OpenRump {

class Game :
    public PyGameInterface,
    public Ogre::FrameListener,
    public InputListener
{
public:

    /*!
     * @brief Constructor
     */
    Game(std::string workingDirectory);

    /*!
     * @brief Default destructor
     */
    ~Game();

    // override public game interface methods
    virtual void test();
    virtual void stop();

private:

    // override internal game interface methods
    virtual void initialise();
    virtual void run();
    virtual void cleanUp();

    // override ogre frame listener methods
    virtual bool frameStarted(const Ogre::FrameEvent&);

    // override input listener methods
    virtual void onButtonExit();

    std::unique_ptr<OgreRenderer> m_OgreRenderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
};

} // namespace OpenRump
