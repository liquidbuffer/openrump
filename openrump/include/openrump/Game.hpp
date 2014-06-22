// ----------------------------------------------------------------------------
// Game.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/InputListener.hpp>

#include <OgreFrameListener.h>

#include <string>
#include <memory>
#include <map>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class OgreRenderer;
    class Input;
    class EntityBase;
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

    /*!
     * @brief Loads a player into the game
     */
    void loadPlayer(std::string entityName, std::string meshFileName);
    void attachCameraToEntity(std::string entityName, std::string cameraName);

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

    std::map< std::string, std::unique_ptr<EntityBase> > m_EntityList;
};

} // namespace OpenRump
