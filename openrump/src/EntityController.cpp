// ----------------------------------------------------------------------------
// EntityController.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityController.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityController::EntityController() :
    m_Entity(nullptr)
{
}

// ----------------------------------------------------------------------------
EntityController::~EntityController()
{
}

// ----------------------------------------------------------------------------
void EntityController::setEntity(EntityBase* entity)
{
    if(m_Entity)
        this->onCleanUp();
    m_Entity = entity;
}

// ----------------------------------------------------------------------------
void EntityController::onCleanUp()
{
}

} // namespace OpenRump
