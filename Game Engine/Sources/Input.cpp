//
//  Input.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Input.hpp"

namespace Pringine {
    
    Input::Input(std::string name, int priority):Module(name,priority)
    {
    }
    
    Input::~Input()
    {
        
    }
    
    bool Input::was_crossed()
    {
        return this->cross_clicked;
    }
    
    bool Input::get_key(int keycode)
    {
        
        return key_pressed[keycode];;
    }
    
    bool Input::get_key_up(int keycode)
    {
        
        return key_up[keycode];
    }
    
    bool Input::get_key_down(int keycode)
    {
        return key_down[keycode];
    }
    
    
    void Input::start()
    {
        cross_clicked = false;
    }
    
    void Input::update()
    {
        
        if(is_active)
        {
            cross_clicked = false;
            key_down.clear();
            key_up.clear();
            
            while(SDL_PollEvent(&input_event))
            {
                switch (input_event.type) {
                    case SDL_KEYDOWN:
                        if(input_event.key.repeat == 0)
                        {
                            key_down[input_event.key.keysym.sym] = true;
                            key_pressed[input_event.key.keysym.sym] = true;
                        }
                        break;
                    case SDL_KEYUP:
                        key_up[input_event.key.keysym.sym] = true;
                        key_pressed[input_event.key.keysym.sym] = false;
                        break;
                    case SDL_QUIT:
                        this->cross_clicked = true;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    
    void Input::end()
    {
        
    }
    
    
    
    

}
