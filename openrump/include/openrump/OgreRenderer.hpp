// ----------------------------------------------------------------------------
// OgreRenderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Renderer.hpp>

#include <OgreFrameListener.h>

// ----------------------------------------------------------------------------
// forward declarations
namespace Ogre {
    class Root;
    class RenderWindow;
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
    virtual void loadObject(std::string ID, std::string filename, std::string path="");

private:

    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

    Ogre::Root* m_Root;
    Ogre::RenderWindow* m_Window;
    Ogre::String m_PluginsCfg;
    Ogre::String m_ResourcesCfg;
};

} // namespace OpenRump
