// ----------------------------------------------------------------------------
// Renderer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Renderer.hpp>
#include <openrump/RendererListener.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
Renderer::Renderer()
{
}

// ----------------------------------------------------------------------------
Renderer::~Renderer()
{
}

// ----------------------------------------------------------------------------
void Renderer::addFrameListener(RendererListener* listener)
{
    for(std::vector<RendererListener*>::iterator it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
        if(*it == listener)
            return;
    m_ListenerList.push_back(listener);
}

// ----------------------------------------------------------------------------
void Renderer::removeFrameListener(RendererListener* listener)
{
    for(std::vector<RendererListener*>::iterator it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
    {
        if(*it == listener)
        {
            m_ListenerList.erase(it);
            return;
        }
    }
}

// ----------------------------------------------------------------------------
bool Renderer::dispatchFrameEvent(float timeSinceListUpdate)
{
    for(std::vector<RendererListener*>::iterator it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
        if(!(*it)->onFrameEvent(timeSinceListUpdate))
            return false;
    return true;
}

} // namespace OpenRump
