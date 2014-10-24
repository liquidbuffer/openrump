// ----------------------------------------------------------------------------
// Speed.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "ontology/Component.hpp"
#include "OgreMath.h"

namespace OpenRump {
    
struct Speed : public Ontology::Component
{
    Ogre::Real currentSpeed;
};

} // namespace OpenRump