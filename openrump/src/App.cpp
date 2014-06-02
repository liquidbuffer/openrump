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
            new EntityPlayer(sm, "TwilightSparkle", "twilightsparkle.mesh")
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

// ----------------------------------------------------------------------------
void App::onChangeDirectionAndVelocity(float x, float y)
{

    // rotate vector by camera angle to get real world direction
    float cs = Ogre::Math::Cos(Ogre::Radian(m_CameraAngleY));
    float sn = Ogre::Math::Sin(Ogre::Radian(m_CameraAngleY));
    Ogre::Vector2 targetPlayerDirection(
            x*cs - y*sn,
            x*sn + y*cs
    );

    //
}

// ----------------------------------------------------------------------------
void App::onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY)
{

    // add deltas and limit X angle to +90° and -90°
    m_CameraAngleX -= deltaAngleX;
    m_CameraAngleY -= deltaAngleY;
    if(m_CameraAngleX < -Ogre::Math::PI*0.5f)
        m_CameraAngleX = -Ogre::Math::PI*0.5f;
    if(m_CameraAngleX > Ogre::Math::PI*0.5f)
        m_CameraAngleX = Ogre::Math::PI*0.5f;

    // apply to camera
    m_Player->getCameraRotateNode()->setOrientation(Ogre::Quaternion());
    m_Player->getCameraRotateNode()->yaw(Ogre::Radian(m_CameraAngleY));
    m_Player->getCameraRotateNode()->pitch(Ogre::Radian(m_CameraAngleX));
}

// ----------------------------------------------------------------------------
void App::onChangeCameraDistanceDelta(float deltaDistance)
{

}

} // namespace OpenRump
