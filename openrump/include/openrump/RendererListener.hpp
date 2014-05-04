// ----------------------------------------------------------------------------
// RendererListener.hpp
// ----------------------------------------------------------------------------

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
