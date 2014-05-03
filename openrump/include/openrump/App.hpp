// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>
#include <OGRE/OgreFrameListener.h>
#include <OIS/OISKeyboard.h>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Renderer;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp,
    public OIS::KeyListener,
    public Ogre::FrameListener
{
public:

    /*!
     * @brief Default constructor
     */
    App();

    /*!
     * @brief Default destructor
     */
    ~App();

private:

    /*!
     * @brief Called when the application should load
     */
    virtual void onLoad();

    /*!
     * @brief Called when the application should run
     */
    virtual void onRun();

    /*!
     * @brief Called when the application is exiting
     */
    virtual void onExit();

    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
    virtual bool keyPressed(const OIS::KeyEvent&);
    virtual bool keyReleased(const OIS::KeyEvent&);

    Renderer* m_Renderer;
};

} // OpenRump
