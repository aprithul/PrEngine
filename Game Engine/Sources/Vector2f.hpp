//
//  Vector2f.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Vector2f_hpp
#define Vector2f_hpp

#include <stdio.h>
#include "math.h"

namespace Pringine {
    class Vector2f
    {
    public:
        template<typename T>
        Vector2f(T x, T y);
        
        ~Vector2f();
        float get_x();
        float get_y();
        Vector2f operator+(Vector2f& v);
        Vector2f operator-(Vector2f& v);
        float operator*(Vector2f& v);
        Vector2f operator/(float v);
        Vector2f normalize();
        float length();
        
    private:
        float x,y;
        
    };
}
#endif /* Vector2f_hpp */
