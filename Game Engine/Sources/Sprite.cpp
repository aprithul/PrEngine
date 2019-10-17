#include "Sprite.hpp"

namespace Pringine
{

     Sprite::Sprite(const std::string& graphics_file_name, TextureSlicingParameters slicing_param, Renderer2D& _renderer2d, int num_of_animation_frames, int pixel_to_world_scale):Entity(ENTITY_TYPE_SPRITE),renderer2d(_renderer2d)
    {
        //LOG(LOGTYPE_GENERAL,"Created sprite");
        graphics.load_graphics(graphics_file_name, slicing_param, _renderer2d, num_of_animation_frames) ;
        this->renderer2d_id = _renderer2d.add_graphics_to_draw(&graphics);
        this->pixel_to_world = pixel_to_world_scale;
        // for sprites we can readiliy assume the diemnsion to be the bound of the sprite
        this->bounding_box.w = slicing_param.w / this->pixel_to_world;
        this->bounding_box.h= slicing_param.h / this->pixel_to_world;

        //LOG(LOGTYPE_GENERAL, std::to_string(bounding_box.w));
        //LOG(LOGTYPE_GENERAL, std::to_string(bounding_box.h));
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

    void Sprite::start()
    {
        
    }

    void Sprite::update()
    {
        //convert world space position of sprite to camera space
        graphics.dst_dimension.x = transform.position.x;//  (int)transform.position.x - (graphics.dst_dimension.w/2);
        graphics.dst_dimension.y = transform.position.y;// (int)transform.position.y - (graphics.dst_dimension.h/2);

        graphics.dst_dimension.w = bounding_box.w;
        graphics.dst_dimension.h = bounding_box.h;
    }

    void Sprite::end()
    {

    }
}