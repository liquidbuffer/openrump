// ----------------------------------------------------------------------------
// Game.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/InputListener.hpp>
#include <openrump/RendererFrameListener.hpp>

#include <boost/python.hpp>

#include <string>
#include <memory>
#include <vector>
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
    public RendererFrameListener,
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
     * @brief Loads a player into the game.
     * @param entityName A globally unique string identifying this entity.
     * @param meshFileName The name of the mesh file to load.
     */
    void loadPlayer(std::string entityName, std::string meshFileName);

    /*!
     * @brief Attaches a camera to the orbit of an entity.
     * @param entityName The entity identifier string.
     * @param cameraName The camera identifier string.
     */
    void attachCameraToEntity(std::string entityName, std::string cameraName);

    void addGameUpdateCallback(boost::python::object callable);

private:

    /*!
     * @brief Initialises the game so it's ready to run.
     */
    void initialise();

    /*!
     * @brief Cleans up everything.
     */
    void cleanUp();

    // override frame events
    virtual bool onPreUpdateRenderLoop(const float timeSinceLastUpdate);
    virtual bool onUpdateGameLoop(const float timeStep);

    // override input listener methods
    virtual void onButtonExit();

    std::unique_ptr<OgreRenderer> m_OgreRenderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
    bool m_IsInitialised;

    std::map< std::string, std::unique_ptr<EntityBase> > m_EntityList;
    std::vector<boost::python::object> m_GameUpdateCallbackList;
};

} // namespace OpenRump
