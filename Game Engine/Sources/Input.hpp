//
//  Input.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <stdio.h>
#include <map>
#include "Component.hpp"
#include "Vector2.cpp"
#include "SDL2/SDL.h"
#include <iostream>

namespace Pringine {
    class Input:public Component
    {
    public:
        Input();
        ~Input();
        bool get_key(int keycode);
        bool get_key_up(int keycode);
        bool get_key_down(int keycode);
        bool get_mouse_button(int button);
        bool get_mouse_button_down(int button);
        bool get_mouse_button_up(int button);
        Vector2<float> get_mouse_position();
        bool was_crossed();
        void start() override;
        void end() override;
        void update() override;
        
    private:
        SDL_Event input_event;
        bool cross_clicked;
        std::map<int, bool> key_down;
        std::map<int, bool> key_up;
        std::map<int, bool> key_pressed;
        
    };
}




#endif /* Input_hpp */
