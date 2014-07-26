// ----------------------------------------------------------------------------
// Entity.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <string>
#include <memory>

#include <Ogre.h>
#include <OgrePrerequisites.h>

#include <openrump/EntityController.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class SceneManager;
    class SceneNode;
    class Camera;
}

namespace OpenRump {
    class AnimationController;
    class OgreRenderer;
}

namespace OpenRump {

class EntityBase
{
private:

    /*!
     * @brief Default constructor - only for delegating.
     */
    EntityBase();

protected:

    /*!
     * @brief Constructs an entity.
     * The entity will use the specified scene manager to load itself into
     * memory.
     * @param renderer The renderer to use to create this entity.
     */
    EntityBase(OgreRenderer* renderer);

    /*!
     * @brief Loads the entity from a mesh name.
     * @param instanceName A globally unique name for this entity.
     * @param meshName The mesh file name to load.
     */
    void load(Ogre::String instanceName, Ogre::String meshName);

public:

    /*!
     * @brief Constructs an entity and loads the specified mesh.
     * @param renderer The renderer to use to create this entity.
     * @param instanceName A globally unique name for this entity.
     * @param meshName The mesh file name to load.
     */
    EntityBase(OgreRenderer* renderer,
           Ogre::String instanceName,
           Ogre::String meshName);

    /*!
     * @brief Allow destruction through base class pointer
     */
    virtual ~EntityBase();

    /*!
     * @brief Returns the name of the entity.
     * This is a globally unique identifier for this particular entity.
     */
    std::string getName() const;

    /*!
     * @brief Creates a new controller for this entity.
     * @param controller The type of controller to create.
     * @param controllerName A unique name for this controller so it can be referenced later.
     */
    void addController(std::shared_ptr<EntityController> controller, std::string controllerName);

    /*!
     * @brief Destroys an existing controller from this entity.
     * @param controllerName The unique name of the controller.
     */
    void removeController(std::string controllerName);

    Ogre::SceneNode* getTranslateSceneNode();
    Ogre::SceneNode* getRotateSceneNode();

protected:

    /*!
     * @brief Extracts a section from one animation into another animation.
     * The specified section of key frames are extracted from the source
     * animation, scaled to the length of the destination animation and
     * copied. The time frame to extract is specified in seconds.
     * @note The source and destination skeletons should have the same amount
     * of nodes. Copying an animation to a skeleton with less nodes or more
     * nodes doesn't crash, but not sure what that does.
     * @note All existing key frames are erased in the destination animation.
     * @param source The source animation to copy from.
     * @param dest The destination animation to copy to.
     * @param startTime Where to begin copying from the source animation.
     * @param endTime Where to stop copying from the source animation.
     */
    void extractAnimation(Ogre::Animation* source,
                          Ogre::Animation* dest,
                          Ogre::Real startTime,
                          Ogre::Real endTime);

private:

    Ogre::SceneManager* m_SceneManager;
    Ogre::Entity* m_OgreEntity;
    Ogre::SceneNode* m_OgreEntityTranslateNode;
    Ogre::SceneNode* m_OgreEntityRotateNode;

    std::map< std::string, std::shared_ptr<EntityController> > m_EntityControllerMap;

    Ogre::String m_Name;
};

} // namespace OpenRump
