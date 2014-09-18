// ----------------------------------------------------------------------------
// OgreRenderSystem.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/ListenerDispatcher.hxx>
#include <openrump/LoopTimer.hpp>

#include <OgreString.h>
#include <OgreFrameListener.h>

#include <ontology/System.hpp>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class RendererFrameListener;
}

namespace Ogre {
    class Root;
    class RenderWindow;
    class SceneManager;
    class Camera;
}

namespace OpenRump {

class OPENRUMP_API OgreRenderSystem :
    public Ontology::System,
    public Ogre::FrameListener
{
public:

    /*!
     * @brief Default constructor
     */
    OgreRenderSystem();

    /*!
     * @brief Default destructor
     */
    ~OgreRenderSystem();

    /*!
     * @brief Checks if the renderer was successfully initialised.
     */
    bool isInitialised();

    /*!
     * @brief Enters an infinite loop
     */
    void startRendering();

    /*!
     * @brief Returns the render window handle
     */
    std::size_t getWindowHandle() const;

    /*!
     * @brief Gets the main scene manager.
     */
    Ogre::SceneManager* getMainSceneManager() const;

    /*!
     * @brief Creates a new camera and returns it.
     * The new camera is set to span the entire screen, and becomes the new
     * main camera.
     * @param name A globally unique name for the camera.
     */
    Ogre::Camera* createCamera(std::string name);

    /*!
     * @brief Gets the main camera.
     */
    Ogre::Camera* getMainCamera() const;

    ListenerDispatcher<RendererFrameListener> frameEvent;

private:

    // override frame listeners
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    /*!
     * @brief Sets up Ogre3D
     * Initialises Ogre, opens the render window, and sets up resources.
     */
    virtual void initialise();

    virtual void processEntity(const Ontology::Entity& e) const {}

    std::unique_ptr<LoopTimer> m_LoopTimer;
    std::unique_ptr<Ogre::Root> m_Root;
    Ogre::RenderWindow* m_Window;
    Ogre::SceneManager* m_SceneManager;
    Ogre::Camera* m_Camera;
    Ogre::String m_PluginsCfg;
    Ogre::String m_ResourcesCfg;

    bool m_IsInitialised;
};

} // namespace OpenRump
