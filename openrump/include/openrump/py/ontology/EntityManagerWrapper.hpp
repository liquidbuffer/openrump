// ----------------------------------------------------------------------------
// EntityManagerWrapper.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <ontology/EntityManager.hpp>

using namespace Ontology;

struct EntityManagerWrapper : EntityManager
{
    // need a version of this function that returns the entity ID rather than an entity reference
    Entity::ID createEntityWrapper(const char* name="");
};