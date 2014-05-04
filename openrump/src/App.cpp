// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>

#include <OIS/OISInputManager.h>

#include <iostream>
#include <sstream>


namespace OpenRump {

// ----------------------------------------------------------------------------
App::App() :
    m_Renderer(0),
    m_Input(0)
{
    m_Renderer = new OgreRenderer();
}

// ----------------------------------------------------------------------------
App::~App()
{

    // destroy renderer
    if(m_Renderer)
        delete m_Renderer;
}

// ----------------------------------------------------------------------------
bool App::onLoad()
{
    // initialise renderer
    if(!m_Renderer->initialise())
        return false;
    m_Renderer->frameEvent.addListener(this, "App");

    // initialise input system
    /*OIS::ParamList pl;
    std::ostringstream hwndstr;
    hwndstr << m_Renderer->getWindowHandle();
    pl.insert(std::make_pair(std::string("WINDOW"), hwndstr.str()));
    m_Input = OIS::InputManager::createInputSystem(pl);*/

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
    return true;
}

} // namespace OpenRump
