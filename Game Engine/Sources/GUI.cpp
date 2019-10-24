#include "GUI.hpp"


namespace Pringine
{
    Mouse* mouse = nullptr;
    Renderer2D* renderer = nullptr;
    std::map<std::string, Graphics> gui_graphics;
    UI hot{0};
    UI active{0};
    int canvas_width = 640;
    int canvas_height = 320;
    
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
        Pringine::mouse = _mouse;
        Pringine::renderer = _renderer;
        int error_flag = 0;

        SDL_Texture* _texture = load_texture( get_resource_path("UI_elements.png"), renderer->sdl_renderer);
        gui_graphics["panel"] = Graphics();
        TextureSlicingParameters slicing_params(0,0,96,0);
        if(!gui_graphics["panel"].load_graphics(_texture, &slicing_params, *(renderer), 1))
        {
            error_flag = 1;
            LOG(LOGTYPE_GENERAL, "Failed to load panel graphics. Texture: ","UI_elements.png");
        }

        gui_graphics["button"] = Graphics();
        slicing_params = TextureSlicingParameters(96,0,96,32,0,0);
        if(!gui_graphics["button"].load_graphics(_texture, &slicing_params, *(renderer), 3, true))
        {
            error_flag = 1;
            LOG(LOGTYPE_GENERAL, "Failed to load button graphics. Texture: ","UI_elements.png");
        }
    }

    void draw_panel(int id, SDL_Rect draw_region)
    {
        //render
        Graphics* graphics = &gui_graphics["panel"];
        graphics->dst_dimension = draw_region;
        graphics->draw(renderer);
    }

    bool do_button(int id, SDL_Rect draw_region, SDL_FRect anchor, const std::string& text, const TextJustification& justification)
    {
        Graphics* graphics = &gui_graphics["button"];
        graphics->dst_dimension = get_rect_from_anchor(draw_region, anchor, renderer->window_width, renderer->window_height);
        //renderer->draw_rectangle(graphics->dst_dimension, SDL_Color{255,0,0,255},true, true);
        //LOG(LOGTYPE_GENERAL, std::to_string(graphics->dst_dimension.x),", ", std::to_string(graphics->dst_dimension.y),", ", std::to_string(graphics->dst_dimension.w),", ", std::to_string(graphics->dst_dimension.h));
        graphics->current_frame_index = 0;
        if(hot.id == id) graphics->current_frame_index = 1;
        if(active.id == id) graphics->current_frame_index = 2;
        graphics->draw(renderer, false, false);

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
        if(inside(mouse->position, graphics->dst_dimension))
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

    bool inside(Vector2<int> pos, SDL_Rect rect)
    {
        if(pos.x<=rect.x+rect.w && pos.x>=rect.x &&
            pos.y<=rect.y+rect.h && pos.y>=rect.y)
                return true;
        else return false;
    }

    SDL_Rect get_rect_from_anchor(SDL_Rect& rect, SDL_FRect& anchor, int width, int height)
    {
        // anchor to pixel position in original canvas 
        Vector2<int> p1_c((int)(anchor.x*canvas_width)  , (int)(anchor.y*canvas_height));
        Vector2<int> p2_c((int)((anchor.x+anchor.w)*canvas_width), (int)((anchor.y+anchor.h)*canvas_height));

        Vector2<int> p1_s((int)(anchor.x*width)  , (int)(anchor.y*height));
        Vector2<int> p2_s((int)((anchor.x+anchor.w)*width), (int)((anchor.y+anchor.h)*height));

        //       p1.......p2.x,p1.y
        //       |        |
        // p1.x,p2.y......p2

        SDL_Rect _r = rect;

        //LOG(LOGTYPE_GENERAL,"Pre: ", std::to_string(_r.x),", ", std::to_string(_r.y),", ", std::to_string(_r.w),", ", std::to_string(_r.h));
        //LOG(LOGTYPE_GENERAL,"Anchor: ", std::to_string(p1.x),", ", std::to_string(p1.y),", ", std::to_string(p2.x),", ", std::to_string(p2.y));
        
//          (x,y)........(x+w, y)
//              |        |
//        (x,y+h)........(x+w, y+h)


        _r.x = (rect.x - p1_c.x) + p1_s.x;
        _r.y = (rect.y - p1_c.y) + p1_s.y;
        _r.w = rect.w - p2_c.x + p2_s.x;
        _r.h = rect.h - p2_c.y + p2_s.y;
        LOG(LOGTYPE_GENERAL, "Post: ",std::to_string(_r.x),", ", std::to_string(_r.y),", ", std::to_string(_r.w),", ", std::to_string(_r.h));
        

        return _r;

    }


    
}