//
//  Vector2.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <stdio.h>
#include "math.h"

namespace Pringine {

    template<typename T>
    class Vector2
    {
    public:
    
        Vector2();
        Vector2(T x, T y);
        ~Vector2();

        T get_x() const;
        T get_y() const;
        void set_x(T x);
        void set_y(T y);

        Vector2 operator+(const Vector2& v);
        Vector2 operator+=(const Vector2& v);
        Vector2 operator-(const Vector2& v);
        T operator*(const Vector2& v);
        Vector2 operator/(const T v);
        Vector2 normalize();
        float length();
        
    private:
        T x,y;
        
    };
}
#endif /* Vector2_hpp */
