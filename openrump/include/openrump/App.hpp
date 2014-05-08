// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>
#include <openrump/RendererListener.hpp>

#include <OIS/OISKeyboard.h>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Renderer;
    class Input;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp,
    public RendererListener,
    public OIS::KeyListener
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
    virtual bool onLoad();

    /*!
     * @brief Called when the application should run
     */
    virtual void onRun();

    /*!
     * @brief Called when the application is exiting
     */
    virtual void onExit();

    // override renderer events
    virtual bool onFrameEvent(float timeSinceLastUpdate);

    // override input events
    virtual bool keyPressed(const OIS::KeyEvent&);
    virtual bool keyReleased(const OIS::KeyEvent&);

    std::unique_ptr<Renderer> m_Renderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
};

} // OpenRump
