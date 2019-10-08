//
//  Display.h
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef RENDERCOMPONENET_HPP
#define RENDERCOMPONENET_HPP

#include "Component.hpp"
#include "TimeComponent.hpp"
#include "LoggerComponenet.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Pringine {
    
    // globally required functions that are related to renderer but shouldn't require access to the renderer
    extern SDL_Renderer* current_renderer;
    extern SDL_Renderer* get_current_renderer();
    extern void set_current_renderer(SDL_Renderer* _renderer);
    extern SDL_Texture* load_texture(const std::string &file, SDL_Renderer *ren); 
    //////////////////////////////////////////////////////////////////////////////////////////////////////


    class RendererComponent_SDL : public Component
    {
    public:

        RendererComponent_SDL(int width, int height, std::string title, bool vsync);
        RendererComponent_SDL();
        ~RendererComponent_SDL();
        
        void set_frame_rate(int frame_rate);
        void set_clear_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void start() override;
        void update() override;
        void end() override;
        
    private:
        
        // display attributes
        int height;
        int width;
        std::string title;

        // draws 'everything' on screen inside renderer update
        void draw();
        void set_vsync(bool value);

        // reference to the sdl window
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        
    };
}


#endif /* Display_h */
