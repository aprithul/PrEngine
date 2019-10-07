//
//  Vector3f.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//


#include "Vector3f.hpp"

namespace Pringine {
    
    Vector3f::Vector3f(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    Vector3f::Vector3f(float x, float y)
    {
        this->x = x;
        this->y = y;
        this->z = 0;
    }
    
    Vector3f::Vector3f()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    
    Vector3f::~Vector3f()
    {
        
    }
    
    float Vector3f::get_x()
    {
        return this->x;
    }
    
    float Vector3f::get_y()
    {
        return this->y;
    }
    
    float Vector3f::get_z()
    {
        return this->z;
    }
    
    Vector3f Vector3f::operator+(Vector3f &v)
    {
        return Vector3f( this->x + v.get_x(), this->y + v.get_y(), this->z + v.get_z());
    }
    
    Vector3f Vector3f::operator-(Vector3f& v)
    {
        return Vector3f( this->x - v.get_x(), this->y - v.get_y(), this->z - v.get_z());
    }
    
    Vector3f Vector3f::operator/(float v)
    {
        return Vector3f( this->x/v, this->y/v, this-> z/v);
    }
    
    float Vector3f::operator*(Vector3f& v)
    {
        return (this->x*v.get_x() + this->y + get_y() + this->z + get_z());
    }
    
    Vector3f Vector3f::cross(Vector3f& v)
    {
        return Vector3f(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    
    Vector3f Vector3f::normalize()
    {
        double len = length();
        x /= len;
        y /= len;
        z /= len;
        return (*this);
    }
    
    float Vector3f::length()
    {
        return sqrt( x*x + y*y + z*z);
    }
}
