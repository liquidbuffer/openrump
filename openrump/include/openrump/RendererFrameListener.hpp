// ----------------------------------------------------------------------------
// RendererFrameListener.hpp
// ----------------------------------------------------------------------------

#ifndef __OPENUMP_RENDERER_FRAME_LISTENER_HPP__
#define __OPENUMP_RENDERER_FRAME_LISTENER_HPP__

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace Ogre {
    struct FrameEvent;
}

namespace OpenRump {

class OPENRUMP_API RendererFrameListener
{
public:

    /*!
     * @brief Allow destruction through base class pointer
     */
    virtual ~RendererFrameListener();

    /*!
     * @brief Called right before the render loop is to be updated.
     * @return Return false to signal program shutdown.
     */
    virtual bool onPreUpdateRenderLoop(const float timeSinceLastUpdate);

    /*!
     * @brief Called when it's time to update the render loop.
     * @return Return false to signal program shutdown.
     */
    virtual bool onUpdateRenderLoop(const float timeSinceLastUpdate);

    /*!
     * @brief Called when it's time to update the game loop.
     * @return Return false to signal program shutdown.
     */
    virtual bool onUpdateGameLoop(const float timeStep);
};

} // namespace OpenRump

#endif // __OPENUMP_RENDERER_FRAME_LISTENER_HPP__
