// ----------------------------------------------------------------------------
// Renderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <cstddef>
#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class RendererListener;
}

namespace OpenRump {

class Renderer
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
     * @brief Adds a listener to the dispatch list
     */
    void addFrameListener(RendererListener*);

    /*!
     * @brief Removes a listener from the dispatch list
     */
    void removeFrameListener(RendererListener*);

    /*!
     * @brief Dispatches a frame event
     * A frame event should occur once every frame, in which the game logic
     * should be updated. The time passed since the last update is passed
     * as an argument.
     * @param timeSinceLastUpdate The time in seconds since the last call to
     * this method.
     * @return Returning false signals the intent to shut down the application.
     */
    bool dispatchFrameEvent(float timeSinceLastUpdate);

private:
    std::vector<RendererListener*> m_ListenerList;
};

} // namespace OpenRump
