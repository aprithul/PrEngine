#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "Vector3.hpp"
#include "Logger.hpp"
#include "Component.hpp"
#include "Matrix4x4f.hpp"
#include <string>

namespace Pringine{
    
    class Transform3D : public Component
    {
        public:
            
            void set_position(Vector3<float> position);
            void set_position(float x, float y, float z);
            void set_scale(Vector3<float> scale);
            void set_scale(float x, float y, float z);
            void set_rotation(Vector3<float> rotation);
            void set_rotation(float x, float y, float z);

            const Vector3<float>& get_position();
            const Vector3<float>& get_scale();
            const Vector3<float>& get_rotation();
        

            Transform3D();
            Transform3D(Vector3<float> position, Vector3<float> angle, Vector3<float> scale);
            ~Transform3D();
            void translate(const Vector3<float>& translation);
            void rotate(float _x, float _y, float _z);


        private:

            Vector3<float> position;
            Vector3<float> angle;
            Vector3<float> scale;

            Matrix4x4<float> translation;
            Matrix4x4<float> scale;
            Matrix4x4<float> rotation_x;
            Matrix4x4<float> rotation_y;
            Matrix4x4<float> rotation_z;

 
    };
}
#endif