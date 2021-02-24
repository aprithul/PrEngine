#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP

#include "Entity.hpp"
#include "Engine.hpp"
#include "TimeModule.hpp"
#include "Vector3.hpp"
#include "Transform3D.hpp"

namespace PrEngine
{
    enum ProjectionType
    {
        PERSPECTIVE = 0,
        ORTHOGRAPHIC = 1
    };

    class Camera: public Component
    {
        public:
            Camera(float near, float far, float width, float height, float fov, Transform3D& _transform);
            ~Camera();
            Transform3D& transform;

            void zoom_in(float zoom_speed);
            void zoom_out(float zoom_speed);
            void awake() override;
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
            ProjectionType projection_type;
    };
}
#endif