// ----------------------------------------------------------------------------
// EntityPlayer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Entity.hpp>

namespace OpenRump {

class EntityPlayer :
    public Entity
{
public:

    /*!
     * @brief Constructs a player using the specified ogre scene manager
     */
    EntityPlayer(Ogre::SceneManager*, std::string instanceName, std::string meshName);

    /*!
     * @brief Default destructor
     */
    ~EntityPlayer();
};

} // namespace OpenRump
