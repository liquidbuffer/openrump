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

    virtual ~RendererFrameListener();

    /*!
     * @brief Called when it's time to update the game loop
     * @return Return false to signal program shutdown
     */
    virtual bool onFrameRenderingQueued(const Ogre::FrameEvent&) = 0;
};

} // namespace OpenRump

#endif // __OPENUMP_RENDERER_FRAME_LISTENER_HPP__
