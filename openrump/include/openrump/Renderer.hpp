// ----------------------------------------------------------------------------
// Renderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <cstddef>
#include <vector>
#include <openrump/ListenerDispatcher.hxx>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class RendererListener;
}

namespace OpenRump {

class OPENRUMP_API Renderer
{
public:

    /*!
     * @brief Default constructor
     */
    Renderer();

    /*!
     * @brief Default destructor
     */
    virtual ~Renderer();

    /*!
     * @brief Called to initialise the implemented renderer.
     * @return Returning false signals the initialisation process was
     * interrupted.
     */
    virtual bool initialise() = 0;

    /*!
     * @brief Enters an infinite loop, in which the frames are rendered as fast as possible.
     */
    virtual void startRendering() = 0;

    /*!
     * @brief Returns the window handle of the render window
     */
    virtual std::size_t getWindowHandle() = 0;

    /*!
     * @brief Handles frame event dispatching to listeners
     * A frame event should occur once every frame, in which the game logic
     * should be updated. The time passed since the last update is passed
     * as an argument.
     * @note Accepts listeners of type RenderListener, dispatches time between
     * each frame event is dispatched as a float in seconds.
     */
    bool dispatchFrameEvent(float timeSinceLastUpdate);

    typedef ListenerDispatcher<RendererListener> FrameEvent;
    FrameEvent frameEvent;

private:
};

} // namespace OpenRump
