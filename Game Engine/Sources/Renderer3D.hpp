//
//  Display.h
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Display_h
#define Display_h

#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_ttf.h>
#include "Module.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include <sstream>

namespace Pringine {
    
    enum ShaderType
    {
        SHADER_PASSTHROUGH,
        SHADER_COUNT
    };

    class Renderer3D : public Module
    {
    public:
        // display attributes
        int height;
        int width;
        std::string title;
        
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
