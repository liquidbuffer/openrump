// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/OISInput.hpp>

#include <OIS/OISInputManager.h>

#include <OgreRoot.h>

#include <iostream>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App() :
    m_OgreRenderer(new OgreRenderer()),
    m_Input(new OISInput()),
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
    m_Input->event.removeListener("App");
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

}

// ----------------------------------------------------------------------------
void App::onChangeCameraDistanceDelta(float deltaDistance)
{

}

} // namespace OpenRump
