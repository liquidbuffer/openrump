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

    virtual void addResourceLocation(std::string path) = 0;
    virtual void loadObject(std::string ID, std::string filename) = 0;

    ListenerDispatcher<RendererListener> frameEvent;

private:
};

} // namespace OpenRump
