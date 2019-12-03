#ifndef GUI_LAYER_HPP
#define GUI_LAYER_HPP

#include "RenderLayer.hpp"
#include "TimeModule.hpp"
#include "../Vendor/imgui-master/imgui.h"
#include "../Vendor/imgui-master/imgui_impl_opengl3.h"
#include "../Vendor/imgui-master/imgui_impl_sdl.h"
namespace Pringine
{
    class GuiLayer : public RenderLayer
    {
        public:
            GuiLayer(SDL_Window* sdl_window, SDL_GLContext* gl_context);
            ~GuiLayer();

            void start() override;
            void update() override;
            void end() override;

        private:
            SDL_Window* window;
            SDL_GLContext* gl_context;

    };
}


#endif