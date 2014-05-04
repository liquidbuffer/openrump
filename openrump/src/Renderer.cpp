// ----------------------------------------------------------------------------
// Renderer.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Renderer.hpp>

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
bool Renderer::dispatchFrameEvent(float timeSinceLastUpdate)
{
    bool ret = true;
    for(Renderer::FrameEvent::iterator it = frameEvent.begin(); it != frameEvent.end(); ++it)
        if(!it->second->onFrameEvent(timeSinceLastUpdate))
            ret = false;
    return ret;
}

} // namespace OpenRump
