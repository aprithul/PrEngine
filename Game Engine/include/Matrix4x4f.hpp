//
//  Matrix4x4.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp

#include <cmath>
#include <stdio.h>
#include "Vector3.hpp"
#define DEG_TO_RAD 0.0174533f

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
        
        Matrix4x4<T> operator+(Matrix4x4<T> m) const 
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

        Matrix4x4<T> operator-(Matrix4x4<T> m) const
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

        Vector3<T> operator*(const Vector3<T>& v) const
        {
            Vector3<T> r;
            r.x =   (data[(0*4)+0]*v.x)+
                    (data[(0*4)+1]*v.y)+
                    (data[(0*4)+2]*v.z);

            r.y =   (data[(1*4)+0]*v.x)+
                    (data[(1*4)+1]*v.y)+
                    (data[(1*4)+2]*v.z);

            r.z =   (data[(2*4)+0]*v.x)+
                    (data[(2*4)+1]*v.y)+
                    (data[(2*4)+2]*v.z);
           
            return r;
        }

        Matrix4x4<T> operator^(Matrix4x4<T> m) const
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
        
        Matrix4x4<T> operator/(T v) const
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

        Matrix4x4<T> operator*(T v) const
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

        Matrix4x4<T> transpose() const
        {
            T _temp;
            Matrix4x4<T> r;
            for(int i=0; i<4; i++)
            {
                for(int j=i;j<4;j++)
                {
                    r.data[(j*4)+i] = data[(i*4)+j];
                    r.data[(i*4)+j] = data[(j*4)+i];
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

        static Matrix4x4 ortho(float left, float right, float bottom, float top, float near_, float far_)
        {
            Matrix4x4<float> ortho;
            ortho.set(0,0, 2.f/(right-left));
            ortho.set(0,3, -(right+left)/(right-left));

            ortho.set(1,1, 2.f/(top-bottom));
            ortho.set(1,3,-(top+bottom)/(top-bottom));

            ortho.set(2,2, -2.f/(far_-near_));
            ortho.set(2,3, -(far_+near_)/(far_-near_));
            ortho.set(2,3, -(far_+near_)/(far_-near_));

            ortho.set(3,3,1);
            
            return ortho;
        }

        static Matrix4x4 perspective(float n, float f, float width, float height, float fov)
        {
            float aspect_ratio = width / height;
            Matrix4x4<float> perspective;
            perspective.set(0,0, 1/(aspect_ratio*std::tan(fov*DEG_TO_RAD/2.f)));
            perspective.set(1,1, 1/(std::tan(fov*DEG_TO_RAD/2.f)));
            perspective.set(2,2, (-f-n)/(n-f));
            perspective.set(2,3, ((2*f*n)/(n-f)));
            perspective.set(3, 2, 1);
            perspective.set(3, 3, 0);
            return perspective;
        }

        static Matrix4x4 perspective(float n, float f, float width, float height)
        {
            Matrix4x4<float> perspective;
            perspective.set(0,0, (n/(width/2.f)));
            perspective.set(1,1, (n/(height/2.f)));
            perspective.set(2,2, (-(f+n)/(f-n)));
            perspective.set(2,3, (-(2*f*n)/(f-n)));
            perspective.set(3, 2,-1);
            perspective.set(3, 3, 0);
            return perspective;
        }

        T data[16];
    };
}

#endif /* Matrix4x4_hpp */
