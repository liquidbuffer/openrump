// ----------------------------------------------------------------------------
// Input.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/ListenerDispatcher.hxx>

#include <cstddef>

// TODO OIS needs to be abstracted more
// Will do for now
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>

namespace OpenRump {

class OPENRUMP_API Input
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

    /*!
     * @brief Captures input from all registered devices
     */
    virtual void capture() = 0;

    // expose listeners so objects can use them to register
    // this SUCKS - OIS needs to be moved to the derived class.
    ListenerDispatcher<OIS::KeyListener> keyEvent;
    ListenerDispatcher<OIS::MouseListener> mouseEvent;
    ListenerDispatcher<OIS::JoyStickListener> joyStickEvent;
};

}  // namespace OpenRump
