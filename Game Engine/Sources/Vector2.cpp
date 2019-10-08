//
//  Vector2.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Vector2.hpp"

namespace Pringine {

    template<typename T>
    Vector2<T>::Vector2()
    {
        
    }

    template<typename T>
    Vector2<T>::Vector2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    
    template<typename T>
    Vector2<T>::~Vector2()
    {
        
    }

    template<typename T>    
    T Vector2<T>::get_x() const
    {
        return this->x;
    }
    
    template<typename T>
    T Vector2<T>::get_y() const
    {
        return this->y;
    }
    
    template<typename T>    
    void Vector2<T>::set_x(T x)
    {
        this->x = x;
    }

    template<typename T>    
    void Vector2<T>::set_y(T y)
    {
        this->y = y;
    }

    template<typename T>    
    Vector2<T> Vector2<T>::operator+(const Vector2<T> &v)
    {
        return Vector2<T>( this->x + v.get_x(), this->y + v.get_y());
    }
    
    template<typename T>    
    Vector2<T> Vector2<T>::operator+=(const Vector2<T> &v)
    {
        this->x += v.get_x();
        this->y += v.get_y();
        return Vector2<T>( this->x, this->y);
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator-(const Vector2<T> &v)
    {
        return Vector2<T>( this->x - v.get_x(), this->y - v.get_y());
    }
    
    template<typename T>
    T Vector2<T>::operator*(const Vector2<T> &v)
    {
        return (this->x * v.get_x() + this->y * v.get_y());
    }
    
    template<typename T>
    Vector2<T> Vector2<T>::operator/(T v)
    {
        return Vector2<T>( this->x / v, this->y / v);
    }
    
    template<typename T>
    Vector2<T> Vector2<T>::normalize()
    {
        double len = length();
        x /= len;
        y /= len;
        return (*this);
    }
    
    template<typename T>
    float Vector2<T>::length()
    {
        return sqrt( x*x + y*y);
    }
}
