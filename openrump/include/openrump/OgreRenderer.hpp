// ----------------------------------------------------------------------------
// OgreRenderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/ListenerDispatcher.hxx>
#include <openrump/LoopTimer.hpp>

#include <OgreString.h>
#include <OgreFrameListener.h>

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

class OPENRUMP_API OgreRenderer :
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
     * @brief Sets up Ogre3D
     * Initialises Ogre, opens the render window, and sets up resources.
     * @return False if the initialisation procedure is interrupted.
     */
    bool initialise();

    /*!
     * @brief Enters an infinite loop
     */
    void startRendering();

    /*!
     * @brief Returns the render window handle
     */
    std::size_t getWindowHandle();

    ListenerDispatcher<RendererFrameListener> frameEvent;

private:

    // override frame listener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    std::unique_ptr<LoopTimer> m_LoopTimer;
    std::unique_ptr<Ogre::Root> m_Root;
    Ogre::RenderWindow* m_Window;
    Ogre::SceneManager* m_SceneManager;
    Ogre::Camera* m_Camera;
    Ogre::String m_PluginsCfg;
    Ogre::String m_ResourcesCfg;
};

} // namespace OpenRump
