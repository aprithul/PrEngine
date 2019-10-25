#include "GUI.hpp"


namespace Pringine
{
    Mouse* mouse = nullptr;
    Renderer2D* renderer = nullptr;
    Graphics gui_graphics[256];
    UI hot{0};
    UI active{0};
    int canvas_width = 640;
    int canvas_height = 360;
    std::map<uintptr_t,SDL_Texture*> rendered_texts;
    TTF_Font* fonts[FONT_ID_MAX];

    void show_file_structure(std::string root, std::string prefix)
    {
        
        #ifdef _WIN32
            const std::string PATH_SEP = "\\";
        #else
            const std::string PATH_SEP = "/";
        #endif

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (root.c_str())) != NULL) 
        {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) 
            {
                std::cout<<prefix<<"|"<<ent->d_name<<std::endl;
                if(ent->d_type == DT_DIR && ent->d_name[0] != '.' )
                    show_file_structure( root.append(ent->d_name).append(PATH_SEP), prefix.append(" "));
            }
            closedir (dir);
        } 
        else
        {
            /* could not open directory */
            perror ("");
            return;
        }
    }

    bool initialize_gui(Mouse* _mouse, Renderer2D* _renderer)
    {
        // load all the fonts that we'll need   
        for(int i=0;i <FONT_ID_MAX; i++)
            fonts[i] = nullptr;

        fonts[FONT_SAMPLE_TTF_16] = renderer->open_font(get_resource_path("sample.ttf"), 16);
        fonts[FONT_SAMPLE_TTF_24] = renderer->open_font(get_resource_path("sample.ttf"), 24);
        fonts[FONT_SAMPLE_TTF_32] = renderer->open_font(get_resource_path("sample.ttf"), 32);
        fonts[FONT_SAMPLE_TTF_48] = renderer->open_font(get_resource_path("sample.ttf"), 48);
        
        ///////////////////////////////////////
        Pringine::mouse = _mouse;
        Pringine::renderer = _renderer;
        int error_flag = 0;

        // load all the texture we'll need
        SDL_Texture* _texture = load_texture( get_resource_path("UI_elements.png"), renderer->sdl_renderer);
        TextureSlicingParameters slicing_params(0,0,96,0);
        if(!gui_graphics[GUI_ID_PANEL].load_graphics(_texture, &slicing_params, *(renderer), 1))
        {
            error_flag = 1;
            LOG(LOGTYPE_GENERAL, "Failed to load panel graphics. Texture: ","UI_elements.png");
        }

        slicing_params = TextureSlicingParameters(96,0,96,32,0,0);
        if(!gui_graphics[GUI_ID_BUTTON].load_graphics(_texture, &slicing_params, *(renderer), 3, true))
        {
            error_flag = 1;
            LOG(LOGTYPE_GENERAL, "Failed to load button graphics. Texture: ","UI_elements.png");
        }

        _texture = load_texture( get_resource_path("UIpack/PNG/grey_sliderHorizontal.png"), renderer->sdl_renderer);
        slicing_params = TextureSlicingParameters(0,0,190,4,0,0);
        if(!gui_graphics[GUI_ID_SLIDER_BASE].load_graphics(_texture, &slicing_params, *(renderer),1))
        {
            error_flag = 1;
            LOG(LOGTYPE_GENERAL, "Failed to load slider background graphics. Texture: ","UI_elements.png");
        }

        _texture = load_texture( get_resource_path("UIpack/PNG/grey_sliderRight.png"), renderer->sdl_renderer);
        slicing_params = TextureSlicingParameters(0,0,39,31,0,0);
        if(!gui_graphics[GUI_ID_SLIDER_KNOB].load_graphics(_texture, &slicing_params, *(renderer),1))
        {
            error_flag = 1;
            LOG(LOGTYPE_GENERAL, "Failed to load slider_knob graphics. Texture: ","UI_elements.png");
        }



        return error_flag;
    }

    void draw_panel(uintptr_t id, SDL_Rect draw_region)
    {
        //render
        Graphics* graphics = &gui_graphics[GUI_ID_PANEL];
        graphics->dst_dimension = draw_region;
        graphics->draw(renderer);
    }

    bool do_button(uintptr_t id, SDL_Rect& draw_region, SDL_FRect& anchor, const std::string& text, const TextJustification& justification)
    {
        process_rect_with_anchor(draw_region, anchor, renderer->window_width, renderer->window_height);
        gui_graphics[GUI_ID_BUTTON].dst_dimension = draw_region;
        //renderer->draw_rectangle(graphics->dst_dimension, SDL_Color{255,0,0,255},true, true);
        //LOG(LOGTYPE_GENERAL, std::to_string(graphics->dst_dimension.x),", ", std::to_string(graphics->dst_dimension.y),", ", std::to_string(graphics->dst_dimension.w),", ", std::to_string(graphics->dst_dimension.h));
        gui_graphics[GUI_ID_BUTTON].current_frame_index = 0;
        if(hot.id == id) gui_graphics[GUI_ID_BUTTON].current_frame_index = 1;
        if(active.id == id) gui_graphics[GUI_ID_BUTTON].current_frame_index = 2;
        gui_graphics[GUI_ID_BUTTON].draw(renderer, false, false);

        if(active.id == id) 
        {
            if(hot.id == id)
            {
                if(mouse->get_mouse_button_up(1))
                {
                    active.id = 0;
                    return true;
                }
            }
        }
        else
        {
            if(hot.id == id)
            {
                if(mouse->get_mouse_button_down(1))
                {
                    active.id = id;
                }
            }
        }

        //LOG(LOGTYPE_GENERAL, std::to_string(mouse->position.x),std::to_string(mouse->position.y));
        if(inside(mouse->position, gui_graphics[GUI_ID_BUTTON].dst_dimension))
        {
            hot.id = id;
        }
        else if(hot.id == id)
        {
            hot.id = 0;
            active.id = 0;
        }

        return false;
    }

    float get_slider(uintptr_t id, float value, SDL_Rect& slider_base_region, SDL_Rect& slider_knob_region, SDL_FRect& anchor, float min, float max, bool horizontal)
    {
        float _h = slider_base_region.h;
        process_rect_with_anchor(slider_base_region, anchor, renderer->window_width, renderer->window_height);
        _h = _h/(float)slider_base_region.h;
        gui_graphics[GUI_ID_SLIDER_BASE].dst_dimension = slider_base_region;
        gui_graphics[GUI_ID_SLIDER_BASE].draw(renderer, false, false);
        if(active.id == id) 
        {
            if(mouse->get_mouse_button(1))
            {
                //active.id = 0;
                value = (mouse->position.x - gui_graphics[GUI_ID_SLIDER_BASE].dst_dimension.x)/(float)gui_graphics[GUI_ID_SLIDER_BASE].dst_dimension.w;
                value = clamp(value,min,max);
            }
            if(mouse->get_mouse_button_up(1))
            {
                active.id = 0;
            }
        }
        else
        {
            if(hot.id == id)
            {
                if(mouse->get_mouse_button_down(1))
                {
                    active.id = id;
                }
            }
        }


        if(inside(mouse->position, gui_graphics[GUI_ID_SLIDER_BASE].dst_dimension))
        {
            hot.id = id;
        }
        else if(hot.id == id)
        {
            hot.id = 0;
        }

        slider_knob_region.x =  slider_base_region.x + slider_base_region.w*value;
        float _s = (gui_graphics[GUI_ID_SLIDER_BASE].dst_dimension.h * 3)/slider_knob_region.h;
        slider_knob_region.h = _s * slider_knob_region.h;
        slider_knob_region.w = _s * slider_knob_region.w;
        slider_knob_region.y = slider_base_region.y + slider_base_region.h/2.f - slider_knob_region.h/2.f;
        gui_graphics[GUI_ID_SLIDER_KNOB].dst_dimension = slider_knob_region;
        gui_graphics[GUI_ID_SLIDER_KNOB].draw(renderer, false, false);
        return value;
    }

    void show_text(uintptr_t id, std::string& text, SDL_Rect& draw_region, SDL_FRect& anchor,Font_ID font_id, SDL_Color& c, float scale)
    {
        if(fonts[font_id] != nullptr)
        {
            SDL_Texture* texTure = renderer->get_text_texture(text, fonts[font_id], c);
            process_rect_with_anchor(draw_region, anchor, renderer->window_width, renderer->window_height);
            
            draw_region.x += ((1.f-scale)*draw_region.w/2);
            draw_region.y += ((1.f-scale)*draw_region.h/2);
            draw_region.w = scale*draw_region.w;
            draw_region.h = scale*draw_region.h;

            SDL_RenderCopy(renderer->sdl_renderer, texTure, NULL, &draw_region);
        }   
        else
        {
            LOG(LOGTYPE_ERROR, "Font hasn't been loaded; please load in load_fonts() ");
        }
    }

    bool inside(Vector2<int> pos, SDL_Rect rect)
    {
        if(pos.x<=rect.x+rect.w && pos.x>=rect.x &&
            pos.y<=rect.y+rect.h && pos.y>=rect.y)
                return true;
        else return false;
    }

    void process_rect_with_anchor(SDL_Rect& rect, SDL_FRect& anchor, int width, int height)
    {
        // anchor to pixel position in original canvas 
        Vector2<int> p1_c((int)(anchor.x*canvas_width)  , (int)(anchor.y*canvas_height));
        Vector2<int> p2_c((int)((anchor.x+anchor.w)*canvas_width), (int)((anchor.y+anchor.h)*canvas_height));

        Vector2<int> p1_s((int)(anchor.x*width)  , (int)(anchor.y*height));
        Vector2<int> p2_s((int)((anchor.x+anchor.w)*width), (int)((anchor.y+anchor.h)*height));

        Vector2<int>r1(rect.x, rect.y);
        Vector2<int>r2(rect.x+rect.w, rect.y+rect.h);
        //LOG(LOGTYPE_GENERAL, std::to_string(p1_c.x),",",std::to_string(p1_s.x));
        //LOG(LOGTYPE_GENERAL, std::to_string(p2_c.x),",",std::to_string(p2_s.x));
        //       p1.......p2.x,p1.y
        //       |        |
        // p1.x,p2.y......p2


//          (x,y)........(x+w, y)
//              |        |
//        (x,y+h)........(x+w, y+h)

        Vector2<int>f1( (r1.x - p1_c.x) + p1_s.x,  (r1.y - p1_c.y) + p1_s.y )  ;
        Vector2<int>f2( (r2.x - p2_c.x) + p2_s.x,  (r2.y - p2_c.y) + p2_s.y )  ;

        rect.x = f1.x;
        rect.y = f1.y;
        rect.w = f2.x - f1.x;
        rect.h = f2.y - f1.y;
    }

    
}