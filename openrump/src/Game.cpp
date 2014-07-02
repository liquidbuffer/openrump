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

    // remove all references to any python objects, otherwise destructor
    // is not called
    // see issue #1
    this->removeAllCallbacks();
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
        throw std::runtime_error(
                "[Game::initialise] Error: Game already initialised!");

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
EntityBase* Game::loadPlayer(std::string entityName, std::string meshFileName)
{
    if(m_EntityMap.find(entityName) != m_EntityMap.end())
        throw std::runtime_error(
                "[Game::loadPlayer] Error: Entity \""
                + entityName + "\" already loaded!"
        );

    EntityBase* entityPtr = new EntityPlayer(m_Input.get(), m_OgreRenderer.get(), entityName, meshFileName);
    m_EntityMap[entityName] = std::unique_ptr<EntityBase>(entityPtr);
    return entityPtr;
}

// ----------------------------------------------------------------------------
void Game::createCamera(std::string cameraName)
{
    m_OgreRenderer->createCamera(cameraName);
}

// ----------------------------------------------------------------------------
void Game::attachCameraToEntity(std::string entityName)
{
    auto it = m_EntityMap.find(entityName);
    if(it == m_EntityMap.end())
        throw std::runtime_error(
                "[Game::attachCameraToEntity] Error: Entity with name \""
                + entityName + "\" doesn't exisẗ"
        );
    it->second->attachCameraToOrbit(m_OgreRenderer->getMainCamera());
}

// ----------------------------------------------------------------------------
void Game::attachCameraToEntity(std::string cameraName, std::string entityName)
{
    auto it = m_EntityMap.find(entityName);
    if(it == m_EntityMap.end())
        throw std::runtime_error(
                "[Game::attachCameraToEntity] Error: Entity with name \""
                + entityName + "\" doesn't exist"
        );
    Ogre::SceneManager* sm = m_OgreRenderer->getMainSceneManager();
    it->second->attachCameraToOrbit(sm->getCamera(cameraName));
}

// ----------------------------------------------------------------------------
void Game::addGameUpdateCallback(boost::python::object callable)
{
    m_PyGameUpdate.addCallback(callable);
}

// ----------------------------------------------------------------------------
void Game::removeGameUpdateCallback(boost::python::object callable)
{
    m_PyGameUpdate.removeCallback(callable);
}

// ----------------------------------------------------------------------------
void Game::removeAllCallbacks()
{
    m_PyGameUpdate.removeAllCallbacks();
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
    return m_PyGameUpdate.dispatchAndFindFalse(std::forward<const float>(timeStep));
}

// ----------------------------------------------------------------------------
void Game::onButtonExit()
{
    this->stop();
}

} // namespace OpenRump
