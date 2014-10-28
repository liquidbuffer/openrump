// ----------------------------------------------------------------------------
// SDLInput.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "InputInterface.hpp"
#include "ontology/System.hpp"
#include <boost/graph/graph_concepts.hpp>

namespace OpenRump {
    
class SDLInput :
    public InputInterface
{
private:

    void dispatchDirectionChange();
    void dispatchCameraAngleChange(int x, int y);
    void dispatchCameraDistanceChange(int y);
    
    // implement ontology abstracts
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    void configureEntity(Ontology::Entity&, std::string="") override;
    
    // implement abstract methods from InputInterface
    void attachToWindow(std::size_t windowHnd) override;
    void detachFromWindow() override;
    void setWindowExtents(unsigned int width, unsigned int height) override;
    void capture() override;
    
    struct MoveAxisState
    {
        MoveAxisState() : up(0), down(0), left(0), right(0) {}
        int up, down, left, right;
    } m_MoveAxisState;
};

} // namespace OpenRump