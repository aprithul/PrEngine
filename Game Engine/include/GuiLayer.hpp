#ifndef GUI_LAYER_HPP
#define GUI_LAYER_HPP

#include "RenderLayer.hpp"
#include "TimeModule.hpp"
#include "../Vendor/imgui-master/imgui.h"
#include "../Vendor/imgui-master/imgui_impl_opengl3.h"
#include "../Vendor/imgui-master/imgui_impl_sdl.h"
#include "Vector2.hpp"
namespace PrEngine
{
    class GuiLayer : public RenderLayer
    {
        public:
            GuiLayer(SDL_Window* sdl_window, SDL_GLContext* gl_context);
            ~GuiLayer();

            void start() override;
            void update() override;
            void end() override;
            Vector2<float> *panning;
            Vector2<float> *tiling;
        private:
            SDL_Window* window;
            SDL_GLContext* gl_context;
            
            // inspector
            bool inspector_active;


    };
}


#endif