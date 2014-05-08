// ----------------------------------------------------------------------------
// OgreRenderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Renderer.hpp>

#include <OgreFrameListener.h>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations
namespace Ogre {
    class Root;
    class RenderWindow;
    class SceneManager;
    class Camera;
}

namespace OpenRump {

class OPENRUMP_API OgreRenderer :
    public Renderer,
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

    // override virtual functions
    virtual bool initialise();
    virtual void startRendering();
    virtual std::size_t getWindowHandle();
    virtual void addResourceLocation(std::string path);
    virtual void loadObject(std::string ID, std::string filename);

private:

    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    std::unique_ptr<Ogre::Root> m_Root;
    Ogre::RenderWindow* m_Window;
    Ogre::SceneManager* m_SceneManager;
    Ogre::Camera* m_Camera;
    Ogre::String m_PluginsCfg;
    Ogre::String m_ResourcesCfg;
};

} // namespace OpenRump
