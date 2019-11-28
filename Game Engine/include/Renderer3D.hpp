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
#include "GlAssert.hpp"

#include "Material.hpp"
#include "Graphics3D.hpp"
#include "Module.hpp"
#include "RenderLayer.hpp"
#include "GeometryLayer.hpp"
#include <vector>

namespace Pringine {
    
    class Renderer3D : public Module
    {

    public:
        std::vector<RenderLayer*> render_layers;

        // display attributes
        int height;
        int width;
        std::string title;
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
        bool make_shader_program(const std::string& path, GLuint& shader_program);
        GLuint make_shader( GLenum type, const std::string& source);
        Graphics3D* generate_graphics3d(const char* base_dir, const char* file_name, const char* texture_file_path);
        //Matrix4x4<float> view_matrix;
        //Matrix4x4<float> projection;

        void start() override;
        void update() override;
        void end() override;
        // reference to the sdl window
        SDL_Window* window;
        // the opengl context used with the window
        SDL_GLContext glContext;
    };
}

#endif /* Display_h */