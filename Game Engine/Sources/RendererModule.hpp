//
//  Display.h
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//


#ifndef RENDERCOMPONENET_HPP
#define RENDERCOMPONENET_HPP

#define MAX_RENDERED_GRAPHICS_PER_FRAME 999999

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <queue>
#include "Module.hpp"
#include "TimeModule.hpp"
#include "Camera.hpp"
#include "Logger.hpp"
#include "Transform.hpp"
#include <map>

namespace Pringine {
    class Graphics;
    
    // globally required functions that are related to renderer but shouldn't require access to the renderer
    extern SDL_Texture* load_texture(const std::string &file, SDL_Renderer *ren); 
    extern std::map<std::string, SDL_Texture*> loaded_texture_library;
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    struct GraphicsFrame
    {
        SDL_Texture* texture;
        SDL_Rect region;
    };

    struct TextureSlicingParameters
    {
        int x;
        int y;
        int w;
        int h;
        int x_pad;
        int y_pad;

        TextureSlicingParameters(int x, int y, int w, int h, int x_pad, int y_pad)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
            this->x_pad = x_pad;
            this->y_pad = y_pad;
        }
        TextureSlicingParameters(int x, int y, int dim, int pad)
        {
            this->x = x;
            this->y = y;
            this->w = dim;
            this->h = dim;
            this->x_pad = pad;
            this->y_pad = pad;
        }

        

    };


    class Renderer2D : public Module
    {
    public:

        // reference to the sdl window
        SDL_Window* sdl_window = NULL;
        SDL_Renderer* sdl_renderer = NULL;
        SDL_Texture* render_texture = NULL;
        // display attributes
        int window_height;
        int window_width;
        int world_unit_to_pixels;
        
        Renderer2D(int width, int height, std::string title, bool vsync, Camera* camera, int world_unit_to_pixels, std::string name, int priority);
        Renderer2D();
        ~Renderer2D();
        
        void set_frame_rate(int frame_rate);
        void set_clear_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        int add_graphics_to_draw(Graphics* graphics);
        void remove_graphics(int id);
        void render_to_render_texture();
        
        void start() override;
        void update() override;
        void end() override;
        
    private:
        
        
        std::string title;
        Camera* camera;
        Graphics* render_list[MAX_RENDERED_GRAPHICS_PER_FRAME];
        std::queue<int> released_positions;
        int render_array_head;

        // draws 'everything' on screen inside renderer update
        void draw();
        void set_vsync(bool value);
        
    };



    class Graphics
    {
    private:
        
        GraphicsFrame* graphics_frames;  //we want to be able to store multiple animation frames
        int current_frame_index;
        int number_of_frames;
        
    public:
        SDL_Rect dst_dimension;
        float angle;
        Graphics();
        ~Graphics();
        GraphicsFrame* get_current_frame();
        GraphicsFrame* get_frame_at(int index);
        void load_graphics(std::string graphics_file, TextureSlicingParameters slicing_params, const Renderer2D& renderer2d, int num_of_frames = 1);
    };
}

#endif /* Display_h */