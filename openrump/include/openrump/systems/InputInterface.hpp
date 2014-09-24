// ----------------------------------------------------------------------------
// InputInterface.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

#include <cstddef>

namespace OpenRump {

class OPENRUMP_API InputInterface
{
public:

    /*!
     * @brief Default destructor
     */
    virtual ~InputInterface() {};

    /*!
     * @brief Attaches the InputInterface system to the specified window.
     * @note If the InputInterface system is already attached to a window, it is first detached.
     * @param height The height of the window
     */
    virtual void attachToWindow(std::size_t windowHnd) = 0;

    /*!
     * @brief Detaches the InputInterface system from the current window.
     * @note If the InputInterface system isn't attached, this method will silently fail.
     */
    virtual void detachFromWindow() = 0;

    /*!
     * @brief Sets how large the InputInterface region is in pixels.
     * This is required in order to define the mouse region, and should be
     * updated whenever the window is resized.
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    virtual void setWindowExtents(unsigned int width, unsigned int height) = 0;

    /*!
     * @brief Captures InputInterface from all registered devices
     */
    virtual void capture() = 0;
};

}  // namespace OpenRump
