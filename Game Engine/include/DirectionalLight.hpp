#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Entity.hpp"
#include "Vector3.hpp"
#include "Matrix4x4f.hpp"
#include "Material.hpp"

namespace PrEngine
{
    #define SHADOW_MAP_WIDTH 4096
    #define SHADOW_MAP_HEIGHT 4096

    class DirectionalLight : public Component
    {
        public:
            DirectionalLight(float specular, float ambient);
            ~DirectionalLight() override;
            float specular;
            float ambient;
            Shader light_shader;
            Matrix4x4<float> projection;
            const Matrix4x4<float>* view;
            void BindShadowmapBuffer();
            void UnbindShadowmapBuffer();
            GLuint shadow_map_texture;
        
        private:
            GLuint shadow_map_fbo;
    };
}


#endif