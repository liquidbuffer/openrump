// ----------------------------------------------------------------------------
// OgreDotSceneManager.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "openrump/systems/OgreDotSceneManager.hpp"

#include <OgreResourceGroupManager.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/pending/property.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
void OgreDotSceneManager::addScene(std::string sceneName, std::string fileName)
{
    using boost::property_tree::ptree;
    
    std::ifstream file(fileName.c_str());
    
    ptree pt;
    read_xml(file, pt);
    
    this->parseExternals(pt.get_child("scene").get_child("externals"), sceneName);
    this->parseNodes(pt.get_child("scene").get_child("nodes"));
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::destroyScene(std::string sceneName)
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::destroyScene()
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseExternals(boost::property_tree::ptree& externals, std::string sceneName)
{
    Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();
        
    for(auto& item : externals)
    {
        if(item.second.get<Ogre::String>("<xmlattr>.type") == "material")
        {
            /*rgm->createResourceGroup();
            item.get_child("file").second.get<Ogre::String>("<xmlattr>.name")*/
        }
    }
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseNodes(boost::property_tree::ptree& nodes)
{
    for(auto& node : nodes)
        this->parseNode(node.second);
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseNode(boost::property_tree::ptree& node)
{
    
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::initialise()
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::processEntity(Ontology::Entity&)
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::configureEntity(Ontology::Entity&, std::string)
{
}

} // namespace OpenRump