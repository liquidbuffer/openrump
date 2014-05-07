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
    return frameEvent.dispatchAndFindFalse(&RendererListener::onFrameEvent, timeSinceLastUpdate);
}

} // namespace OpenRump
