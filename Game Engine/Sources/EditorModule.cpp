#include "EditorModule.hpp"
namespace Pringine
{
            
    SDL_Rect right_panel_outer_region;
    SDL_Rect right_panel_inner_region;
    SDL_FRect right_panel_outer_anchor;
    SDL_FRect right_panel_inner_anchor;

    SDL_Rect left_panel_outer_region;
    SDL_Rect left_panel_inner_region;
    SDL_FRect left_panel_outer_anchor;
    SDL_FRect left_panel_inner_anchor;

    SDL_Rect left_panel_text_0_region;
    SDL_Rect left_panel_text_1_region;
    SDL_Rect left_panel_text_2_region;

    SDL_FRect left_panel_text_0_anchor;
    SDL_FRect left_panel_text_1_anchor;
    SDL_FRect left_panel_text_2_anchor;

    uintptr_t editor_panel_id_0 = 0;
    uintptr_t editor_panel_id_1 = 1;
    uintptr_t editor_panel_id_2 = 2;
    uintptr_t editor_panel_id_3 = 3;
    uintptr_t editor_text_id_4 = 4;
    uintptr_t editor_text_id_5 = 5;
    uintptr_t editor_text_id_6 = 6;
    

    Editor::Editor(std::string name, int priority, Renderer2D* renderer):Module(name,priority)
    {
        this->renderer = renderer;

        right_panel_outer_region = {canvas_width - (canvas_width/8), 0, (canvas_width/8),canvas_height};
        get_anchor_full(right_panel_outer_region, right_panel_outer_anchor);
        right_panel_inner_region = {canvas_width - (canvas_width/8)+5, 5, (canvas_width/8)-10,canvas_height-10};
        get_anchor_full(right_panel_outer_region, right_panel_inner_anchor);

        left_panel_outer_region = {0, 0, (canvas_width/8),canvas_height};
        get_anchor_full(left_panel_outer_region, left_panel_outer_anchor);
        left_panel_inner_region = {5, 5, (canvas_width/8)-10,canvas_height-10};
        get_anchor_full(left_panel_outer_region, left_panel_inner_anchor);

    }

    Editor::~Editor()
    {

    }

    void Editor::start()
    {

    }

    void Editor::update()
    {
        // left panel
        left_panel_outer_region = {0, 0, (canvas_width/8),canvas_height};
        draw_panel(editor_panel_id_2, left_panel_outer_region, left_panel_outer_anchor, GUI_ID_PANEL_2);
        left_panel_inner_region = {5, 5, (canvas_width/8)-10,canvas_height-10};
        draw_panel(editor_panel_id_3, left_panel_inner_region, left_panel_inner_anchor);




        // right panel
        right_panel_outer_region = {canvas_width - (canvas_width/8), 0, (canvas_width/8),canvas_height};
        draw_panel(editor_panel_id_0, right_panel_outer_region, right_panel_outer_anchor, GUI_ID_PANEL_2);
        right_panel_inner_region = {canvas_width - (canvas_width/8)+5, 5, (canvas_width/8)-10,canvas_height-10};
        draw_panel(editor_panel_id_1, right_panel_inner_region, right_panel_inner_anchor);




    }

    void Editor::end()
    {
        
    }

}
