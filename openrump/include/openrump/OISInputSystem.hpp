// ----------------------------------------------------------------------------
// OISInputSystem.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/InputInterface.hpp>

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>

#include <Artemis/EntityProcessingSystem.h>

#include <cstddef>
#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace OIS {
    class InputManager;
}

namespace OpenRump {

class OPENRUMP_API OISInputSystem :
    public InputInterface,
    public artemis::EntityProcessingSystem,
    public OIS::KeyListener,
    public OIS::MouseListener,
    public OIS::JoyStickListener
{
public:

    /*!
     * @brief Default constructor
     */
    OISInputSystem();

    /*!
     * @brief Default destructor
     */
    ~OISInputSystem();

    // implement derived input methods
    virtual void attachToWindow(std::size_t windowHnd);
    virtual void detachFromWindow();
    virtual void setWindowExtents(unsigned int width, unsigned int height);
    virtual void capture();

private:

    /*!
     * @brief Computes the directional vector of the player and dispatches
     */
    void dispatchNewDirection();

    // implement artemis methods
    virtual void processEntity(artemis::Entity&) {};

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
