#include "Cube.hpp"

namespace Pringine{

    Cube::Cube(Graphics3D* graphics):Entity3D(ENTITY_TYPE_CUBE, graphics)
    {

    }

    Cube::~Cube()
    {

    }

    void Cube::start()
    {
    }

    void Cube::update()
    {
        float factor = 1.f;
        if(input_manager->keyboard.get_key(SDLK_z))
            factor += (Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_x))
            factor -= (Time::Frame_time*1.f);
        transform.set_scale(transform.get_scale() * factor);

        Vector3<float> pos = transform.get_position();
        if(input_manager->keyboard.get_key(SDLK_UP))
            pos.y = pos.y+(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_DOWN))
            pos.y = pos.y-(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_RIGHT))
            pos.x = pos.x+(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_LEFT))
            pos.x = pos.x-(Time::Frame_time*1.f);
        transform.set_position(pos);

        Vector3<float> rot = transform.get_rotation();
        if(input_manager->keyboard.get_key(SDLK_q))
            rot.x = rot.x-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_e))
            rot.x = rot.x+(Time::Frame_time*20.f);

        if(input_manager->keyboard.get_key(SDLK_a))
            rot.y = rot.y-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_d))
            rot.y = rot.y+(Time::Frame_time*20.f);

        if(input_manager->keyboard.get_key(SDLK_r))
            rot.z = rot.z-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_t))
            rot.z = rot.z+(Time::Frame_time*20.f);

        transform.set_rotation(rot);

    }

    void Cube::end()
    {

    }


}