// ----------------------------------------------------------------------------
// EntityManagerWrapper.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <ontology/EntityManager.hpp>

struct EntityManagerWrapper : Ontology::EntityManager
{
    // need a version of this function that returns the entity ID rather than an entity reference
    Ontology::Entity::ID createEntityWrapper(const char* name="");
};