//
//  Matrix4x4.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp

#include <stdio.h>

namespace Pringine {
    class Matrix4x4f
    {
    public:
        Matrix4x4f();
        ~Matrix4x4f();
        Matrix4x4f operator+(Matrix4x4f m);
        Matrix4x4f operator-(Matrix4x4f m);
        Matrix4x4f operator*(Matrix4x4f m);
        Matrix4x4f operator/(float v);
        Matrix4x4f operator*(float v);
        
        void set(int i, int j, float v);
        float get(int i, int j);
        
    private:
        float m[4][4];
    };
}

#endif /* Matrix4x4_hpp */
