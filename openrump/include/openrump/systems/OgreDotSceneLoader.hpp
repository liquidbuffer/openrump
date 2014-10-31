// ----------------------------------------------------------------------------
// OgreDotSceneLoader.hpp
// ----------------------------------------------------------------------------

#ifndef _OPENRUMP_DOT_SCENE_LOADER_HPP_
#define _OPENRUMP_DOT_SCENE_LOADER_HPP_

// ----------------------------------------------------------------------------
// include files

#include <ontology/System.hpp>

#include <boost/property_tree/ptree.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    class SceneNode;
}

namespace OpenRump {

class OgreDotSceneLoader : public Ontology::System
{
public:
    
    struct Settings
    {
        Settings();
        bool loadCameras;
        bool loadLights;
        bool loadEntities;
        bool loadExternalResources;
        std::set<std::string> excludeNodes;
    };
    
    /*!
     * @brief Default constructor
     */
    OgreDotSceneLoader();
    
    /*!
     * @brief Default destructor
     */
    ~OgreDotSceneLoader();
    
    /*!
     * @brief Loads a dot-scene file and sets up everything.
     * 
     * If a scene already exists, the scene being loaded will simply be merged
     * with the existing scene. You can delete the scene at any later point in
     * with OgreDotSceneLoader::destroyScene(sceneName).
     * @param fileName The name of the dot-scene file to load.
     * @param sceneName A unique name for this part of the scene. You can use
     * @param settings A settings object controls the details of which parts should be loaded.
     * this parameter to delete the scene later on.
     */
    void addScene(const std::string& sceneName,
                  const std::string& fileName,
                  const Settings& settings = Settings());
    
    /*!
     * @brief Destroys a section of the scene.
     * @param sceneName The section of the scene to destroy.
     */
    void destroyScene(const std::string& sceneName);
    
    /*!
     * @brief Destroys the entire scene. Everything.
     */
    void destroyScene();
    
private:
    
    void prepareSceneForLoading(const std::string& sceneName, const Settings&);
    void sceneLoadingSucceeded();
    void sceneLoadingFailed();
    
    void parseExternals(boost::property_tree::ptree& externals);
    void parseNodes(boost::property_tree::ptree& nodes);
    void parseNode(boost::property_tree::ptree& xmlNode, Ogre::SceneNode* parentSceneNode);
    Ogre::SceneNode* createSceneNode(boost::property_tree::ptree& node, Ogre::SceneNode* parentSceneNode);
    void parseNodePosition(boost::property_tree::ptree& position, Ogre::SceneNode* node);
    void parseNodeRotation(boost::property_tree::ptree& rotation, Ogre::SceneNode* node);
    void parseNodeScale(boost::property_tree::ptree& scale, Ogre::SceneNode* node);
    void parseNodeEntity(boost::property_tree::ptree& entity, Ogre::SceneNode* node);
    
    // override ontology methods
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    void configureEntity(Ontology::Entity&, std::string) override;
    
    std::string m_SceneName;
    Ogre::SceneNode* m_SceneNode;
    Settings m_Settings;
    
    std::set<std::string> m_Scenes;
};

} // namespace OpenRump

#endif // _OPENRUMP_DOT_SCENE_LOADER_HPP_