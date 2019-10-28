//
//  Mesh.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/31/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include "Vertex.hpp"
#include <OpenGL/gl3.h>

namespace Pringine {
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();
        void set_vertices(Vertex* vertices, int length);
        GLint size; 
        GLint vertex_count;
        GLfloat* vertices;
        
    };
}

#endif /* Mesh_hpp */
