#include "Sprite.hpp"

namespace Pringine
{

     Sprite::Sprite(const std::string& graphics_file_name, const TextureSlicingParameters* slicing_param, Renderer2D& _renderer2d, int num_of_animation_frames, int pixel_to_world_scale, int layer):Entity(ENTITY_TYPE_SPRITE),renderer2d(_renderer2d)
    {
        //#if !IS_SERVER
            name = graphics_file_name;
            //LOG(LOGTYPE_GENERAL,"Created sprite");
            graphics.load_graphics(graphics_file_name, slicing_param, _renderer2d, num_of_animation_frames, false) ;
            this->layer = layer;
            graphics.layer = layer;
            do_animate = false;
            this->renderer2d_id = _renderer2d.add_graphics_to_draw(&graphics);
            this->pixel_to_world = pixel_to_world_scale;
            // for sprites we can readiliy assume the diemnsion to be the bound of the sprite
            if(graphics.get_current_frame() != nullptr)
            {
                this->bounding_box.w = graphics.get_current_frame()->region.w / this->pixel_to_world;
                this->bounding_box.h= graphics.get_current_frame()->region.h / this->pixel_to_world;
                
            }
            
            add_componenet(&graphics);
            add_componenet(&transform);

            //LOG(LOGTYPE_GENERAL, std::to_string(graphics.get_current_frame()->region.w));
            //LOG(LOGTYPE_GENERAL, std::to_string(graphics.get_current_frame()->region.h));
        //#endif
    }

    Sprite::~Sprite()
    {
        #if !IS_SERVER
            this->renderer2d.remove_graphics(this->renderer2d_id);
        #endif
    }
    
    void Sprite::awake()
    {


    }

    void Sprite::set_animation(bool do_animate, int fps)
    {
        #if !IS_SERVER
            this->do_animate = do_animate;
            animation_accumulator = 0.0;
            animation_delta = 1.0/fps;
        #endif
    }

    void Sprite::start()
    {

    }

    void Sprite::update()
    {
        #if !IS_SERVER


            if(do_animate)
            {
                animation_accumulator += Time::Frame_time;
                if(animation_accumulator > animation_delta)
                {
                    graphics.current_frame_index = (graphics.current_frame_index+1)%graphics.number_of_frames;
                    animation_accumulator -= animation_delta;
                }
            }

            world_space_bounds.x = transform.position.x;
            world_space_bounds.y = transform.position.y;
            world_space_bounds.w = bounding_box.w * transform.scale.x;
            world_space_bounds.h = bounding_box.h * transform.scale.y;

            graphics.dst_dimension = renderer2d.get_world_to_screen_rect(world_space_bounds);
            graphics.angle = transform.angle;

            //convert world space position of sprite to camera space
            //graphics.dst_dimension.x = transform.position.x;//  (int)transform.position.x - (graphics.dst_dimension.w/2);
            //graphics.dst_dimension.y = transform.position.y;// (int)transform.position.y - (graphics.dst_dimension.h/2);

            //graphics.dst_dimension.w = bounding_box.w * transform.scale.x;
            //graphics.dst_dimension.h = bounding_box.h * transform.scale.y;
            //world_space_bounds = graphics.dst_dimension;

            

            SDL_FRect bounds{transform.position.x, transform.position.y, bounding_box.w, bounding_box.h};
            SDL_Color color;
            color.r = 255;
            color.g = 122;
            color.b = 10;
            color.a = 255;
            //renderer2d.draw_rectangle(bounds, color);
            renderer2d.draw_rectangle(world_space_bounds, color);
        #endif
    }

    void Sprite::end()
    {

    }

    void Sprite::set_layer(int layer)
    {
        this->layer = layer;
        graphics.layer = layer;
        renderer2d.sort_render_order();   
    }
}