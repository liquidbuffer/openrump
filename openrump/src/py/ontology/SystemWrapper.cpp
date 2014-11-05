// ----------------------------------------------------------------------------
// SystemWrapper.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/py/ontology/SystemWrapper.hpp>

void SystemWrapper::initialise()
{
    this->get_override("initialise")();
}

void SystemWrapper::processEntity(Entity& e)
{
    this->get_override("processEntity")(e);
}

void SystemWrapper::configureEntity(Entity&, std::string params)
{
    this->get_override("configureEntity")(params);
}