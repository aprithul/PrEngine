#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Entity.hpp"
#include "Engine.hpp"
#include "TimeModule.hpp"
#include "Vector2.hpp"
#include "RendererModule.hpp"

namespace Pringine
{

    class Camera: public Entity
    {
        public:
            Camera(int width, int height, float zoom_speed, Renderer2D* renderer2d);
            ~Camera();
            Transform transform;
            int width;
            int height;
            float zoom_speed;
            float zoom_amount;
            float aspect_ratio;
            Renderer2D* renderer2d;

            void start() override;
            void update() override;

        private:
            Vector2<float> speed;

        
    };
}
#endif