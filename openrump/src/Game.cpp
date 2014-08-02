// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/OISInput.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/EntityPlayer.hpp>
#include <openrump/EntityControllerCameraOrbit.hpp>

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
void
Game::run()
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
void
Game::stop()
{
    m_Shutdown = true;
}

// ----------------------------------------------------------------------------
void
Game::initialise()
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
EntityBase*
Game::createEntityPlayer(std::string entityName, std::string meshFileName)
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
void
Game::destroyEntity(std::string entityName)
{
    auto it = m_EntityMap.find(entityName);
    if(it == m_EntityMap.end())
        throw std::runtime_error(
            "[Game::destroyEntity] Error: Entity with name \"" + entityName + "\" does not exist"
        );
    m_EntityMap.erase(it);
}

// ----------------------------------------------------------------------------
void
Game::destroyEntity(EntityBase* entity)
{
    for(auto it = m_EntityMap.begin(); it != m_EntityMap.end(); ++it)
        if(it->second.get() == entity)
        {
            m_EntityMap.erase(it);
            return;
        }
    throw std::runtime_error("[Game::destroyEntity] Error: Entity does not exist");
}

// ----------------------------------------------------------------------------
EntityController*
Game::createEntityControllerCameraOrbit(float distance)
{
    return new EntityControllerCameraOrbit(m_OgreRenderer->getMainSceneManager(), m_Input.get());
}

// ----------------------------------------------------------------------------
void
Game::createCamera(std::string cameraName)
{
    m_OgreRenderer->createCamera(cameraName);
}

// ----------------------------------------------------------------------------
void
Game::destroyCamera(std::string cameraName)
{
    // TODO implement destroying cameras
}

// ----------------------------------------------------------------------------
void
Game::addGameUpdateCallback(boost::python::object callable)
{
    m_PyGameUpdate.addCallback(callable);
}

// ----------------------------------------------------------------------------
void
Game::removeGameUpdateCallback(boost::python::object callable)
{
    m_PyGameUpdate.removeCallback(callable);
}

// ----------------------------------------------------------------------------
void
Game::removeAllCallbacks()
{
    m_PyGameUpdate.removeAllCallbacks();
}

// ----------------------------------------------------------------------------
void
Game::cleanUp()
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
bool
Game::onPreUpdateRenderLoop(const float timeSinceLastUpdate)
{
    // capture input before frame is rendered for maximum responsiveness
    m_Input->capture();

    if(m_Shutdown)
        return false;

    return true;
}

// ----------------------------------------------------------------------------
bool
Game::onUpdateGameLoop(const float timeStep)
{
    return m_PyGameUpdate.dispatchAndFindFalse(std::forward<const float>(timeStep));
}

// ----------------------------------------------------------------------------
void
Game::onButtonExit()
{
    this->stop();
}

} // namespace OpenRump
