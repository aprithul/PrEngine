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
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#elif _WIN64
#include <GL/glew.h>
#endif


namespace Pringine {
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();
        void set_vertices(Vertex* _vertices, int vertex_count);
        void set_indices(GLuint* indices, int count);
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
