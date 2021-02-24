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

    struct Shader
    {
        GLuint id;
        std::unordered_map<std::string, std::pair<std::string, GLuint>> uniform_locations;
    };

    struct Material
    {
        Material(const std::string& shader_path, const std::string& diffuse_tex_path,const std::string& name);
        Material(const std::string& shader_path, const std::string& diffuse_tex_path, TextureCubeMap& env_map, const std::string& name);
        Material(const std::string& shader_path, const std::vector<std::string>& cubemap_tex_path,const std::string& name);
        //void Generate(const std::string& shader_path, const std::string& diffuse_tex_path, const std::string& name);
        void Delete();
        ~Material();
        Shader shader_program;
        std::string source_file_path;
        Texture* diffuse_texture;
        TextureCubeMap* environment_map_texture;
        void Bind();
        void Unbind();
        static bool make_shader_program(const std::string& path, Shader& shader_program);
        static GLuint make_shader(GLenum type,  const std::string& source);
        static void load_uniform_location(const std::string& uniform, const std::string& type, Shader& shader_program);
        static void parse_shader(const std::string& source, Shader& shader_program);
        Vector2<float> tiling;
        Vector2<float> panning;
    };
    extern std::unordered_map<std::string, Material*> material_library;
    extern std::unordered_map<std::string, Shader> shader_library;

} // namespace PrEngine

#endif