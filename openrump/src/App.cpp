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
void App::onLoad()
{
    m_Renderer->initialise();
}

// ----------------------------------------------------------------------------
void App::onRun()
{

}

// ----------------------------------------------------------------------------
void App::onExit()
{

}

// ----------------------------------------------------------------------------
bool App::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

}

// ----------------------------------------------------------------------------
bool App::keyPressed(const OIS::KeyEvent& evt)
{

    // return true so buffer isn't cleared
    return true;
}

// ----------------------------------------------------------------------------
bool App::keyReleased(const OIS::KeyEvent& evt)
{

    // return true so buffer isn't cleared
    return true;
}

} // namespace OpenRump
