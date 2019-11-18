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
            Camera3D(Renderer3D& renderer_3D);
            ~Camera3D();
            Transform3D transform;

            void zoom_in(float zoom_speed);
            void zoom_out(float zoom_speed);
            void start() override;
            void update() override;
            void end() override;            

        private:
            Renderer3D& renderer_3d;
    };
}
#endif