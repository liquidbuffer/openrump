// ----------------------------------------------------------------------------
// OgreRenderer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/systems/OgreRenderer.hpp>

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
OgreRenderer::OgreRenderer() :
    m_Window(nullptr),
    m_SceneManager(nullptr),
    m_Camera(nullptr),
    m_PluginsCfg(Ogre::StringUtil::BLANK),
    m_ResourcesCfg(Ogre::StringUtil::BLANK),
    m_IsInitialised(false)
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
    m_Root->removeFrameListener(this);

    // destroy scene
    m_SceneManager->destroyLight(m_SceneManager->getLight("SecondLight"));
    m_SceneManager->destroyLight(m_SceneManager->getLight("MainLight"));
    m_Root->destroySceneManager(m_SceneManager);
}

// ----------------------------------------------------------------------------
bool OgreRenderer::isInitialised()
{
    return m_IsInitialised;
}

// ----------------------------------------------------------------------------
void OgreRenderer::initialise()
{
    if(m_Root)
        return;

    m_Root = std::unique_ptr<Ogre::Root>(new Ogre::Root(m_PluginsCfg));

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
    if(!(m_Root->restoreConfig() || m_Root->showConfigDialog()))
        return;
#else
    if(!m_Root->showConfigDialog());
        return;
#endif // _DEBUG

    // initialise render window
    m_Window = m_Root->initialise(true, "Open Rump");

    // set default mipmap level (note: some APIs ignore this)
    Ogre::TextureManager::getSingletonPtr()->setDefaultNumMipmaps(5);

    // initialise essential resources
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Essential");

    // set up scene manager
    m_SceneManager = m_Root->createSceneManager("OctreeSceneManager", "MainSceneManager");

    // create default lights
    m_SceneManager->createLight("MainLight")->setPosition(60, 200, -500);
    m_SceneManager->createLight("SecondLight")->setPosition(-60, -200, 500);

    m_Root->addFrameListener(this);

    m_IsInitialised = true;
}

// ----------------------------------------------------------------------------
void OgreRenderer::startRendering()
{
    m_Root->startRendering();
}

// ----------------------------------------------------------------------------
std::size_t OgreRenderer::getWindowHandle() const
{
    std::size_t hwnd;
    m_Window->getCustomAttribute("WINDOW", &hwnd);
    return hwnd;
}

// ----------------------------------------------------------------------------
Ogre::SceneManager* OgreRenderer::getMainSceneManager() const
{
    return m_SceneManager;
}

// ----------------------------------------------------------------------------
Ogre::Camera* OgreRenderer::createCamera(std::string name)
{
    m_Camera = m_SceneManager->createCamera(name);
    Ogre::Viewport* vp = m_Window->addViewport(m_Camera);
    vp->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.5f));
    m_Camera->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) /
            Ogre::Real(vp->getActualHeight())
    );
    m_Camera->setNearClipDistance(0.2);
    m_Camera->setFarClipDistance(500);
    return m_Camera;
}

// ----------------------------------------------------------------------------
Ogre::Camera* OgreRenderer::getMainCamera() const
{
    return m_Camera;
}

// ----------------------------------------------------------------------------
bool OgreRenderer::frameStarted(const Ogre::FrameEvent& evt)
{
    this->on_frame_started();
    return true;
}

// ----------------------------------------------------------------------------
bool OgreRenderer::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // dispatch game loop event
    /* TODO should be in LoopTimer
    int updates = 0;
    while(m_LoopTimer->isTimeToUpdate())
    {
        if(!this->event.dispatchAndFindFalse(&OgreRendererListener::onUpdateGameLoop,
            m_LoopTimer->getTimeBetweenFrames()))
            return false;

        if(++updates >= 10)  // don't allow more than 10 game loop updates
            break;           // without a render loop update
    }*/

    this->on_frame_queued();
    return true;
}

} // namespace OpenRump
