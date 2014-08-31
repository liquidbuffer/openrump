// ----------------------------------------------------------------------------
// OgreRenderComponent.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/OgreRenderComponent.hpp>
#include <openrump/RendererFrameListener.hpp>

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
OgreRenderComponent::OgreRenderComponent() :
    m_LoopTimer(new LoopTimer()),
    m_Root(nullptr),
    m_Window(nullptr),
    m_SceneManager(nullptr),
    m_Camera(nullptr),
    m_PluginsCfg(Ogre::StringUtil::BLANK),
    m_ResourcesCfg(Ogre::StringUtil::BLANK)
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
OgreRenderComponent::~OgreRenderComponent()
{
}

// ----------------------------------------------------------------------------
bool OgreRenderComponent::initialise()
{
    if(m_Root)
        return false;

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
        return false;
#else
    if(!m_Root->showConfigDialog());
        return false;
#endif // _DEBUG

    // initialise render window
    m_Window = m_Root->initialise(true, "Open Rump");

    // set default mipmap level (note: some APIs ignore this)
    Ogre::TextureManager::getSingletonPtr()->setDefaultNumMipmaps(5);

    // initialise essential resources
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Essential");

    // set up scene manager
    m_SceneManager = m_Root->createSceneManager("OctreeSceneManager", "MainSceneManager");

    m_Root->addFrameListener(this);

    // set game loop fps to 60
    m_LoopTimer->setFPS(60);

    return true;
}

// ----------------------------------------------------------------------------
void OgreRenderComponent::startRendering()
{
    m_LoopTimer->reset();
    m_Root->startRendering();
}

// ----------------------------------------------------------------------------
std::size_t OgreRenderComponent::getWindowHandle() const
{
    std::size_t hwnd;
    m_Window->getCustomAttribute("WINDOW", &hwnd);
    return hwnd;
}

// ----------------------------------------------------------------------------
Ogre::SceneManager* OgreRenderComponent::getMainSceneManager() const
{
    return m_SceneManager;
}

// ----------------------------------------------------------------------------
Ogre::Camera* OgreRenderComponent::createCamera(std::string name)
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
Ogre::Camera* OgreRenderComponent::getMainCamera() const
{
    return m_Camera;
}

// ----------------------------------------------------------------------------
bool OgreRenderComponent::frameStarted(const Ogre::FrameEvent& evt)
{
    // dispatch pre render loop event
    return frameEvent.dispatchAndFindFalse(&RendererFrameListener::onPreUpdateRenderLoop,
            evt.timeSinceLastFrame);
}

// ----------------------------------------------------------------------------
bool OgreRenderComponent::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // dispatch game loop event
    int updates = 0;
    while(m_LoopTimer->isTimeToUpdate())
    {
        if(!frameEvent.dispatchAndFindFalse(&RendererFrameListener::onUpdateGameLoop,
            m_LoopTimer->getTimeBetweenFrames()))
            return false;

        if(++updates >= 10)  // don't allow more than 10 game loop updates
            break;           // without a render loop update
    }

    // dispatch render loop event
    return frameEvent.dispatchAndFindFalse(&RendererFrameListener::onUpdateRenderLoop,
            evt.timeSinceLastFrame);
}

} // namespace OpenRump
