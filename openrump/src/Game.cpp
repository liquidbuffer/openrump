// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/OISInput.hpp>
#include <openrump/OgreRenderer.hpp>

#include <OgreRoot.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Game::Game(std::string workingDirectory) :
    m_OgreRenderer(new OgreRenderer),
    m_Input(new OISInput),
    m_Shutdown(false),
    PyGameInterface(workingDirectory)
{
}

// ----------------------------------------------------------------------------
Game::~Game()
{
}

// ----------------------------------------------------------------------------
void Game::test()
{
    std::cout << "test successful!" << std::endl;
}

// ----------------------------------------------------------------------------
void Game::stop()
{
    m_Shutdown = true;
}

// ----------------------------------------------------------------------------
void Game::initialise()
{

    // initialise renderer
    m_OgreRenderer->initialise();

    // initialise input
    m_Input->attachToWindow(m_OgreRenderer->getWindowHandle());

    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");

    // create default light
    Ogre::Light* light = sm->createLight("MainLight");
    light->setPosition(60, 200, 500);

    // register as listener
    m_Input->event.addListener(this, "Game");
    Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

// ----------------------------------------------------------------------------
void Game::run()
{
    m_OgreRenderer->startRendering();
}

// ----------------------------------------------------------------------------
void Game::cleanUp()
{
    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");

    // remove lights
    sm->destroyLight(sm->getLight("MainLight"));

    // clean up input
    Ogre::Root::getSingletonPtr()->removeFrameListener(this);
    m_Input->event.removeListener(this);
}

// ----------------------------------------------------------------------------
bool Game::frameStarted(const Ogre::FrameEvent&)
{
    // capture input before frame is rendered for maximum responsiveness
    m_Input->capture();

    if(m_Shutdown)
        return false;

    return true;
}

// ----------------------------------------------------------------------------
void Game::onButtonExit()
{
    this->stop();
}

} // namespace OpenRump
