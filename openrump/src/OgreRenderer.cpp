// ----------------------------------------------------------------------------
// OgreRenderer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/OgreRenderer.hpp>

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
OgreRenderer::OgreRenderer() :
    m_Root(0),
    m_PluginsCfg(""),
    m_ResourcesCfg("")
{

    // set where config files are located
#ifdef _DEBUG
    m_PluginsCfg = Ogre::String("../../res/cfg/plugins_d.cfg");
    m_ResourcesCfg = Ogre::String("../../res/cfg/resources_d.cfg");
#else
    m_PluginsCfg = Ogre::String("res/cfg/plugins.cfg");
    m_ResourcesCfg = Ogre::String("res/cfg/resources.cfg");
#endif // _DEBUG

}

// ----------------------------------------------------------------------------
OgreRenderer::~OgreRenderer()
{
    if(m_Root)
        delete m_Root;
}

// ----------------------------------------------------------------------------
void OgreRenderer::initialise()
{
    if(m_Root)
        return;

    m_Root = new Ogre::Root(m_PluginsCfg);

    // load resources configuration file
    Ogre::ConfigFile cf;
    cf.load(m_ResourcesCfg);
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while(seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;
        for(it = settings->begin(); it != settings->end(); ++it)
        {
            typeName = it->first;
            archName = it->second;
            Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(
                    archName,
                    typeName,
                    secName
            );
        }
    }

    // configure rendering window
#ifdef _DEBUG
    if(!m_Root->showConfigDialog())
        return;
#else
    if(!m_Root->showConfigDialog());
        return;
#endif // _DEBUG

    // initialise render window
    m_Window = m_Root->initialise(true, "Open Rump");

    // set default mipmap level (note: some APIs ignore this)
    Ogre::TextureManager::getSingletonPtr()->setDefaultNumMipmaps(5);

    // initialise resources
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Essential");
}

// ----------------------------------------------------------------------------
void OgreRenderer::startRendering()
{
    m_Root->startRendering();
}

// ----------------------------------------------------------------------------
std::size_t OgreRenderer::getWindowHandle()
{
    std::size_t hwnd;
    m_Window->getCustomAttribute("WINDOW", &hwnd);
    return hwnd;
}

} // namespace OpenRump
