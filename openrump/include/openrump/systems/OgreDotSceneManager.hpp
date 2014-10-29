// ----------------------------------------------------------------------------
// OgreDotSceneManager.hpp
// ----------------------------------------------------------------------------

#ifndef _OPENRUMP_DOT_SCENE_MANAGER_HPP_
#define _OPENRUMP_DOT_SCENE_MANAGER_HPP_

// ----------------------------------------------------------------------------
// include files

#include <ontology/System.hpp>

#include <boost/property_tree/ptree.hpp>

namespace OpenRump {

class OgreDotSceneManager : public Ontology::System
{
public:
    
    /*!
     * @brief Loads a dot-scene file and sets up everything.
     * 
     * If a scene already exists, the scene being loaded will simply be merged
     * with the existing scene. You can delete the scene at any later point in
     * with OgreDotSceneManager::destroyScene(sceneName).
     * @param fileName The name of the dot-scene file to load.
     * @param sceneName A unique name for this part of the scene. You can use
     * this parameter to delete the scene later on.
     */
    void addScene(std::string sceneName, std::string fileName);
    
    /*!
     * @brief Destroys a section of the scene.
     * @param sceneName The section of the scene to destroy.
     */
    void destroyScene(std::string sceneName);
    
    /*!
     * @brief Destroys the entire scene. Everything.
     */
    void destroyScene();
    
private:
    
    void parseExternals(boost::property_tree::ptree& externals, std::string sceneName);
    void parseNodes(boost::property_tree::ptree& nodes);
    void parseNode(boost::property_tree::ptree& node);
    
    // override ontology methods
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    void configureEntity(Ontology::Entity&, std::string) override;
};

} // namespace OpenRump

#endif // _OPENRUMP_DOT_SCENE_MANAGER_HPP_