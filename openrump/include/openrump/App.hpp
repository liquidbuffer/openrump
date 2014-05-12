// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>
#include <openrump/RendererListener.hpp>
#include <openrump/InputListener.hpp>

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
    public InputListener
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
    virtual void onButtonExit();
    virtual void onChangeDirectionAndVelocity(float x, float y);
    virtual void onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY);
    virtual void onChangeCameraDistanceDelta(float deltaDistance);

    std::unique_ptr<Renderer> m_Renderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
};

} // OpenRump
