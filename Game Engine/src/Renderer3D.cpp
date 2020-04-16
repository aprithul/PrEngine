//
//  Display.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//
#include "Renderer3D.hpp"

namespace Pringine {
    
    Renderer3D::Renderer3D(int width, int height, std::string title):Module("Opengl Renderer", 20)
    {
        this->width = width;
        this->height = height;
        this->title = title;
        //light_direction = 
        // initialize sdl and opengl related settings for graphics
        init();
        
        // create window
        window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
        // create the openGL context from the window  that was created
        glContext = SDL_GL_CreateContext(window);

        GL_CALL(glFrontFace(GL_CCW))     // points are gonna get supplid in clockwise order
        GL_CALL(glDisable(GL_CULL_FACE))
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

        std::cout<<"Loading default texture"<<std::endl;
        Texture* _tex = new Texture(get_resource_path("default.jpg").c_str());
        texture_library[get_resource_path("default.jpg")] = _tex;
        //data = stbi_load( get_resource_path("default.jpg").c_str() ,&width, &height, &no_of_channels, 0);


        /// create render layers
        Camera3D* camera = (Camera3D*)entity_management_system->get_entity(ENTITY_TYPE_CAMERA);
        long camera_handle = -1;
        if(camera == nullptr){
            LOG(LOGTYPE_ERROR, "No camera found");
            return;
        }
        else
            camera_handle = camera->id;
        std::cout<<"cam handle "<<camera_handle<<std::endl;

        GeometryLayer* geometry_layer = new GeometryLayer(camera_handle);
        render_layers.push_back(geometry_layer);

        GuiLayer* gui_layer = new GuiLayer(window, &glContext);
        render_layers.push_back(gui_layer);
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
    GLuint fbo;
    void Renderer3D::start()
    {
        //projection = Matrix4x4<float>::ortho(-1.f, 1.f, -0.75f, 0.75f,-1.f,1.f);
        //projection = Matrix4x4<float>::perspective(1.f,-1.f,2.f,1.5f);
        //projection = Matrix4x4<float>::perspective(0.f,1.f,4.f,3.f, 45.f);
        //view_matrix = Matrix4x4<float>::identity();

        //SDL_ShowCursor(0);
        //if(SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
        //    LOG(LOGTYPE_ERROR, "Failed to set relative mouse mode");
        for(std::vector<RenderLayer*>::iterator it=render_layers.begin(); it!=render_layers.end(); it++)
            (*it)->start();

/*
        GLuint col_buf;
        glGenRenderbuffers(1, &col_buf);
        glBindRenderbuffer(GL_RENDERBUFFER, col_buf);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
        
        GLuint dep_buf;
        glGenRenderbuffers(1, &dep_buf);
        glBindRenderbuffer(GL_RENDERBUFFER, dep_buf);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        
        GL_CALL(glGenFramebuffers(1, &fbo))
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, col_buf);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dep_buf);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
*/

    }

    bool my_tool_active = true;

    void Renderer3D::update()
    {
        Clear(1,1,1,1);

        for(std::vector<RenderLayer*>::iterator layer=render_layers.begin(); layer!=render_layers.end(); layer++)
            (*layer)->update();
        SwapBuffers();
    }

    void Renderer3D::end()
    {
        for(std::vector<RenderLayer*>::iterator it=render_layers.begin(); it!=render_layers.end(); it++)
            (*it)->end();
    }

    static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]) {
        float v10[3];
        v10[0] = v1[0] - v0[0];
        v10[1] = v1[1] - v0[1];
        v10[2] = v1[2] - v0[2];

        float v20[3];
        v20[0] = v2[0] - v0[0];
        v20[1] = v2[1] - v0[1];
        v20[2] = v2[2] - v0[2];

        N[0] = v20[1] * v10[2] - v20[2] * v10[1];
        N[1] = v20[2] * v10[0] - v20[0] * v10[2];
        N[2] = v20[0] * v10[1] - v20[1] * v10[0];

        float len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
        if (len2 > 0.0f) {
            float len = sqrtf(len2);

            N[0] /= len;
            N[1] /= len;
            N[2] /= len;
        }
    }

    Graphics3D* Renderer3D::generate_graphics3d(const char* base_dir, const char* file_name, const char* texture_file_path)
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

        Graphics3D* graphics = new Graphics3D();                
        VertexLayout layout;
        VertexAttribute attribute_0(0,3,GL_FLOAT,GL_FALSE);
        VertexAttribute attribute_1(1,4,GL_FLOAT,GL_FALSE);
        VertexAttribute attribute_2(2,3,GL_FLOAT,GL_FALSE);
        VertexAttribute attribute_3(3,2,GL_FLOAT,GL_FALSE);
        layout.add_attribute(attribute_0);
        layout.add_attribute(attribute_1);
        layout.add_attribute(attribute_2);
        layout.add_attribute(attribute_3);
        std::cout<<"1"<<std::endl;
        /*
        std::cout<<"ind size: "<<shapes[0].mesh.indices.size()<<std::endl;
        std::cout<<"vertices size: "<<attrib.vertices.size()<<std::endl;
        for( int i=0; i<shapes[0].mesh.indices.size(); i++)
        {
            std::cout<<"ind: "<<shapes[0].mesh.indices[i].vertex_index<<std::endl;
            std::cout<<" v1: "<< attrib.vertices[shapes[0].mesh.indices[i].vertex_index + 0];
            std::cout<<" v2: "<< attrib.vertices[shapes[0].mesh.indices[i].vertex_index + 1];
            std::cout<<" v3: "<< attrib.vertices[shapes[0].mesh.indices[i].vertex_index + 2]<<std::endl;
            
        }*/

        float bmin[3], bmax[3];
        for (size_t s = 0; s < shapes.size(); s++) 
        {
            std::vector<GLuint> indices;
            std::vector<Vertex> buffer;
            /*for (size_t f = 0; f < shapes[s].mesh.indices.size() / 3; f++) 
            {
                tinyobj::index_t idx0 = shapes[s].mesh.indices[3 * f + 0];
                tinyobj::index_t idx1 = shapes[s].mesh.indices[3 * f + 1];
                tinyobj::index_t idx2 = shapes[s].mesh.indices[3 * f + 2];

                float tc[3][2];
                if (attrib.texcoords.size() > 0) 
                {
                    if ((idx0.texcoord_index < 0) || (idx1.texcoord_index < 0) ||
                        (idx2.texcoord_index < 0)) 
                    {
                        // face does not contain valid uv index.
                        tc[0][0] = 0.0f;
                        tc[0][1] = 0.0f;
                        tc[1][0] = 0.0f;
                        tc[1][1] = 0.0f;
                        tc[2][0] = 0.0f;
                        tc[2][1] = 0.0f;
                    } 
                    else 
                    {
                        assert(attrib.texcoords.size() >
                            size_t(2 * idx0.texcoord_index + 1));
                        assert(attrib.texcoords.size() >
                            size_t(2 * idx1.texcoord_index + 1));
                        assert(attrib.texcoords.size() >
                            size_t(2 * idx2.texcoord_index + 1));

                        // Flip Y coord.
                        tc[0][0] = attrib.texcoords[2 * idx0.texcoord_index];
                        tc[0][1] = attrib.texcoords[2 * idx0.texcoord_index + 1];
                        tc[1][0] = attrib.texcoords[2 * idx1.texcoord_index];
                        tc[1][1] = attrib.texcoords[2 * idx1.texcoord_index + 1];
                        tc[2][0] = attrib.texcoords[2 * idx2.texcoord_index];
                        tc[2][1] = attrib.texcoords[2 * idx2.texcoord_index + 1];
                    }
                } 
                else 
                {
                    tc[0][0] = 0.0f;
                    tc[0][1] = 0.0f;
                    tc[1][0] = 0.0f;
                    tc[1][1] = 0.0f;
                    tc[2][0] = 0.0f;
                    tc[2][1] = 0.0f;
                }

                float v[3][3];
                for (int k = 0; k < 3; k++) 
                {
                    int f0 = idx0.vertex_index;
                    int f1 = idx1.vertex_index;
                    int f2 = idx2.vertex_index;
                    assert(f0 >= 0);
                    assert(f1 >= 0);
                    assert(f2 >= 0);

                    v[0][k] = attrib.vertices[3 * f0 + k];
                    v[1][k] = attrib.vertices[3 * f1 + k];
                    v[2][k] = attrib.vertices[3 * f2 + k];
                    bmin[k] = std::min(v[0][k], bmin[k]);
                    bmin[k] = std::min(v[1][k], bmin[k]);
                    bmin[k] = std::min(v[2][k], bmin[k]);
                    bmax[k] = std::max(v[0][k], bmax[k]);
                    bmax[k] = std::max(v[1][k], bmax[k]);
                    bmax[k] = std::max(v[2][k], bmax[k]);
                }

                float n[3][3];
                {
                    bool invalid_normal_index = false;
                    if (attrib.normals.size() > 0) 
                    {
                        int nf0 = idx0.normal_index;
                        int nf1 = idx1.normal_index;
                        int nf2 = idx2.normal_index;

                        if ((nf0 < 0) || (nf1 < 0) || (nf2 < 0)) 
                        {
                            // normal index is missing from this face.
                            invalid_normal_index = true;
                        } 
                        else
                        {
                            for (int k = 0; k < 3; k++) 
                            {
                                assert(size_t(3 * nf0 + k) < attrib.normals.size());
                                assert(size_t(3 * nf1 + k) < attrib.normals.size());
                                assert(size_t(3 * nf2 + k) < attrib.normals.size());
                                n[0][k] = attrib.normals[3 * nf0 + k];
                                n[1][k] = attrib.normals[3 * nf1 + k];
                                n[2][k] = attrib.normals[3 * nf2 + k];
                            }
                        }
                    } 
                    else 
                    {
                        invalid_normal_index = true;
                    }

                    if (invalid_normal_index) 
                    {
                        // compute geometric normal
                        CalcNormal(n[0], v[0], v[1], v[2]);
                        n[1][0] = n[0][0];
                        n[1][1] = n[0][1];
                        n[1][2] = n[0][2];
                        n[2][0] = n[0][0];
                        n[2][1] = n[0][1];
                        n[2][2] = n[0][2];
                    }
                }

                for (int k = 0; k < 3; k++) 
                {
                    Vertex vert;
                    vert.p_x = (v[k][0]);
                    vert.p_y = (v[k][1]);
                    vert.p_z = (v[k][2]);
                    vert.n_x = (n[k][0]);
                    vert.n_y = (n[k][1]);
                    vert.n_z = (n[k][2]);
                    // Combine normal and diffuse to get color.
                    float normal_factor = 0.2;
                    float diffuse_factor = 1 - normal_factor;
                    float c[3] = {1.f,1.f,1.f};
                    float len2 = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
                    if (len2 > 0.0f) 
                    {
                        float len = sqrtf(len2);
                        c[0] /= len;
                        c[1] /= len;
                        c[2] /= len;
                    }

                    vert.c_r = (c[0] * 0.5 + 0.5);
                    vert.c_g = (c[1] * 0.5 + 0.5);
                    vert.c_b = (c[2] * 0.5 + 0.5);
                    vert.c_a = 1.f;

                    vert.u = (tc[k][0]);
                    vert.v = (tc[k][1]);
                    buffer.push_back(vert);
                }
            }
*/


            


            std::unordered_map<std::string, GLuint> indices_map;
            GLuint index = 0;
        std::cout<<"2: "<<shapes.size()<<std::endl;
            
            for(int i=0; i< shapes[s].mesh.indices.size(); i++)
            {
                std::string key =   
                            std::to_string(shapes[s].mesh.indices[i].normal_index).append(
                            std::to_string(shapes[s].mesh.indices[i].texcoord_index)).append(
                            std::to_string(shapes[s].mesh.indices[i].vertex_index));

                std::unordered_map<std::string, GLuint>::iterator item;
                if( (item = indices_map.find(key)) != indices_map.end() )
                {

                    tinyobj::index_t ind = shapes[s].mesh.indices[i];
                    //std::cout<<attrib.vertices[ind.vertex_index+0]<<","<<attrib.vertices[ind.vertex_index+1]<<","<<attrib.vertices[ind.vertex_index+2]<<std::endl;
                    indices.push_back(item->second);
                }
                else
                {

                    tinyobj::index_t ind = shapes[s].mesh.indices[i];
                    
                    Vertex vert;
                    vert.p_x = attrib.vertices[(ind.vertex_index*3)+0];
                    vert.p_y = attrib.vertices[(ind.vertex_index*3)+1];
                    vert.p_z = attrib.vertices[(ind.vertex_index*3)+2];
                    vert.c_r = 1.f;
                    vert.c_g = 1.f;
                    vert.c_b = 1.f;
                    vert.c_a = 1.f;
                    vert.n_x = attrib.normals[ (ind.normal_index*3) + 0];
                    vert.n_y = attrib.normals[ (ind.normal_index*3) + 1];
                    vert.n_z = attrib.normals[ (ind.normal_index*3) + 2];
                    vert.u   = attrib.texcoords[ (ind.texcoord_index*2) +0];
                    vert.v   = attrib.texcoords[ (ind.texcoord_index*2) +1];
                    buffer.push_back(vert);

                    indices_map[key] = index;
                    //std::cout<<ind.vertex_index<<"//"<<ind.normal_index<<<<":"<<attrib.vertices[ind.vertex_index+0]<<","<<attrib.vertices[ind.vertex_index+1]<<","<<attrib.vertices[ind.vertex_index+2]<<std::endl;

                    indices.push_back(index);
                    index++;
                }
            }   

            std::cout<<"Buffer: "<<buffer.size()<<std::endl;
            std::cout<<"Indices: "<<indices.size()<<std::endl;


            /*for(int i=0; i<indices.size(); i++)
                std::cout<<indices[i]<<std::endl;
            for(int i=0; i<buffer.size(); i++)
                std::cout<<buffer[i].p_x<<","<<buffer[i].p_y<<","<<buffer[i].p_z<<std::endl;*/
            //std::cout<<indices[i]<<" : "<<buffer[i].p_x<<","<<buffer[i].p_y<<","<<buffer[i].p_z<<std::endl;

            //IndexBuffer ib( &(shapes[s].mesh.indices[0]), )
            //for(int i=0; i<buffer.size(); i++)
            //    std::cout<< ((&buffer[0])+i)->p_x<<","<<((&buffer[0])+i)->p_y<<","<<((&buffer[0])+i)->p_z <<std::endl;

            GraphicsElement g_element;

            graphics->elements.push_back(g_element);
            graphics->elements.back().material.Generate("shaders"+PATH_SEP+"PassThrough.shader", std::string(texture_file_path));
            graphics->elements.back().material.load_uniform_location("u_sampler2d");
            graphics->elements.back().material.load_uniform_location("u_MVP");
            graphics->elements.back().material.load_uniform_location("u_Normal_M");
            graphics->elements.back().material.load_uniform_location("u_Dir_Light");
            graphics->elements.back().material.load_uniform_location("u_Tiling");
            graphics->elements.back().material.load_uniform_location("u_Panning");





            graphics->elements.back().ibo.Generate( &indices[0], indices.size()*sizeof(GLuint), indices.size());
            graphics->elements.back().vbo.Generate(&buffer[0], buffer.size()*sizeof(Vertex));
            graphics->elements.back().vao.Generate();
            graphics->elements.back().layout = layout;
            graphics->elements.back().num_of_triangles = (buffer.size()/3);
        }

        for(int i=0; i<graphics->elements.size(); i++)
        {
            graphics->elements[i].vao.Bind();
            graphics->elements[i].vbo.Bind();
            for(std::vector<VertexAttribute>::iterator attr = graphics->elements[i].layout.vertex_attributes.begin(); attr !=  graphics->elements[i].layout.vertex_attributes.end(); attr++)
            {
                GL_CALL(
                    glEnableVertexAttribArray( attr->index))
                GL_CALL(
                    glVertexAttribPointer(attr->index, attr->count, attr->type, attr->normalized, layout.stride, (void*)attr->offset))
            }
            graphics->elements[i].vbo.Unbind();
            graphics->elements[i].vao.Unbind();
        }
        /*for(std::vector<RenderLayer*>::iterator it=render_layers.begin(); it!=render_layers.end(); it++)
        {
                if((*it)->name == "Geometry"){
                    ((GeometryLayer*)(*it))->graphics3d_list.push_back(graphics);
                    std::cout<<"added graphics"<<std::endl;
                }
                std::cout<<"name : "<<(*it)->name<<std::endl;
        }*/

        GeometryLayer* geom_layer = (GeometryLayer*)get_layer("Geometry");

        if(geom_layer != nullptr)
            geom_layer->graphics3d_list.push_back(graphics);

        std::cout<<"returning"<<std::endl;
        return graphics;

    }

    RenderLayer* Renderer3D::get_layer(const std::string& layer_name)
    {
        for(std::vector<RenderLayer*>::iterator it=render_layers.begin(); it!=render_layers.end(); it++)
        {
                if((*it)->name == layer_name){
                    return (*it);
                }
        }
        return nullptr;
    }

/*
    void Renderer3D::upload_mesh(const Mesh& mesh)
    {
        
    }*/
}