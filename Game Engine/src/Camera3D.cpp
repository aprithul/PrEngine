#include "Camera3D.hpp"

namespace Pringine
{
    Camera3D::Camera3D(Renderer3D& renderer_3d): renderer_3d(renderer_3d),Entity(ENTITY_TYPE_CAMERA)
    {
    
    }

    Camera3D::~Camera3D()
    {

    }

    void Camera3D::start()
    {

    }

    void Camera3D::update()
    {

        Vector3<float> pos = transform.get_position();
        if(input_manager->keyboard.get_key(SDLK_UP))
            pos.y = pos.y+(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_DOWN))
            pos.y = pos.y-(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_RIGHT))
            pos.x = pos.x+(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_LEFT))
            pos.x = pos.x-(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_z))
            pos.z = pos.z-(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_c))
            pos.z = pos.z+(Time::Frame_time*1.f);
        transform.set_position(pos);

        Vector3<float> rot = transform.get_rotation();
        if(input_manager->keyboard.get_key(SDLK_a))
            rot.y = rot.y-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_d))
            rot.y = rot.y+(Time::Frame_time*20.f);
        transform.set_rotation(rot);

        // set view matrix based on camera

        renderer_3d.view_matrix = Matrix4x4<float>::identity();
        renderer_3d.view_matrix.set(0,3, -transform.get_position().x);
        renderer_3d.view_matrix.set(1,3, -transform.get_position().y);
        renderer_3d.view_matrix.set(2,3, -transform.get_position().z);
        Matrix4x4<float> reverse_rot = transform.get_rotation_transformation().transpose();
        renderer_3d.view_matrix = reverse_rot * renderer_3d.view_matrix;

/*
        Vector3<float> rot = transform.get_rotation();
        if(input_manager->keyboard.get_key(SDLK_a))
            rot.y = rot.y-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_d))
            rot.y = rot.y+(Time::Frame_time*20.f);
        transform.set_rotation(rot);
        if(input_manager->keyboard.get_key(SDLK_z))
            rot.z = rot.z-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_c))
            rot.z = rot.z+(Time::Frame_time*20.f);

        if(input_manager->keyboard.get_key(SDLK_q))
            rot.x = rot.x-(Time::Frame_time*20.f);
        if(input_manager->keyboard.get_key(SDLK_e))
            rot.x = rot.x+(Time::Frame_time*20.f);
        transform.set_rotation(rot);*/
    }

    void Camera3D::end()
    {

    }
}