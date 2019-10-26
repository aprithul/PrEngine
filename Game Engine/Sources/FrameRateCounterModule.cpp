//
//  FrameRateCounter.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "FrameRateCounterModule.hpp"

namespace Pringine {
    
    FrameRateCounter::FrameRateCounter(std::string name, int priority):Module(name,priority)
    {
        one_second = 0;
    }
    
    FrameRateCounter::~FrameRateCounter()
    {
        #if !IS_SERVER
            renderer2D->close_font(font);
            if(text_texture != nullptr)
                SDL_DestroyTexture(text_texture);
        #endif
    }
    
    void FrameRateCounter::start()
    {
        this->frame_count = 0;
        this->last_frame_count = 0;
        #if !IS_SERVER
            font = renderer2D->open_font(get_resource_path("sample.ttf"), 16);
            text_texture = nullptr;
        #endif

    }

    std::string text = "";    
    std::string text2 = "pri";    
    bool toggle  = false;
    void FrameRateCounter::update()
    {
        frame_count++;
        one_second += Time::Frame_time;
        
        if(one_second>=1.0)
        {
            //LOG(LOGTYPE_GENERAL, std::string("frame rate: ").append(std::to_string(frame_count)));
            
            last_frame_count = frame_count;

            #if !IS_SERVER
                // print frame rate to screen
                std::string fr = "prithul : ";
                fr.append(std::to_string(last_frame_count));
                SDL_Color black;
                black.r = 0;
                black.g = 0;
                black.b = 0;
                black.a = 255;

                if(text_texture != nullptr)
                    SDL_DestroyTexture(text_texture);
                text_texture = renderer2D->get_text_texture(fr, font, black);// 
            #endif

            frame_count = 0;
            one_second -= 1.0;
        }

        // not destroying texture every frame to save on performance, instead doing it once a second
        #if !IS_SERVER
            if(text_texture != nullptr) 
                renderer2D->draw_text(text_texture ,Vector2<int>{0,0}, TOP_LEFT);
                TextJustification tj;
                //SDL_FRect anchor{0,0.0306f,0.3125f,0.0306f};  // fraction!!!!!!!
                //SDL_FRect anchor{0,0.027777f,0,0.1389f};
                SDL_Rect text_region{100,120,200,32};
                SDL_Rect button_region{100,120,200,64};
                SDL_Rect toggle_region{100,100, 38,36};

                //SDL_Rect _region{0,0,20,32};
                SDL_FRect button_anchor{ text_region.x/(float)canvas_width, text_region.y/(float)canvas_height,
                                  text_region.w/(float)canvas_width, text_region.h/(float)canvas_height };//0.1388f};
                SDL_FRect text_anchor{ (text_region.x+(text_region.w/2))/(float)canvas_width, text_region.y/(float)canvas_height,
                                        0, text_region.h/(float)canvas_height};
                SDL_FRect toggle_anchor{toggle_region.x/(float)canvas_width, toggle_region.y/(float)canvas_height,
                                  toggle_region.w/(float)canvas_width, toggle_region.h/(float)canvas_height};

                /*if(do_button( (uintptr_t)(&this->is_active), button_region, button_anchor,"",tj))
                {
                //    ;
                }*/
                SDL_Color c{0,0,0,255};
                std::string t = "Hello World";
                //show_text((uintptr_t)(&this->name), t, text_region, text_anchor, FONT_SAMPLE_TTF_48,c, 0.7f);
                //_v = Pringine::get_slider((uintptr_t)(&frame_count), _v, region, _region, anchor);
                //LOG(LOGTYPE_GENERAL, std::to_string( _v = Pringine::get_slider((uintptr_t)(&frame_count), _v, region, _region, anchor)));
                //get_text_input((uintptr_t)(&this->priority), text, text_region, text_anchor);
                //SDL_Rect text_region2{100,120,200,64};
                //show_text((uintptr_t)(&this->name), t, text_region, text_anchor, FONT_SAMPLE_TTF_48,c, 1.f);
                //get_text_input((uintptr_t)(&this->frame_count), text, text_region, text_anchor);

                toggle = do_toggle((uintptr_t)(&this->name),toggle, toggle_region, toggle_anchor);
                //LOG(LOGTYPE_GENERAL, std::to_string(toggle));

        #endif
    }
    
    void FrameRateCounter::end()
    {
        
    }
}
