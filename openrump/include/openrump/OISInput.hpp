// ----------------------------------------------------------------------------
// OISInput.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Input.hpp>

#include <cstddef>
#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace OIS {
    class InputManager;
}

namespace OpenRump {

class OPENRUMP_API OISInput :
    public Input,
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

private:

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

};

}  // namespace OpenRump
