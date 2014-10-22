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

#include <SDL.h>
#include <SDL_syswm.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
OgreRenderer::OgreRenderer() :
    m_OgreWindow(nullptr),
    m_SceneManager(nullptr),
    m_Camera(nullptr),
    m_SDLWindow(nullptr),
    m_PluginsCfg(Ogre::StringUtil::BLANK),
    m_ResourcesCfg(Ogre::StringUtil::BLANK),
    m_IsInitialised(false),
    m_Shutdown(false)
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
    
    m_Root.reset(nullptr);
    SDL_DestroyWindow(m_SDLWindow);
    SDL_Quit();
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
    
    // read ogre configuration file and extract window dimensions
    int width, height;
    cf.load("ogre.cfg");
    seci = cf.getSectionIterator();
    while(seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;
        for(it = settings->begin(); it != settings->end(); ++it)
        {
            typeName = it->first;
            archName = it->second;
            if(typeName == "Video Mode")
            {
                std::size_t split = archName.find("x");
                if(split == Ogre::String::npos)
                    throw std::runtime_error("Failed to parse video mode from ogre.cfg");
                width = std::stoi(archName.substr(0, split));
                height = std::stoi(archName.substr(split+1));
            }
        }
    }
    
    SDL_Init(SDL_INIT_VIDEO);
    
    m_SDLWindow = SDL_CreateWindow(
        "Open Rump",        // window title
        0,                  // initial x position
        0,                  // initial y position
        width,              // width
        height,             // height
        SDL_WINDOW_SHOWN    // flags, see below
    );
    if(!m_SDLWindow)
        throw std::runtime_error(std::string("Could not create SDL window: ") + SDL_GetError());

    m_Root->initialise(false);
    
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    if(SDL_GetWindowWMInfo(m_SDLWindow, &wmInfo) == SDL_FALSE)
        throw std::runtime_error("Couldn't get SDL window info");
    
    Ogre::String winHandle;
    switch(wmInfo.subsystem)
    {
        case SDL_SYSWM_X11:
            winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.x11.window);
            break;
        default:
            throw std::runtime_error("Unexpected WM");
            break;
    }
    
    Ogre::NameValuePairList params;
    params.insert(std::make_pair("parentWindowHandle", winHandle));
    
    m_OgreWindow = Ogre::Root::getSingleton().createRenderWindow("OGRE Window", width, height, false, &params);
    m_OgreWindow->setVisible(true);

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
void OgreRenderer::stopRendering()
{
    m_Shutdown = true;
}

// ----------------------------------------------------------------------------
std::size_t OgreRenderer::getWindowHandle() const
{
    std::size_t hwnd;
    m_OgreWindow->getCustomAttribute("WINDOW", &hwnd);
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
    Ogre::Viewport* vp = m_OgreWindow->addViewport(m_Camera);
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
    return !m_Shutdown;
}

// ----------------------------------------------------------------------------
bool OgreRenderer::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    this->on_frame_queued();
    return !m_Shutdown;
}

} // namespace OpenRump
