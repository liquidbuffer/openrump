// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/systems/OISInput.hpp>
#include <openrump/systems/OgreRenderer.hpp>
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
    m_World.getSystemManager().getSystem<OgreRenderer>().startRendering();

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
    m_World.getSystemManager().addSystem<OgreRenderer>();
    m_World.getSystemManager().addSystem<OISInput>();
    m_World.getSystemManager().initialise();

    OgreRenderer& renderer = m_World.getSystemManager().getSystem<OgreRenderer>();
    OISInput&     input    = m_World.getSystemManager().getSystem<OISInput>();

    // ogre can cancel initialisation procedure without error
    if(!renderer.isInitialised())
        return;

    // attach OIS to Ogre's window
    input.attachToWindow(renderer.getWindowHandle());

    // create connections
    renderer.on_frame_started.connect(boost::bind(&OISInput::capture, &input));
    input.on_exit.connect(boost::bind(&Game::onButtonExit, this));

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
    m_World.getSystemManager().getSystem<OgreRenderer>().createCamera(cameraName);
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

    m_IsInitialised = false;
}

// ----------------------------------------------------------------------------
void Game::onUpdateGameLoop()
{
    //m_World.setDeltaTime();
    m_World.update();
}

// ----------------------------------------------------------------------------
void Game::onButtonExit()
{
    this->stop();
}

} // namespace OpenRump
