#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "Vector2.cpp"

namespace Pringine{
    
    class Transform
    {
        public:
            Transform();
            ~Transform();

            //gettters
            Vector2<float> get_position() const;
            float get_angle() const;
            Vector2<float> get_scale() const;

            //setters
            void set_position(const Vector2<float>& pos);
            void set_position(float x, float y);
            void set_angle(float angle);
            void set_scale(const Vector2<float>& scale);
            void set_scale(float x, float y);

            //
            Vector2<float> translate(const Vector2<float>& translation);
            void rotate(float amount);


        private:
            Vector2<float> position;
            float angle;
            Vector2<float> scale;
 
    };
}
#endif