// ----------------------------------------------------------------------------
// SDLInput.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "InputInterface.hpp"
#include "ontology/System.hpp"

namespace OpenRump {
    
class SDLInput :
    public InputInterface
{
    // implement ontology abstracts
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    
    // implement abstract methods from InputInterface
    void attachToWindow(std::size_t windowHnd) override;
    void detachFromWindow() override;
    void setWindowExtents(unsigned int width, unsigned int height) override;
    void capture() override;
};

} // namespace OpenRump