// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/Game.hpp>

#include <iostream>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App(std::string workingDirectory) :
    m_WorkingDirectory(workingDirectory),
    m_GameInterface(new Game(workingDirectory))
{
}

// ----------------------------------------------------------------------------
App::~App()
{
}

// ----------------------------------------------------------------------------
void App::onLoad()
{
    m_GameInterface->initialise();
}

// ----------------------------------------------------------------------------
void App::onRun()
{
    m_GameInterface->run();
}

// ----------------------------------------------------------------------------
void App::onExit()
{
    m_GameInterface->cleanUp();
}

} // namespace OpenRump
