//
//  Component.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Component.hpp"

namespace Pringine
{
    
    Component::Component(std::string name, int priority)
    {
        this->priority = priority;
        this->name = name;
        this->is_active = true;
    }
    
    Component::~Component()
    {
        
    }

}
