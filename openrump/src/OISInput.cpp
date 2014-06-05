// ----------------------------------------------------------------------------
// OISInput.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/OISInput.hpp>
#include <openrump/ListenerDispatcher.hxx>

#include <OIS/OISInputManager.h>

#include <sstream>
#include <cmath>
#ifdef _DEBUG
#   include <iostream>
#endif // _DEBUG

namespace OpenRump {

// ----------------------------------------------------------------------------
OISInput::OISInput() :
    m_InputSystem(nullptr),
    m_Keyboard(nullptr),
    m_Mouse(nullptr)
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

    event.removeAllListeners();

    if(m_Keyboard)
    {
        m_InputSystem->destroyInputObject(m_Keyboard);
        m_Keyboard = nullptr;
    }

    if(m_Mouse)
    {
        m_InputSystem->destroyInputObject(m_Mouse);
        m_Mouse = nullptr;
    }

    if(m_Joysticks.size() > 0)
    {
        for(std::vector<OIS::JoyStick*>::iterator it = m_Joysticks.begin(); it != m_Joysticks.end(); ++it)
            m_InputSystem->destroyInputObject(*it);
        m_Joysticks.clear();
    }

    OIS::InputManager::destroyInputSystem(m_InputSystem);
    m_InputSystem = nullptr;
}

// ----------------------------------------------------------------------------
void OISInput::capture()
{
    if(m_Keyboard)
        m_Keyboard->capture();
    if(m_Mouse)
        m_Mouse->capture();
    for(auto it : m_Joysticks)
        it->capture();
}

// ----------------------------------------------------------------------------
bool OISInput::keyPressed(const OIS::KeyEvent& evt)
{
    // exit with escape key
    if(evt.key == OIS::KC_ESCAPE)
        event.dispatch(&InputListener::onButtonExit);

    // process WASD
    bool directionChanged = false;
    if(evt.key == OIS::KC_W)
    {
        m_PlayerMoveUpDown = -1000;
        directionChanged = true;
    }
    if(evt.key == OIS::KC_S)
    {
        m_PlayerMoveUpDown = 1000;
        directionChanged = true;
    }
    if(evt.key == OIS::KC_A)
    {
        m_PlayerMoveLeftRight = -1000;
        directionChanged = true;
    }
    if(evt.key == OIS::KC_D)
    {
        m_PlayerMoveLeftRight = 1000;
        directionChanged = true;
    }
    if(directionChanged)
        this->dispatchNewDirection();

    return true; // Don't clear input buffer
}

// ----------------------------------------------------------------------------

bool OISInput::keyReleased(const OIS::KeyEvent& evt)
{
    // process WASD
    bool directionChanged = false;
    if(evt.key == OIS::KC_W || evt.key == OIS::KC_S)
    {
        m_PlayerMoveUpDown = 0;
        directionChanged = true;
    }
    if(evt.key == OIS::KC_A || evt.key == OIS::KC_D)
    {
        m_PlayerMoveLeftRight = 0;
        directionChanged = true;
    }
    if(directionChanged)
        this->dispatchNewDirection();

    return true; // Don't clear input buffer
}

// ----------------------------------------------------------------------------
void OISInput::dispatchNewDirection()
{
    if(m_PlayerMoveLeftRight == 0 && m_PlayerMoveUpDown == 0)
    {
        event.dispatch(&InputListener::onChangeDirectionAndVelocity, 0, 0);
        return;
    }

    // clamp length to 1.0 - don't want player going faster when walking diagonally
    float normaliseX = m_PlayerMoveLeftRight / 1000.0f;
    float normaliseY = m_PlayerMoveUpDown / 1000.0f;
    float length = sqrt(pow(normaliseX, 2) + pow(normaliseY, 2));
    if(length > 1.0f)
    {
        normaliseX /= length;
        normaliseY /= length;
    }
    event.dispatch(&InputListener::onChangeDirectionAndVelocity, normaliseX, normaliseY);
}

// ----------------------------------------------------------------------------
bool OISInput::mouseMoved(const OIS::MouseEvent& evt)
{
    event.dispatch(
            &InputListener::onChangeCameraAngleDelta,
            static_cast<float>(evt.state.Y.rel) * 0.02f,
            static_cast<float>(evt.state.X.rel) * 0.02f
    );
    this->dispatchNewDirection();

    event.dispatch(
        &InputListener::onChangeCameraDistanceDelta,
        static_cast<float>(evt.state.Z.rel) * 0.02f
    );
    return true; // Don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID mbid)
{
    return true; // Don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID mbid)
{
    return true; // Don't clear input buffer
}

// ----------------------------------------------------------------------------
bool OISInput::povMoved( const OIS::JoyStickEvent &evt, int pov )
{
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
