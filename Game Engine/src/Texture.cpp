#include "Texture.hpp"

namespace PrEngine
{
        
    std::unordered_map<std::string, Texture*> texture_library;
    std::unordered_map<std::string, stbi_uc*> texture_data_library;

    int Texture::texture_create_status;
    Texture::Texture(const char* path)
    {
        texture_create_status = 0;
        stbi_set_flip_vertically_on_load(true);
        if(texture_data_library.count(path) > 0)
            data = texture_data_library[path];
        else
        {
            data = stbi_load(path,&width, &height, &no_of_channels, 0);
            if(data!=nullptr)
                texture_data_library[path] = data;

        }


        if(data == NULL){
            LOG(LOGTYPE_ERROR, "Couldn't create texture");
        }
        else
        {
            LOG(LOGTYPE_GENERAL, "Image ",std::string(path)," loaded");

            GL_CALL(glGenTextures(1, &id))
            GL_CALL(glBindTexture(GL_TEXTURE_2D, id))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT))
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT))
            
            GLenum type = GL_RGBA;
            switch(no_of_channels)
            {
                case 1:type = GL_R;break;
                case 2:type = GL_RG;break;
                case 3:type = GL_RGB;break;
                case 4:type = GL_RGBA;break;
            }
            LOG(LOGTYPE_GENERAL, "Number of channels ", std::to_string(type));
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, type, GL_UNSIGNED_BYTE, data))
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0))
            texture_create_status = 1;
        }
    }

    Texture::~Texture()
    {
        Unbind();
        GL_CALL(
            glDeleteTextures(1, &id))
        //if(data != NULL)
        //    stbi_image_free(data);
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

    void delete_texture_from_library()
    {
        
    }
}
