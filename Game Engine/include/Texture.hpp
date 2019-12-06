#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GlAssert.hpp"
#include <unordered_map>
#include "../Vendor/include/stb_image.h"
#include "Logger.hpp"

namespace Pringine
{
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

    extern std::unordered_map<std::string, stbi_uc*> texture_data_library;
    extern std::unordered_map<std::string, Texture*> texture_library;
}
#endif