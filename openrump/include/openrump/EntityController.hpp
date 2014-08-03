// ----------------------------------------------------------------------------
// EntityController.hpp
// ----------------------------------------------------------------------------

#ifndef __OPEN_RUMP_ENTITY_CONTROLLER_HPP__
#define __OPEN_RUMP_ENTITY_CONTROLLER_HPP__

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class EntityBase;
}

namespace OpenRump {

class EntityController
{
public:

    /*!
     * @brief Default constructor
     */
    EntityController();

    /*!
     * @brief Virtual destructor
     */
    virtual ~EntityController();

    /*!
     * @brief Sets the entity this controller should take control over.
     * @note This should not be used manually - this is called by the entity
     * when the controller is added to the entity.
     */
    virtual void setEntity(EntityBase* entity);

    /*!
     * @brief Called when the entity being controlled is switched.
     * @param newEntity The new entity being switched to.
     */
    virtual void notifyEntityChange(EntityBase* newEntity);

protected:

    EntityBase* m_Entity;
};

} // namespace OpenRump

#endif // __OPEN_RUMP_ENTITY_CONTROLLER_HPP__
