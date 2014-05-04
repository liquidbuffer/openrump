// ----------------------------------------------------------------------------
// Renderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <cstddef>

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

    virtual void initialise() = 0;
    virtual void startRendering() = 0;
    virtual std::size_t getWindowHandle() = 0;
};

} // namespace OpenRump
