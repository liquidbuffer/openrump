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

    /*!
     * @brief Called when it's time to update the game loop
     * @return Return false to signal program shutdown
     */
    virtual bool onUpdateGameLoop(float timeSinceLastUpdate);

    Renderer* m_Renderer;
};

} // OpenRump
