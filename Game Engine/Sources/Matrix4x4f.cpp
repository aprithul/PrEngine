//
//  Matrix4x4.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Matrix4x4f.hpp"

namespace Pringine {
    Matrix4x4f::Matrix4x4f()
    {   
        
    }
    
    Matrix4x4f::~Matrix4x4f()
    {
        
    }
    
    float Matrix4x4f::get(int i, int j)
    {
        return m[i][j];
    }
    
    void Matrix4x4f::set(int i, int j, float v)
    {
        m[i][j] = v;
    }
    
    Matrix4x4f Matrix4x4f::operator*(Matrix4x4f _m)
    {
        Matrix4x4f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j,  m[i][0]*_m.get(0,j) + m[i][1]*_m.get(1,j) + m[i][2]*_m.get(2,j) + m[i][3]*_m.get(3,j));
            }
        return r;
    }
    
    Matrix4x4f Matrix4x4f::operator*(float v)
    {
        Matrix4x4f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j]* v);
            }
        return r;
    }

    Matrix4x4f Matrix4x4f::operator/(float v)
    {
        Matrix4x4f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j] / v);
            }
        return r;
    }
    
    Matrix4x4f Matrix4x4f::operator-(Matrix4x4f _m)
    {
        Matrix4x4f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j] - _m.get(i,j));
            }
        return r;
        
    }
    
    Matrix4x4f Matrix4x4f::operator+(Matrix4x4f _m)
    {
        Matrix4x4f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j] + _m.get(i,j));
            }
        return r;
        
    }
    
}
