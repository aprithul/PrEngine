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
#include "Component.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "InputModule.hpp"
#include "Matrix4x4f.hpp"
#include "../Vendor/include/stb_image.h"
#include "../Vendor/include/tiny_obj_loader.h"
#include <vector>
#include <tuple>
#include <unordered_map>

#define DEBUG true

#define Assert(x) if(!x) __builtin_trap();

#ifdef DEBUG
    #define GL_CALL(x) gl_clear_error(); x; Assert(gl_get_error(#x, __FILE__, __LINE__))
#else
    #define GL_CALL(x) x
#endif

namespace Pringine {
    
    class Texture;
    
    extern std::unordered_map<std::string, stbi_uc*> texture_data_library;
    extern std::unordered_map<std::string, Texture*> texture_library;
    
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
        static int texture_create_status;

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
        Material();
        void Generate(const std::string& shader_path, const std::string& diffuse_tex_path);
        void Delete();
        ~Material();
        GLuint shader_program;
        std::string source_file_path;
        std::unordered_map<const char*,GLint> uniform_locations;
        Texture* diffuse_texture;
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
        void Generate();
        void Delete();
    };

    struct VertexBuffer
    {
        GLuint id;
        VertexBuffer();
        ~VertexBuffer();
        void Bind();
        void Unbind();
        void Generate(const Vertex* vertices, GLuint size);
        void Delete();
    };

    struct IndexBuffer
    {
        GLuint id;
        GLsizei count;
        IndexBuffer();
        ~IndexBuffer();
        void Bind();
        void Unbind();
        void Generate(const GLuint* indices, GLuint indices_size, GLsizei count);
        void Delete();
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


    struct GraphicsElement
    {
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;
        Material material;
        VertexLayout layout;
        int num_of_triangles;
        void Delete();
    };

    struct Graphics3D : public Component
    {
        std::vector<GraphicsElement> elements;
        //Material* material;
        //VertexLayout layout;  

        const Matrix4x4<float>* model;
        const Matrix4x4<float>* normal;

        Graphics3D();// const Vertex* vertices, GLuint vertices_size, const GLuint* indices, GLuint indices_size, GLsizei indices_count, Material material,Texture texture, VertexLayout layout);
        ~Graphics3D();
        private:
            Matrix4x4<float> _model;
            Matrix4x4<float> _normal;
        
    };
    


    class Renderer3D : public Module
    {

    public:
        // display attributes
        int height;
        int width;
        std::string title;
        std::vector<Mesh*>meshes;
        std::vector<Graphics3D*> graphics3d_list;
        Vector3<float> light_direction;

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
        Graphics3D* generate_graphics3d(const char* base_dir, const char* file_name, const char* texture_file_path);
        
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
