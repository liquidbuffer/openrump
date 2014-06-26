// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/OISInput.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/EntityPlayer.hpp>

#include <OgreRoot.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Game::Game() :
    m_OgreRenderer(new OgreRenderer),
    m_Input(new OISInput),
    m_Shutdown(false),
    m_IsInitialised(false)
{
    this->initialise();
}

// ----------------------------------------------------------------------------
Game::~Game()
{
    this->cleanUp();
}

// ----------------------------------------------------------------------------
void Game::run()
{
    // attach OIS to render window before running
    m_Input->attachToWindow(m_OgreRenderer->getWindowHandle());

    m_OgreRenderer->startRendering();
}

// ----------------------------------------------------------------------------
void Game::stop()
{
    m_Shutdown = true;
}

// ----------------------------------------------------------------------------
void Game::initialise()
{
    if(m_IsInitialised)
        return;

    // initialise renderer
    m_OgreRenderer->initialise();

    Ogre::SceneManager* sm = m_OgreRenderer->getMainSceneManager();

    // create default light
    Ogre::Light* light = sm->createLight("MainLight");
    light->setPosition(60, 200, -500);
    sm->createLight("SecondLight")->setPosition(-60, -200, 500);

    // register as listener
    m_Input->event.addListener(this, "Game");
    m_OgreRenderer->frameEvent.addListener(this, "Game");

    m_IsInitialised = true;
}

// ----------------------------------------------------------------------------
void Game::loadPlayer(std::string entityName, std::string meshFileName)
{
    if(m_EntityList.find(entityName) != m_EntityList.end())
        return;
    Ogre::SceneManager* sm = m_OgreRenderer->getMainSceneManager();
    m_EntityList[entityName] = std::unique_ptr<EntityBase>(
        new EntityPlayer(m_Input.get(), m_OgreRenderer.get(), sm, entityName, meshFileName)
    );
}

// ----------------------------------------------------------------------------
void Game::attachCameraToEntity(std::string entityName, std::string cameraName)
{
    auto it = m_EntityList.find(entityName);
    if(it == m_EntityList.end())
        return;
    Ogre::SceneManager* sm = m_OgreRenderer->getMainSceneManager();
    it->second->attachCameraToOrbit(sm->getCamera(cameraName));
}

// ----------------------------------------------------------------------------
void Game::addGameUpdateCallback(boost::python::object callable)
{
    m_GameUpdateCallbackList.push_back(callable);
}

// ----------------------------------------------------------------------------
void Game::cleanUp()
{
    if(!m_IsInitialised)
        return;

    Ogre::SceneManager* sm = m_OgreRenderer->getMainSceneManager();

    // remove lights
    sm->destroyLight(sm->getLight("MainLight"));

    // clean up input
    m_OgreRenderer->frameEvent.removeListener(this);
    m_Input->event.removeListener(this);

    m_IsInitialised = false;
}

// ----------------------------------------------------------------------------
bool Game::onPreUpdateRenderLoop(const float timeSinceLastUpdate)
{
    // capture input before frame is rendered for maximum responsiveness
    m_Input->capture();

    if(m_Shutdown)
        return false;

    return true;
}

// ----------------------------------------------------------------------------
bool Game::onUpdateGameLoop(const float timeStep)
{
    for(auto it : m_GameUpdateCallbackList)
        if(!it(timeStep))
            return false;

    return true;
}

// ----------------------------------------------------------------------------
void Game::onButtonExit()
{
    this->stop();
}

} // namespace OpenRump
