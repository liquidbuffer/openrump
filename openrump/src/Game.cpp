// ----------------------------------------------------------------------------
// Game.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/OISInput.hpp>
#include <openrump/OgreRenderer.hpp>

#include <openrump/EntityPlayer.hpp>

#include <OgreRoot.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
Game::Game() :
    m_OgreRenderer(new OgreRenderer),
    m_Input(new OISInput),
    m_Shutdown(false),
    m_IsInitialised(false)
{
    this->initialise();
}

// ----------------------------------------------------------------------------
Game::~Game()
{
    this->cleanUp();
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
    if(m_IsInitialised)
        return;

    // initialise renderer
    m_OgreRenderer->initialise();

    // initialise input
    m_Input->attachToWindow(m_OgreRenderer->getWindowHandle());

    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");

    EntityPlayer* entity = new EntityPlayer(m_Input.get(), m_OgreRenderer.get(), sm, "applejack", "Body.mesh");
    entity->attachCameraToOrbit(sm->getCamera("MainCamera"));

    // create default light
    Ogre::Light* light = sm->createLight("MainLight");
    light->setPosition(60, 200, -500);
    sm->createLight("SecondLight")->setPosition(-60, -200, 500);

    // register as listener
    m_Input->event.addListener(this, "Game");
    Ogre::Root::getSingletonPtr()->addFrameListener(this);

    m_IsInitialised = true;
}

// ----------------------------------------------------------------------------
void Game::run()
{
    m_OgreRenderer->startRendering();
}

// ----------------------------------------------------------------------------
void Game::cleanUp()
{
    if(!m_IsInitialised)
        return;

    Ogre::SceneManager* sm = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");

    // remove lights
    sm->destroyLight(sm->getLight("MainLight"));

    // clean up input
    Ogre::Root::getSingletonPtr()->removeFrameListener(this);
    m_Input->event.removeListener(this);

    m_IsInitialised = false;
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
