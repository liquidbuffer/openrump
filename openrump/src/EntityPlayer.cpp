// ----------------------------------------------------------------------------
// EntityPlayer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityPlayer.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
EntityPlayer::EntityPlayer(Ogre::SceneManager* sm, std::string instanceName, std::string meshName) :
    Entity(sm, instanceName, meshName)
{
}

// ----------------------------------------------------------------------------
EntityPlayer::~EntityPlayer()
{
}

} // namespace OpenRump
