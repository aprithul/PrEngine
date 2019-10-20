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
    std::map<std::string, SDL_Texture*> loaded_texture_library;

    SDL_Texture* load_texture(const std::string &file_name, SDL_Renderer *ren)
    {
        if(loaded_texture_library.count(file_name) == 0)
        {
            if(ren == nullptr)
            {
                LOG(LOGTYPE_ERROR, std::string("Renderer provided in load_texture is null"));
                return nullptr;
            }

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
            SDL_Texture *texture = IMG_LoadTexture(ren, file_name.c_str());
            if (texture == nullptr){
                LOG(LOGTYPE_ERROR, std::string("Couldn't load texture : ").append(file_name));
                return nullptr;
            }
            
            loaded_texture_library[file_name] = texture;
            return texture;
        }
        else
            return loaded_texture_library[file_name];
    }

    //////////////////////////////////////////////////////////////////////
    
    // publics

    void insertionSort(Graphics** arr, int n)  
    {  
        int i, j;  
        //LOG(LOGTYPE_GENERAL, std::to_string(n));
        Graphics* key;
        for (i = 2; i <= n; i++) 
        {  
            key = arr[i];  
            j = i - 1;  
    
            /* Move elements of arr[0..i-1], that are  
            greater than key, to one position ahead  
            of their current position */
            while (j >= 1 && arr[j]->layer > key->layer) 
            {  
                arr[j + 1] = arr[j];  
                j = j - 1;  
            }  
            arr[j + 1] = key;  
        }  

    } 


    Renderer2D::Renderer2D(int width, int height, std::string title, bool vsync, int world_unit_to_pixels, std::string name, int priority):Module(name,priority)
    {
        // initialize SDL video
        SDL_Init(SDL_INIT_VIDEO);
        
        this->window_width = width;
        this->window_height = height;
        this->title = title;
        this->zoom_amount = 1.0f;
        this->view_position.x = 0.0f;
        this->view_position.y = 0.0f;
        this->world_unit_to_pixels = world_unit_to_pixels;
        this->clear_color={255,255,255,255};
        this->do_draw_debug_shapes = true;
        // create window and sdl_renderer
        set_vsync(vsync);
        SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
        sdl_window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->window_width, this->window_height,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        render_texture = SDL_CreateTexture( sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->window_width, this->window_height );
    }

    void Renderer2D::set_draw_color(SDL_Color color)
    {
        SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    }
    
    Renderer2D::~Renderer2D()
    {
        std::map<std::string, SDL_Texture*>::iterator ptr;
        for (ptr = loaded_texture_library.begin(); ptr != loaded_texture_library.end(); ptr++) 
        {
            if(ptr->second!=nullptr)
                SDL_DestroyTexture( ptr->second);
            else
            {
                LOG(LOGTYPE_WARNING, "Renderer found texture to be null while cleaning up");
            }
            
        }

        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }
    
    void Renderer2D::start()
    {
        
    }
    
    void Renderer2D::update()
    {
        //if( Pringine::engine->input_handler->get_key_down(SDLK_d))
        //    do_draw_debug_shapes = !do_draw_debug_shapes;

        if(is_active)
        {
            //set render target to texture 
            //SDL_SetRenderTarget(sdl_renderer, render_texture);
            set_draw_color(clear_color);
            SDL_RenderClear(sdl_renderer);
            draw();
            if(do_draw_debug_shapes)
                draw_debug();
            SDL_RenderPresent(sdl_renderer);

            //reset back to render to screen
            //SDL_SetRenderTarget(sdl_renderer, NULL);
            //copy over the render texture to screen
            // before that resize the texture to apply any screen effect ( zoom / rotation)
            int src_w = this->window_width;// * 1/zoom_amount;
            int src_h = this->window_height;// * 1/zoom_amount;
            SDL_Rect src_rct;
            src_rct.x = (this->window_width - src_w)/2;
            src_rct.y = (this->window_height - src_h)/2;
            src_rct.w = src_w;
            src_rct.h = src_h;
            SDL_RenderCopy(sdl_renderer, render_texture, &src_rct, NULL);
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
            
            insertionSort(render_list, render_array_head);
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

    void Renderer2D::draw_rectangle(Rect rect, SDL_Color color, bool screen_space)
    {
        static SDL_Rect sdl_rect;
        if(!screen_space)
        {
            sdl_rect.x = ((rect.x - view_position.x) - rect.w/2.0f)*world_unit_to_pixels*zoom_amount + window_width/2.0f;
            sdl_rect.y = (-(rect.y - view_position.y) - rect.h/2.0f)*world_unit_to_pixels*zoom_amount + window_height/2.0f;
            sdl_rect.w = rect.w * world_unit_to_pixels*zoom_amount;
            sdl_rect.h = rect.h * world_unit_to_pixels*zoom_amount;
        }

        debug_shapes_rect.emplace( std::make_pair(color, sdl_rect));
        //SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color. b, color.a);
        //SDL_RenderDrawRect( sdl_renderer , &sdl_rect);
    }

    void Renderer2D::draw_line(Vector2<float> p1, Vector2<float>p2, SDL_Color color, bool screen_space)
    {
        if(!screen_space)
        {
            p1.x *= world_unit_to_pixels*zoom_amount;
            p1.y *= world_unit_to_pixels*zoom_amount;
            p2.x *= world_unit_to_pixels*zoom_amount;
            p2.y *= world_unit_to_pixels*zoom_amount;
        }

        //debug_shapes_line.emplace(color, p1,p2 );

    }

    // private    
    void Renderer2D::draw()
    {

        for(int _i=0; _i<=render_array_head; _i++)
        {
            Graphics* _graphics = render_list[_i];
            if(_graphics != nullptr)
            {
                // dst_dimension has world unit values, convert to screen space
                // also make drawing relative to camera position
                // also make center of screen 0,0
                _graphics->dst_dimension.w *= (world_unit_to_pixels * zoom_amount);
                _graphics->dst_dimension.h *= (world_unit_to_pixels * zoom_amount);
                
                _graphics->dst_dimension.x = (((_graphics->dst_dimension.x - view_position.x)*world_unit_to_pixels*zoom_amount) - (_graphics->dst_dimension.w/2) + window_width/2);
                _graphics->dst_dimension.y = ((-(_graphics->dst_dimension.y - view_position.y)*world_unit_to_pixels*zoom_amount) - (_graphics->dst_dimension.h/2) + window_height/2);

                SDL_RenderCopyEx(this->sdl_renderer, _graphics->get_current_frame()->texture , &(_graphics->get_current_frame()->region), 
                                        &_graphics->dst_dimension, _graphics->angle, NULL, SDL_FLIP_NONE) ;
            }
        }
    }

    void Renderer2D::draw_debug()
    {
        while(!debug_shapes_rect.empty())
        {
            SDL_Color &c = debug_shapes_rect.front().first;
            SDL_Rect &rect = debug_shapes_rect.front().second; 
            set_draw_color(c);
            SDL_RenderDrawRect( sdl_renderer , &rect);
            debug_shapes_rect.pop();
        }

        while(!debug_shapes_line.empty())
        {
            SDL_Color &c = debug_shapes_line.front().first;
            std::pair<Vector2<float>, Vector2<float>> &line = debug_shapes_line.front().second; 
            set_draw_color(c);
            SDL_RenderDrawLineF(sdl_renderer, line.first.x, line.first.y, line.second.x, line.second.y);
            debug_shapes_line.pop();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////GRAPHICS CLASS DEFINTION///////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Graphics::Graphics()
    {
        this->current_frame_index = -1;
        this->angle = 0;
    }

    Graphics::~Graphics()
    {
        if(graphics_frames != nullptr)
        {
            /*for(int _i=0; _i < number_of_frames; _i++)
            {
                if(graphics_frames[_i].texture != nullptr)
                    SDL_DestroyTexture(graphics_frames[_i].texture);
            }*/
            //LOG(LOGTYPE_GENERAL,"Deleted: ");
            delete[] graphics_frames;
        }
    }
    
    void Graphics::load_graphics(std::string graphics_file, TextureSlicingParameters slicing_params, const Renderer2D& renderer2d, int num_of_frames)
    {
        // load all animation frames
        this->number_of_frames = num_of_frames;
        graphics_frames = new GraphicsFrame[num_of_frames];
        SDL_Texture* texture = Pringine::load_texture(graphics_file, renderer2d.sdl_renderer);
        if(texture != nullptr)
        {
            int w = 0;
            int h = 0;
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);
            //LOG(LOGTYPE_GENERAL, std::to_string(w).append("  ").append(std::to_string(h)));

            int columns = w/(slicing_params.w+slicing_params.x_pad);
            int rows = h/(slicing_params.h+slicing_params.y_pad);
            int frame_no = 0;


            for(int _i= slicing_params.x + slicing_params.x_pad; _i<w; _i += (slicing_params.w+slicing_params.x_pad))
            {
                for(int _j = slicing_params.y + slicing_params.y_pad; _j<h; _j += (slicing_params.h+slicing_params.y_pad))
                {
                    if(frame_no<this->number_of_frames)
                    {
                        GraphicsFrame* frame = &graphics_frames[frame_no];
                        frame->texture = texture;
                        frame->region.x = _i;
                        frame->region.y = _j;
                        
                        if(_i+slicing_params.w > w)
                            frame->region.w = slicing_params.w - (_i+slicing_params.w-w);
                        else
                            frame->region.w = slicing_params.w;

                        if(_j+slicing_params.h > h)
                            frame->region.h = slicing_params.h - (_j+slicing_params.h-h);
                        else
                            frame->region.h = slicing_params.h;

                        frame_no++;
                    }
                }
            }
            current_frame_index = 0;
        }
    }

    GraphicsFrame* Graphics::get_current_frame()
    {
        return &this->graphics_frames[this->current_frame_index];
    }

    GraphicsFrame* Graphics::get_frame_at(int index)
    {
        if(index>=number_of_frames)
            LOG(LOGTYPE_ERROR, "index is greater than frame count");
        return &this->graphics_frames[index];
    }  
}