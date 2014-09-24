// ----------------------------------------------------------------------------
// Game.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/PyCallbackDispatcher.hpp>

#include <ontology/World.hpp>

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

class Game
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
    //EntityBase* loadPlayer(std::string entityName, std::string meshFileName);

    /*!
     * @brief Creates a new camera and attaches it to the window.
     * @param cameraName A globally unique name for this camera.
     * @return The new camera,
     */
    void createCamera(std::string cameraName);

    /*!
     * @brief Attaches the main camera to the orbit of an entity.
     * @param entityName The entity identifier string.
     */
    //void attachCameraToEntity(std::string entityName);

    /*!
     * @brief Attaches a camera to the orbit of an entity.
     * @param cameraName The camera identifier string.
     * @param entityName The entity identifier string.
     */
    //void attachCameraToEntity(std::string cameraName, std::string entityName);

    /*!
     * @brief Registers a callback for when game updates occur.
     * By default a game update occurs at a constant rate of 60 times a second,
     * regardless of frame rate.
     */
    void addGameUpdateCallback(boost::python::object callable);

    /*!
     * @brief Unregisters a callback for game updates.
     */
    void removeGameUpdateCallback(boost::python::object callable);

    /*!
     * @brief Removes each and every callback managed by this class.
     */
    void removeAllCallbacks();

private:

    /*!
     * @brief Initialises the game so it's ready to run.
     */
    void initialise();

    /*!
     * @brief Cleans up everything.
     */
    void cleanUp();

    // slot receivers
    void onButtonExit();
    void onUpdateRenderLoop();
    void onUpdateGameLoop();

    Ontology::World m_World;

    bool m_Shutdown;
    bool m_IsInitialised;

    std::map< std::string, std::unique_ptr<EntityBase> > m_EntityMap;

    PyCallbackDispatcher m_PyGameUpdate;
};

} // namespace OpenRump
