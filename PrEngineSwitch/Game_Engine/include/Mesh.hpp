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
#include "Types.hpp"
#include <GLES2/gl2.h>  // OpenGL ES 2.0 library

namespace PrEngine {
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();
        void set_vertices(Vertex* _vertices, Int_32 vertex_count);
        void set_indices(GLuint* indices, Int_32 count);
        void upload();
        void draw();
        
        GLint vertices_array_size; 
        GLint indices_array_size; 
        GLint vertex_count;
        GLint index_count;
        Vertex* vertices;
        GLuint* vertex_indices;

        
    };
}

#endif /* Mesh_hpp */
