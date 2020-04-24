#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "GlAssert.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include <sstream>
#include <string>
#include <GL/glew.h>

namespace PrEngine
{

    struct Material
    {
        Material(const std::string& shader_path, const std::string& diffuse_tex_path,const std::string& name);
        Material(const std::string& shader_path, const std::vector<std::string>& cubemap_tex_path,const std::string& name);
        //void Generate(const std::string& shader_path, const std::string& diffuse_tex_path, const std::string& name);
        void Delete();
        ~Material();
        GLuint shader_program;
        std::string source_file_path;
        std::unordered_map<std::string, GLint> uniform_locations;
        Texture* diffuse_texture;
        void Bind();
        void Unbind();
        bool make_shader_program(const std::string& path);
        GLuint make_shader(GLenum type,  const std::string& source);
        void load_uniform_location(std::string uniform);
        Vector2<float> tiling;
        Vector2<float> panning;
    };
    extern std::unordered_map<std::string, Material*> material_library;
    extern std::unordered_map<std::string, GLuint> shader_library;

} // namespace PrEngine

#endif