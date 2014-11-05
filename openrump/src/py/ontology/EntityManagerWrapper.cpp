// ----------------------------------------------------------------------------
// EntityManagerWrapper.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/py/ontology/EntityManagerWrapper.hpp>

// ----------------------------------------------------------------------------
Entity::ID EntityManagerWrapper::createEntityWrapper(const char* name)
{
    return this->createEntity(name).getID();
}