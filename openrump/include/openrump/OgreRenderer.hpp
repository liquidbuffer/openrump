// ----------------------------------------------------------------------------
// OgreRenderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Renderer.hpp>

#include <OgreString.h>

// ----------------------------------------------------------------------------
// forward declarations
namespace Ogre {
    class Root;
    class RenderWindow;
}

namespace OpenRump {

class OgreRenderer :
    public Renderer
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
     * @brief Initialise renderer
     */
    virtual void initialise();
    virtual void startRendering();
    virtual std::size_t getWindowHandle();

private:

    Ogre::Root* m_Root;
    Ogre::RenderWindow* m_Window;
    Ogre::String m_PluginsCfg;
    Ogre::String m_ResourcesCfg;
};

} // namespace OpenRump
