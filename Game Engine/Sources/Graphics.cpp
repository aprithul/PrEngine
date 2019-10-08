#include "Graphics.hpp"
namespace Pringine
{
    Graphics::Graphics()
    {
        current_frame_index = -1;
    }

    Graphics::~Graphics()
    {
    }

    void Graphics::load_graphics(std::string graphics_file, int num_of_frames)
    {
        // load all animation frames
        this->graphics_frames = new SDL_Texture*[num_of_frames];
        for(int _i=0; _i<num_of_frames; _i++)
        {
            this->graphics_frames[_i] = Pringine::load_texture(graphics_file, Pringine::get_current_renderer());
        }

        this->current_frame_index = 0;
        this->number_of_frames = number_of_frames;

    }

    SDL_Texture* Graphics::get_current_frame()
    {
        return this->graphics_frames[this->current_frame_index];
    }

    SDL_Texture* Graphics::get_frame_at(int index)
    {
        if(index>=number_of_frames)
            log_to(LOGTYPE_ERROR, "index is greater than frame count");
        return this->graphics_frames[index];
    }


}