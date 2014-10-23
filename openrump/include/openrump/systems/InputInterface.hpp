// ----------------------------------------------------------------------------
// InputInterface.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

#include <boost/signals2.hpp>

#include <ontology/System.hpp>

#include <cstddef>

namespace OpenRump {

class OPENRUMP_API InputInterface :
    public Ontology::System
{
public:

    /*!
     * @brief Default destructor
     */
    virtual ~InputInterface() {};

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
    
    // events
    boost::signals2::signal<void ()>    on_exit;
    boost::signals2::signal<void ()>    on_new_direction;
    boost::signals2::signal<void ()>    on_new_camera_angle;
    boost::signals2::signal<void ()>    on_new_camera_distance;
    
};

}  // namespace OpenRump
