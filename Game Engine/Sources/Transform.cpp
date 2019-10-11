#include "Transform.hpp"
namespace  Pringine
{
    Transform::Transform()
    {
        this->position = Vector2<float>(0.f, 0.f);
        this->angle = 0.f;
        this->scale = Vector2<float>(1.f, 1.f);
    }

    Transform::Transform(Vector2<float> position, float angle, Vector2<float> scale)
    {
        this->position = position;
        this->angle = angle;
        this->scale = scale;
    }


    Transform::~Transform()
    {

    }

    Vector2<float> Transform::translate(const Vector2<float>& translation)
    {
        this->position += translation;
    }

    void Transform::rotate(float angle)
    {
        this->angle += angle;
    }
}