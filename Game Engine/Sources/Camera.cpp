#include "Camera.hpp"

namespace Pringine
{
    Camera::Camera(int width, int height, float zoom_speed, Renderer2D* renderer2d):Entity(ENTITY_TYPE_CAMERA)
    {
        this->width = width;
        this->height = height;
        this->aspect_ratio = width/height;
        this->zoom_amount = 1.0f;
        this->zoom_speed = zoom_speed;
        this->renderer2d = renderer2d;
    }

    Camera::~Camera()
    {

    }

    void Camera::start()
    {
        speed.x = 5.0f;
        speed.y = 5.0f;
    }

    void Camera::update()
    {
        /*if(Pringine::engine->input_handler->get_key(SDLK_z))
        {
            zoom_amount += zoom_speed;//(zoom_speed * Time::Frame_time);
        }
        else if(Pringine::engine->input_handler->get_key(SDLK_x))
        {
            zoom_amount -= zoom_speed;//(zoom_speed * Time::Frame_time);
        }

        Vector2<float> move_direction;
        if(engine->input_handler->get_key(SDLK_LEFT))
        {
            move_direction.x = -1;
        }
        else if(engine->input_handler->get_key(SDLK_RIGHT))
        {
            move_direction.x = 1;
        }
        if(engine->input_handler->get_key(SDLK_DOWN))
        {
            move_direction.y = -1;
        }
        else if(engine->input_handler->get_key(SDLK_UP))
        {
            move_direction.y = 1;
        }
       
        transform.translate( (move_direction ^ speed) * Time::Frame_time);
        //LOG(LOGTYPE_GENERAL, std::to_string(transform.position.x).append(", ").append(std::to_string(transform.position.y)));
 */
       
        zoom_amount = Pringine::clamp(zoom_amount,1.0f, 5.0f);

        renderer2d->view_position = transform.position;
        renderer2d->zoom_amount = zoom_amount;

        //LOG(LOGTYPE_GENERAL, std::string("zoom amount: ").append(std::to_string(zoom_amount)));


        Rect camera_bounds(transform.position.x, transform.position.y, width, height);
        SDL_Color color;
        color.r = 255;
        color.g = 122;
        color.b = 10;
        color.a = 255;
        renderer2d->draw_rectangle(camera_bounds, color);

    }
}