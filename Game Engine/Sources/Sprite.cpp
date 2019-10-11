#include "Sprite.hpp"

namespace Pringine
{

     Sprite::Sprite(const std::string& graphics_file_name,  Renderer2D& _renderer2d):renderer2d(_renderer2d)
    {
        transform = new Transform();
        graphics = new Graphics();
        graphics->load_graphics(graphics_file_name, _renderer2d);
        this->renderer2d_id = _renderer2d.add_graphics_to_draw(graphics);
    }

    Sprite::~Sprite()
    {
        this->renderer2d.remove_graphics(this->renderer2d_id);
        delete transform;
        delete graphics;
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
        graphics->dimension.x = (int)transform->position.x;
        graphics->dimension.y = (int)transform->position.y;
    }

    void Sprite::end()
    {

    }
}