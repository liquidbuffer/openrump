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
                    // escape key
                    case SDLK_ESCAPE:
                        on_exit();
                        break;
                        
                    // WASD directional input state changes
                    case SDLK_w:
                        m_MoveAxisState.up = 1000;
                        break;
                    case SDLK_s:
                        m_MoveAxisState.down = 1000;
                        break;
                    case SDLK_a:
                        m_MoveAxisState.left = 1000;
                        break;
                    case SDLK_d:
                        m_MoveAxisState.right = 1000;
                        break;
                        
                    default:
                        break;
                }
                break;
            
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    // WASD directional input state changes
                    case SDLK_w:
                        m_MoveAxisState.up = 0;
                        break;
                    case SDLK_s:
                        m_MoveAxisState.down = 0;
                        break;
                    case SDLK_a:
                        m_MoveAxisState.left = 0;
                        break;
                    case SDLK_d:
                        m_MoveAxisState.right = 0;
                        break;
                        
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