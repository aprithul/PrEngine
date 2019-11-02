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
    
    template<typename T>
    class Matrix4x4
    {
    public:
        Matrix4x4()
        {
            for(int i=0; i<16; i++)
            {
                data[i] = 0;
            }
        }

        ~Matrix4x4()
        {

        }
        
        Matrix4x4<T> operator+(Matrix4x4<T> m)
        {
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    r.data[(i*4)+j] = data[(i*4)+j] + m.data[(i*4)+j];
                }
            }
            return r;
        }

        Matrix4x4<T> operator-(Matrix4x4<T> m)
        {
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    r.data[(i*4)+j] = data[(i*4)+j] - m.data[(i*4)+j];
                }
            }
            return r;
        }
                
        Matrix4x4<T> operator*(const Matrix4x4<T>& m) const
        {
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    r.data[(i*4)+j] =   (data[(i*4)+0]*m.data[0+j]) +
                                        (data[(i*4)+1]*m.data[4+j]) +
                                        (data[(i*4)+2]*m.data[8+j]) +
                                        (data[(i*4)+3]*m.data[12+j]);
                }
            }
            return r;
        }

        Matrix4x4<T> operator^(Matrix4x4<T> m)
        {
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    r.data[(i*4)+j] = data[(i*4)+j] * m.data[(i*4)+j];
                }
            }
            return r;
        }
        
        Matrix4x4<T> operator/(T v)
        {
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    r.data[(i*4)+j] = data[(i*4)+j] / v;
                }
            }
            return r;
        } 

        Matrix4x4<T> operator*(T v)
        {
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    r.data[(i*4)+j] = data[(i*4)+j] * v;
                }
            }
            return r;
        }        

        void set(int i, int j, T v)
        {
            data[(i*4)+j] = v;
        }
        T get(int i, int j)
        {
            return data[(i*4)+j];
        }

        static Matrix4x4 identity()
        {
            Matrix4x4<T> identity;
            identity.set(0,0,1);
            identity.set(1,1,1);
            identity.set(2,2,1);
            identity.set(3,3,1);
            return identity;
        }

        static Matrix4x4 ortho(float left, float right, float bottom, float top, float near, float far)
        {
            Matrix4x4<float> ortho;
            ortho.set(0,0, 2.f/(right-left));
            ortho.set(0,3, -(right+left)/(right-left));

            ortho.set(1,1, 2.f/(top-bottom));
            ortho.set(1,3,-(top+bottom)/(top-bottom));

            ortho.set(2,2, -2.f/(far-near));
            ortho.set(2,3, -(far+near)/(far-near));

            ortho.set(3,3,1);
            
            return ortho;
        }

        T data[16];
    };
}

#endif /* Matrix4x4_hpp */
