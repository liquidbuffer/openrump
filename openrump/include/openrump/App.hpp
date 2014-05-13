// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>
#include <openrump/InputListener.hpp>
#include <openrump/RendererFrameListener.hpp>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class OgreRenderer;
    class Input;
}

namespace Ogre {
    struct FrameEvent;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp,
    public InputListener,
    public RendererFrameListener
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

    // override frame listener
    virtual bool onFrameRenderingQueued(const Ogre::FrameEvent&);

    // override input events
    virtual void onButtonExit();
    virtual void onChangeDirectionAndVelocity(float x, float y);
    virtual void onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY);
    virtual void onChangeCameraDistanceDelta(float deltaDistance);

    std::unique_ptr<OgreRenderer> m_OgreRenderer;
    std::unique_ptr<Input> m_Input;

    bool m_Shutdown;
};

} // OpenRump
