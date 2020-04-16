#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "GlAssert.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include <sstream>
#include <string>
#include <GL/glew.h>

namespace Pringine
{

    struct Material
    {
        Material();
        void Generate(const std::string& shader_path, const std::string& diffuse_tex_path);
        void Delete();
        ~Material();
        GLuint shader_program;
        std::string source_file_path;
        std::unordered_map<std::string, GLint> uniform_locations;
        Texture* diffuse_texture;
        bool make_shader_program(const std::string& path);
        GLuint make_shader(GLenum type,  const std::string& source);
        void load_uniform_location(std::string uniform);
        Vector2<float> tiling;
        Vector2<float> panning;
    };

} // namespace Pringine

#endif