#include "Cube.hpp"

namespace Pringine{

    Cube::Cube(Graphics3D& graphics):graphics(&graphics), Entity(ENTITY_TYPE_CUBE)
    {

    }

    Cube::~Cube()
    {

    }

    float s = 1.f;
    float x = 0.f;
    float y = 0.f;

    Matrix4x4<float> scale;
    Matrix4x4<float> translation;
    void Cube::start()
    {
        scale = Matrix4x4<float>::identity();
        translation = Matrix4x4<float>::identity();
    }

    void Cube::update()
    {
        if(input_manager->keyboard.get_key(SDLK_z))
            s += 1.f*Time::Frame_time;
        if(input_manager->keyboard.get_key(SDLK_x))
            s -= 1.f*Time::Frame_time;

        if(input_manager->keyboard.get_key(SDLK_UP))
            y += 1.f*Time::Frame_time;
        if(input_manager->keyboard.get_key(SDLK_DOWN))
            y -= 1.f*Time::Frame_time;
        if(input_manager->keyboard.get_key(SDLK_RIGHT))
            x += 1.f*Time::Frame_time;
        if(input_manager->keyboard.get_key(SDLK_LEFT))
            x -= 1.f*Time::Frame_time;
        
        // scale 
        scale.set(0,0,s);
        scale.set(1,1,s);

        // translate
        translation.set(0,3,x);
        translation.set(1,3,y);

        this->graphics->model = scale * translation;
    }

    void Cube::end()
    {

    }


}