#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Entity.hpp"
#include "RendererModule.hpp"
#include "TimeModule.hpp"
#include "Transform.hpp"
#include <string>
namespace Pringine
{

    class Sprite : public Entity
    {
        public:
            Sprite(const std::string& graphics_file_name, const TextureSlicingParameters* slicing_param, Renderer2D& renderer2d, int num_of_animation_frames = 1, int pixel_to_world_scale = 100, int layer = 999);
            ~Sprite() override;
            Transform transform;
            Graphics graphics;
            Renderer2D& renderer2d;
            int pixel_to_world;
            SDL_FRect world_space_bounds;

            void set_layer(int layer);
            void set_animation(bool do_animate, int fps);
            void awake() override;
            void start() override;
            void update() override;
            void end() override;

        private:
            int renderer2d_id;
            double animation_accumulator;
            double animation_delta;
            bool do_animate;
            int layer;



    };

}

#endif