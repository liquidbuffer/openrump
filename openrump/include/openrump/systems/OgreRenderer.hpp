// ----------------------------------------------------------------------------
// OgreRenderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

#include <OgreString.h>
#include <OgreFrameListener.h>

#include <ontology/System.hpp>
#include <ontology/Entity.hxx>

#include <boost/signals2.hpp>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class OgreRendererListener;
}

namespace Ogre {
    class Root;
    class RenderWindow;
    class SceneManager;
    class Camera;
}

typedef struct SDL_Window SDL_Window;

namespace OpenRump {

class OPENRUMP_API OgreRenderer :
    public Ontology::System,
    public Ogre::FrameListener
{
public:

    /*!
     * @brief Default constructor
     */
    OgreRenderer();

    /*!
     * @brief Default destructor
     */
    ~OgreRenderer();

    /*!
     * @brief Checks if the renderer was successfully initialised.
     */
    bool isInitialised();

    /*!
     * @brief Enters an infinite loop
     */
    void startRendering();

    /*!
     * @brief Stops the rendering process
     */
    void stopRendering();

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
    
    void setCameraView(Ogre::Camera* camera, Ogre::Real left,
                       Ogre::Real top, Ogre::Real width, Ogre::Real height);
    void setCameraClipping(Ogre::Camera* camera, Ogre::Real near, Ogre::Real far);
    void setMainCamera(Ogre::Camera* camera);
    void destroyCamera(Ogre::Camera* camera);

    /*!
     * @brief Gets the main camera.
     */
    Ogre::Camera* getMainCamera() const;
    
    Ogre::SceneNode* getSceneNode(std::string nodeName) const;

    boost::signals2::signal<void ()> on_frame_started;
    boost::signals2::signal<void ()> on_frame_queued;

private:

    // override frame listeners
    bool frameStarted(const Ogre::FrameEvent& evt) override;
    bool frameRenderingQueued(const Ogre::FrameEvent&) override;

    /*!
     * @brief Sets up Ogre3D
     * Initialises Ogre, opens the render window, and sets up resources.
     */
    void initialise() override;

    void processEntity(Ontology::Entity& e) override {}
    void configureEntity(Ontology::Entity&, std::string="") override {}

    std::unique_ptr<Ogre::Root> m_Root;
    Ogre::RenderWindow* m_OgreWindow;
    Ogre::SceneManager* m_SceneManager;
    Ogre::Camera* m_Camera;
    SDL_Window* m_SDLWindow;
    Ogre::String m_PluginsCfg;
    Ogre::String m_ResourcesCfg;

    bool m_IsInitialised;
    bool m_Shutdown;
};

} // namespace OpenRump
