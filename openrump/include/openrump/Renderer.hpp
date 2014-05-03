// ----------------------------------------------------------------------------
// Renderer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

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
};

} // namespace OpenRump
