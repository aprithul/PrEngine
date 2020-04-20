#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GlAssert.hpp"
#include <unordered_map>
#include "../Vendor/include/stb_image.h"
#include "Logger.hpp"
#include <vector>
#include <string>

namespace PrEngine
{
    extern int texture_create_status;

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

    struct TextureCubeMap
    {

        GLuint id;
        int width;
        int height;
        int no_of_channels;
        stbi_uc* data;

        TextureCubeMap( const std::vector<std::string> paths);
        ~TextureCubeMap();
        void Bind(int slot);
        void Unbind();
    };

    void delete_texture_from_library(GLuint id);
    extern std::unordered_map<std::string, stbi_uc*> texture_data_library;
    extern std::unordered_map<std::string, Texture*> texture_library;
}
#endif