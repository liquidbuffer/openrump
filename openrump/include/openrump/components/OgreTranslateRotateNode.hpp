// ----------------------------------------------------------------------------
// OgreTranslateRotateNode.hpp
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

struct OgreTranslateRotateNode : public Ontology::Component
{
    OgreTranslateRotateNode(Ogre::SceneNode* translation,
                            Ogre::SceneNode* rotation) :
        translation(translation),
        rotation(rotation)
    {
    }

    Ogre::SceneNode* translation;
    Ogre::SceneNode* rotation;
};

} // namespace OpenRump
