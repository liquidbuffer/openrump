// ----------------------------------------------------------------------------
// SDLInput.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "openrump/systems/SDLInput.hpp"

#include "SDL.h"
#include <boost/graph/graph_concepts.hpp>

namespace OpenRump {
    
// ----------------------------------------------------------------------------
void SDLInput::initialise()
{
}

// ----------------------------------------------------------------------------
void SDLInput::processEntity(Ontology::Entity&)
{
}

// ----------------------------------------------------------------------------
void SDLInput::attachToWindow(std::size_t windowHnd)
{
}

// ----------------------------------------------------------------------------
void SDLInput::detachFromWindow()
{
}

// ----------------------------------------------------------------------------
void SDLInput::setWindowExtents(unsigned int width, unsigned int height)
{
}

// ----------------------------------------------------------------------------
void SDLInput::capture()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                on_exit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        on_exit();
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

} // namespace OpenRump