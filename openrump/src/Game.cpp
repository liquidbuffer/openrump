// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/systems/CameraOrbit.hpp>
#include <openrump/systems/SDLInput.hpp>
#include <openrump/systems/OgreRenderer.hpp>
#include <openrump/systems/LoopTimer.hpp>
#include <openrump/systems/ThirdPersonController.hpp>
#include <openrump/components/OgreCamera.hpp>
#include <openrump/components/OgreCameraOrbitNode.hpp>
#include <openrump/components/OgreEntity.hpp>
#include <openrump/components/OgreTranslateRotateNode.hpp>
#include <openrump/components/Direction2D.hpp>
#include <openrump/components/Speed.hpp>

#include <ontology/Ontology.hpp>

#include <OgreRoot.h>
#include <OgreEntity.h>

#include <SDL.h>
#include <boost/graph/graph_concepts.hpp>

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
    m_World.getSystemManager().addSystem<LoopTimer>(60)
        .supportsComponents<
            None>();
    m_World.getSystemManager().addSystem<OgreRenderer>()
        .supportsComponents<
            None>();
    m_World.getSystemManager().addPolymorphicSystem<InputInterface, SDLInput>()
        .supportsComponents<
            None>();
    m_World.getSystemManager().addSystem<CameraOrbit>()
        .supportsComponents<
            OgreCameraOrbitNode>();
    m_World.getSystemManager().addSystem<ThirdPersonController>("../../res/twilightsparkle.xml")
        .supportsComponents<
            OgreCameraOrbitNode,
            OgreTranslateRotateNode,
            Direction2D,
            Speed>();
    
    // initialise all systems
    m_World.getSystemManager().initialise();

    CameraOrbit&    cameraOrbit     = m_World.getSystemManager().getSystem<CameraOrbit>();
    LoopTimer&      loopTimer       = m_World.getSystemManager().getSystem<LoopTimer>();
    OgreRenderer&   renderer        = m_World.getSystemManager().getSystem<OgreRenderer>();
    InputInterface* input           = m_World.getSystemManager().getSystemPtr<InputInterface>();
    ThirdPersonController& thirdPC  = m_World.getSystemManager().getSystem<ThirdPersonController>();

    // ogre can cancel initialisation procedure without error
    if(!renderer.isInitialised())
        return;

    // attach OIS to Ogre's window
    //input.attachToWindow(renderer.getWindowHandle());

    // create connections
    renderer.on_frame_queued.connect(boost::bind(&LoopTimer::onFrameRendered, &loopTimer));
    input->on_camera_angle_change.connect(boost::bind(&CameraOrbit::onNewCameraAngle, &cameraOrbit, _1, _2));
    input->on_camera_distance_change.connect(boost::bind(&CameraOrbit::onNewCameraDistance, &cameraOrbit, _1));
    input->on_direction_change.connect(boost::bind(&ThirdPersonController::onDirectionChange, &thirdPC, _1, _2));
    input->on_exit.connect(boost::bind(&Game::onButtonExit, this));
    loopTimer.on_game_loop.connect(boost::bind(&Game::onUpdateGameLoop, this));
    loopTimer.on_game_loop.connect(boost::bind(&InputInterface::capture, input));

    m_IsInitialised = true;
}

// ----------------------------------------------------------------------------
Ontology::Entity::ID Game::loadPlayer(std::string entityName, std::string meshFileName)
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
        .addComponent<Direction2D>()
        .addComponent<Speed>()
        .getID()
        ;
}

// ----------------------------------------------------------------------------
Ontology::Entity::ID Game::createCamera(std::string cameraName)
{
    Ogre::Camera* camera = m_World.getSystemManager().getSystem<OgreRenderer>().createCamera(cameraName);
    return m_World.getEntityManager().createEntity(cameraName.c_str())
        .addComponent<OgreCamera>(camera)
        .getID()
        ;
}

// ----------------------------------------------------------------------------
void Game::attachCameraToEntity(Ontology::Entity::ID cameraID, Ontology::Entity::ID entityID)
{
    Ontology::Entity& camera = m_World.getEntityManager().getEntity(cameraID);
    Ontology::Entity& entity = m_World.getEntityManager().getEntity(entityID);
    
    Ogre::SceneNode* attachNode = entity.getComponent<OgreTranslateRotateNode>().translation;
    Ogre::SceneNode* rotateNode = attachNode->createChildSceneNode(entity.getName()+std::string("CameraRotateNode"));
    Ogre::SceneNode* translateNode = rotateNode->createChildSceneNode(entity.getName()+std::string("CameraTranslateNode"));
    
    translateNode->attachObject(camera.getComponent<OgreCamera>().camera);

    entity.addComponent<OgreCameraOrbitNode>(rotateNode, translateNode);
    translateNode->setPosition(0, 0, 100);
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

    this->removeAllCallbacks();
    //m_World.getSystemManager().getSystem<OISInput>().detachFromWindow();

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
