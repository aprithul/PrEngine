#ifndef IMGUI_MODULE
#define IMGUI_MODULE
#include "Renderer3D.hpp"
#include "Module.hpp"
#include "../Vendor/imgui-master/imgui.h"
#include "../Vendor/imgui-master/imgui_impl_opengl3.h"
#include "../Vendor/imgui-master/imgui_impl_sdl.h"
namespace Pringine
{
    class ImGuiModule : public Module
    {
        private:
            /* data */
            Renderer3D& renderer_3d;
        public:
            ImGuiModule(std::string name, int priority, Renderer3D& renderer);
            ~ImGuiModule();

            void start() override;
            void update() override;
            void end() override;
        }; 
} // namespace Pringine
#endif