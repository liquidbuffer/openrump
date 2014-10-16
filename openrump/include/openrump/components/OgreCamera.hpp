// ----------------------------------------------------------------------------
// OgreCamera.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <ontology/Component.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class Camera;
}

namespace OpenRump {

struct OgreCamera : public Ontology::Component
{
    OgreCamera(Ogre::Camera* camera) : camera(camera)
    {
    }

    Ogre::Camera* camera;
};

} // namespace OpenRump
