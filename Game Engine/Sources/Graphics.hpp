#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Module.hpp"
#include <string>
#include "LoggerComponenet.hpp"
#include "RendererComponent_SDL.hpp"

namespace Pringine
{
    class Graphics
    {
    private:
        
        SDL_Texture** graphics_frames;  //we want to be able to store multiple animation frames
        void load_graphics(std::string graphics_file, int num_of_frames = 1);
        int current_frame_index;
        int number_of_frames;
    public:
        Graphics();
        ~Graphics();
        SDL_Texture* get_current_frame();
        SDL_Texture* get_frame_at(int index);

    };
    

    
} // namespace Pringine
#endif