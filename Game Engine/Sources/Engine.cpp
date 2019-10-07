//
//  Engine.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Engine.hpp"
#include "Input.hpp"

namespace Pringine {
    
    Engine::Engine()
    {
        
    }
    
    Engine::~Engine()
    {
        
        // delete each object pointed by iterator, cause clearing before that will cause only the pointers to get deleted
        // but the objects themselves will remain in memory, causing memory leak
        for(std::map< string_int_pair,Component*>::iterator it = engine_components.begin(); it!=engine_components.end(); ++it)
        {
            delete (it->second);
        }
        // can safley clear now
        engine_components.clear();
        std::cout<<"engine destructor"<<std::endl;
    }
    
    // add a new component to the engine
    Component* Engine::add_component(std::string component_name, int order, Pringine::Component* component)
    {
        string_int_pair key(component_name,order);
        engine_components[key] = component;
        std::cout<<"Component "<<component_name<<" added to engine"<<std::endl;
        return component;
    }
    
    // get the specified component
    Component* Engine::get_component(std::string component_name)
    {
        for(std::map< string_int_pair,Component*>::iterator it = engine_components.begin(); it!=engine_components.end(); ++it)
        {
            if((it->first).first == component_name)
                return it->second;
        }
        
        return NULL;
    }
    
    // called in the start
    void Engine::start()
    {
        this->is_running = true;
        
        for(std::map< string_int_pair,Component*>::iterator it = engine_components.begin(); it!=engine_components.end(); ++it)
        {
            (*(it->second)).start();
        }
        
        std::cout<<"Engine started"<<std::endl;
        
    }
    
    // called every frame
    void Engine::update()
    {
        // get the reference to the input component
        Pringine::Input* input_handler = (Pringine::Input*)this->get_component("Input");
        
        // engine loop
        // updates at specified frame rate
        while(this->is_running)
        {
            // update all components
            for(std::map< string_int_pair,Component*>::iterator it = engine_components.begin(); it!=engine_components.end(); ++it)
            {
                (*(it->second)).update();
            }
            
            // check if window was crossed
            if(input_handler->was_crossed())
                is_running = false;
            
            if(input_handler->get_key_down(SDLK_q))
            {
                
                is_running = false;
                log_detailed_to(LOGMODE_MONITOR, LOGTYPE_GENERAL, 0, NULL, "Key 'q' pressed", NULL);
            }
        }
    }
    
    
    // called in the end
    void Engine::end()
    {
        for(std::map< string_int_pair,Component*>::iterator it = engine_components.begin(); it!=engine_components.end(); ++it)
        {
            (*(it->second)).end();
        }
    }
    


    
}
