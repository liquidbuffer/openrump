// ----------------------------------------------------------------------------
// RendererListener.hpp
// ----------------------------------------------------------------------------

#ifndef __OPENUMP_RENDERER_LISTENER_HPP__
#define __OPENUMP_RENDERER_LISTENER_HPP__

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

namespace OpenRump {

class OPENRUMP_API RendererListener
{
public:

    /*!
     * @brief Called when it's time to update the game loop
     * @return Return false to signal program shutdown
     */
    virtual bool onFrameEvent(float timeSinceLastUpdate);
};

} // namespace OpenRump

#endif // __OPENUMP_RENDERER_LISTENER_HPP__
