#include "DirectionalLight.hpp"

namespace PrEngine
{
    DirectionalLight::DirectionalLight(float _specular, float _ambient):Component(COMP_LIGHT)
    {
        this->specular = _specular;
        this->ambient = _ambient;
        
        // generate a render texture
        glGenTextures(1, &shadow_map_texture);  
        glActiveTexture(GL_TEXTURE0+2);
        glBindTexture(GL_TEXTURE_2D, shadow_map_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
        
        // use texture as depth buffer
        glGenFramebuffers(1, &shadow_map_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, shadow_map_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_map_texture,0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);  
        /*glGenFramebuffers(1, &shadow_map_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, shadow_map_fbo);   
        glGenTextures(1, &shadow_map_texture);
        glBindTexture(GL_TEXTURE_2D, shadow_map_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);*/

// attach it to currently bound framebuffer object
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadow_map_texture, 0);  
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
glBindFramebuffer(GL_FRAMEBUFFER, 0);  

        //make shader program
        Material::make_shader_program( std::string("shaders")+PATH_SEP+"PassThrough.shader", light_shader);
        this->projection = Matrix4x4<float>::ortho(-8, 8, -4.5f, 4.5f, -10, 10);

    }

    DirectionalLight::~DirectionalLight()
    {

    }

    void DirectionalLight::BindShadowmapBuffer()
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, shadow_map_fbo))
        GL_CALL(glUseProgram(light_shader.id))

    }

    void DirectionalLight::UnbindShadowmapBuffer()
    {
        GL_CALL(glUseProgram(0))
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0))
    }

}