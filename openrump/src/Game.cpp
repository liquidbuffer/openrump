// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/systems/CameraOrbit.hpp>
#include <openrump/systems/OISInput.hpp>
#include <openrump/systems/OgreRenderer.hpp>
#include <openrump/systems/LoopTimer.hpp>
#include <openrump/components/OgreCamera.hpp>
#include <openrump/components/OgreCameraOrbitNode.hpp>
#include <openrump/components/OgreEntity.hpp>
#include <openrump/components/OgreTranslateRotateNode.hpp>

#include <ontology/Ontology.hpp>

#include <OgreRoot.h>
#include <OgreEntity.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Game::Game() :
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
    m_World.getSystemManager().getSystem<OgreRenderer>().stopRendering();
}

// ----------------------------------------------------------------------------
void Game::initialise()
{
    if(m_IsInitialised)
        throw std::runtime_error(
                "[Game::initialise] Error: Game already initialised!");

    // create systems
    using namespace Ontology;
    m_World.getSystemManager().addSystem<LoopTimer>()
        .supportsComponents<
            None>();
    m_World.getSystemManager().addSystem<OgreRenderer>()
        .supportsComponents<
            None>();
    m_World.getSystemManager().addSystem<OISInput>()
        .supportsComponents<
            None>();
    m_World.getSystemManager().addSystem<CameraOrbit>()
        .supportsComponents<
            OgreCameraOrbitNode>();
    m_World.getSystemManager().initialise();

    CameraOrbit&    cameraOrbit = m_World.getSystemManager().getSystem<CameraOrbit>();
    LoopTimer&      loopTimer   = m_World.getSystemManager().getSystem<LoopTimer>();
    OgreRenderer&   renderer    = m_World.getSystemManager().getSystem<OgreRenderer>();
    OISInput&       input       = m_World.getSystemManager().getSystem<OISInput>();

    // ogre can cancel initialisation procedure without error
    if(!renderer.isInitialised())
        return;

    // attach OIS to Ogre's window
    input.attachToWindow(renderer.getWindowHandle());

    // create connections
    renderer.on_frame_queued.connect(boost::bind(&LoopTimer::onFrameRendered, &loopTimer));
    renderer.on_frame_started.connect(boost::bind(&OISInput::capture, &input));
    input.on_exit.connect(boost::bind(&Game::onButtonExit, this));
    input.on_new_camera_angle.connect(boost::bind(&CameraOrbit::onNewCameraAngle, &cameraOrbit, _1, _2));
    input.on_new_camera_distance.connect(boost::bind(&CameraOrbit::onNewCameraDistance, &cameraOrbit, _1));
    loopTimer.on_game_loop.connect(boost::bind(&Game::onGameLoop, this));

    m_IsInitialised = true;
}

// ----------------------------------------------------------------------------
Ontology::Entity& Game::loadPlayer(std::string entityName, std::string meshFileName)
{
    OgreRenderer& renderer = m_World.getSystemManager().getSystem<OgreRenderer>();
    Ogre::SceneManager* sm = renderer.getMainSceneManager();

    Ogre::SceneNode* translateNode = sm->getRootSceneNode()->createChildSceneNode(entityName+"TranslateNode");
    Ogre::SceneNode* rotateNode = translateNode->createChildSceneNode(entityName+"RotateNode");
    Ogre::Entity* entity = sm->createEntity(entityName, meshFileName);
    rotateNode->attachObject(entity);

    return m_World.getEntityManager().createEntity(entityName.c_str())
        .addComponent<OgreTranslateRotateNode>(translateNode, rotateNode)
        .addComponent<OgreEntity>(entity)
        ;
}

// ----------------------------------------------------------------------------
Ontology::Entity& Game::createCamera(std::string cameraName)
{
    Ogre::Camera* camera = m_World.getSystemManager().getSystem<OgreRenderer>().createCamera(cameraName);
    m_World.getEntityManager().createEntity(cameraName.c_str())
        .addComponent<OgreCamera>(camera)
        ;
}

// ----------------------------------------------------------------------------
void Game::attachCameraToEntity(Ontology::Entity& camera, Ontology::Entity& entity)
{
    Ogre::SceneNode* attachNode = entity.getComponent<OgreTranslateRotateNode>().translation;
    Ogre::SceneNode* rotateNode = attachNode->createChildSceneNode(entity.getName()+std::string("CameraRotateNode"));
    Ogre::SceneNode* translateNode = rotateNode->createChildSceneNode(entity.getName()+std::string("CameraTranslateNode"));
    translateNode->attachObject(camera.getComponent<OgreCamera>().camera);

    entity.addComponent<OgreCameraOrbitNode>(rotateNode, translateNode);
    translateNode->setPosition(0, 0, 100);
}

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

    this->removeAllCallbacks();
    m_World.getSystemManager().getSystem<OISInput>().detachFromWindow();

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

// ----------------------------------------------------------------------------
void Game::onGameLoop()
{
    m_World.update();
}

} // namespace OpenRump
