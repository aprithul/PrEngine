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
            Sprite(const std::string& graphics_file_name, TextureSlicingParameters slicing_param, Renderer2D& renderer2d, int num_of_animation_frames = 1, int pixel_to_world_scale = 100);
            ~Sprite() override;
            Transform transform;
            Graphics graphics;
            Renderer2D& renderer2d;
            int pixel_to_world;

            void awake() override;
            void start() override;
            void update() override;
            void end() override;

        private:
            int renderer2d_id;
    };

}