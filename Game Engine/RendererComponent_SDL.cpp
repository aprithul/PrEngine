//
//  Display.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//
#include "RendererComponent_SDL.hpp"

namespace Pringine {
    
    // publics
    RendererComponent_SDL::RendererComponent_SDL(int width, int height, std::string title, bool vsync)
    {
        // initialize SDL video
        SDL_Init(SDL_INIT_VIDEO);
        
        this->width = width;
        this->height = height;
        this->title = title;
        
        // create window and sdl_renderer
        set_vsync(vsync);
        window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        set_clear_color(255,0,0,255);
    }

    void RendererComponent_SDL::set_clear_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(renderer, r,g,b,a);
    }
    
    RendererComponent_SDL::~RendererComponent_SDL()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    void RendererComponent_SDL::start()
    {
    }
    
    void RendererComponent_SDL::update()
    {
        if(is_active)
        {
            SDL_RenderClear(renderer);
            draw();
            SDL_RenderPresent(renderer);
        }
    }

    void RendererComponent_SDL::end()
    {
        std::cout<<"RendererComponent Ended"<<std::endl;
    }

        
    void RendererComponent_SDL::set_vsync(bool value)
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

    // private    
    void RendererComponent_SDL::draw()
    {

        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
}
