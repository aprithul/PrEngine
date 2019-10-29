//
//  Display.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//
#include "Renderer3D.hpp"

namespace Pringine {
    
    Renderer3D::Renderer3D(int width, int height, std::string title):Module("Opengl Renderer", 4)
    {
        this->width = width;
        this->height = height;
        this->title = title;
        
        // initialize sdl and opengl related settings for graphics
        init();
        
        // create window
        window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);
        // create the openGL context from the window  that was created
        glContext = SDL_GL_CreateContext(window);

        glFrontFace(GL_CCW);     // points are gonna get supplid in clockwise order
        glEnable(GL_CULL_FACE);        


        if( glewInit() != GLEW_OK)
            printf("Glew not initialized properly");

        // if context creation failed, log the error
        if(glContext==NULL)
        {
            printf("SDL_Init failed: %s\n", SDL_GetError());
        }
        else
            printf("Context created with OpenGL version  (%s)\n", glGetString(GL_VERSION));

        std::cout<<"Vector3 size"<<sizeof(Vector3<float>)<<std::endl;
    }
    
    
    Renderer3D::~Renderer3D()
    {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    void Renderer3D::init()
    {
        SDL_Init(SDL_INIT_VIDEO);
        //TTF_Init();
        
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1 );
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        //glCullFace(GL_BACK);    // cull the back face
        //glEnable(GL_CULL_FACE); // enalbe face culling
        //glEnable(GL_DEPTH_TEST); //
        //glEnable(GL_FRAMEBUFFER_SRGB);  // auto gamma correction
        
    }
    
    void Renderer3D::Clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    }
    
    void Renderer3D::SwapBuffers()
    {
        SDL_GL_SwapWindow(window);
    }
    
    void Renderer3D::set_vsync(GLboolean value)
    {
        SDL_GL_SetSwapInterval(value);
    }

    const int number_of_meshes = 1;
    Mesh meshes[number_of_meshes];
    void Renderer3D::start()
    {

        LOG(LOGTYPE_GENERAL, std::string( (const char*)(glGetString(GL_VERSION))));//,",  ",std::string( (const char*)(glGetString(GL_EXTENSIONS)) ));

        Vertex vertices[4];
                    // pos,   color
                    // x,y,z, r,g,b,a
        vertices[0] = {-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f};
        vertices[1] = {0.5f,-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f};
        vertices[2] = { 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f};
        vertices[3] = {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f};
        GLuint element_array[] = {
            0, 1, 2,
            2, 3, 0
        };

        meshes[0].set_vertices(vertices, 4);
        meshes[0].set_indices(element_array, 6);

        upload_mesh(meshes[0]);
        if(make_shader_program("shaders"+PATH_SEP+"PassThrough.shader", shader_programs[SHADER_PASSTHROUGH]))
        {
            glUseProgram(shader_programs[SHADER_PASSTHROUGH]);
            //glDeleteProgram(shader_programs[SHADER_PASSTHROUGH]);
        }
    }


    void Renderer3D::update()
    {
        Clear(0,0,0,1);
        for(int i=0; i<number_of_meshes; i++)
            GL_CALL(
                //glDrawArrays(GL_TRIANGLES, 0, 6))
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        SwapBuffers();
    }

    void Renderer3D::end()
    {

    }

    bool Renderer3D::make_shader_program(const std::string& path, GLuint& shader_program)
    {
        std::string _source = read_file(get_resource_path(path).c_str());
        std::stringstream shader_source;
        shader_source << _source;
        
        std::string vert = "";
        std::string frag = "";
        std::string line = "";
        GLenum type = GL_VERTEX_SHADER;
        while(std::getline(shader_source, line))
        {
            //std::cout<<line<<std::endl;
            if(line.find("#vertex") != std::string::npos){
                type = GL_VERTEX_SHADER;

            }
            else if(line.find("#fragment")!= std::string::npos){
                type = GL_FRAGMENT_SHADER;
            }
            else
            {
                if(type == GL_VERTEX_SHADER)
                    vert += line+"\n";
                else if(type == GL_FRAGMENT_SHADER)
                    frag += line+"\n";
            }
        }

        shader_program = glCreateProgram();
        if(shader_program == 0)
        {
            std::cout<<"Couldn't create shader program"<<std::endl;
            return false;
        }

        GLuint v = make_shader( GL_VERTEX_SHADER, vert);
        GLuint f = make_shader( GL_FRAGMENT_SHADER, frag);
        if(v != -1 && f != -1)
        {
            glAttachShader(shader_program, v);
            glAttachShader(shader_program, f);
            glLinkProgram(shader_program);
            GLint program_linked;

            glGetProgramiv(shader_program, GL_LINK_STATUS, &program_linked);
            if (program_linked != GL_TRUE)
            {
                int length;
                glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
                GLchar* log = (GLchar*)alloca(length*sizeof(GLchar));
                glGetProgramInfoLog(shader_program, length, &length, log);
                LOG(LOGTYPE_ERROR, "Shader linking error\n",std::string(log));
            }
            else
            {   
                return true;
            }
        }
        return false;
    }

    GLuint Renderer3D::make_shader( GLenum type,  const std::string& source)
    {
        GLuint shader =  glCreateShader(type);
        if(shader == 0)
            std::cout<<"Couldn't create shader"<<std::endl;
            
        const char* _source = source.c_str();
        glShaderSource(shader,1, &(_source) , NULL);
        glCompileShader(shader);
        
        // check
        GLint compilation_status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);
        if(compilation_status != GL_TRUE)
        {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            GLchar* log = (GLchar*)alloca(length*sizeof(GLchar));
            glGetShaderInfoLog(shader, length, &length, log);
            LOG(LOGTYPE_ERROR, "Shader compilation error in ",(type==GL_VERTEX_SHADER?"Vertex":"Fragment"),"shader: \n"+std::string(log)+"\n");
            glDeleteShader(shader);
            shader = -1;
        }
        return shader;
        
    }

    void Renderer3D::upload_mesh(const Mesh& mesh)
    {
        // vertex buffer
        GLuint vertexBuffer;
        GL_CALL( 
            glGenBuffers(1, &vertexBuffer))
        GL_CALL( 
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer))
        GL_CALL( 
            glBufferData(GL_ARRAY_BUFFER, mesh.vertices_array_size, mesh.vertices, GL_STATIC_DRAW))
        ////////////////////

        // vertex array object
        GLuint vao;
        GL_CALL(
            glGenVertexArrays(1, &vao))
        GL_CALL(
            glBindVertexArray(vao))
        ///////////

        // index buffer
        GLuint index_buffer;        
        GL_CALL(
            glGenBuffers(1, &index_buffer))
        GL_CALL(
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer))
        GL_CALL(
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices_array_size, mesh.indices, GL_STATIC_DRAW))

        // attribute pointer position
        GL_CALL(
            glEnableVertexAttribArray(AttributeIndex::ATTRIB_POSITION))
        GL_CALL(
            glVertexAttribPointer(AttributeIndex::ATTRIB_POSITION, ATTRIB_POSITION_LENGTH, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)ATTRIB_POSITION_OFFSET))
        
        //GL_CALL(
        //    glDisableVertexAttribArray(AttributeIndex::ATTRIB_POSITION))

        // attribute pointer color
        GL_CALL(
            glEnableVertexAttribArray(AttributeIndex::ATTRIB_COLOR))
        GL_CALL(
            glVertexAttribPointer(AttributeIndex::ATTRIB_COLOR, ATTRIB_COLOR_LENGTH, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)ATTRIB_COLOR_OFFSET))
        //GL_CALL(
        //    glDisableVertexAttribArray(AttributeIndex::ATTRIB_COLOR))

    }
}
