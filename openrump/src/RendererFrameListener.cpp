// ----------------------------------------------------------------------------
// RendererFrameListener.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/RendererFrameListener.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
RendererFrameListener::~RendererFrameListener()
{
}

// ----------------------------------------------------------------------------
bool RendererFrameListener::onUpdateRenderLoop(const float timeSinceLastUpdate)
{
    return true;
}

// ----------------------------------------------------------------------------
bool RendererFrameListener::onUpdateGameLoop(const float timeStep)
{
    return true;
}

} // namespace OpenRump
