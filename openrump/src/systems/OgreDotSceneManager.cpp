// ----------------------------------------------------------------------------
// OgreDotSceneManager.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "openrump/systems/OgreDotSceneManager.hpp"
#include "openrump/systems/OgreRenderer.hpp"

#include <ontology/Ontology.hpp>

#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/pending/property.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
void OgreDotSceneManager::addScene(const std::string& sceneName, const std::string& fileName)
{
    std::ifstream file(fileName.c_str());
    if(!file.is_open())
    {
        std::cerr << "Failed to open file \"" << fileName << "\"" << std::endl;
        return;
    }

    // prepare resource group and root scene node
    Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->createResourceGroup(sceneName, false);
    m_SceneName = sceneName;
    m_SceneNode = this->world->getSystemManager()
        .getSystem<OgreRenderer>()
        .getMainSceneManager()
        ->getRootSceneNode()
        ->createChildSceneNode(sceneName);
    
    using namespace boost::property_tree;
    try
    {
        ptree pt;
        read_xml(file, pt);
    
        this->parseExternals(pt.get_child("scene.externals"));
        rgm->initialiseResourceGroup(sceneName);
        this->parseNodes(pt.get_child("scene.nodes"));
    }
    catch(const ptree_bad_data& e)
    {
        std::cerr << "ptree_bad_data exception: " << e.what() << std::endl;
        rgm->destroyResourceGroup(sceneName);
    }
    catch(const ptree_bad_path& e)
    {
        std::cout << "ptree_bad_path exception: " << e.what() << std::endl;
        rgm->destroyResourceGroup(sceneName);
    }
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::destroyScene(const std::string& sceneName)
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::destroyScene()
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseExternals(boost::property_tree::ptree& externals)
{
    Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();

    for(auto& item : externals) // iterates over items in <externals> 
    {
        if(item.second.get<Ogre::String>("<xmlattr>.type") == "material")
        {
            for(auto& resourceLocation : item.second) // iterates over nodes in <item>
            {
                if(resourceLocation.first == "file")
                {
                    rgm->addResourceLocation(
                        resourceLocation.second.get<Ogre::String>("<xmlattr>.name"),
                        "FileSystem",
                        m_SceneName
                    );
                }
            }
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
    Ogre::SceneNode* sn = m_SceneNode->createChildSceneNode(
        m_SceneName + "." + node.get<Ogre::String>("<xmlattr>.name")
    );
    this->parseNodePosition(node.get_child("position"), sn);
    this->parseNodeRotation(node.get_child("rotation"), sn);
    this->parseNodeScale(node.get_child("scale"),       sn);
    this->parseNodeEntity(node.get_child("entity"),     sn);
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseNodePosition(boost::property_tree::ptree& position,
                                            Ogre::SceneNode* node)
{
    boost::property_tree::ptree& attr = position.get_child("<xmlattr>");
    node->setPosition(attr.get<Ogre::Real>("x"),
                      attr.get<Ogre::Real>("y"),
                      attr.get<Ogre::Real>("z"));
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseNodeRotation(boost::property_tree::ptree& rotation,
                                            Ogre::SceneNode* node)
{
    boost::property_tree::ptree& attr = rotation.get_child("<xmlattr>");
    node->setOrientation(Ogre::Quaternion(attr.get<Ogre::Real>("qw"),
                                          attr.get<Ogre::Real>("qx"),
                                          attr.get<Ogre::Real>("qy"),
                                          attr.get<Ogre::Real>("qz")));
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseNodeScale(boost::property_tree::ptree& scale,
                                         Ogre::SceneNode* node)
{
    boost::property_tree::ptree& attr = scale.get_child("<xmlattr>");
    node->setScale(attr.get<Ogre::Real>("x"),
                   attr.get<Ogre::Real>("y"),
                   attr.get<Ogre::Real>("z"));
}

// ----------------------------------------------------------------------------
void OgreDotSceneManager::parseNodeEntity(boost::property_tree::ptree& entity,
                                          Ogre::SceneNode* node)
{
    Ogre::String entityName = m_SceneName + "." + entity.get<Ogre::String>("<xmlattr>.name");
    Ogre::String entityMesh = entity.get<Ogre::String>("<xmlattr>.meshFile");
    Ogre::Entity* ogreEntity = this->world->getSystemManager()
        .getSystem<OgreRenderer>()
        .getMainSceneManager()
        ->createEntity(entityName, entityMesh);
    node->attachObject(ogreEntity);
    
    for(auto& property : entity.get_child("<xmlattr>"))
    {
    }
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