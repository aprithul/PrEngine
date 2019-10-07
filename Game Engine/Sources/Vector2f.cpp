//
//  Vector2f.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Vector2f.hpp"

namespace Pringine {
    template<typename T>
    Vector2f::Vector2f(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    
    float Vector2f::get_x()
    {
        return this->x;
    }
    
    float Vector2f::get_y()
    {
        return this->y;
    }
    
    Vector2f Vector2f::operator+(Pringine::Vector2f &v)
    {
        return Vector2f( this->x + v.get_x(), this->y + v.get_y());
    }
    
    Vector2f Vector2f::operator-(Pringine::Vector2f &v)
    {
        return Vector2f( this->x - v.get_x(), this->y - v.get_y());
    }
    
    float Vector2f::operator*(Pringine::Vector2f &v)
    {
        return (this->x * v.get_x() + this->y * v.get_y());
    }
    
    Vector2f Vector2f::operator/(float v)
    {
        return Vector2f( this->x / v, this->y / v);
    }
    
    Vector2f Vector2f::normalize()
    {
        double len = length();
        x /= len;
        y /= len;
        return (*this);
    }
    
    float Vector2f::length()
    {
        return sqrt( x*x + y*y);
    }
}
