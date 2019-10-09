#include "Transform.hpp"
namespace  Pringine
{
    Transform::Transform()
    {
        this->position = Vector2<float>(2.f,2.f);
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