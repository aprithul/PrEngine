#include "Sprite.hpp"

namespace Pringine
{

     Sprite::Sprite(const std::string& graphics_file_name, TextureSlicingParameters slicing_param, Renderer2D& _renderer2d, int num_of_animation_frames, int pixel_to_world_scale, int layer):Entity(ENTITY_TYPE_SPRITE),renderer2d(_renderer2d)
    {
        name = graphics_file_name;
        //LOG(LOGTYPE_GENERAL,"Created sprite");
        graphics.load_graphics(graphics_file_name, slicing_param, _renderer2d, num_of_animation_frames) ;
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

        LOG(LOGTYPE_GENERAL, std::to_string(graphics.get_current_frame()->region.w));
        LOG(LOGTYPE_GENERAL, std::to_string(graphics.get_current_frame()->region.h));
    }

    Sprite::~Sprite()
    {
        this->renderer2d.remove_graphics(this->renderer2d_id);
        //delete transform;
        //delete graphics;
    }
    
    void Sprite::awake()
    {


    }

    void Sprite::set_animation(bool do_animate, int fps)
    {
        this->do_animate = do_animate;
        animation_accumulator = 0.0;
        animation_delta = 1.0/fps;
    }

    void Sprite::start()
    {
    }

    void Sprite::update()
    {
        
        if(do_animate)
        {
            animation_accumulator += Time::Frame_time;
            if(animation_accumulator > animation_delta)
            {
                graphics.current_frame_index = (graphics.current_frame_index+1)%graphics.number_of_frames;
                animation_accumulator -= animation_delta;
            }
        }


        //convert world space position of sprite to camera space
        graphics.dst_dimension.x = transform.position.x;//  (int)transform.position.x - (graphics.dst_dimension.w/2);
        graphics.dst_dimension.y = transform.position.y;// (int)transform.position.y - (graphics.dst_dimension.h/2);

        graphics.dst_dimension.w = bounding_box.w;
        graphics.dst_dimension.h = bounding_box.h;

        Rect bounds(transform.position.x, transform.position.y, bounding_box.w, bounding_box.h);
        SDL_Color color;
        color.r = 255;
        color.g = 122;
        color.b = 10;
        color.a = 255;
        renderer2d.draw_rectangle(bounds, color);
    }

    void Sprite::end()
    {

    }

}