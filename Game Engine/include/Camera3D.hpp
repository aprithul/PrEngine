#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP

#include "Entity.hpp"
#include "Engine.hpp"
#include "TimeModule.hpp"
#include "Vector3.hpp"
#include "Renderer3D.hpp"
#include "Transform3D.hpp"

namespace Pringine
{

    class Camera3D: public Entity
    {
        public:
            Camera3D(float width, float height, float near, float far, float fov);
            ~Camera3D();
            Transform3D transform;

            void zoom_in(float zoom_speed);
            void zoom_out(float zoom_speed);
            void start() override;
            void update() override;
            void end() override;     


            float fov;
            float near_;
            float far_; 
            float width;
            float height;

            Matrix4x4<float> view_matrix;
            Matrix4x4<float> projection_matrix;
    };
}
#endif