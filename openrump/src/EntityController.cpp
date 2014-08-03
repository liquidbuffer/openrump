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
        this->notifyEntityChange(entity);
    m_Entity = entity;
}

// ----------------------------------------------------------------------------
void EntityController::notifyEntityChange(EntityBase*)
{
}

} // namespace OpenRump
