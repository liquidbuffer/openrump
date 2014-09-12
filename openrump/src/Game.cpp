// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/OISInputSystem.hpp>
#include <openrump/OgreRenderSystem.hpp>
#include <openrump/EntityPlayer.hpp>

#include <ontology/SystemManager.hpp>

#include <OgreRoot.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Game::Game() :
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
    //m_Input->attachToWindow(m_OgreRenderer->getWindowHandle());

    m_World.getSystemManager().getSystem<OgreRenderSystem>().startRendering();

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

    // create systems
    m_World.getSystemManager()
        .addSystem(new OgreRenderSystem())
        .addSystem(new OISInputSystem())
        .initialise()
        ;

    OgreRenderSystem& renderer = m_World.getSystemManager().getSystem<OgreRenderSystem>();
    OISInputSystem& input = m_World.getSystemManager().getSystem<OISInputSystem>();

    // ogre can cancel initialisation proceedure
    if(!renderer.isInitialised())
        return;

    // attach input system to render window
    input.attachToWindow(renderer.getWindowHandle());

    Ogre::SceneManager* sm = renderer.getMainSceneManager();

    // create default lights
    sm->createLight("MainLight")->setPosition(60, 200, -500);
    sm->createLight("SecondLight")->setPosition(-60, -200, 500);

    // register as listener
    input.event.addListener(this, "Game");
    renderer.frameEvent.addListener(this, "Game");

    m_IsInitialised = true;
}

// ----------------------------------------------------------------------------
/*EntityBase* Game::loadPlayer(std::string entityName, std::string meshFileName)
{
    if(m_EntityMap.find(entityName) != m_EntityMap.end())
        throw std::runtime_error(
                "[Game::loadPlayer] Error: Entity \""
                + entityName + "\" already loaded!"
        );

    EntityBase* entityPtr = new EntityPlayer(m_Input.get(), m_OgreRenderer.get(), entityName, meshFileName);
    m_EntityMap[entityName] = std::unique_ptr<EntityBase>(entityPtr);
    return entityPtr;
}*/

// ----------------------------------------------------------------------------
void Game::createCamera(std::string cameraName)
{
    m_World.getSystemManager().getSystem<OgreRenderSystem>().createCamera(cameraName);
}

// ----------------------------------------------------------------------------
/*void Game::attachCameraToEntity(std::string entityName)
{
    auto it = m_EntityMap.find(entityName);
    if(it == m_EntityMap.end())
        throw std::runtime_error(
                "[Game::attachCameraToEntity] Error: Entity with name \""
                + entityName + "\" doesn't exisẗ"
        );
    it->second->attachCameraToOrbit(
            m_World.getSystemManager()->getSystem<OgreRenderSystem>()->getMainCamera()
    );
}*/

// ----------------------------------------------------------------------------
/*void Game::attachCameraToEntity(std::string cameraName, std::string entityName)
{
    auto it = m_EntityMap.find(entityName);
    if(it == m_EntityMap.end())
        throw std::runtime_error(
                "[Game::attachCameraToEntity] Error: Entity with name \""
                + entityName + "\" doesn't exist"
        );
    Ogre::SceneManager* sm = m_World.getSystemManager()->getSystem<OgreRenderSystem>()->getMainSceneManager();
    it->second->attachCameraToOrbit(sm->getCamera(cameraName));
}*/

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

    OgreRenderSystem& renderer = m_World.getSystemManager().getSystem<OgreRenderSystem>();
    OISInputSystem& input = m_World.getSystemManager().getSystem<OISInputSystem>();

    // detach input from render window
    input.detachFromWindow();

    // destroy scene
    Ogre::SceneManager* sm = renderer.getMainSceneManager();
    sm->destroyLight(sm->getLight("MainLight"));

    // remove all listeners
    renderer.frameEvent.removeListener(this);
    input.event.removeListener(this);

    m_IsInitialised = false;
}

// ----------------------------------------------------------------------------
bool Game::onPreUpdateRenderLoop(const float timeSinceLastUpdate)
{
    // capture input before frame is rendered for maximum responsiveness
    m_World.getSystemManager().getSystem<OISInputSystem>().capture();

    if(m_Shutdown)
        return false;

    return true;
}

// ----------------------------------------------------------------------------
bool Game::onUpdateGameLoop(const float timeStep)
{
    m_World.setDeltaTime(timeStep);
    m_World.update();
    return m_PyGameUpdate.dispatchAndFindFalse(std::forward<const float>(timeStep));
}

// ----------------------------------------------------------------------------
void Game::onButtonExit()
{
    this->stop();
}

} // namespace OpenRump
