// ----------------------------------------------------------------------------
// OISInput.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/systems/InputInterface.hpp>

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>

#include <ontology/System.hpp>

#include <boost/signals2.hpp>

#include <cstddef>
#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace OIS {
    class InputManager;
}

namespace OpenRump {

class OPENRUMP_API OISInput :
    public InputInterface,
    public Ontology::System,
    public OIS::KeyListener,
    public OIS::MouseListener,
    public OIS::JoyStickListener
{
public:

    /*!
     * @brief Default constructor
     */
    OISInput();

    /*!
     * @brief Default destructor
     */
    ~OISInput();

    // implement derived input methods
    virtual void attachToWindow(std::size_t windowHnd);
    virtual void detachFromWindow();
    virtual void setWindowExtents(unsigned int width, unsigned int height);
    virtual void capture();

    boost::signals2::signal<void ()>             on_exit;
    boost::signals2::signal<void (float, float)> on_new_direction;
    boost::signals2::signal<void (float, float)> on_new_camera_angle;
    boost::signals2::signal<void (float)>        on_new_camera_distance;

private:

    /*!
     * @brief Computes the directional vector of the player and dispatches
     */
    void dispatchNewDirection();

    // implement ontology methods
    void initialise() override;
    void processEntity(Ontology::Entity&) override {};

    // implement RenderFrameListener methods
    bool onPreUpdateRenderLoop(const float timeSinceLastUpdate);

    // implement OIS input events
    virtual bool keyPressed(const OIS::KeyEvent&);
    virtual bool keyReleased(const OIS::KeyEvent&);
    virtual bool mouseMoved(const OIS::MouseEvent&);
    virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
    virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
    virtual bool povMoved( const OIS::JoyStickEvent&, int pov );
    virtual bool axisMoved( const OIS::JoyStickEvent&, int axis );
    virtual bool sliderMoved( const OIS::JoyStickEvent&, int sliderID );
    virtual bool buttonPressed( const OIS::JoyStickEvent&, int button );
    virtual bool buttonReleased( const OIS::JoyStickEvent&, int button );

    OIS::InputManager*              m_InputSystem;
    OIS::Keyboard*                  m_Keyboard;
    OIS::Mouse*                     m_Mouse;
    std::vector<OIS::JoyStick*>    m_Joysticks;

    // numbers between -1000 and 1000, depending on the direction of the input
    // joystick or WASD keys. The angle of the player's direction can be
    // calculated using these.
    int m_PlayerMoveUpDown;
    int m_PlayerMoveLeftRight;
};

}  // namespace OpenRump
