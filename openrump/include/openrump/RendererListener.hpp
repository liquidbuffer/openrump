// ----------------------------------------------------------------------------
// RendererListener.hpp
// ----------------------------------------------------------------------------

#ifndef __OPENUMP_RENDERER_LISTENER_HPP__
#define __OPENUMP_RENDERER_LISTENER_HPP__

namespace OpenRump {

class RendererListener
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
