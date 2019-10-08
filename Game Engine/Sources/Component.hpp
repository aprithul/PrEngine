//
//  Component.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <iostream>
#include <string>
#include "SDL2/SDL.h"

namespace Pringine {
    
    // every component class extends this
    class Component
    {
    public:
        Component(std::string, int name);
        virtual ~Component();
        virtual void start() = 0;
        virtual void update() = 0;
        virtual void end() = 0;
        bool is_active;
        std::string name;
        int priority;
        
    };
}

#endif /* Component_hpp */
