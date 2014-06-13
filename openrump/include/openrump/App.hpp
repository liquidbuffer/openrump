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
    class EntityPlayer;
    class Entity;
}

namespace Ogre {
    struct FrameEvent;
    class Entity;
    class SceneNode;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp,
    public InputListener,
    public RendererFrameListener
{
public:

    /*!
     * @brief constructor
     */
    App(std::string workingDirectory);

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
    virtual bool onUpdateRenderLoop(const float timeSinceLastUpdate);

    // override input events
    virtual void onButtonExit();

    std::string m_WorkingDirectory;

    std::unique_ptr<OgreRenderer> m_OgreRenderer;
    std::unique_ptr<Input> m_Input;

    std::unique_ptr<EntityPlayer> m_Player;
    std::unique_ptr<Entity> m_World;

    Ogre::SceneNode* m_CameraRotateNode;
    Ogre::SceneNode* m_CameraNode;
    float m_CameraAngleX;
    float m_CameraAngleY;
    float m_CameraDistance;

    bool m_Shutdown;
};

} // OpenRump
