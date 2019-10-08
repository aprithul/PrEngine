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

    Vector2<float> Transform::get_position() const
    {
        return this->position;
    }

    float Transform::get_angle() const
    {
        return this->angle;
    }

    Vector2<float> Transform::get_scale() const
    {
        return this->scale;
    }    
    
    void Transform::set_position(const Vector2<float>& pos)
    {
        this->position = Vector2<float>(pos);
    }

    void Transform::set_position(float x, float y)
    {
        this->position.set_x(x);
        this->position.set_y(y);
    }

    void Transform::set_angle(float angle)
    {
        this->angle = angle;
    }

    void Transform::set_scale(const Vector2<float>& scale)
    {
        this->scale = Vector2<float>(scale);
    }

    void Transform::set_scale(float x, float y)
    {
        this->scale.set_x(x);
        this->scale.set_y(y);
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