// ----------------------------------------------------------------------------
// OISInput.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/OISInput.hpp>
#include <openrump/ListenerDispatcher.hxx>

#include <OIS/OISInputManager.h>

#include <sstream>
#ifdef _DEBUG
#   include <iostream>
#endif // _DEBUG

namespace OpenRump {

// ----------------------------------------------------------------------------
OISInput::OISInput() :
    m_InputSystem(0),
    m_Keyboard(0),
    m_Mouse(0)
{
}

// ----------------------------------------------------------------------------
OISInput::~OISInput()
{
    this->detachFromWindow();
}

// ----------------------------------------------------------------------------
void OISInput::attachToWindow(std::size_t windowHnd)
{
    if(m_InputSystem)
        this->detachFromWindow();

    // create an input system
    OIS::ParamList pl;
    std::ostringstream hwndstr;
    hwndstr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), hwndstr.str()));
    m_InputSystem = OIS::InputManager::createInputSystem(pl);

    // If possible create a buffered keyboard
    if (m_InputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0)
    {
        m_Keyboard = static_cast<OIS::Keyboard*>(m_InputSystem->createInputObject(OIS::OISKeyboard, true));
        m_Keyboard->setEventCallback(this);
#ifdef _DEBUG
        std::cout << "[OISInput::attachToWindow] Info: Detected keyboard" << std::endl;
#endif // _DEBUG
    }

    // If possible create a buffered mouse
    if (m_InputSystem->getNumberOfDevices(OIS::OISMouse) > 0)
    {
        m_Mouse = static_cast<OIS::Mouse*>(m_InputSystem->createInputObject(OIS::OISMouse, true));
        m_Mouse->setEventCallback(this);
#ifdef _DEBUG
        std::cout << "[OISInput::attachToWindow] Info: Detected mouse" << std::endl;
#endif // _DEBUG
    }

    // If possible create all joysticks in buffered mode
    if(m_InputSystem->getNumberOfDevices(OIS::OISJoyStick) > 0)
    {
        unsigned int count = m_InputSystem->getNumberOfDevices(OIS::OISJoyStick);
        for(unsigned int n = 0; n != count; ++n)
        {
            OIS::JoyStick* newJoy = static_cast<OIS::JoyStick*>(m_InputSystem->createInputObject(OIS::OISJoyStick, true));
            newJoy->setEventCallback(this);
            m_Joysticks.push_back(newJoy);
        }
#ifdef _DEBUG
        std::cout << "[OISInput::attachToWindow] Info: Detected " << count << " joysticks" << std::endl;
#endif // _DEBUG
    }

}

// ----------------------------------------------------------------------------
void OISInput::setWindowExtents(unsigned int width, unsigned int height)
{
    const OIS::MouseState& mouseState = m_Mouse->getMouseState();
    mouseState.width = width;
    mouseState.height = height;
}

// ----------------------------------------------------------------------------
void OISInput::detachFromWindow()
{
    if(!m_InputSystem)
        return;

    keyEvent.removeAllListeners();
    if(m_Keyboard)
    {
        m_InputSystem->destroyInputObject(m_Keyboard);
        m_Keyboard = 0;
    }

    mouseEvent.removeAllListeners();
    if(m_Mouse)
    {
        m_InputSystem->destroyInputObject(m_Mouse);
        m_Mouse = 0;
    }

    if(m_Joysticks.size() > 0)
    {
        for(std::vector<OIS::JoyStick*>::iterator it = m_Joysticks.begin(); it != m_Joysticks.end(); ++it)
            m_InputSystem->destroyInputObject(*it);
        m_Joysticks.clear();
    }

    OIS::InputManager::destroyInputSystem(m_InputSystem);
    m_InputSystem = 0;
}

// ----------------------------------------------------------------------------
void OISInput::capture()
{
    if(m_Keyboard)
        m_Keyboard->capture();
    if(m_Mouse)
        m_Mouse->capture();
    for(std::vector<OIS::JoyStick*>::iterator it = m_Joysticks.begin(); it != m_Joysticks.end(); ++it)
        (*it)->capture();
}

// ----------------------------------------------------------------------------
bool OISInput::keyPressed(const OIS::KeyEvent& evt)
{
    return keyEvent.dispatchAndFindFalse<const OIS::KeyEvent&>(&OIS::KeyListener::keyPressed, evt);
}

// ----------------------------------------------------------------------------

bool OISInput::keyReleased(const OIS::KeyEvent& evt)
{
    return keyEvent.dispatchAndFindFalse<const OIS::KeyEvent&>(&OIS::KeyListener::keyReleased, evt);
}

// ----------------------------------------------------------------------------
bool OISInput::mouseMoved(const OIS::MouseEvent& evt)
{
    return mouseEvent.dispatchAndFindFalse<const OIS::MouseEvent&>(&OIS::MouseListener::mouseMoved, evt);
}

// ----------------------------------------------------------------------------
bool OISInput::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID mbid)
{
    return mouseEvent.dispatchAndFindFalse<const OIS::MouseEvent&>(&OIS::MouseListener::mousePressed, evt, mbid);
}

// ----------------------------------------------------------------------------
bool OISInput::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID mbid)
{
    return mouseEvent.dispatchAndFindFalse<const OIS::MouseEvent&>(&OIS::MouseListener::mouseReleased, evt, mbid);
}

// ----------------------------------------------------------------------------
bool OISInput::povMoved( const OIS::JoyStickEvent &evt, int pov )
{
    // TODO joystick dispatch is broken - fix!
    return true; // True means: don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::axisMoved( const OIS::JoyStickEvent &evt, int axis )
{
    return true; // True means: don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::sliderMoved( const OIS::JoyStickEvent &evt, int sliderID )
{
    return true; // True means: don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::buttonPressed( const OIS::JoyStickEvent &evt, int button )
{
    return true; // True means: don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::buttonReleased( const OIS::JoyStickEvent &evt, int button )
{
    return true; // True means: don't clear input buffer
}

}  // namespace OpenRump
