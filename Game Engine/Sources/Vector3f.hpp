//
//  Vector3f.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Vector3f_hpp
#define Vector3f_hpp

#include <cmath>

namespace Pringine {
    class Vector3f
    {
    public:
        Vector3f(float x, float y, float z);
        Vector3f(float x, float y);
        Vector3f();
        
        ~Vector3f();
        float get_x();
        float get_y();
        float get_z();
        Vector3f operator+(Vector3f& v);
        Vector3f operator-(Vector3f& v);
        float operator*(Vector3f& v);
        Vector3f operator/(float v);
        Vector3f normalize();
        float length();
        Vector3f cross(Vector3f& v);
        
    private:
        float x,y,z;
        
    };
}
#endif /* Vector3f_hpp */
