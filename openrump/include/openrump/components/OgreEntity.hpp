// ----------------------------------------------------------------------------
// OgreEntity.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <ontology/Component.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class Entity;
}

namespace OpenRump {

struct OgreEntity : public Ontology::Component
{
    OgreEntity(Ogre::Entity* entity) : entity(entity)
    {
    }

    Ogre::Entity* entity;
};

} // namespace OpenRump
