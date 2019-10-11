//
//  Display.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//
#include "RendererModule.hpp"

namespace Pringine {

    // globally required functions that are related to renderer but shouldn't require access to the renderer
    SDL_Renderer* current_renderer = NULL;


    SDL_Texture* load_texture(const std::string &file, SDL_Renderer *ren)
    {
        if(ren == nullptr)
        {
            LOG(LOGTYPE_ERROR, std::string("Renderer provided in load_texture is null"));
            return nullptr;
        }

        SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
        if (texture == nullptr){
            LOG(LOGTYPE_ERROR, std::string("Couldn't load texture : ").append(file));
            return nullptr;
        }
        return texture;
    }

    //////////////////////////////////////////////////////////////////////
    
    // publics
    Renderer2D::Renderer2D(int width, int height, std::string title, bool vsync,std::string name, int priority):Module(name,priority)
    {
        // initialize SDL video
        SDL_Init(SDL_INIT_VIDEO);
        
        this->width = width;
        this->height = height;
        this->title = title;
        
        // create window and sdl_renderer
        set_vsync(vsync);
        sdl_window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height,  SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
        sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        current_renderer = sdl_renderer;
        set_clear_color(255,0,0,255);
    }

    void Renderer2D::set_clear_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(sdl_renderer, r,g,b,a);
    }
    
    Renderer2D::~Renderer2D()
    {
        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }
    
    void Renderer2D::start()
    {
        
    }
    
    void Renderer2D::update()
    {
        if(is_active)
        {
            SDL_RenderClear(sdl_renderer);
            draw();
            SDL_RenderPresent(sdl_renderer);
        }
    }

    void Renderer2D::end()
    {
        LOG(LOGTYPE_GENERAL, "RendererComponent Ended");
    }

        
    void Renderer2D::set_vsync(bool value)
    {
        if(value == 1)
        {
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"); 
        }
        else
        {
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"); 
        }
    }

    int Renderer2D::add_graphics_to_draw(Graphics* graphics)
    {
        if(graphics!=nullptr)
        {
            int next_pos = -1;
            if(!released_positions.empty())
            {
                next_pos = released_positions.front();
                released_positions.pop();
            }
            else
            {
                if(render_array_head < MAX_RENDERED_GRAPHICS_PER_FRAME)
                {
                    render_array_head++;
                    next_pos = render_array_head;
                }
                else
                {
                    LOG(LOGTYPE_ERROR, "Cant add anymore graphics to draw, array full");
                    return -1;
                }
                
            }

            render_list[next_pos] = graphics;
            return next_pos;
            
        }
        else
        {    
            LOG(LOGTYPE_ERROR, "Cant put null graphics in render_list");
            return -1;
        }

    }

    void Renderer2D::remove_graphics(int id)
    {
        if(id<=render_array_head)
        {   
            Graphics* _graphics = render_list[id];    
            if(_graphics!= nullptr)
            {
                render_list[id] = nullptr;
                released_positions.push(id);
            }
            else
            {
                LOG(LOGTYPE_WARNING, std::string("No graphics object with id: ").append(std::to_string(id)).append(" exists"));
            }
        }
        else
        {
            LOG(LOGTYPE_WARNING, std::string("Requested graphics object id: ").append(std::to_string(id)).append(" is out of id range"));
        }
    }


    // private    
    void Renderer2D::draw()
    {

        for(int _i=0; _i<=render_array_head; _i++)
        {
            Graphics* _graphics = render_list[_i];
            if(_graphics != nullptr)
            {
                SDL_RenderCopyEx(this->sdl_renderer, _graphics->get_current_frame() , &(_graphics->dimension), 
                                        NULL, _graphics->angle, NULL, SDL_FLIP_NONE) ;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////GRAPHICS CLASS DEFINTION///////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Graphics::Graphics()
    {
        this->current_frame_index = -1;
    }

    Graphics::~Graphics()
    {
        if(graphics_frames != nullptr)
        {
            for(int _i=0; _i < number_of_frames; _i++)
            {
                if(graphics_frames[_i] != nullptr)
                    SDL_DestroyTexture(graphics_frames[_i]);
            }
            delete[] graphics_frames;
        }
    }

    void Graphics::load_graphics(std::string graphics_file, const Renderer2D& renderer2d, int num_of_frames)
    {
        // load all animation frames
        this->number_of_frames = num_of_frames;
        graphics_frames = new SDL_Texture*[num_of_frames];
        for(int _i=0; _i<num_of_frames; _i++)
        {
            graphics_frames[_i] = Pringine::load_texture(graphics_file, renderer2d.sdl_renderer);
        }

        if(graphics_frames[0] == nullptr)
        {
            return;
        }
        else
        {
            SDL_QueryTexture(graphics_frames[0],NULL,NULL, &dimension.w, &dimension.h);
            current_frame_index = 0;
        }


    }

    SDL_Texture* Graphics::get_current_frame()
    {
        return this->graphics_frames[this->current_frame_index];
    }

    SDL_Texture* Graphics::get_frame_at(int index)
    {
        if(index>=number_of_frames)
            LOG(LOGTYPE_ERROR, "index is greater than frame count");
        return this->graphics_frames[index];
    }



    
}
