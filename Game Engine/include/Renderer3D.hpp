//
//  Display.h
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Display_h
#define Display_h

#include "tiny_obj_loader.h"

#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "Module.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "InputModule.hpp"
#include "Matrix4x4f.hpp"
#include "../Vendor/include/stb_image.h"
#include <vector>
#include <unordered_map>

#define DEBUG true

#define Assert(x) if(!x) __builtin_trap();

#ifdef DEBUG
    #define GL_CALL(x) gl_clear_error(); x; Assert(gl_get_error(#x, __FILE__, __LINE__))
#else
    #define GL_CALL(x) x
#endif

namespace Pringine {
    
    static void gl_clear_error()
    {
        while(glGetError() != GL_NO_ERROR); 
    }

    static bool gl_get_error(char* func_name, char* file_name, int line_no)
    {
        bool no_error = true;
        GLuint err = GL_NO_ERROR;
        while((err = glGetError())!=GL_NO_ERROR){
            std::cout<<"OpenGL error [ code: "<<err<<" ], in function: "<<func_name
                    <<","<<" (line:"<<line_no<<") file: "<<file_name<<std::endl;
            no_error = false;
        }
        
        return no_error;
        
    }

    enum ShaderType
    {
        SHADER_PASSTHROUGH,
        SHADER_COUNT
    };
    
    struct Texture
    {
        GLuint id;
        int width;
        int height;
        int no_of_channels;
        stbi_uc* data;

        Texture(const char* path);
        ~Texture();
        void Bind(int slot);
        void Unbind();
    };

    struct Material
    {
        Material(const std::string& path);
        ~Material();
        GLuint shader_program;
        std::string source_file_path;
        std::unordered_map<const char*,GLint> uniform_locations;
        bool make_shader_program(const std::string& path);
        GLuint make_shader(GLenum type,  const std::string& source);
        void load_uniform_location(const char* uniform);
    };

    struct VertexArray
    {
        GLuint id;
        VertexArray();
        ~VertexArray();
        void Bind();
        void Unbind();
    };

    struct VertexBuffer
    {
        GLuint id;
        VertexBuffer(const Vertex* vertices, GLuint size);
        ~VertexBuffer();
        void Bind();
        void Unbind();
    };

    struct IndexBuffer
    {
        GLuint id;
        GLsizei count;
        IndexBuffer(const GLuint* indices, GLuint size, GLsizei count);
        ~IndexBuffer();
        void Bind();
        void Unbind();
    };

    struct VertexAttribute
        {
            GLuint index;     
            GLuint count;
            int type;
            GLboolean normalized;
            GLsizei offset;

            GLsizei size;

            VertexAttribute(GLuint index, GLuint count, int type, GLboolean normalized);
    };

    struct VertexLayout
    {
        VertexLayout();
        GLsizei stride;
        std::vector<VertexAttribute> vertex_attributes;
        void add_attribute(VertexAttribute& attribute);
    };


    struct Graphics3D
    {
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;
        Material material;
        Texture texture;
        Vertex* vertices;
        GLuint* indices;  
        VertexLayout layout;  

        Matrix4x4<float> model;
        Graphics3D( const Vertex* vertices, GLuint vertices_size, const GLuint* indices, GLuint indices_size, GLsizei indices_count, Material material,Texture texture, VertexLayout layout);
        ~Graphics3D();
    };


    class Renderer3D : public Module
    {

    public:
        // display attributes
        int height;
        int width;
        std::string title;
        std::vector<Graphics3D*> graphics3d_list;
        // constructor/ destructors
        Renderer3D(int width, int height, std::string title);
        ~Renderer3D();
        void init();
        // clears the display with the color specified
        void Clear(float r, float g, float b, float a);
        // swaps buffers in a double buffer environment
        void SwapBuffers();
        void set_vsync(GLboolean value);
        void upload_mesh(const Mesh& mesh);
        bool make_shader_program(const std::string& path, GLuint& shader_program);
        GLuint make_shader( GLenum type, const std::string& source);

        void start() override;
        void update() override;
        void end() override;
        
    private:
        // reference to the sdl window
        SDL_Window* window;
        // the opengl context used with the window
        SDL_GLContext glContext;
        GLuint shader_programs[SHADER_COUNT];
        
    };
}


#endif /* Display_h */
