// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <iostream>

#include <openrump/OgreRenderer.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App() :
    m_Renderer(0)
{
    m_Renderer = new OgreRenderer();
}

// ----------------------------------------------------------------------------
App::~App()
{
    if(m_Renderer)
        delete m_Renderer;
}

// ----------------------------------------------------------------------------
bool App::onLoad()
{
    if(!m_Renderer->initialise())
        return false;
    m_Renderer->addFrameListener(this);
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
    m_Renderer->removeFrameListener(this);
}

// ----------------------------------------------------------------------------
bool App::onFrameEvent(float timeSinceLastUpdate)
{
    return true;
}

} // namespace OpenRump
