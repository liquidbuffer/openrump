// ----------------------------------------------------------------------------
// Game.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityController.hpp>
#include <openrump/InputListener.hpp>
#include <openrump/RendererFrameListener.hpp>
#include <openrump/PyCallbackDispatcher.hpp>

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
    void
    stop();

    /*!
     * @brief Begins running the game (main loop).
     */
    void
    run();

    /*!
     * @brief Loads a player into the game.
     * @param entityName A globally unique string identifying this entity.
     * @param meshFileName The name of the mesh file to load.
     */
    EntityBase*
    createEntityPlayer(std::string entityName, std::string meshFileName);

    /*!
     * @brief Destroys and entity by name.
     * @param entityName The unique identifier of the entity to destroy.
     */
    void
    destroyEntity(std::string entityName);

    /*!
     * @brief Destroys an entity by pointer.
     * @param entity The pointer to the entity to destroy.
     */
    void
    destroyEntity(EntityBase* entity);

    /*!
     * @brief Creates a camera orbit controller, ready to be attached to an entity.
     */
    EntityController*
    createEntityControllerCameraOrbit(float distance=0.0f);

    /*!
     * @brief Creates a new camera and attaches it to the window.
     * @param cameraName A globally unique name for this camera.
     * @return The new camera,
     */
    void
    createCamera(std::string cameraName);

    /*!
     * @brief Destroys the specifed camera
     * @param cameraName The name of the camera to destroy.
     */
    void
    destroyCamera(std::string cameraName);

    /*!
     * @brief Registers a callback for when game updates occur.
     * By default a game update occurs at a constant rate of 60 times a second,
     * regardless of frame rate.
     */
    void
    addGameUpdateCallback(boost::python::object callable);

    /*!
     * @brief Unregisters a callback for game updates.
     */
    void
    removeGameUpdateCallback(boost::python::object callable);

    /*!
     * @brief Removes each and every callback managed by this class.
     */
    void
    removeAllCallbacks();

private:

    /*!
     * @brief Initialises the game so it's ready to run.
     */
    void
    initialise();

    /*!
     * @brief Cleans up everything.
     */
    void
    cleanUp();

    // override frame events
    virtual bool onPreUpdateRenderLoop(const float timeSinceLastUpdate);
    virtual bool onUpdateGameLoop(const float timeStep);

    // override input listener methods
    virtual void onButtonExit();

    std::unique_ptr<OgreRenderer> m_OgreRenderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
    bool m_IsInitialised;

    std::map< std::string, std::unique_ptr<EntityBase> > m_EntityMap;

    PyCallbackDispatcher m_PyGameUpdate;
};

} // namespace OpenRump
