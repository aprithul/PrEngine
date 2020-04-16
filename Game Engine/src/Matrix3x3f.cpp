//
//  Matrix4x4.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Matrix3x3f.hpp"

namespace Pringine {
    Matrix3x3f::Matrix3x3f()
    {   
        
    }
    
    Matrix3x3f::~Matrix3x3f()
    {
        
    }
    
    float Matrix3x3f::get(int i, int j)
    {
        return m[i][j];
    }
    
    void Matrix3x3f::set(int i, int j, float v)
    {
        m[i][j] = v;
    }
    
    Matrix3x3f Matrix3x3f::operator*(Matrix3x3f _m)
    {
        Matrix3x3f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j,  m[i][0]*_m.get(0,j) + m[i][1]*_m.get(1,j) + m[i][2]*_m.get(2,j) + m[i][3]*_m.get(3,j));
            }
        return r;
    }
    
    Matrix3x3f Matrix3x3f::operator*(float v)
    {
        Matrix3x3f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j]* v);
            }
        return r;
    }

    Matrix3x3f Matrix3x3f::operator/(float v)
    {
        Matrix3x3f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j] / v);
            }
        return r;
    }
    
    Matrix3x3f Matrix3x3f::operator-(Matrix3x3f _m)
    {
        Matrix3x3f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j] - _m.get(i,j));
            }
        return r;
        
    }
    
    Matrix3x3f Matrix3x3f::operator+(Matrix3x3f _m)
    {
        Matrix3x3f r;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                r.set( i, j, m[i][j] + _m.get(i,j));
            }
        return r;
        
    }
    
}
