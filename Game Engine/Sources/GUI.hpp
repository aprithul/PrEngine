#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <dirent.h>
#include <map>
#include "Vector2.hpp"
#include "InputModule.hpp"
#include "Utils.hpp"
#include "RendererModule.hpp"
namespace Pringine
{

    struct UI
    {
        uintptr_t id;
    };

    extern bool initialize_gui(Mouse* mouse, Renderer2D* renderer);
    extern void show_file_structure(std::string root, std::string prefix);
    extern void draw_panel(int id, SDL_Rect draw_region);
    extern bool do_button(int id, SDL_Rect draw_region, SDL_FRect anchor, const std::string& text, const TextJustification& justification);
    extern bool inside(Vector2<int> pos, SDL_Rect rect);
    extern SDL_Rect get_rect_from_anchor(SDL_Rect& rect, SDL_FRect& anchor, int width, int height);
    extern Mouse* mouse;
    extern Renderer2D* renderer;
    extern std::map<std::string, Graphics> gui_graphics;
    extern UI hot;
    extern UI active;
    extern int canvas_width;
    extern int canvas_height;
}


#endif