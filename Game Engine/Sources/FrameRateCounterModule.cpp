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
                std::string fr = "Frame rate : ";
                fr.append(std::to_string(last_frame_count));
                SDL_Color black{0,0,0,255};

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
        #endif
    }
    
    void FrameRateCounter::end()
    {
        
    }
}
