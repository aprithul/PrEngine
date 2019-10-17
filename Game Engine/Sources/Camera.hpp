#include "Entity.hpp"
#include "Engine.hpp"
#include "TimeModule.hpp"
#include "Vector2.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP
namespace Pringine
{
    class Camera: public Entity
    {
        public:
            Camera(int width, int height, float zoom_speed);
            ~Camera();
            Transform transform;
            int width;
            int height;
            float zoom_speed;
            float zoom_amount;
            float aspect_ratio;
            
            void start() override;
            void update() override;

        private:
            Vector2<float> speed;

        
    };
}
#endif