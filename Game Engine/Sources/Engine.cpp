//
//  Engine.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Engine.hpp"

namespace Pringine {
    
    Engine::Engine()
    {
    }
    
    Engine::~Engine()
    {
        
        for(int _i=0; _i<engine_components.size(); _i++)
        {
            delete engine_components[_i];
        }
        // can safley clear now
        engine_components.clear();
        log_to(LOGTYPE_GENERAL, "Engine destroyed");
    }
    
    static bool priority_comparer(Component* a, Component* b)
    {
        return (a->priority<b->priority);        
    }

    // add a new component to the engine
    Component* Engine::add_component(Component* component)
    {
        //string_int_pair key(component_name,order);
        //engine_components[key] = component;
        engine_components.push_back(component);
        //std::sort(engine_components.begin(), engine_components.end(), priority_comparer);
        //std::cout<<"Component "<<component_name<<" added to engine"<<std::endl;
        return component;
    }
    
    // get the specified component
    Component* Engine::get_component(std::string component_name)
    {
        for(int _i=0; _i<engine_components.size(); _i++)
        {
            if(engine_components[_i]->name == component_name)
            {
                return engine_components[_i];
            }
        }
        
        return NULL;
    }
    
    // called in the start
    void Engine::start()
    {
        this->is_running = true;
        for(int _i=0; _i<engine_components.size(); _i++)
        {
                engine_components[_i]->start();
        }

        // get the reference to the input component
        input_handler = (Pringine::Input*)this->get_component("Input");


        log_to(LOGTYPE_GENERAL, "Engine started");
        
    }
    
    // called every frame
    void Engine::update()
    {
                
        // engine loop
        // updates at specified frame rate
        while(this->is_running)
        {
            // update all components
            for(int _i=0; _i<engine_components.size(); _i++)
            {
                engine_components[_i]->update();
            }
            
            // check if window was crossed
            if(input_handler->was_crossed())
                is_running = false;
            
            if(input_handler->get_key_down(SDLK_q))
            {
                is_running = false;
                log_to(LOGTYPE_GENERAL, "Key 'q' pressed");
            }
        }
    }
    
    // called in the end
    void Engine::end()
    {
        for(int _i=0; _i<engine_components.size(); _i++)
        {
            engine_components[_i]->end();
        }
    }
}
