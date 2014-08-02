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
     * @note This should not be used manually (hackety)
     */
    virtual void setEntity(EntityBase* entity);

    /*!
     * @brief Called when the entity being controlled is removed from the entity itself.
     */
    virtual void onCleanUp();

protected:

    EntityBase* m_Entity;
};

} // namespace OpenRump

#endif // __OPEN_RUMP_ENTITY_CONTROLLER_HPP__
