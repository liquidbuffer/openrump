// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/OISInput.hpp>

#include <OIS/OISInputManager.h>

#include <iostream>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App() :
    m_Renderer(new OgreRenderer()),
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
    if(!m_Renderer->initialise())
        return false;
    m_Renderer->frameEvent.addListener(this, "App");

    // initialise input
    m_Input->attachToWindow(m_Renderer->getWindowHandle());
    m_Input->keyEvent.addListener(this, "App");

    m_Renderer->loadObject("twilight sparkle", "twilightsparkle/twilightsparkle.mesh");

    return true;
}

// ----------------------------------------------------------------------------
void App::onRun()
{
    m_Renderer->startRendering();
}

// ----------------------------------------------------------------------------
void App::onExit()
{
}

// ----------------------------------------------------------------------------
bool App::onFrameEvent(float timeSinceLastUpdate)
{
    m_Input->capture();

    if(m_Shutdown)
        return false;

    return true;
}

// ----------------------------------------------------------------------------
bool App::keyPressed(const OIS::KeyEvent& evt)
{
    if(evt.key == OIS::KC_ESCAPE)
        m_Shutdown = true;
    return true;
}

// ----------------------------------------------------------------------------
bool App::keyReleased(const OIS::KeyEvent& evt)
{
    return true;
}

} // namespace OpenRump
