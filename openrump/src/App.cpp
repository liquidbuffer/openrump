// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/OISInput.hpp>
#include <openrump/EntityPlayer.hpp>

#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreQuaternion.h>

#include <iostream>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App() :
    m_OgreRenderer(new OgreRenderer()),
    m_Input(new OISInput()),
    m_Player(nullptr),
    m_CameraRotateNode(nullptr),
    m_CameraNode(nullptr),
    m_CameraAngleX(0.0f),
    m_CameraAngleY(0.0f),
    m_CameraDistance(200.0f),
    m_Shutdown(false)
{
}

// ----------------------------------------------------------------------------
App::~App()
{
}

// ----------------------------------------------------------------------------
bool App::onLoad()
{
    // initialise renderer
    if(!m_OgreRenderer->initialise())
        return false;
    m_OgreRenderer->frameEvent.addListener(this, "App");

    // initialise input
    m_Input->attachToWindow(m_OgreRenderer->getWindowHandle());
    m_Input->event.addListener(this, "App");

    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");

    // load player character and attach camera to its orbit
    m_Player = std::unique_ptr<EntityPlayer>(
            new EntityPlayer(m_Input.get(), sm, "TwilightSparkle", "twilightsparkle.mesh")
    );
    // move camera's centre up a little
    m_Player->attachCameraToOrbit(sm->getCamera("MainCamera"), 200)->setPosition(0, 20, 0);

    // load world
    m_World = std::unique_ptr<Entity>(
        new Entity(sm, "World", "prototype-test-map.mesh")
    );
    m_World->getEntitySceneNode()->setScale(200, 200, 200);
    m_World->getEntitySceneNode()->setPosition(0, -300, 0);

    // create default light
    Ogre::Light* light = sm->createLight("MainLight");
    light->setPosition(60, 200, 500);

    this->onChangeCameraAngleDelta(0, 0);

    return true;
}

// ----------------------------------------------------------------------------
void App::onRun()
{
    m_OgreRenderer->startRendering();
}

// ----------------------------------------------------------------------------
void App::onExit()
{
    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");

    // remove lights
    sm->destroyLight(sm->getLight("MainLight"));

    // remove player character
    m_Player.reset(nullptr);

    // clean up input
    m_Input->event.removeListener("App");

    // clean up renderer
    m_OgreRenderer->frameEvent.removeListener("App");
}

// ----------------------------------------------------------------------------
bool App::onFrameRenderingQueued(const Ogre::FrameEvent& evt)
{
    m_Input->capture();

    if(m_Shutdown)
        return false;

    return true;
}

// ----------------------------------------------------------------------------
void App::onButtonExit()
{
    m_Shutdown = true;
}

} // namespace OpenRump
