// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>
#include <openrump/RendererListener.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Renderer;
    class Input;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp,
    public RendererListener
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

    Renderer* m_Renderer;
    Input* m_Input;
};

} // OpenRump
