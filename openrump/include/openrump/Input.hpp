// ----------------------------------------------------------------------------
// Input.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <cstddef>

// TODO OIS needs to be abstracted more
#include <openrump/ListenerDispatcher.hxx>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>

namespace OpenRump {

class Input
{
public:

    /*!
     * @brief Default constructor
     */
    Input();

    /*!
     * @brief Default destructor
     */
    virtual ~Input();

    /*!
     * @brief Attaches the input system to the specified window.
     * @note If the input system is already attached to a window, it is first detached.
     * @param height The height of the window
     */
    virtual void attachToWindow(std::size_t windowHnd) = 0;

    /*!
     * @brief Detaches the input system from the current window.
     * @note If the input system isn't attached, this method will silently fail.
     */
    virtual void detachFromWindow() = 0;

    /*!
     * @brief Sets how large the input region is in pixels.
     * This is required in order to define the mouse region, and should be
     * updated whenever the window is resized.
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    virtual void setWindowExtents(unsigned int width, unsigned int height) = 0;

    // expose listeners so objects can use them to register
    typedef ListenerDispatcher<OIS::KeyListener*> KeyEvent;
    KeyEvent keyEvent;
    typedef ListenerDispatcher<OIS::MouseListener*> MouseEvent;
    MouseEvent mouseEvent;
    typedef ListenerDispatcher<OIS::JoyStickListener*> JoyStickEvent;
    JoyStickEvent joyStickEvent;
};

}  // namespace OpenRump
