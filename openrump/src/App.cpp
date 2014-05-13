// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/OISInput.hpp>

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
    m_PlayerEntity(nullptr),
    m_PlayerNode(nullptr),
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

    // load player character
    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");
    m_PlayerNode = sm->getRootSceneNode()->createChildSceneNode("PlayerRootNode");
    m_PlayerEntity = sm->createEntity("Player", "twilightsparkle/twilightsparkle.mesh");
    m_PlayerNode->attachObject(m_PlayerEntity);

    // set up camera to orbit player
    m_CameraRotateNode = m_PlayerNode->createChildSceneNode("PlayerCameraRotateNode");
    m_CameraNode = m_CameraRotateNode->createChildSceneNode("PlayerCameraNode");
    m_CameraNode->attachObject(sm->getCamera("MainCamera"));
    m_CameraNode->setPosition(0, 0, m_CameraDistance);
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

    // remove player character
    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");
    Ogre::SceneNode* node = sm->getSceneNode("PlayerRootNode");
    Ogre::Entity* entity = sm->getEntity("Player");
    node->detachObject(entity);
    sm->destroyEntity(entity);
    sm->destroySceneNode(node);

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

}

// ----------------------------------------------------------------------------
void App::onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY)
{

    // add deltas and limit X angle to +90° and -90°
    m_CameraAngleX += deltaAngleX;
    m_CameraAngleY += deltaAngleY;
    if(m_CameraAngleX < -Ogre::Math::PI*0.5f)
        m_CameraAngleX = -Ogre::Math::PI*0.5f;
    if(m_CameraAngleX > Ogre::Math::PI*0.5f)
        m_CameraAngleX = Ogre::Math::PI*0.5f;

    // apply to camera
    m_CameraRotateNode->setOrientation(Ogre::Quaternion());
    m_CameraRotateNode->yaw(Ogre::Radian(m_CameraAngleY));
    m_CameraRotateNode->pitch(Ogre::Radian(m_CameraAngleX));
}

// ----------------------------------------------------------------------------
void App::onChangeCameraDistanceDelta(float deltaDistance)
{

}

} // namespace OpenRump
