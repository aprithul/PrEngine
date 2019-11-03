//
//  Display.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//
#include "Renderer3D.hpp"

namespace Pringine {
    
    VertexArray::VertexArray()
    {
        GL_CALL(
            glGenVertexArrays(1, &id))
        
    }
    VertexArray::~VertexArray()
    {
        GL_CALL(
            glDeleteVertexArrays(1, &id))
    }

    void VertexArray::Bind()
    {
        GL_CALL(
            glBindVertexArray(id))
    }

    void VertexArray::Unbind()
    {
        GL_CALL(
            glBindVertexArray(0))
    }

    VertexBuffer::VertexBuffer(const Vertex* vertices, GLuint size)
    {
        GL_CALL( 
            glGenBuffers(1, &id))
        Bind(); 
        GL_CALL( 
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW))
        Unbind();
    }

    VertexBuffer::~VertexBuffer()
    {
        GL_CALL( 
            glDeleteBuffers(1, &id));
    }

    void VertexBuffer::Bind()
    {
        GL_CALL(
            glBindBuffer(GL_ARRAY_BUFFER, id));
    }

    void VertexBuffer::Unbind()
    {
        GL_CALL(
            glBindBuffer(GL_ARRAY_BUFFER, 0));
    }


    IndexBuffer::IndexBuffer(const GLuint* indices, GLuint indices_size, GLsizei count)
    {
        this->count = count;
        GL_CALL( 
            glGenBuffers(1, &id));
        Bind();
        GL_CALL(
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW))
        Unbind();
    }

    IndexBuffer::~IndexBuffer()
    {
        GL_CALL( 
            glDeleteBuffers(1, &id));

    }

    void IndexBuffer::Bind()
    {
        GL_CALL(
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    }

    void IndexBuffer::Unbind()
    {
        GL_CALL(
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    Graphics3D::Graphics3D(const Vertex* vertices, GLuint vertices_size, const GLuint* indices, 
                                    GLuint indices_size, GLsizei indices_count, Material material, 
                                    Texture texture, VertexLayout layout)
                                :vbo(vertices,vertices_size),ibo(indices,indices_size,indices_count),
                                    material(material),texture(texture),layout(layout),Component(COMP_GRAPHICS_3D)
    {
        vao.Bind();
        vbo.Bind();
        for(std::vector<VertexAttribute>::iterator attr = layout.vertex_attributes.begin(); attr !=  layout.vertex_attributes.end(); attr++)
        {
            GL_CALL(
                glEnableVertexAttribArray( attr->index))
            GL_CALL(
                glVertexAttribPointer(attr->index, attr->count, attr->type, attr->normalized, layout.stride, (void*)attr->offset))
        }
        vbo.Unbind();
        vao.Unbind();

        _model = Matrix4x4<float>::identity();
        model = &_model;
        _normal = Matrix4x4<float>::identity();
        model = &_normal;
    }

    Graphics3D::~Graphics3D()
    {
        std::cout<<"DESTROYED"<<std::endl;   
    }

    Texture::Texture(const char* path)
    {
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(path,&width, &height, &no_of_channels, 0);
        if(data == NULL)
            LOG(LOGTYPE_ERROR, "Image ",std::string(path)," loading failed");
        else
        {
            GL_CALL(glGenTextures(1, &id))
            GL_CALL(glBindTexture(GL_TEXTURE_2D, id))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER))
            
            GLenum type = GL_RGBA;
            switch(no_of_channels)
            {
                case 1:type = GL_R;break;
                case 2:type = GL_RG;break;
                case 3:type = GL_RGB;break;
                case 4:type = GL_RGBA;break;
            }
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, type, GL_UNSIGNED_BYTE, data))
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0))
        }
    }

    Texture::~Texture()
    {
        if(data != NULL)
            stbi_image_free(data);
    }

    void Texture::Bind(int slot)
    {
        GL_CALL(
            glActiveTexture(GL_TEXTURE0 + slot))
        GL_CALL(
            glBindTexture(GL_TEXTURE_2D, id))
    }

    void Texture::Unbind()
    {
        GL_CALL(
            glBindTexture(GL_TEXTURE_2D, 0))
    }

    Material::Material(const std::string& path)
    {
        this->source_file_path = std::string(path);
        make_shader_program(this->source_file_path);
        GL_CALL(
            glUseProgram(shader_program))
    }

    Material::~Material()
    {
        GL_CALL(
            glDeleteProgram(shader_program))
    }

    void Material::load_uniform_location(const char* uniform)
    {
        GLint loc = -1;
        GL_CALL(
            loc = glGetUniformLocation(shader_program, uniform))
        
        if(loc != -1)
            uniform_locations[uniform] = loc;
    }

    bool Material::make_shader_program(const std::string& path)
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
                
                glDetachShader(shader_program, v);
                glDeleteShader(v);
                glDetachShader(shader_program, f);
                glDeleteShader(f);       
            }
            else
            {   
                glDetachShader(shader_program, v);
                glDeleteShader(v);
                glDetachShader(shader_program, f);
                glDeleteShader(f);
                return true;
            }
        }
        return false;
    }

    GLuint Material::make_shader( GLenum type,  const std::string& source)
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



    VertexLayout::VertexLayout()
    {
        stride = sizeof(Vertex);
    }

    VertexAttribute::VertexAttribute(GLuint index, GLuint count, int type, GLboolean normalized)
    {
        this->index = index;
        this->count = count;
        this->type  = type;
        this->normalized = normalized;
        this->offset = 0;
        this->size = 0;
    }

    void VertexLayout::add_attribute(VertexAttribute& attribute)
    {
        if(vertex_attributes.size() >= 1)
        {
            attribute.offset = (vertex_attributes.back().size + vertex_attributes.back().offset);
        }

        switch (attribute.type)
        {
        case GL_FLOAT:
            attribute.size = (sizeof(GLfloat) * attribute.count);
            break;
        case GL_UNSIGNED_INT:
            attribute.size = (sizeof(GLuint) * attribute.count);
            break;
        case GL_INT:
            attribute.size = (sizeof(GLint) * attribute.count);
            break;
            //....
            //....
            //....
        default:
            LOG(LOGTYPE_ERROR, "Attribute type not found");
            break;
        }

        //stride += attribute.size;
        vertex_attributes.push_back(attribute);

    }









    Renderer3D::Renderer3D(int width, int height, std::string title):Module("Opengl Renderer", 4)
    {
        this->width = width;
        this->height = height;
        this->title = title;
        light_direction = Vector3<float>(.5f,-.2f,1.f).normalize();
        // initialize sdl and opengl related settings for graphics
        init();
        
        // create window
        window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);
        // create the openGL context from the window  that was created
        glContext = SDL_GL_CreateContext(window);

        GL_CALL(glFrontFace(GL_CCW))     // points are gonna get supplid in clockwise order
        GL_CALL(glEnable(GL_CULL_FACE))
        GL_CALL(glEnable(GL_BLEND))
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
        GL_CALL(glEnable(GL_DEPTH_TEST))
        GL_CALL(glDepthFunc(GL_LESS))


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

    Matrix4x4<float> projection;
    void Renderer3D::start()
    {
        projection = Matrix4x4<float>::ortho(-1.f, 1.f, -0.75f, 0.75f,-1.f,1.f);
        //projection = Matrix4x4<float>::ortho(-1.f, 1.f, -1.f, 1.f,-1.f,1.f);

        
    }

    
    void Renderer3D::update()
    {
        Clear(0,0,0,1);
        for(std::vector<Graphics3D*>::iterator it = graphics3d_list.begin(); it != graphics3d_list.end(); it++ )
        {
            (*it)->vao.Bind();
            (*it)->ibo.Bind();
            Matrix4x4<float> mvp = (projection) * (*((*it)->model)) ;
            //GL_CALL(
            //    glUniform1f((*it)->material.uniform_locations["u_red"], 1.f))
            //(*it)->texture.Bind(0);
            //GL_CALL(
            //    glUniform1i((*it)->material.uniform_locations["u_sampler2d"], 0))
            GL_CALL(
                glUniformMatrix4fv((*it)->material.uniform_locations["u_MVP"],1, GL_TRUE, mvp.data))
            GL_CALL(
                glUniformMatrix4fv((*it)->material.uniform_locations["u_Normal_M"],1, GL_TRUE, ((*it))->normal->data ))
            GL_CALL(
                glUniform3f((*it)->material.uniform_locations["u_Dir_Light"],light_direction.x, light_direction.y, light_direction.z))
            
            GL_CALL(
                glDrawElements(GL_TRIANGLES, (*it)->ibo.count, GL_UNSIGNED_INT, nullptr));
            
            (*it)->vao.Unbind();
            (*it)->ibo.Unbind();
        }
        SwapBuffers();
    }

    void Renderer3D::end()
    {

    }

    Graphics3D* Renderer3D::generate_graphics3d(const char* base_dir, const char* file_name)
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file_name, base_dir);
        if (!warn.empty())
            LOG(LOGTYPE_WARNING, warn);
        if (!err.empty())
            LOG(LOGTYPE_ERROR, err);
        if (!ret) {
            LOG(LOGTYPE_ERROR,"Loading ", std::string(file_name)," failed");
            return nullptr;
        }   
        else
            LOG(LOGTYPE_GENERAL, "Successfully loaded mesh ", std::string(file_name));

        int index_count = 0;
        for(int i=0; i<shapes.size(); i++)
            index_count += shapes[i].mesh.indices.size();
        GLuint* indices = new GLuint[index_count];
        for(int j=0; j<shapes.size(); j++)
            for(int i=0; i<shapes[j].mesh.indices.size(); i++)
                indices[ (j*shapes.size())+i] = shapes[j].mesh.indices[i].vertex_index;

        int vertex_count = attrib.vertices.size()/3;
        Vertex* vertices = new Vertex[vertex_count];
        for(int i=0; i < vertex_count; i++)
        {
            vertices[i].p_x = attrib.vertices[ (i*3)+0 ];
            vertices[i].p_y = attrib.vertices[ (i*3)+1 ];
            vertices[i].p_z = attrib.vertices[ (i*3)+2 ];
            vertices[i].c_r = 1.0f;
            vertices[i].c_g = 1.0f;
            vertices[i].c_b = 1.0f;
            vertices[i].c_a = 1.0f;
            vertices[i].n_x = attrib.normals[ (i*3)+0 ];
            vertices[i].n_y = attrib.normals[ (i*3)+1 ];
            vertices[i].n_z = attrib.normals[ (i*3)+2 ];
            vertices[i].u = 0.f;
            vertices[i].v = 1.f;
        }

        Mesh* mesh = new Mesh();
        mesh->set_indices(indices, index_count);
        mesh->set_vertices(vertices, vertex_count);
        
        delete indices;
        delete vertices;

        /*for(int i=0; i<mesh->vertex_count; i++)
            std::cout<<mesh->vertices[i].p_x<<","<<mesh->vertices[i].p_y<<","<<mesh->vertices[i].p_z<<std::endl;
        for(int i=0; i<mesh->index_count; i++)
            std::cout<<mesh->vertex_indices[i]<<std::endl;
*/
        VertexLayout layout;
        VertexAttribute attribute_0(0,3,GL_FLOAT,GL_FALSE);
        VertexAttribute attribute_1(1,4,GL_FLOAT,GL_FALSE);
        VertexAttribute attribute_2(2,3,GL_FLOAT,GL_FALSE);
        layout.add_attribute(attribute_0);
        layout.add_attribute(attribute_1);
        layout.add_attribute(attribute_2);

        Graphics3D* graphics = new Graphics3D(mesh->vertices, mesh->vertices_array_size, 
                                    mesh->vertex_indices, mesh->indices_array_size, mesh->index_count,
                                        Material("shaders"+PATH_SEP+"PassThrough.shader"), 
                                        Texture(get_resource_path("cube.png").c_str()),
                                        layout);
        //graphics->material.load_uniform_location("u_red");
        //graphics->material.load_uniform_location("u_sampler2d");
        graphics->material.load_uniform_location("u_MVP");
        graphics->material.load_uniform_location("u_Normal_M");
        graphics->material.load_uniform_location("u_Dir_Light");

        graphics3d_list.push_back(graphics);

        return graphics;

        //std::copy(shapes[0].mesh.indices.begin() ,shapes[0].mesh.indices.end(), mesh->indices); 
        //mesh->index_count = shapes[0].mesh.indices.size();

        //LOG(LOGTYPE_GENERAL, std::to_string(mesh->indices[mesh->index_count-1]));
        //LOG(LOGTYPE_GENERAL, std::to_string(mesh->index_count));
    }


    void Renderer3D::upload_mesh(const Mesh& mesh)
    {
        
    }
}
