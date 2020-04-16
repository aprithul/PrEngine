#include "Camera3D.hpp"

namespace Pringine
{
    Camera3D::Camera3D(float width, float height, float near_, float far_, float fov):Entity(ENTITY_TYPE_CAMERA)
    {
        //fov = 45.f;
        //near_ = 0.1f;
        //far_ = -1.f;    
        this->width = width;
        this->height = height;
        this->near_ = near_;
        this->far_ = far_;
        this->fov = fov;
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

        view_matrix = Matrix4x4<float>::identity();
        view_matrix.set(0,3, -transform.get_position().x);
        view_matrix.set(1,3, -transform.get_position().y);
        view_matrix.set(2,3, -transform.get_position().z);
        Matrix4x4<float> reverse_rot = transform.get_rotation_transformation().transpose();
        view_matrix = reverse_rot * view_matrix;
        projection_matrix = Matrix4x4<float>::perspective(near_, far_,width, height, fov);

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