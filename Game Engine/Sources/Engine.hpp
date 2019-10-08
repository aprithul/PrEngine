//
//  Engine.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include "Component.hpp"
#include "Utils.hpp"
#include "Input.hpp"
#include <map>
#include <iostream>
#include "LoggerComponenet.hpp"


namespace Pringine {
    // pair typedef, used as component map key
    // string is the name of the component
    // int is the order of execution
    typedef std::pair<std::string, int> string_int_pair;
    
    // comparator object, used to sort map so that execution order is maintained
    struct CompareComponent
    {
        bool operator()(const string_int_pair& a, const string_int_pair& b) const {
            return a.second < b.second;
        }
    };
    
    // engine class to manage engine components
    class Engine
    {
    public:
        Engine();
        ~Engine();
        Component* add_component(std::string, int order, Component* component);
        Component* get_component(std::string);
        void start();
        void update();
        void end();
        void set_frame_rate(int frame_rate);
        bool compare(std::string a, std::string b);
    private:
        
        // map to store all components
        // sorted in execution order
        std::map< string_int_pair, Component*, CompareComponent> engine_components;
        int frame_rate;
        double frame_delta;
        bool is_running;

    };
}

#endif /* Engine_hpp */
