#include "Camera3D.hpp"

namespace Pringine
{
    Camera3D::Camera3D(Renderer3D& renderer_3d): renderer_3d(renderer_3d),Entity(ENTITY_TYPE_CAMERA)
    {
        fov = 45.f;
        near = 0.1f;
        far = -1.f;    
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
        if(input_manager->keyboard.get_key(SDLK_z))
            pos.y = pos.y+(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_c))
            pos.y = pos.y-(Time::Frame_time*1.f);
        if(input_manager->keyboard.get_key(SDLK_d))
            pos = pos + (transform.get_right()*(float)(Time::Frame_time*5.f));
        if(input_manager->keyboard.get_key(SDLK_a))
            pos = pos - (transform.get_right()*(float)(Time::Frame_time*5.f));
        if(input_manager->keyboard.get_key(SDLK_s))
            pos = pos - (transform.get_forward()*(float)(Time::Frame_time*5.f));
        if(input_manager->keyboard.get_key(SDLK_w))
            pos = pos + (transform.get_forward()*(float)(Time::Frame_time*5.f));
        transform.set_position(pos);



        // set view matrix based on camera

        renderer_3d.view_matrix = Matrix4x4<float>::identity();
        renderer_3d.view_matrix.set(0,3, -transform.get_position().x);
        renderer_3d.view_matrix.set(1,3, -transform.get_position().y);
        renderer_3d.view_matrix.set(2,3, -transform.get_position().z);
        Matrix4x4<float> reverse_rot = transform.get_rotation_transformation().transpose();
        renderer_3d.view_matrix = reverse_rot * renderer_3d.view_matrix;
        renderer_3d.projection = Matrix4x4<float>::perspective(near, far,4.f,3.f, fov);

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

        //std::cout<<"Mouse delta: "<<input_manager->mouse.delta.length()<<std::endl;

        float rotation_factor = 15.f;
        Vector3<float> rot = transform.get_rotation();
        //if(input_manager->keyboard.get_key(SDLK_a))
        rot.y = rot.y+(Time::Frame_time*rotation_factor*input_manager->mouse.delta.x);
        rot.x = rot.x+(Time::Frame_time*rotation_factor*input_manager->mouse.delta.y);
        //if(input_manager->keyboard.get_key(SDLK_d))
        //    rot.y = rot.y-(Time::Frame_time*100.f);
        transform.set_rotation(rot);

    }

    void Camera3D::end()
    {

    }
}