// ----------------------------------------------------------------------------
// EntityManagerWrapper.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/py/ontology/EntityManagerWrapper.hpp>

// ----------------------------------------------------------------------------
Ontology::Entity::ID EntityManagerWrapper::createEntityWrapper(const char* name)
{
    return this->createEntity(name).getID();
}