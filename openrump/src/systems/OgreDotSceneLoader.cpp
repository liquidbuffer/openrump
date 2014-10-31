// ----------------------------------------------------------------------------
// OgreDotSceneLoader.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "openrump/systems/OgreDotSceneLoader.hpp"
#include "openrump/systems/OgreRenderer.hpp"

#include <ontology/Ontology.hpp>

#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/pending/property.hpp>
#include <boost/graph/graph_concepts.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
OgreDotSceneLoader::Settings::Settings() :
    loadCameras(true),
    loadLights(true),
    loadEntities(true),
    loadExternalResources(true),
    excludeNodes()
{
}

// ----------------------------------------------------------------------------
OgreDotSceneLoader::OgreDotSceneLoader()
{
}

// ----------------------------------------------------------------------------
OgreDotSceneLoader::~OgreDotSceneLoader()
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::addScene(const std::string& sceneName,
                                   const std::string& fileName,
                                   const Settings& settings)
{
    // check for scenes with the same name
    if(m_Scenes.find(sceneName) != m_Scenes.end())
    {
        std::cerr << "[OgreDotSceneLoader::addScene] Error: Scene with name \""
            << sceneName << "\" already created" << std::endl;
        return;
    }
    
    // open the dot scene file for parsing
    std::ifstream file(fileName.c_str());
    if(!file.is_open())
    {
        std::cerr << "[OgreDotSceneLoader::addScene] Error: Failed to open file \""
            << fileName << "\"" << std::endl;
        return;
    }

    // prepare resource group and root scene node
    this->prepareSceneForLoading(sceneName, settings);
    
    using namespace boost::property_tree;
    try
    {
        ptree pt;
        read_xml(file, pt);
    
        if(m_Settings.loadExternalResources)
        {
            this->parseExternals(pt.get_child("scene.externals"));
            Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(sceneName);
        }
        this->parseNodes(pt.get_child("scene.nodes"));
        this->sceneLoadingSucceeded();
    }
    catch(const ptree_bad_data& e)
    {
        std::cerr << "[OgreDotSceneLoader::addScene] ptree_bad_data exception: "
            << e.what() << std::endl;
        this->sceneLoadingFailed();
    }
    catch(const ptree_bad_path& e)
    {
        std::cout << "[OgreDotSceneLoader::addScene] ptree_bad_path exception: "
            << e.what() << std::endl;
        this->sceneLoadingFailed();
    }
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::prepareSceneForLoading(const std::string& sceneName,
                                                 const Settings& settings)
{
    // create a resource group for the scene being created
    Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup(sceneName, false);
    
    // create a scene node for the scene to be attached to
    m_SceneNode = this->world->getSystemManager()
        .getSystem<OgreRenderer>()
        .getMainSceneManager()
        ->getRootSceneNode()
        ->createChildSceneNode(sceneName);
    
    // store required info for scene being created
    m_SceneName = sceneName;
    m_Scenes.insert(sceneName);
    m_Settings = settings;
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::sceneLoadingSucceeded()
{
    m_Scenes.insert(m_SceneName);
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::sceneLoadingFailed()
{
    // clean up resource group and scene node
    this->world->getSystemManager()
        .getSystem<OgreRenderer>()
        .getMainSceneManager()
        ->destroySceneNode(m_SceneNode);
    Ogre::ResourceGroupManager::getSingleton()
        .destroyResourceGroup(m_SceneName);
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::destroyScene(const std::string& sceneName)
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::destroyScene()
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseExternals(boost::property_tree::ptree& externals)
{
    std::set<Ogre::String> resourceLocations;

    for(auto& item : externals) // iterates over items in <externals> 
    {
        if(item.second.get<Ogre::String>("<xmlattr>.type") == "material")
        {
            for(auto& resourceLocation : item.second) // iterates over nodes in <item>
            {
                if(resourceLocation.first == "file")
                {
                    // add location to set (prevents duplicates)
                    Ogre::String resourceFile = resourceLocation.second
                        .get<Ogre::String>("<xmlattr>.name");
                    resourceLocations.insert(resourceFile.substr(0, resourceFile.find_last_of("\\/")));
                }
            }
        }
    }

    // add set to ogre resource group
    for(const auto& resourceFile : resourceLocations)
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
            resourceFile,
            "FileSystem",
            m_SceneName
        );
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseNodes(boost::property_tree::ptree& nodes)
{
    for(auto& node : nodes)
        this->parseNode(node.second, m_SceneNode);
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseNode(boost::property_tree::ptree& xmlNode,
                                    Ogre::SceneNode* parentSceneNode)
{
    for(auto& nodeAttribtes : xmlNode)
    {
        // skip nodes
        if(m_Settings.excludeNodes.find(
            xmlNode.get<Ogre::String>("<xmlattr>.name")
        ) != m_Settings.excludeNodes.end())
            return;
        
        // nested nodes
        if(nodeAttribtes.first == "node")
        {
            this->parseNode(nodeAttribtes.second, parentSceneNode);
        }
        
        // 3D endtities
        if(m_Settings.loadEntities && nodeAttribtes.first == "entity")
        {
            Ogre::SceneNode* sn = this->createSceneNode(xmlNode, parentSceneNode);
            this->parseNodeEntity(nodeAttribtes.second, sn);
        }
        
        // lights
        if(m_Settings.loadLights && nodeAttribtes.first == "light")
        {
        }
        
        // cameras
        if(m_Settings.loadCameras && nodeAttribtes.first == "camera")
        {
        }
    }
}

// ----------------------------------------------------------------------------
Ogre::SceneNode* OgreDotSceneLoader::createSceneNode(boost::property_tree::ptree& xmlNode,
                                                      Ogre::SceneNode* parentSceneNode)
{
    Ogre::SceneNode* sn = parentSceneNode->createChildSceneNode(
        m_SceneName + "." + xmlNode.get<Ogre::String>("<xmlattr>.name")
    );
    
    // every node must have these three attributes
    this->parseNodePosition(xmlNode.get_child("position"), sn);
    this->parseNodeRotation(xmlNode.get_child("rotation"), sn);
    this->parseNodeScale(xmlNode.get_child("scale"),       sn);
    
    return sn;
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseNodePosition(boost::property_tree::ptree& position,
                                            Ogre::SceneNode* node)
{
    boost::property_tree::ptree& attr = position.get_child("<xmlattr>");
    node->setPosition(attr.get<Ogre::Real>("x"),
                      attr.get<Ogre::Real>("y"),
                      attr.get<Ogre::Real>("z"));
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseNodeRotation(boost::property_tree::ptree& rotation,
                                            Ogre::SceneNode* node)
{
    boost::property_tree::ptree& attr = rotation.get_child("<xmlattr>");
    node->setOrientation(Ogre::Quaternion(attr.get<Ogre::Real>("qw"),
                                          attr.get<Ogre::Real>("qx"),
                                          attr.get<Ogre::Real>("qy"),
                                          attr.get<Ogre::Real>("qz")));
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseNodeScale(boost::property_tree::ptree& scale,
                                         Ogre::SceneNode* node)
{
    boost::property_tree::ptree& attr = scale.get_child("<xmlattr>");
    node->setScale(attr.get<Ogre::Real>("x"),
                   attr.get<Ogre::Real>("y"),
                   attr.get<Ogre::Real>("z"));
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::parseNodeEntity(boost::property_tree::ptree& entity,
                                          Ogre::SceneNode* node)
{
    // entity name and entity mesh file name are essential
    Ogre::String entityName = m_SceneName + "." + entity.get<Ogre::String>("<xmlattr>.name");
    Ogre::String entityMesh = entity.get<Ogre::String>("<xmlattr>.meshFile");
    
    // create entity and attach it to its corresponding scene node
    Ogre::Entity* ogreEntity = this->world->getSystemManager()
        .getSystem<OgreRenderer>()
        .getMainSceneManager()
        ->createEntity(entityName, entityMesh, m_SceneName);
    node->attachObject(ogreEntity);
    
    // process optional entity attributes
    for(auto& property : entity.get_child("<xmlattr>"))
    {
    }
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::initialise()
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::processEntity(Ontology::Entity&)
{
}

// ----------------------------------------------------------------------------
void OgreDotSceneLoader::configureEntity(Ontology::Entity&, std::string)
{
}

} // namespace OpenRump