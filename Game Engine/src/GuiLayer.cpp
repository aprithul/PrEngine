#include "GuiLayer.hpp"

namespace Pringine
{

    GuiLayer::GuiLayer(SDL_Window* sdl_window, SDL_GLContext* gl_context):window(sdl_window),gl_context(gl_context)
    {

    }

    GuiLayer::~GuiLayer()
    {

    }

    void GuiLayer::start()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 410");
        //ImGui::StyleColorsClassic();
    }

    void GuiLayer::update()
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup
        
        ImGuiIO& io = ImGui::GetIO();
        //io.DisplaySize = ImVec2( 1440, 900);
        //io.DisplayFramebufferScale
        io.DeltaTime = Time::Frame_time;
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData());
    }

    void GuiLayer::end()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
    }
}