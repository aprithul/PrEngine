//
//  Vertex.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/30/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>  
#include <memory>
#include "Vector3.hpp"
#include <OpenGL/gl3.h>

namespace Pringine {

    static const int ATTRIB_POSITION_LENGTH = 3;
    static const int ATTRIB_POSITION_OFFSET = 0*sizeof(float);
    static const int ATTRIB_COLOR_LENGTH = 4;
    static const int ATTRIB_COLOR_OFFSET = 3*sizeof(float);

    enum AttributeIndex
    {
        ATTRIB_POSITION = 0,
        ATTRIB_COLOR = 1
    };
    
    struct Vertex
    {
        float x;
        float y;
        float z;
        float r;
        float g;
        float b;
        float a;
        float u;
        float v;
    };
}


#endif /* Vertex_hpp */
