// ----------------------------------------------------------------------------
// OgreCameraOrbitNode.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <ontology/Component.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class SceneNode;
}

namespace OpenRump {

struct OgreCameraOrbitNode : public Ontology::Component
{
    OgreCameraOrbitNode(Ogre::SceneNode* rotation,
                            Ogre::SceneNode* translation) :
        rotation(rotation),
        translation(translation)
    {
    }

    Ogre::SceneNode* rotation;
    Ogre::SceneNode* translation;
};

} // namespace OpenRump
