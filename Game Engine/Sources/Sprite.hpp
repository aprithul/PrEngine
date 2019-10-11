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
            Sprite(const std::string& graphics_file_name, Renderer2D& renderer2d);
            ~Sprite() override;
            Transform* transform;
            Graphics* graphics;
            Renderer2D& renderer2d;

            void awake() override;
            void start() override;
            void update() override;
            void end() override;

        private:
            int renderer2d_id;
    };

}