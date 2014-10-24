// ----------------------------------------------------------------------------
// Direction2D.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "ontology/Component.hpp"
#include "OgreVector2.h"

namespace OpenRump {

struct Direction2D : public Ontology::Component
{
    Ogre::Vector2 currentDirection;
    Ogre::Vector2 targetDirection;
};

} // namespace OpenRump